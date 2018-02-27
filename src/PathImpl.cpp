
#include "PathImpl.hpp"


bool setNameGPL(std::list<Path *> *inPathList){

	static int number = 0;

	std::list<Path *>::iterator iter;

	for(iter = inPathList->begin();
			iter != inPathList->end(); iter++){

		Path *currentPath = (*iter);
		currentPath->setName(std::string("[") + std::to_string(number++) + std::string("]"));
	}

	return true;
}



std::list<Path *>  *PathImpl::insertPath(Path *TargetPath, wBasicBlock *CallBB, std::list<Path *> *InsertedPathList){

	/* TargetPath & InsertedPathList should not be modified */
	/* TargetPath must be copied (as many InsertedPathList Path Num) */
	/* InsertedPathList must be inserted into TargetPath */
	/* Calculated new CallBBLIST */
	/* Return new newPathList (It shall be freed in the outer function) */

	//static int insertPathRoutineNum = 0;

	std::list<Path *> *newPathList = new std::list<Path *>;

	//std::cout << "InsertPathRoutineNum: " << insertPathRoutineNum++ << std::endl;
	
	int next_callBB_number = TargetPath->getdeleteNextNumberInCallBBList();
	

	if(next_callBB_number == -1){

		/* Impossible path */
		std::cout << "ERROR!!" << std::endl;
	}

	std::list<Path *>::iterator iter1;
	std::list<unsigned int>::iterator iter2;
	std::list<unsigned int>::iterator iter3;
	std::list<wBasicBlock *>::iterator iter4;
	std::list<wBasicBlock *>::iterator iter5;

	
	for(iter1 = InsertedPathList->begin(); \
			iter1 != InsertedPathList->end(); iter1++){

	
		/* Copy */
		/* new_path should be stored in newPathList */ 
		Path *new_path = new Path(TargetPath);

		/* Insert InsertedPath into new_path */
		Path *inserted_path = (*iter1);

		std::list<wBasicBlock *> *wBBListIn_new_path = new_path->getPath();
		std::list<wBasicBlock *> *wBBListIn_inserted_path \
			= inserted_path->getPath();

		unsigned int number = 0;
	
		for(iter4 = wBBListIn_new_path->begin(), number = 0;\
				(iter4 != wBBListIn_new_path->end()) \
				&& (number < wBBListIn_new_path->size()); \
				iter4++, number++){

			if(number == (unsigned int)next_callBB_number && CallBB == *(iter4)){
				iter4++;
				break;
			}

		}

		
		for(iter5 = wBBListIn_inserted_path->begin(); \
				iter5 != wBBListIn_inserted_path->end(); \
				iter5++){

			wBasicBlock *inserted_bb = (*iter5); 
			wBBListIn_new_path->insert(iter4, inserted_bb);

		}

		/* new Path CallBBList Update */
		
		std::list<unsigned int> *new_path_CallBBList = new_path->getCallBBList();

		Path *currentInsertedPath = (*iter1);
		std::list<unsigned int> *currentInsertedPathCallBBList \
			= currentInsertedPath->getCallBBList();
		
		unsigned int InsertedPathSize \
			= currentInsertedPath->getPath()->size();

#ifdef DEBUG_IMPL
		std::cout << "InsertedPath Size: " << InsertedPathSize << std::endl;
#endif
		/* 1. Update: Inserting insertedPath results in existing CallBB change */

		int tmp_size = new_path_CallBBList->size();

#ifdef DEBUG_IMPL
		std::cout << "InsertedPath: " << std::endl; 
		for(iter2 = currentInsertedPathCallBBList->begin(); \
			iter2 != currentInsertedPathCallBBList->end(); iter2++){
			std::cout << (*iter2) << " ";
		}
		std::cout << std::endl;

		std::cout << "ShowBB(Before): " << std::endl; 
		for(iter2 = new_path_CallBBList->begin();
				iter2 != new_path_CallBBList->end(); iter2++){
			std::cout << (*iter2) << " ";
		}
		std::cout << std::endl;
#endif

		iter2 = new_path_CallBBList->begin();
		for(int i = 0; i < tmp_size; i++){
			unsigned int UpdateValue 
				= new_path_CallBBList->front() + InsertedPathSize;
			new_path_CallBBList->pop_front();
			new_path_CallBBList->push_back(UpdateValue);
		}
#ifdef DEBUG_IMPL
		std::cout << "ShowBB(pop): " << std::endl; 
		for(iter2 = new_path_CallBBList->begin();
				iter2 != new_path_CallBBList->end(); iter2++){
			std::cout << (*iter2) << " ";
		}
		std::cout << std::endl;		
#endif		

		/* 2. Update: CallBBList in InsertedPath should be changed */

		iter3 = new_path_CallBBList->begin();

		if(currentInsertedPathCallBBList->empty() == false){

			for(iter2 = currentInsertedPathCallBBList->begin(); \
				iter2 != currentInsertedPathCallBBList->end(); iter2++){

				unsigned int PassingValue \
					= (*iter2) + next_callBB_number +1;
				
				new_path_CallBBList->insert(iter3, PassingValue);
			}

		}

		newPathList->push_back(new_path);
		

	}
	


	return newPathList;

}


