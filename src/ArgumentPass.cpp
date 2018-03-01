
#include <unistd.h>
#include <iostream>
#include <getopt.h>
#include <cstring>
#include "ArgumentPass.hpp" 



using namespace IPA;

option longopts[4] = {

	{"target", 1, NULL, 't'},
	{"thread", 1, NULL, 'x'},
	{"analysis", 1, NULL, 'a'}, 
	{"debug", 0, NULL, 'd'}
};

bool ArgumentPass::processArguPass(int argc, char *argv[])
{
	int opt;

	message(argc, argv);

	while((opt = getopt_long(argc, argv, ":t:d", longopts, NULL)) != -1)
	{
		switch(opt)
		{
			case 't':

				if(!strcmp((char* )optarg,"Linux"))
				{
					argument.setTargetTy(Argument::targetTy::Linux);		
				}
				else if(!strcmp((char* )optarg, "OSEC"))
				{
					argument.setTargetTy(Argument::targetTy::OSEC);		
				}
				else if(!strcmp((char* )optarg, "FreeRTOS"))
				{
					argument.setTargetTy(Argument::targetTy::FreeRTOS);		
				}
				else if(!strcmp((char* )optarg, "MicroC/OS-II"))
				{
					argument.setTargetTy(Argument::targetTy::MicroC);		
				}
				else
				{
					std::cout << "unknown OS" << std::endl;
					argument.setTargetTy(Argument::targetTy::UnknownTargetTy);		
				}

				break;

			case 'x':

				if(!strcmp((char* )optarg,"Multithread"))
				{
					argument.setThreadTy(Argument::threadTy::MultiThread);		
				}
				else if(!strcmp((char* )optarg, "Unithread"))
				{
					argument.setThreadTy(Argument::threadTy::UniThread);		
				}
				else
				{
					std::cout << "unknown ThreadTy" << std::endl;
					argument.setThreadTy(Argument::threadTy::UnknownThreadTy);		
				}
		
				break;


			case 'a':

				if(!strcmp((char* )optarg,"MemoryAllocationC"))
				{
					argument.setAnalysisTy(Argument::analysisTy::MemoryAllocationC);
				}
				else if(!strcmp((char* )optarg, "FilePointerAnalysisC"))
				{
					argument.setAnalysisTy(Argument::analysisTy::FilePointerAnalysisC);		
				}
				else if(!strcmp((char* )optarg, "Deadlock"))
				{
					argument.setAnalysisTy(Argument::analysisTy::Deadlock);		
				}
				else if(!strcmp((char* )optarg, "SemaphoreIntegrity"))
				{
					argument.setAnalysisTy(Argument::analysisTy::SemaphoreIntegrity);		
				}
				else if(!strcmp((char* )optarg, "SharedVariables"))
				{
					argument.setAnalysisTy(Argument::analysisTy::SharedVariables);
				}
				else if(!strcmp((char* )optarg, "SharedFunctions"))
				{
					argument.setAnalysisTy(Argument::analysisTy::SharedFunctions);
				}
				else
				{
					std::cout << "unknown ThreadTy" << std::endl;
					argument.setAnalysisTy(Argument::analysisTy::UnknownAnalysisTy);
				}
		
				break;


			case 'd':
				std::cout << "debug" << std::endl;
				break;
		}
	}

	return true;
}

bool ArgumentPass::message(int argc, char* argv[])
{

	if (argc < 2) {
   		std::cerr << "Usage: " << argv[0] << "bitcode_filename" << std::endl;
    	return false;
	}

	return true;

}



bool Argument::setTargetTy(Argument::targetTy type)
{
	TargetTy = type;
	return true;
}

bool Argument::setThreadTy(Argument::threadTy type)
{
	ThreadTy = type;
	return true;
}

bool Argument::setAnalysisTy(Argument::analysisTy type)
{
	AnalysisTy = type;
	return true;
}


Argument::targetTy Argument::getTargetTy()
{
	return TargetTy;
}

Argument::threadTy Argument::getThreadTy()
{
	return ThreadTy;
}

Argument::analysisTy Argument::getAnalysisTy()
{
	return AnalysisTy;
}


bool ArgumentPass::showArgument()
{
	std::cout << "[Argument Info]" << std::endl;

	// OSTy //
	if(argument.getTargetTy() == Argument::targetTy::Linux)
	{
		std::cout << "TargetTy: Linux" << std::endl;
	}
	else if(argument.getTargetTy() == Argument::targetTy::OSEC)
	{
		std::cout << "TargetTy: OSEC" << std::endl;
	}
	else if(argument.getTargetTy() == Argument::targetTy::FreeRTOS)
	{
		std::cout << "TargetTy: FreeRTOS" << std::endl;
	}
	else if(argument.getTargetTy() == Argument::targetTy::MicroC)
	{
		std::cout << "TargetTy: MicroC/OS-II" << std::endl;
	}
	else
	{
		std::cout << "TargetTy: Unknown Target" << std::endl;
	}
	
	// ThreadTy //
	if(argument.getThreadTy() == Argument::threadTy::MultiThread)
	{
		std::cout << "ThreadTy: Multi-thread"  << std::endl;
	}
	else if(argument.getThreadTy() == Argument::threadTy::UniThread)
	{
		std::cout << "ThreadTy: Uni-thread" << std::endl;
	}
	else
	{
		std::cout << "ThreadTy: Unknown threadTy" << std::endl;
	}

	// AnalysisTy //
	if(argument.getAnalysisTy() == Argument::analysisTy::MemoryAllocationC)
	{
		std::cout << "AnalysisTy: MemoryAllocationC" << std::endl;
	}
	else if(argument.getAnalysisTy() == Argument::analysisTy::FilePointerAnalysisC)
	{
		std::cout << "AnalysisTy: FilePointerAnalysisC" << std::endl;
	}
	else if(argument.getAnalysisTy() == Argument::analysisTy::Deadlock)
	{
		std::cout << "AnalysisTy: Deadlock" << std::endl;
	}
	else if(argument.getAnalysisTy() == Argument::analysisTy::SemaphoreIntegrity)
	{
		std::cout << "AnalysisTy: SemaphoreIntegrity" << std::endl;
	}
	else if(argument.getAnalysisTy() == Argument::analysisTy::SharedVariables)
	{
		std::cout << "AnalysisTy: SharedVariables" << std::endl;
	}
	else if(argument.getAnalysisTy() == Argument::analysisTy::SharedFunctions)
	{
		std::cout << "AnalysisTy: SharedFunctions" << std::endl;
	}
	else 
	{
		std::cout << "AnalysisTy: UnknownAnalysisTy" << std::endl;
	}


	std::cout << std::endl;

	return true;
}

Argument* ArgumentPass::getArgument()
{
	return &argument;
}

