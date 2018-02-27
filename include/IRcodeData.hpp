
#ifndef WRAPPER
#define WRAPPER

#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <iostream>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include "IRcodeTextDataSet.hpp"
#include "wFunction.hpp"
#include "wBasicBlock.hpp"
#include "wInstruction.hpp"

using namespace llvm;

class IRcodeData;
class IRcodeTextDataSetList;
class IRcodeTextDataSet;
class wFunction;
class wBasicBlock;
class wInstruction;


class IRcodeData
{

private:
	IRcodeTextDataSet* wtask;
	std::unique_ptr<Module>* IRmodule;
	
	class Data
	{
	public:
		Function *f;
		BasicBlock *bb;
		Instruction *inst;

		Data(Function *f, BasicBlock *bb, Instruction *inst):f(f), bb(bb), inst(inst){}
	};
	

public:

	IRcodeData(std::unique_ptr<Module> &m);
	~IRcodeData();
	IRcodeTextDataSet* getIRcodeTextDataSet();

	/* [preprocess] BasicBlock split */
	bool Preprocess1();
	bool Preprocess2();
	bool Preprocess3();

	/* Create GlovalVariables Info */
	void ShowGlobalVariables(std::unique_ptr<Module> &m);
	GlobalVariable *popGlobalVariable(std::unique_ptr<Module> &m, int number);


	/* Create Wrapper class */
	
	bool ShowPathsInEachFunc();

	/* [debug] show IRcodeData element */
	bool DebugWrapperModule();

private:
	bool splitBBModuleOnce(std::unique_ptr<Module> &m);
	int splitBBModuleChecker(std::unique_ptr<Module> &m);

private:
	bool BasicBlockBranchAndFunctionCallImpl();
	bool makePathsInEachFunction();



};


#endif
