#ifndef PATH
#define PATH

#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include "wBasicBlock.hpp"
#include <fstream>

using namespace llvm;

class wBasicBlock;
class Path;
class PathList;

typedef std::list<Path* > GPL;

class PathList
{
private:
	std::list<Path *> *PathListPtr;

public:
	PathList(std::list<Path *> *);
	std::list<Path *> *getPathList();
	bool ShowPathList();
};


class Path
{

private:
	std::string *name;
	std::list<wBasicBlock *> *PathPtr;
	unsigned int NumCallBB;
	unsigned int CallBBNumToBeProcessed;
	std::list<unsigned int> CallBBList;

public:

	Path(){};
	Path(Path *);
	Path(std::list<wBasicBlock *> *);

	bool setName(std::string);
	std::string *getName();

	bool setPath(std::list<wBasicBlock *> *);
	std::list<wBasicBlock *> *getPath();
	
	bool setNumCallBB(unsigned int);
	unsigned int getNumCallBB();

	bool setNumCallBBToBeProcessed(unsigned int);
	unsigned int getNumCallBBToBeProcessed();

	bool setCallBBList();
	std::list<unsigned int> *getCallBBList();

	std::list<Path *> *SearchNextCallBBandReturnPath();
	int getjustNextNumberInCallBBList();
	int getdeleteNextNumberInCallBBList();
	wBasicBlock *SearchCallBBListWithIterNumber(unsigned int);
	bool deleteNextNumberInCallBBList(unsigned int);
	
	bool ShowPath();
	bool ShowPath(std::ofstream&);
	void ShowCallBBList();

};


#endif
