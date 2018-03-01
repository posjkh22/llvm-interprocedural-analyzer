#ifndef CHECKER
#define CHECKER

#include <iomanip>
#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include <fstream>

#include "wBasicBlock.hpp"
#include "wInstruction.hpp"
#include "Path.hpp"
#include "PathImpl.hpp"
#include "BugReport.hpp"
#include "ArgumentPass.hpp"

using namespace llvm;

class Instruction;
class wBasicBlock;
class wInstruction;
class Path;
class PathList;


extern GlobalVariable *comp_gv;




class Checker
{

public:
	typedef enum {
		CHECK1,
		CHECK2,
		CHECK3,
		CHECK4,
		CHECK5,
		MemoryAllocationC,
		FilePointerAnalysisC,
		Deadlock,
		SemaphoreIntegrity,
		SharedVariables,
		SharedFunctions,
		UnknownCheckerTy
	}checker_ty;

	class TraceData
	{
	
	public:
		Value *traceVal;
		llvm::Instruction* Location;
		wBasicBlock* LocationBB; 
		int *checker_state_flag;
		int bug_location_flag;
		int return_update_flag;
		int unique_number;
		llvm::Function *f;

		TraceData(Value *tVal, int *tStatef, llvm::Function *F, 
				int uNumber){
			traceVal = tVal;
			checker_state_flag = tStatef;
			f = F;
			bug_location_flag = 0;
			return_update_flag = 0;
			unique_number= uNumber;
		}
		
		TraceData(Value *tVal, int *tStatef, llvm::Function *F){
			traceVal = tVal;
			checker_state_flag = tStatef;
			f = F;
			bug_location_flag = 0;
			return_update_flag = 0;
		}

		bool setUniqueNumber(Checker *checker){

			static int number = 0;
			
			if(checker->reset_flag == 1){
				number = 0;
				checker->reset_flag = 0;
				unique_number = number++;
			}
			else{
				unique_number = number++;
			}
			return true;
		}
		
	};

	class Argument 
	{
	public:
		int number;
		Value *traceVal;

		Argument(int num, Value *tVal){
			number = num;
			traceVal = tVal;
		}
	};

	/*
	class ReturnVal
	{
	public:
		Value *traceVal;
	
		ReturnVal(Value *tVal){
			traceVal = tVal;
		}
	};
	*/

private:
	IPA::BugReport *m_BugReport;
	IPA::ArgumentPass *m_ArgumentPass;

private:
	checker_ty type;
	int trace_flag;
	int trace_new_func_flag;
	int basic_checker_state_flag;
	int reset_flag;

	std::list<Checker::Argument *> PassingArgument;
	std::list<TraceData *> PassingReturnVal;
	std::list<TraceData *> traceValState;

	wBasicBlock *currentBB;
	PathList *currentPathList;
	Path *currentPath;


public:
	Checker(IPA::BugReport *bugReport, IPA::ArgumentPass *argument);

	bool checkerTyDetermination();

	bool setCheckerTy(checker_ty ty);
	TraceData *SearchTraceVal(unsigned int iter_count);
	TraceData *SearchTraceVal(llvm::Value *cmp_val);
	bool ShowTraceData();
	bool ShowPassingReturnVal();
	unsigned int check_checker_state_flag();
	bool deleteTraceValwithReturn(llvm::Function *fid);
	bool setBugLocationFlag(llvm::Function *fid);

	bool setCheckerState();
	bool ResetCheckerState();
	bool ResetCheckerVariable();
	bool ResetTraceValState();
	bool ResetPassingReturnVal();
	bool ResetPassingArgument();

	bool BugReport();

	/* check */

	bool check(PathList *pathlist);
	bool check(Path *path);
	bool check(wBasicBlock *BB);

	/* checker set */
	bool check1(wBasicBlock *BB, wInstruction *Inst);
	bool check2(wBasicBlock *BB, wInstruction *Inst, GlobalVariable *gv);
	bool check3(wBasicBlock *BB, wInstruction *Inst, GlobalVariable *gv);
	bool check4(wBasicBlock *BB, wInstruction *Inst);
	bool check5(wBasicBlock *BB, wInstruction *Inst);

	/* PathList */
	Checker(PathList *);

	bool attachPathList(PathList *);
	
	bool setCurrentPathList(PathList *);

	PathList *getCurrentPathList();

	bool movePath();


	/* Path */
	Checker(Path *);

	bool attachPath(Path *);
	
	Path *getCurrentPath();
	bool setCurrentPath(Path *);

	bool move();


	/* BB */

	wBasicBlock *getCurrentBB();
	bool setCurrentBB(wBasicBlock *);

	wBasicBlock *getNextBB();
	wBasicBlock *getNextBB(Path *);


};


#endif
