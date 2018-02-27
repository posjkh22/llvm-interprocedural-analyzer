#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <utility>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Bitcode/BitcodeReader.h>

#include "IRcodeData.hpp"
#include "IRcodeTextDataSet.hpp"
#include "wFunction.hpp"
#include "wBasicBlock.hpp"
#include "wInstruction.hpp"
#include "Support.hpp"
#include "Path.hpp"
#include "PathImpl.hpp"
#include "checker.hpp"
#include "ArgumentPass.hpp"
#include "TaskManager.hpp"
#include "BugReport.hpp"

/* 2018-01-25 */

/*

    [solved] problem: GPL
	[solved] problem: split;
	[solved] problem: delete argument (function) 

	problem: C code linking
	probelm: Intrincs (llvm.memcpy)
	problem: other ptr(return or argument) case: malloc & free
	problem: real malloc/ real free

	return -> function ret type -> if ret something, pusch argulist, (stack) get, update.

	unique number:

	problem: C lang is squential. -> revserse iterator  or delete inserted value

*/

using namespace llvm;

/* To easily pass varaibles */
GlobalVariable *comp_gv;

//std::unique_ptr<Module> m; 

int main(int argc, char *argv[]) {

	/* Process Argument */
	IPA::ArgumentPass arg;
	arg.processArguPass(argc, argv);
	arg.showArgument();

	/* IRParser */
	StringRef filename = argv[3];
	LLVMContext context;
	SMDiagnostic error;
	std::unique_ptr<Module> m = parseIRFile(filename, error, context);
	
	/* Wrapper */
	IRcodeData IRcode(m);

	/* Global Variable */
/*
	IRcode.ShowGlobalVariables(m);
*/
	comp_gv = IRcode.popGlobalVariable(m, 0);

	/* Function */
	IRcode.Preprocess1();
	IRcode.Preprocess2();
	IRcode.Preprocess3();
	
/*
	IRcode.DebugWrapperModule();	
*/

/*	
	IRcode.ShowPathsInEachFunc();
*/

	/* TaskManager */
	IPA::TaskManager tm(&arg, &IRcode);

	for(unsigned int i = 0; i < tm.getTaskNum(); i++)
	{
		PathImpl pathimpl;
	
		GPL* gpl = pathimpl.GenerateGPL(tm.getTask()->getPATHSLIST());
		PathList m_PathList(gpl);
		m_PathList.ShowPathList();
	
		IPA::BugReport brp;

		Checker checker(&brp);
		checker.check(&m_PathList);
		
		//brp.showBugLocation();

	}


	return 0;
}
