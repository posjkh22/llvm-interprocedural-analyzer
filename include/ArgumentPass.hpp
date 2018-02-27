
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

public:
	bool setTargetTy(Argument::targetTy);
	bool setThreadTy(Argument::threadTy);
	Argument::targetTy getTargetTy();
	Argument::threadTy getThreadTy();

private:
	targetTy TargetTy;
	threadTy ThreadTy;
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
