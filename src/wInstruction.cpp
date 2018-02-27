
#include "wInstruction.hpp"

/* Instruction */
bool wInstruction::setwInstruction(Instruction *ins){
	inst = ins;
	return true;
}

Instruction *wInstruction::getInstruction(){
	return inst;
}

unsigned int wInstruction::getNumOperands(){
	return getInstruction()->getNumOperands();
}

bool wInstruction::pushOperandList(Value *opnd){
	OperandList.push_back(opnd);
	return true;
}

