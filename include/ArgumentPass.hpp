
#ifndef ARGUMENTPASS
#define ARGUMENTPASS

namespace IPA
{
	
class Argument;
class ArgumentPass;


class Argument
{

public:
	typedef enum
	{
		Linux,
		OSEC,
		FreeRTOS,
		MicroC,
		UnknownTargetTy
	} targetTy;

	typedef enum
	{
		UniThread,	
		MultiThread,
		UnknownThreadTy
	} threadTy;

	typedef enum
	{
		MemoryAllocationC,
		FilePointerAnalysisC,
		Deadlock,
		SemaphoreIntegrity,
		SharedVariables,
		SharedFunctions,
		UnknownAnalysisTy
	} analysisTy;

public:
	bool setTargetTy(Argument::targetTy);
	bool setThreadTy(Argument::threadTy);
	bool setAnalysisTy(Argument::analysisTy);
	Argument::targetTy getTargetTy();
	Argument::threadTy getThreadTy();
	Argument::analysisTy getAnalysisTy();


private:
	targetTy TargetTy;
	threadTy ThreadTy;
	analysisTy AnalysisTy;
};

class ArgumentPass
{

public:
	bool processArguPass(int argc, char* argv[]);
	bool message(int argc, char* argv[]);
	bool showArgument();
	Argument* getArgument();
private:
	IPA::Argument argument;
};

};

#endif
