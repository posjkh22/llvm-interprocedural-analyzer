
#include "BugReport.hpp"

using namespace IPA;

/*
BugReport::BugReport(IRcodeData* IRcode)
{
	m_IRcode = IRcode;
}
*/


unsigned int BugReport::returnBugLocation()
{
	
	BugLocation* bugloc = popBugLocation();
	//1llvm::BasicBlock* bugloc_bb = bugloc->bb;
	//llvm::Instruction* bug_inst = bugloc->inst;

	unsigned int LineNum = 0;
	//if(DILocation* loc = bug_inst->getDebugLoc())
	if(DILocation* loc = bugloc->getDebugLoc())
	{
		LineNum = loc->getLine();
	}

	std::cout << "[LineNum] " << LineNum << std::endl; 

	return LineNum;

}

bool BugReport::showBugLocation(BugLocation* bugloc, std::ofstream& fout)
{

	unsigned int LineNum = 0;
	llvm::StringRef filename;
	llvm::StringRef dirname;
	//if(DILocation* loc = bug_inst->getDebugLoc())
	if(DILocation* loc = bugloc->getDebugLoc())
	{
		LineNum = loc->getLine();
		filename = loc->getFilename();
		dirname = loc->getDirectory();
		std::cout << " - Directory: " << dirname.str() << std::endl; 
		std::cout << " - Finename: " << filename.str() << std::endl; 
		std::cout << " - Line: " << LineNum << std::endl;
	
		std::string dirnameStr(dirname.str());
		std::string filenameStr(filename.str());

		
		std::string dirnameOnlyStr = dirnameStr.substr(dirnameStr.find("/") + 1);
		std::string tmp_dirnameOnlyStr;
		std::string comp_dirnameOnlyStr;
		while(tmp_dirnameOnlyStr != (dirnameOnlyStr = dirnameOnlyStr.substr(dirnameOnlyStr.find("/") + 1)))
		{
			tmp_dirnameOnlyStr = dirnameOnlyStr;
			//comp_dirnameOnlyStr = dirnameOnlyStr;
		}

		std::string filenameOnlyStr = filenameStr.substr(filenameStr.find("/") + 1);
		std::string tmp_filenameOnlyStr;
		while(tmp_filenameOnlyStr != (filenameOnlyStr = filenameOnlyStr.substr(filenameOnlyStr.find("/") + 1)))
		{
			tmp_filenameOnlyStr = filenameOnlyStr;
		}
		
		/*
		fout << " - Directory: " << dirname.str() << std::endl; 
		fout << " - Finename: " << filename.str() << std::endl; 
		*/

		fout << " - Directory: " << dirnameOnlyStr << std::endl; 
		fout << " - Finename: " << filenameOnlyStr << std::endl; 
		fout << " - Line: " << LineNum << std::endl;
	}	


	return true;
}


bool BugReport::showBugLocation()
{
	while(m_BugLocationList.empty() == false)
	{
		BugLocation* bugloc = popBugLocation();
		//llvm::BasicBlock* bugloc_bb = bugloc->bb;
		//llvm::Instruction* bug_inst = bugloc->inst;

		unsigned int LineNum = 0;
		llvm::StringRef filename;
		llvm::StringRef dirname;
		//if(DILocation* loc = bug_inst->getDebugLoc())
		if(DILocation* loc = bugloc->getDebugLoc())
		{
			LineNum = loc->getLine();
			filename = loc->getFilename();
			dirname = loc->getDirectory();
			std::cout << " - Directory: " << dirname.str() << std::endl; 
			std::cout << " - Finename: " << filename.str() << std::endl; 
			std::cout << " - Line: " << LineNum << std::endl;
		}	
	}

	return true;
}

BugLocation* BugReport::popBugLocation()
{
	BugLocation* retBugLoc = m_BugLocationList.back();
	m_BugLocationList.pop_back();
	return retBugLoc;
}


bool BugReport::AddBugLocation(BugLocation* bugloc)
{
	m_BugLocationList.push_back(bugloc);
	return true;
}
