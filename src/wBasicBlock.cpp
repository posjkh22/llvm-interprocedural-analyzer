
#include "wBasicBlock.hpp"

///////////////////* BasicBlock *///////////////////////

bool wBasicBlock::setName(std::string tname){
	name = new std::string(tname);
	return true;
}

std::string *wBasicBlock::getName(){
	return name;
}

bool wBasicBlock::setwBasicBlock(BasicBlock *b){
	bb = b;
	return true;
}

BasicBlock *wBasicBlock::getBasicBlock(){
	return bb;
}


bool wBasicBlock::setType(wBasicBlock::BB_type ty){
	type = ty;
	return true;
}

wBasicBlock::BB_type wBasicBlock::getType(){
	return type;
}

bool wBasicBlock::setCurrentInstruction(wInstruction *inst){
	CurrentInstruction = inst;
	return true;
}

wInstruction* wBasicBlock::getCurrentInstruction(){
	return CurrentInstruction;
}


unsigned int wBasicBlock::getNumFuncCall(){
	return wFuncCallList.size();
}
	
std::list<wFunction *> *wBasicBlock::getFuncCallList(){
	return &wFuncCallList;
}

bool wBasicBlock::pushFuncCallList(wFunction *wf){
	wFuncCallList.push_back(wf);
	return true;
}

wFunction *wBasicBlock::getFuncCall(){

	if(hasCall()){

		return getFuncCallList()->front();
	}

	return nullptr;
}

wFunction *wBasicBlock::getParent(){
	return Parent;
}

bool wBasicBlock::setParent(wFunction* wf){
	Parent = wf;
	return true;
}

Function *wBasicBlock::getParentFunction(){
	llvm::BasicBlock *bb = getBasicBlock();
	llvm::Function *F = bb->getParent();
	return F;
}


bool wBasicBlock::pushInstList(wInstruction* inst){
	wInstList.push_back(inst);
	return true;
}

bool wBasicBlock::setReturnBlock(wBasicBlock* bb){
	ReturnBlock = bb;
	return true;
}

wBasicBlock *wBasicBlock::getReturnBlock(){
	return ReturnBlock;
}

bool wBasicBlock::setBranchBlock(std::pair<wBasicBlock* , wBasicBlock* > *branch){
	BranchBlock = branch;
	return true;
}

std::pair<wBasicBlock *, wBasicBlock *> *wBasicBlock::getBranchBlock(){
	return BranchBlock;
}

std::list<wInstruction *> *wBasicBlock::getwInstList(){
	return &wInstList;
}

bool wBasicBlock::setCall(bool hasCall){
	this->hasFunctionCall = hasCall;
	return true;
}

bool wBasicBlock::hasCall(){
	return hasFunctionCall;
}

///////////////////* BasicBlock *///////////////////////
