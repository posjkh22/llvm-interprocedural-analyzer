
#include "IRcodeTextDataSet.hpp"

/* IRcodeTextDataSet */
bool IRcodeTextDataSet::setEntryFunc(wFunction *wf){
	EntryFunc = wf;
	return true;
}

wFunction *IRcodeTextDataSet::getEntryFunc(){
	return EntryFunc;
}

bool IRcodeTextDataSet::pushFuncList(wFunction *f){
	wFuncList.push_back(f);
	return true;
}

std::list<wFunction *> *IRcodeTextDataSet::getwFuncList(){
	return &wFuncList;
}

wFunction* IRcodeTextDataSet::SearchFunction(Function* f){

	std::list<wFunction *> *wfunclist = getwFuncList();
	std::list<wFunction *>::iterator iter;

	for(iter = wfunclist->begin(); iter != wfunclist->end(); iter++){
		if( (*iter)->getFunction() == f){
			//std::cout << "Target Func Find! ";
			break;
		}
	}
	return (*iter);
}

wFunction* IRcodeTextDataSet::SearchFunction(const std::string &name){

	std::list<wFunction *> *wfunclist = getwFuncList();
	std::list<wFunction *>::iterator iter;
	for(iter = wfunclist->begin(); iter != wfunclist->end(); iter++){
		if( (*iter)->getFunction()->getName().str() == name){
			break;
		}
	}
	return (*iter);
}


bool IRcodeTextDataSet::ShowPathsInEachFunc(){

	std::list<wFunction *> *TraverseFuncList = getwFuncList();
	std::list<wFunction *>::iterator iter;

	for(iter = TraverseFuncList->begin(); iter != TraverseFuncList->end(); iter++){
		(*iter)->showPathsList();	
	}
	return true;

}
	
std::list<std::list<wBasicBlock *> *> *IRcodeTextDataSet::getGlobalPathsList(){
	return &GlobalPathsList;
}

bool IRcodeTextDataSet::ShowTempPathsList(std::list<std::list<wBasicBlock *> *> *PathsList){

	std::list<std::list<wBasicBlock *> *>::iterator iter1;
	std::list<wBasicBlock *>::iterator iter2;

	for(iter1 = PathsList->begin(); iter1 != PathsList->end(); iter1++){
		
		std::cout << "PATH: ";
		for(iter2 = (*iter1)->begin(); iter2 != (*iter1)->end(); iter2++){

			std::cout << *((*iter2)->getName()) << " ";
		}
		std::cout << std::endl;
	}

	return true;
}

bool IRcodeTextDataSet::insertPath(std::list<std::list<wBasicBlock *> *> **pResult, std::list<wBasicBlock *> *Target, wBasicBlock *CallBB, std::list<std::list<wBasicBlock *> *> *Inserted){

	std::list<wBasicBlock *> *CurrentPath; 
	std::list<wBasicBlock *>::iterator iter1;
	std::list<wBasicBlock *>::iterator iter2;
	std::list<std::list<wBasicBlock *> *>::iterator iter3;

	std::list<std::list<wBasicBlock *> *> *Result;
	Result = new std::list<std::list<wBasicBlock *> *>;

	for(iter3 = Inserted->begin(); iter3 != Inserted->end(); iter3++){

		std::list<wBasicBlock *> *NewPath = new std::list<wBasicBlock *>;
		CurrentPath = (*iter3);

		std::list<wBasicBlock *>::iterator NextIter;

		for(iter1 = Target->begin(); iter1 != Target->end(); iter1++){
			if( (*iter1) != CallBB){
				NewPath->push_back(*iter1);
			}
			else{
				NewPath->push_back(*iter1);
				NextIter = ++iter1;
				break;
			}
		}
		for(iter2 = (*iter3)->begin(); iter2 != (*iter3)->end(); iter2++){

			NewPath->push_back(*iter2);

		}
		for(iter1 = NextIter; iter1 != Target->end(); iter1++){
			NewPath->push_back(*iter1);
		}

		Result->push_back(NewPath);
	}

	(*pResult) = Result;
	return true;
}


