#include "IRcodeData.hpp"


/* IRcodeData */

IRcodeData::IRcodeData(std::unique_ptr<Module>& m)
{
	IRmodule = &m;
	wtask = new IRcodeTextDataSet;
}

IRcodeData::~IRcodeData(){
	delete wtask;
}

IRcodeTextDataSet* IRcodeData::getIRcodeTextDataSet(){
	return wtask;
}



void IRcodeData::ShowGlobalVariables(std::unique_ptr<Module> &m){
	
	int number = 1;
	std::cout << "[Show Global Variable]" << std::endl;
	for(auto iter = m->global_begin(); iter != m->global_end(); iter++){

		GlobalVariable &gv = (*iter);
		std::cout << number++ << ". " << gv.getName().str() << std::endl;

	}
	std::cout << std::endl;

}


GlobalVariable* IRcodeData::popGlobalVariable(std::unique_ptr<Module> &m, int number){

		
	int comp_num = 0;
	//std::cout << "get Global Variable" << std::endl;
	GlobalVariable *gv = nullptr;
	
	for(auto iter = m->global_begin(); iter != m->global_end(); iter++, comp_num++){
		if(comp_num == number){

			gv = &(*iter);
			//std::cout << number++ << " " << gv->getName().str() << std::endl;
			break;
		}
	}

	//std::cout << "Successfully Get a global variable" << std::endl;
	return gv;

}




int IRcodeData::splitBBModuleChecker(std::unique_ptr<Module> &m){


	int CheckSum = 0;
	int InstCall_flag = 0;

	std::list<Data *> ToSplitBBList;
  
	for (auto iter1 = m->getFunctionList().begin(); 
			iter1 != m->getFunctionList().end(); iter1++) {

		Function &f = *iter1;
		for (auto iter2 = f.getBasicBlockList().begin(); 
				iter2 != f.getBasicBlockList().end(); iter2++) {

			InstCall_flag = 0;
			
			BasicBlock &bb = *iter2;
			for (auto iter3 = bb.begin(); iter3 != bb.end(); iter3++) {
				
				Instruction &inst = *iter3;
				/* Increase CheckSum per Call Inst */
				if(!strcmp(inst.getOpcodeName(), "call")){
					CheckSum++;
#ifdef DEBUG_WRAPPER
					std::cout << "[INCREASE]" <<std::endl;
#endif
					InstCall_flag = 1;
				}
      		}
			/* Decrease CheckSum per BB if BB has a Call Inst */
			if(InstCall_flag == 1){
				CheckSum--;
#ifdef DEBUG_WRAPPER
				std::cout << "[DECREASE]" <<std::endl;
#endif			
			}
    	}
		
		
  	}

#ifdef DEBUG_WRAPPER
	std::cout << "[CheckSum]: " << CheckSum << std::endl;
#endif			

	return CheckSum;
}



bool IRcodeData::Preprocess1(){

	std::unique_ptr<Module> &m = *IRmodule;

	while(splitBBModuleChecker(m) != 0){
		splitBBModuleOnce(m);
	}
	splitBBModuleOnce(m);

	return true;
}

bool IRcodeData::splitBBModuleOnce(std::unique_ptr<Module> &m){

	std::list<Data *> ToSplitBBList;
	Data *data;
  
	for (auto iter1 = m->getFunctionList().begin(); iter1 != m->getFunctionList().end(); iter1++) {
		Function &f = *iter1;
		for (auto iter2 = f.getBasicBlockList().begin(); iter2 != f.getBasicBlockList().end(); iter2++) {

			BasicBlock &bb = *iter2;
			Instruction *pastInst = reinterpret_cast<Instruction *>(0);
			for (auto iter3 = bb.begin(); iter3 != bb.end(); iter3++) {

				Instruction &inst = *iter3;
				/* store split point */
				if(pastInst != reinterpret_cast<Instruction *>(0)){
					/* Ignore if the next instruction is "br" */
					//if((!strcmp(pastInst->getOpcodeName(), "call")) && (strcmp(inst.getOpcodeName(), "br") && strcmp(inst.getOpcodeName(), "ret"))){
					if((!strcmp(pastInst->getOpcodeName(), "call")) && strcmp(inst.getOpcodeName(), "br")){
						data = new Data(&f, &bb, &inst);
						ToSplitBBList.push_back(data);
						break;
					}
				}
				pastInst = &inst;
      		}
    	}
  	}


	BasicBlock *tmp;
	std::list<Data *>::iterator iter;
	/* split by using splitBasicBlock function */
	for(iter = ToSplitBBList.begin(); iter != ToSplitBBList.end(); iter++){
		tmp = (*iter)->bb->splitBasicBlock((*iter)->inst);
	}

	return true;
}

bool IRcodeData::Preprocess3()
{
	
	BasicBlockBranchAndFunctionCallImpl();
	makePathsInEachFunction();

	return true;
}


