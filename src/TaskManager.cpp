
#include "TaskManager.hpp"

using namespace IPA;

TaskManager::TaskManager(ArgumentPass *arg, IRcodeData *IRcode)
{
	
	m_threadList = new TaskList;
	
	if(arg->getArgument()->getThreadTy() == Argument::threadTy::UniThread)
	{
		
		isMultiTask = false;
		
		m_threadList->push_back(
			IRcode->getIRcodeTextDataSet()->SearchFunction(std::string("main"))
		);
	}
	else if(arg->getArgument()->getThreadTy() == Argument::threadTy::MultiThread)
	{
		isMultiTask = true;
		m_threadList->push_back(
			IRcode->getIRcodeTextDataSet()->SearchFunction(std::string("task1"))
		);
		m_threadList->push_back(
			IRcode->getIRcodeTextDataSet()->SearchFunction(std::string("task2"))
		);

		setTaskNum(2);

	}
	else
	{
		std::cerr << "Undefined TaskTy " << std::endl;
	}
}

TaskList* TaskManager::getTaskList()
{
	return m_threadList;
}

Task* TaskManager::getTask()
{ 
	Task* retTask = m_threadList->back();
	m_threadList->pop_back();
	
	return retTask;
}

bool TaskManager::setTaskNum(unsigned int num)
{
	taskNum = num;
	return true;
}

unsigned int TaskManager::getTaskNum()
{
	if(isMultiTask == true)
		return taskNum;

	else
		return 1;
}


