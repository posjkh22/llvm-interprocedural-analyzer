
#ifndef PrintFunction

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
#include <list>

using namespace llvm;

class Support
{

public:
	bool PrintAllModule(std::unique_ptr<Module> &m);

private:
	bool PrintModule(std::unique_ptr<Module> &m);
	bool PrintFunction(Function& f);
	bool PrintBasicBlock(BasicBlock& bb);
	bool PrintInstruction(Instruction& inst);
	bool PrintOpnd(Instruction& inst, Value* opnd);
};



#endif