std::list<Path *> *PathImpl::ProcessCallInInputPathOnce(std::list<Path *> *InputPath){

	//static int processNum = 0;
	std::list<Path *>::iterator iter1;
	std::list<Path *>::iterator iter2;

	std::list<Path *> *inserted_path_list;
	std::list<Path *> *result_path_list;

	wBasicBlock *target_block;

	/* InputPath is from Entry function */
	/* So No modifications to InputPath is allowed */
	std::list<Path *> *new_return_path_list = new std::list<Path *>;
	//std::cout << "ProcessNum(Once): " << processNum++ << std::endl;

	for(iter1 = InputPath->begin(); iter1 != InputPath->end(); iter1++){

		Path *current_path = (*iter1);

		/* inserted_path_list is from wFunction Path: Not allowed to be freed */
		inserted_path_list = current_path->SearchNextCallBBandReturnPath();

		if(inserted_path_list == nullptr){

			/*
			for(iter2 = current_path_list->begin(); \
				iter2 != inserted_path_list->end(); iter2++){

				new_return_path_list->push_back((*iter2));
			}
			*/
			new_return_path_list->push_back(current_path);
			continue;
		}

		target_block = current_path->SearchCallBBListWithIterNumber(current_path->getjustNextNumberInCallBBList());
	
		/* return_path_list is malloced in inserPath function: Need to be freed */
		result_path_list = insertPath(current_path, target_block, inserted_path_list);

		/*
		unsigned int iter_cnt = current->getCallBBNextNumbering();
		wBasicBlock *target_block = current->SearchNumberingBB(iter_cnt);
		wFunction *target_func = target_block->getFuncCall();
		inserted_path_list = target_func->getPATHSLIST();
		*/

		for(iter2 = result_path_list->begin(); \
				iter2 != result_path_list->end(); iter2++){

			new_return_path_list->push_back((*iter2));
		}

		//free(result_path_list);

	}

	return new_return_path_list;
}


std::list<Path *> *PathImpl::GenerateGPL(std::list<Path *> *EntryFuncPath){

#ifdef DEBUG_PATHIMPL
	std::cout << std::endl << "[GPL creator]: Start! " << std::endl;
#endif
	std::list<Path *> *GPL;
	std::list<Path *> *InputPath = new std::list<Path *>(*EntryFuncPath);

	std::list<Path *>::iterator iter;

#ifdef DEBUG_PATHIMPL	
	static int processNum = 0; 
	

	std::cout << "GPL input: " << std::endl;

	
	for(iter = InputPath->begin(); iter != InputPath->end(); iter++){

		(*iter)->ShowCallBBList();
		(*iter)->ShowPath();
	}
	std::cout << std::endl;
	

	std::cout << "First New for GPL" << std::endl;

#endif

	while(!IsAllCallBBProcessed(InputPath)){

#ifdef DEBUG_PATHIMPL
		std::cout << "Input Process GPL: " << std::endl;
		
		for(iter = InputPath->begin(); iter != InputPath->end(); iter++){

			(*iter)->ShowCallBBList();
			(*iter)->ShowPath();
		}
		std::cout << std::endl;
		
#endif

		GPL = ProcessCallInInputPathOnce(InputPath);
		InputPath = GPL;
		
#ifdef DEBUG_PATHIMPL
		std::cout << "Process GPL: " << processNum++ << std::endl;
	
		for(iter = GPL->begin(); iter != GPL->end(); iter++){

			(*iter)->ShowCallBBList();
			(*iter)->ShowPath();
		}
		std::cout << std::endl;
#endif		
	}

#ifdef DEBUG_PATHIMPL
	std::cout << "[GPL creator]: Successfully done! " << std::endl;
#endif		
	setNameGPL(GPL);

	return GPL;
}



bool PathImpl::IsAllCallBBProcessed(std::list<Path *> *input){

	//static int ProcessNum = 0;
	//std::cout << "ProcessNum(Checker): " << ProcessNum++ << std::endl;

	unsigned int sum = 0;
	
	std::list<Path *>::iterator iter;

	Path *current_path;

	for(iter = input->begin(); iter != input->end(); iter++){ 

		current_path = (*iter);
		sum += current_path->getNumCallBBToBeProcessed();
	}

	if(sum == 0){
#ifdef DEBUG_PATHIMPL
		std::cout << "[GPL creator]: All process is done" << std::endl;
#endif
		return true;
	}
	else{
#ifdef DEBUG_PATHIMPL
		std::cout << "[GPL creator]: The rest of process: " << sum << std::endl;
#endif
		return false;
	}


	return false;
}





