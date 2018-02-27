#include "Support.hpp"


using namespace llvm;

bool Support::PrintAllModule(std::unique_ptr<Module> &m){

	PrintModule(m);

	/* Module Entry */
  	for (auto iter1 = m->getFunctionList().begin(); iter1 != m->getFunctionList().end(); iter1++) {

		/* Function Entry */
		Function &f = *iter1;
		PrintFunction(f);


		for (auto iter2 = f.getBasicBlockList().begin(); iter2 != f.getBasicBlockList().end(); iter2++) {

			/* BasicBlock Entry */
			BasicBlock &bb = *iter2;
			PrintBasicBlock(bb);
				

			Instruction* br_inst;
		  	for (auto iter3 = bb.begin(); iter3 != bb.end(); iter3++) {

				/* Instruction Entry */
				Instruction &inst = *iter3;
				br_inst = &inst;
				PrintInstruction(inst);

       		 	int opnt_cnt = inst.getNumOperands();

				for(int i = 0; i < opnt_cnt; i++)
       	 		{
          			Value *opnd = inst.getOperand(i);
					PrintOpnd(inst, opnd);
        		}

				if(!strcmp(inst.getOpcodeName(), "call")){

					if(inst.getNumOperands() == 1){

						std::cout << "[call]";
					}
					else {
						//std::error();
					}
				}
				
				
        		std:: cout << std::endl;
      		}
		
			/* BasicBlock EndPoint */
			/* BasicBlock Pointer */
			if(!strcmp(br_inst->getOpcodeName(), "br")){
				if(br_inst->getNumOperands() == 1){

					Value* opnd = br_inst->getOperand(br_inst->getNumOperands() -1);
					std::cout << "     [branch][point to: " << opnd << "]" << std::endl;
					std::cout << std::endl;


				}else if(br_inst->getNumOperands() == 3) {

					Value* opnd1 = br_inst->getOperand(br_inst->getNumOperands() -1);
					Value* opnd2 = br_inst->getOperand(br_inst->getNumOperands() -2);

					std::cout << "     [branch][point to: " << opnd1 << "]" << std::endl;
					std::cout << "     [branch][point to: " << opnd2 << "]" << std::endl;
					std::cout << std::endl;

				}

			}

			if(!strcmp(br_inst->getOpcodeName(), "ret")){		
				std::cout << "    [return!]" << std::endl << std::endl;
			}

		/* Function EndPoint */	
    	}
  	}

	return true;
}

bool Support::PrintModule(std::unique_ptr<Module> &m){

	std::cout << " Successfully read Module:" << std::endl;
	std::cout << " Name: " << m->getName().str() << std::endl;
	std::cout << " Target triple: " << m->getTargetTriple() << std::endl;

	return true;
}

bool Support::PrintFunction(Function& f){

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << " [Function]: " << f.getName().str() << std::endl;
	std::cout << " [ARG]: ";
	for(auto iter = f.arg_begin(); iter != f.arg_end(); iter++){
		std::cout << "(" << &(*iter) << ") ";
	}
	std::cout << std::endl;
	std::cout << " [Function EntyBlackBlock]: " << &(f.getEntryBlock()) << std::endl;	
	
	return true;
}


bool Support::PrintBasicBlock(BasicBlock& bb){

	std::cout << "  [BasicBlock]: " << &bb << std::endl;
	//std::cout << "  BasicBlock Parent: " << bb.getParent()->getName().str() << std::endl;
	//std::cout << "  BasicBlock Module: " << bb.getModule()->getName().str() << std::endl;

	return true;
}

bool Support::PrintInstruction(Instruction& inst){

	//std::cout << "   #Instruction " << &inst << std::endl;
   	//std::cout << "   #Instruction Type.TypeID " << inst.getType()->getTypeID() << std::endl; 
	//std::cout << "   #Instruction OpCode: " << inst.getOpcode() << std::endl;
	//std::cout << "   #Instruction OpName: " << inst.getOpcodeName() << std::endl;
	//std::cout << "   #Instruction Operand Num: " << inst.getNumOperands() << std::endl;

	std::cout << "   #Instruction OpName(" << &inst << "): " << inst.getOpcodeName();
	std::cout << "[" << inst.getNumOperands() << "] ";

	return true;
}

bool Support::PrintOpnd(Instruction& inst, Value* opnd){

	std::string o;
	//std::cout << "      opnd Type.ValueID print: " << opnd->getValueID() <<std::endl;	
	//std::cout << "      opnd Type.TypeID: " << opnd->getType()->getTypeID() << std::endl;
	//std::cout << "      opnd type Print: " << std::endl;

	if(opnd->hasName()) {
		o = opnd->getName();
		std::cout << "[Name]" << o << " ";

	} else {
		std::cout << "[ptr]" << opnd << " ";;
	}

	return true;
}
