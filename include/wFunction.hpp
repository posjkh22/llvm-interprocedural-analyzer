#ifndef WFUNCTION
#define WFUNCTION

#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <iostream>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include "wBasicBlock.hpp"
#include "Path.hpp"

using namespace llvm;

class Path;
class wFunction;
class wBasicBlock;

class wFunction 
{

public:
	typedef enum {
		VoidTy,
		NonVoidTy
	}FuncRetTy;

private:
	Function *func;
	FuncRetTy retTy;
	std::list<wBasicBlock *> wBBList;
	wFunction *callerFunc;
	wBasicBlock *CurrentBasicBlock;
	std::list<std::list<wBasicBlock *> *> PathsList;
	std::list<Path *> PATHSLIST;

public:


	wFunction();

	bool determineFuncRetTy();
	bool setFuncRetTy(wFunction::FuncRetTy);
	wFunction::FuncRetTy getFuncRetTy();

	/* wrapping function */
	bool setwFunction(Function *);
	Function *getFunction();

	wFunction *getCallerFunc();
	bool setCallerFunc(wFunction *);

	bool pushBBList(wBasicBlock *);
	wBasicBlock *getCurrentBasicBlock();

	bool setCurrentBasicBlock(wBasicBlock *);
	std::list<wBasicBlock *> *getwBBList();
	wBasicBlock* SearchBasicBlock(BasicBlock *);
	
	/* cfg Impl */
	std::list<std::list<wBasicBlock *> *> *getPathsList();
	bool makePathsList(wBasicBlock *);
	bool IntrinsicFuncMakePathsList(wBasicBlock *);
	unsigned int getNumPaths();
	bool showPathsList();

	/* Path */
	std::list<Path *> *makePATHSLIST();
	std::list<Path *> *getPATHSLIST();


};

#endif
