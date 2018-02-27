#ifndef WINSTRUCTION
#define WINSTRUCTION

#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>
#include <iostream>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>

using namespace llvm;

class wInstruction
{
private:
	Instruction *inst;
	std::list<Value *> OperandList;

public:
	bool setwInstruction(Instruction *);
	Instruction *getInstruction();
	unsigned int getNumOperands();
	
	bool pushOperandList(Value *);

};

#endif
