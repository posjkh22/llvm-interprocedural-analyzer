
#ifndef PATHIMPL
#define PATHIMPL

#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include "wBasicBlock.hpp"
#include "Path.hpp"

using namespace llvm;

class wBasicBlock;
class Path;
class PathList;

class PathImpl
{

private:
	//PathList *global_path_list;

public:


	//std::list<Path *> *insertPath(const Path *, const wBasicBlock *, const std::list<Path *> *);
	std::list<Path *> *insertPath(Path *, wBasicBlock *, std::list<Path *> *);

	//std::list<Path *> *ProcessCallInInputPathOnce(const std::list<Path *> *);
	std::list<Path *> *ProcessCallInInputPathOnce(std::list<Path *> *);

	//std::list<Path *> *GenerateGPL(const std::list<Path *> *);
	std::list<Path *> *GenerateGPL(std::list<Path *> *);

	bool IsAllCallBBProcessed(std::list<Path *> *);

};


#endif
