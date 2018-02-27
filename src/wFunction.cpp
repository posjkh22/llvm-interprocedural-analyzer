#include "wFunction.hpp"

///////////////* wFunction */////////////


wFunction::wFunction(){
	makePATHSLIST();
}

bool wFunction::determineFuncRetTy(){

	llvm::Function *f = getFunction();

	for(auto iter1 = f->getBasicBlockList().begin();
			iter1 != f->getBasicBlockList().end(); iter1++){

		llvm::BasicBlock &bb = *iter1;
		for (auto iter2 = bb.begin(); iter2 != bb.end(); iter2++) {

			llvm::Instruction &inst = *iter2; 

			if(inst.getOpcodeName() == std::string("ret")){

				if(inst.getNumOperands() == 0){
					setFuncRetTy(FuncRetTy::VoidTy);
				}
				else{
					setFuncRetTy(FuncRetTy::NonVoidTy);
				}
			}else{

				continue;
			}		
			
		}
	}
	/*
	if(){
		setFuncRetTy(FuncRetTy::voidTy)
	}
	else{
		setFuncRetTy(FuncRetTy::NonVoidTy)
	}
	*/
	return true;
}

bool wFunction::setFuncRetTy(wFunction::FuncRetTy type){
	retTy = type;
	return true;
}

wFunction::FuncRetTy wFunction::getFuncRetTy(){
	return retTy;
}


/* wrapper */
bool wFunction::setwFunction(Function *f){
	func = f;
	return true;
}

Function *wFunction::getFunction(){
	return func;
}

wFunction* wFunction::getCallerFunc(){
	return callerFunc;
}

bool wFunction::setCallerFunc(wFunction* func){
	callerFunc = func;
	return true;
}

bool wFunction::pushBBList(wBasicBlock *bb){
	wBBList.push_back(bb);
	return true;
}

wBasicBlock *wFunction::getCurrentBasicBlock(){
	return CurrentBasicBlock;
}

bool wFunction::setCurrentBasicBlock(wBasicBlock *wbb){
	CurrentBasicBlock = wbb;
	return true;
}

std::list<wBasicBlock *> *wFunction::getwBBList(){
	return &wBBList;
}

wBasicBlock *wFunction::SearchBasicBlock(BasicBlock *bb){

	std::list<wBasicBlock *> *wbblist = getwBBList();
	std::list<wBasicBlock *>::iterator iter;

	for(iter = wbblist->begin(); iter != wbblist->end(); iter++){
		if( (*iter)->getBasicBlock() == bb){
			//std::cout << "Target BB Find! ";
			break;
		}
	}
	return (*iter);
}



/* CFG Impl */

std::list<std::list<wBasicBlock *> *> *wFunction::getPathsList(){
	return &PathsList;
}


bool wFunction::IntrinsicFuncMakePathsList(wBasicBlock *wbb){

	std::list<wBasicBlock *> *new_cfg = new std::list<wBasicBlock *>;
	new_cfg->push_back(wbb);
	PathsList.push_back(new_cfg);
	
	return true;
}


bool wFunction::makePathsList(wBasicBlock *wbb){


	/* function entryBB */
	if(PathsList.empty()){
	
		//std::cout << "FIRST!" << std::endl;
		std::list<wBasicBlock *> *new_cfg = new std::list<wBasicBlock *>;
		new_cfg->push_back(wbb);
		PathsList.push_back(new_cfg);
	}

	/* NOT function entryBB */
	std::list<wBasicBlock *> *current_cfg;
	std::list<std::list<wBasicBlock *> *>::iterator iter;
	/* Find out the right CFG */
	for(iter = PathsList.begin(); iter != PathsList.end(); iter++){
		current_cfg = (*iter);
		if(wbb == current_cfg->back()){
			//std::cout << "FIND!" << std::endl;
			break;
		}
	}

	if(wbb->getType() == wBasicBlock::ONE_BRANCH){
		//std::cout << "ONE PATH!" << std::endl;

		std::pair<wBasicBlock *, wBasicBlock *> *BranchBlockPair;
		BranchBlockPair = wbb->getBranchBlock();
		wBasicBlock *targetBlock = BranchBlockPair->first;
		current_cfg->push_back(targetBlock);
		makePathsList(targetBlock);
	}

	else if(wbb->getType() == wBasicBlock::TWO_BRANCH){

		//std::cout << "TWO PATH!" << std::endl;
		std::list<wBasicBlock *> *new_copy_cfg = new std::list<wBasicBlock *>(*current_cfg);
		
		std::pair<wBasicBlock *, wBasicBlock *> *BranchBlockPair;
		BranchBlockPair = wbb->getBranchBlock();
		wBasicBlock *targetBlock1 = BranchBlockPair->first;
		wBasicBlock *targetBlock2 = BranchBlockPair->second;
		
		current_cfg->push_back(targetBlock1);
		new_copy_cfg->push_back(targetBlock2);
		PathsList.push_back(new_copy_cfg);
		makePathsList(targetBlock1);
		makePathsList(targetBlock2);

	}
	/* BB_type = RETURN*/

	else{
		//std::cout << "RETURN! " << std::endl;
		return true;
	}

	return true;
}

bool wFunction::showPathsList(){


	std::list<wBasicBlock *> *current_cfg;
	std::list<std::list<wBasicBlock *> *>::iterator iter1;
	std::list<wBasicBlock *>::iterator iter2;

	for(iter1 = PathsList.begin(); iter1 != PathsList.end(); iter1++){
		current_cfg = (*iter1);
		
		std::cout << " - path: ";
		for(iter2 = current_cfg->begin(); iter2 != current_cfg->end(); iter2++){

			std::cout << " " << *((*iter2)->getName());
		}
		std::cout << std::endl;
	}

	return true;
}

unsigned int wFunction::getNumPaths(){
	return PathsList.size();
}

std::list<Path *> *wFunction::makePATHSLIST(){

	std::list<std::list<wBasicBlock *> *>::iterator iter;

	Path *temp_path;
	for(iter = PathsList.begin(); iter != PathsList.end(); iter++){

		temp_path = new Path(*iter);
		PATHSLIST.push_back(temp_path);

	}

	return &PATHSLIST;
}

std::list<Path *> *wFunction::getPATHSLIST(){
	return &PATHSLIST;
}
