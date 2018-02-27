#ifndef WTASKLIST
#define WTASKLIST

#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <iostream>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>

#include <wFunction.hpp>

using namespace llvm;

class IRcodeTextDataSet;

class IRcodeTextDataSet
{

private:
	std::list<wFunction *> wFuncList;
	wFunction *EntryFunc;
	std::list<std::list<wBasicBlock *> *> GlobalPathsList;

public:
	bool setEntryFunc(wFunction *);
	wFunction *getEntryFunc();
	bool pushFuncList(wFunction *);
	std::list<wFunction *> *getwFuncList();
	wFunction* SearchFunction(Function*);
	wFunction* SearchFunction(const std::string &); 
	bool ShowPathsInEachFunc();

	/* GlobalPaths */
	std::list<std::list<wBasicBlock *> *> *getGlobalPathsList();
	bool ShowGlobalPaths();
	bool makeGlobalPaths();

	bool ShowTempPathsList(std::list<std::list<wBasicBlock *> *> *);
	bool insertPath(std::list<std::list<wBasicBlock *> *> **, std::list<wBasicBlock *> *, wBasicBlock *, std::list<std::list<wBasicBlock *> *> *);

	std::list<wBasicBlock *>::iterator SearchwBlock(std::list<wBasicBlock *> *TargetPath, wBasicBlock *BB);

	bool makeGlobalPathsList(std::list<std::list<wBasicBlock *> *> *);

};

#endif