bool IRcodeData::BasicBlockBranchAndFunctionCallImpl(){

	std::list<wFunction *>::iterator iter1;
	for(iter1 = wtask->getwFuncList()->begin(); iter1 != wtask->getwFuncList()->end(); iter1++){

		wFunction *CurrentFunc = (*iter1);
		CurrentFunc->determineFuncRetTy();
		std::list<wBasicBlock *>::iterator iter2;
		for(iter2 = CurrentFunc->getwBBList()->begin(); iter2 != CurrentFunc->getwBBList()->end(); iter2++){

			wBasicBlock *CurrentBB = (*iter2);
			CurrentBB->setParent(CurrentFunc);
			std::list<wInstruction *>::iterator iter3;
			for(iter3 = CurrentBB->getwInstList()->begin(); iter3 != CurrentBB->getwInstList()->end(); iter3++){
				
				Instruction *CurrentInst = (*iter3)->getInstruction();

				if(!strcmp(CurrentInst->getOpcodeName(), "call")){
					CurrentBB->setCall(true);					
					Value *branch_opnd = CurrentInst->getOperand(CurrentInst->getNumOperands() -1);
					Function *branch_func = reinterpret_cast<Function *>(branch_opnd);
					wFunction *target_wfunc =  wtask->SearchFunction(branch_func);
					(*iter2)->pushFuncCallList(target_wfunc);
				}

				if(!strcmp(CurrentInst->getOpcodeName(), "br")){
					/* Unconditional branch */
					if(CurrentInst->getNumOperands() == 1){
						Value* opnd = CurrentInst->getOperand(CurrentInst->getNumOperands() -1);
						CurrentBB->setType(wBasicBlock::ONE_BRANCH);

						BasicBlock *BranchBB = reinterpret_cast<BasicBlock *>(opnd);
						wBasicBlock* BranchwBB = CurrentFunc->SearchBasicBlock(BranchBB);
			
						std::pair<wBasicBlock* , wBasicBlock *> *BranchwBBpair = new std::pair<wBasicBlock *, wBasicBlock *>(BranchwBB , reinterpret_cast<wBasicBlock *>(0)); 
						CurrentBB->setBranchBlock(BranchwBBpair);

					/* Conditional branch: LLVM IR only two direction */	
					}else if(CurrentInst->getNumOperands() == 3) {
						Value* opnd1 = CurrentInst->getOperand(CurrentInst->getNumOperands() -1);
						BasicBlock *BranchBB1 = reinterpret_cast<BasicBlock *>(opnd1);
						wBasicBlock* BranchwBB1 = CurrentFunc->SearchBasicBlock(BranchBB1);
					

						Value* opnd2 = CurrentInst->getOperand(CurrentInst->getNumOperands() -2);
						BasicBlock *BranchBB2 = reinterpret_cast<BasicBlock *>(opnd2);
						wBasicBlock* BranchwBB2 = CurrentFunc->SearchBasicBlock(BranchBB2);
						CurrentBB->setType(wBasicBlock::TWO_BRANCH);
						
						std::pair<wBasicBlock* , wBasicBlock *> *BranchwBBpair = new std::pair<wBasicBlock *, wBasicBlock *>(BranchwBB1 , BranchwBB2); 
						CurrentBB->setBranchBlock(BranchwBBpair);
					}
				}
				if(!strcmp(CurrentInst->getOpcodeName(), "ret")){		
					CurrentBB->setType(wBasicBlock::RETURN);
				}
			}
		}


	}
	return true;
}

bool IRcodeData::makePathsInEachFunction(){

	std::list<wFunction *> *TraverseFuncList = wtask->getwFuncList();
	std::list<wFunction *>::iterator iter;


	for(iter = TraverseFuncList->begin(); iter != TraverseFuncList->end(); iter++){

		wFunction *current = *iter;

		/* if work well without this, delete it */
		 
		if( current->getFunction()->getName().str() == "free" 
				|| current->getFunction()->getName().str() == "malloc"){

			Function *f = current->getFunction();
			BasicBlock &entry = f->getBasicBlockList().front();
			wBasicBlock *entrywBB = current->SearchBasicBlock(&entry);
			(*iter)->IntrinsicFuncMakePathsList(entrywBB);
			(*iter)->makePATHSLIST();
		}
		
		else{
		
		
			(*iter)->makePathsList((*iter)->SearchBasicBlock(&((*iter)->getFunction()->getEntryBlock())));
			(*iter)->makePATHSLIST();
		
		}
	}
	return true;
}

bool IRcodeData::ShowPathsInEachFunc(){

	std::cout << "[Function Paths]" << std::endl;

	std::list<wFunction *> *TraverseFuncList = wtask->getwFuncList();
	std::list<wFunction *>::iterator iter;

	for(iter = TraverseFuncList->begin(); iter != TraverseFuncList->end(); iter++){
		std::cout << (*iter)->getFunction()->getName().str();
		std::cout << "(PathNum: " << (*iter)->getNumPaths()  << ")" << std::endl;;
		(*iter)->showPathsList();	
		std::cout << std::endl;
	}

	std::cout << std::endl;
	return true;
}