std::list<wBasicBlock *>::iterator IRcodeTextDataSet::SearchwBlock(std::list<wBasicBlock *> *TargetPath, wBasicBlock *BB){

	std::list<wBasicBlock *>::iterator iter;
	for(iter = TargetPath->begin(); iter != TargetPath->end(); iter++){ 

		if(BB == (*iter)){			
			break;
		}
	}

	return iter;
}



bool IRcodeTextDataSet::makeGlobalPathsList(std::list<std::list<wBasicBlock *> *> *insertedPathList){

#ifdef DD

	std::list<std::list<wBasicBlock *> *> *gpl = getGlobalPathsList();
	std::list<std::list<wBasicBlock *> *> *currentPathList;
	std::list<wBasicBlock *> *currentPath;
	std::list<std::list<wBasicBlock *> *> *tempPathList;
	std::list<wFunction *> *CallFuncList;

	

	std::list<std::list<wBasicBlock *> *>::iterator iter1;
	std::list<wBasicBlock *>::iterator iter2;
	std::list<wFunction *>::iterartor iter3;


	wBasicBlock *CallBB;
	wFunction *CalleeFunc;
	
	/* Entry Function */
	
	if(gpl->empty()){

		currentPathList = getEntryFunc()->getPathsList();

		for(iter1 = currentPathList->begin(); iter1 != currentPathList->end(); iter1++){
		
			//itempPath = new std::list<std::list<wBasicBlock *> *>;
			//tempPath->push_back(*(iter1));			
			gpl->push_back(*(iter1));
		}

	}

	else{
		
		while(tempPathList->empty()){
			currentPath = tempPathList->front();
			currentPath = tempPathList->pop_front();




	}

	else{
		std::list<std::list<wBasicBlock *> *> *tempPathList;
		tempPathList = new std::list<std::list<wBasicBlock *> *>(*gpl);
		
		while(tempPathList->empty()){
			currentPath = tempPathList->front();
			currentPath = tempPathList->pop_front();
			
			for(iter2 = currentPath->begin(); iter2 != currentPath->end(); iter2++){
				
				if((*iter2)->hasCall()){

					CallBB = (*iter2);
					CallFuncList = CallBB->getFuncCallList();
					iter3 = CallFuncList->begin();
					CalleeFunc = (*iter3);


					std::list<std::list<wBasicBlock *> *> *ResultPath;
					insertPath(ResultPath, currentPath, insertedPathList);


	}


	else{
		std::list<std::list<wBasicBlock *> *> *temp_insertedPathList;
		tempPathList = new std::list<std::list<wBasicBlock *> *>(*gpl);
		std::list<std::list<wBasicBlock *> *> *ResultPath;
			
		while(tempPathList->empty()){
			currentPath = tempPathList->front();
			currentPath = tempPathList->pop_front();

			for(iter2 = currentPath->begin(); iter2 != currentPath->end(); iter2++){
			
				if((*iter2)->hasCall()){

					CallBB = (*iter2);
					CallFuncList = CallBB->getFuncCallList();
					iter3 = CallFuncList->begin();
					CalleeFunc = (*iter3);
					temp_insertedPathList = calleeFunc->getPathList();

					insertPath(ResultPath, currentPath, temp_insertedPathList);
			
					gpl->push_back(ResultPath);

				}


			}
		}


	}


	tempPath->

	currentPath = insertedPath;
	
	for(iter1 = currentPath->begin(); iter1 != currentPath->end(); iter1++){


		for(iter2 = (*iter1)->begin(); iter2 != (*iter1)->end(); iter2++){

			if((*iter2)->hasCall){

				CallBB = (*iter2);
				CallFuncList = CallBB->getFuncCallList();
				iter3 = CallFuncList->begin();
				CalleeFunc = (*iter3);

				inertPath( , gpl, CallBB, insertedPath, CalleeFunc->getPathsList());
			}
		
		}


	}

#endif

	return true;
}

