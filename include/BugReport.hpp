
#ifndef BUGREPORT
#define BUGREPORT

#include <list>
#include "IRcodeData.hpp"
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/DebugInfoMetadata.h>

/*
typedef struct
{
	llvm::BasicBlock* bb;
	llvm::Instruction* inst;

} BugLocation;

typedef std::list<BugLocation* > BugLocationList;
*/


namespace IPA
{
	class BugReport;

typedef llvm::Instruction BugLocation;
typedef std::list<BugLocation* > BugLocationList;

class BugReport
{
public:
//	BugReport(IRcodeData* IRcode);

public:
	bool AddBugLocation(BugLocation* );
	BugLocation* popBugLocation();
	unsigned int returnBugLocation();
	
	bool showBugLocation();
	bool showBugLocation(BugLocation* );

private:
	BugLocationList m_BugLocationList;
	//IRcodeData* m_IRcode;
};

};
#endif