bool IRcodeData::Preprocess2(){

	std::unique_ptr<Module> &m = *IRmodule;

	/* Module Entry */
  	for (auto iter1 = m->getFunctionList().begin(); iter1 != m->getFunctionList().end(); iter1++) {

		/* Function Entry */
		Function &f = *iter1;
		wFunction *wf = new wFunction;
		wf->setwFunction(&f);
		wtask->pushFuncList(wf);

		/* Need to be fashioned */
		if(f.getName().str() == "free" 
				|| f.getName().str() == "malloc"
				|| f.getName().str() == "pthread_create"
				|| f.getName().str() == "pthread_join"
				|| f.getName().str() == "llvm.dbg.declare"
				
				){

			BasicBlock &bb = f.getBasicBlockList().front();
			wBasicBlock *wbb = new wBasicBlock;
			wbb->setName(f.getName().str() + std::string("%") + std::to_string(0));
				
			wbb->setwBasicBlock(&bb);
			wf->pushBBList(wbb);
			
			continue;
		}
		
		else {
	
			unsigned int BBNumber = 0;
			for (auto iter2 = f.getBasicBlockList().begin(); iter2 != f.getBasicBlockList().end(); iter2++) {


				/* BasicBlock Entry */
				BasicBlock &bb = *iter2;
				wBasicBlock *wbb = new wBasicBlock;
				wbb->setName(f.getName().str() + std::string("%") + std::to_string(BBNumber++));
				
				wbb->setwBasicBlock(&bb);
				wf->pushBBList(wbb);
	
				Instruction* br_inst;
				for (auto iter3 = bb.begin(); iter3 != bb.end(); iter3++) {

					/* Instruction Entry */
					Instruction &inst = *iter3;
					br_inst = &inst;

					wInstruction *wInst = new wInstruction;
					wInst->setwInstruction(&inst);
					wbb->pushInstList(wInst);

					int opnt_cnt = inst.getNumOperands();

					for(int i = 0; i < opnt_cnt; i++){
						Value *opnd = inst.getOperand(i);
						wInst->pushOperandList(opnd);
					}

				}
				/* BasicBlock EndPoint */
			
			}
		}
			/* Function EndPoint */	
  	}


	return true;

}


bool IRcodeData::DebugWrapperModule()
{

	std::cout << "[Debug Test]" << std::endl;
	std::list<wFunction *>::iterator iter1;
	for(iter1 = wtask->getwFuncList()->begin(); iter1 != wtask->getwFuncList()->end(); iter1++){
		std::cout << "Function: " << (*iter1)->getFunction()->getName().str() << "(" ;

		wFunction *wfunc = (*iter1);
		std::list<wBasicBlock *>::iterator iter2;

		if(wfunc->getFuncRetTy() == wFunction::FuncRetTy::VoidTy){
			std::cout << "VoidTy)" << std::endl;
		}else{
			std::cout << "NonVoidTy)" << std::endl;
		}

		for(iter2 = wfunc->getwBBList()->begin(); iter2 != wfunc->getwBBList()->end(); iter2++){
			std::cout << " BasicBlock: " << (*iter2)->getBasicBlock() << " ";
			std::cout << " wBasicBlock: " << (*iter2) << " ";
			std::cout << "[" << *((*iter2)->getName()) << "]";
			std::cout << "Call Num: " << (*iter2)->getNumFuncCall() << std::endl;

			std::pair<wBasicBlock *, wBasicBlock *> *branchBlockPair = (*iter2)->getBranchBlock();

			if((*iter2)->getType() == wBasicBlock::ONE_BRANCH){
				wBasicBlock *target1 = branchBlockPair->first;
				std::cout << " [BranchBlock]: " << target1->getBasicBlock() << " ";
				std::cout << " [wBranchBlock]: " << target1->getBasicBlock() << std::endl;

			}else if((*iter2)->getType() == wBasicBlock::TWO_BRANCH){
				wBasicBlock *target1 = branchBlockPair->first;
				wBasicBlock *target2 = branchBlockPair->second;
				std::cout << " [BranchBlock]: " << target1->getBasicBlock() << " ";
				std::cout << " [wBranchBlock]: " << target1 << std::endl;
				std::cout << " [BranchBlock]: " << target2->getBasicBlock() << " ";
				std::cout << " [wBranchBlock]: " << target2 << std::endl;
			}else{
				std::cout << " [Return]" << std::endl;

			}

			wBasicBlock *wbb = (*iter2);
			std::list<wInstruction *>::iterator iter3;
			for(iter3 = wbb->getwInstList()->begin(); iter3 != wbb->getwInstList()->end(); iter3++){
				std::cout << "   Instruction: " << (*iter3)->getInstruction()->getOpcodeName();
					
				wInstruction *wInst = *iter3;
				int opnt_cnt = wInst->getInstruction()->getNumOperands();

				for(int i = 0; i < opnt_cnt; i++)
       	 		{
          			Value *opnd = wInst->getInstruction()->getOperand(i);
					std::string o = opnd->getName();
					if(opnd->hasName()) {
						std::cout << " [S]" << o;

					} else {
						std::cout << " [P]" << opnd;
					}
				}
				std::cout << std::endl;
				
			}
		}	
	}
	return true;

}

/////////////////////////////////////////////////////////////

