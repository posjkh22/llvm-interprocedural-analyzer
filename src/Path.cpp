
#include "Path.hpp"

/* class PathList */

PathList::PathList(std::list<Path *> *pathlist){

	//std::list<Path *> *new_pathlist = new std::list<Path *>(*pathlist);
	std::list<Path *> *new_pathlist = new std::list<Path *>;

	std::list<Path *>::iterator iter1;

	for(iter1 = pathlist->begin(); iter1 != pathlist->end(); iter1++){ 
		new_pathlist->push_back(*iter1);
	}
	
	PathListPtr = new_pathlist;
}

std::list<Path *> *PathList::getPathList(){

	return PathListPtr;
}

bool PathList::ShowPathList(){

	std::list<Path *>::iterator iter1;
	
	std::ofstream fout;
	fout.open("AnalysisPaths", std::ofstream::out | std::ofstream::app);

	for(iter1 = PathListPtr->begin(); iter1 != PathListPtr->end(); iter1++){ 

		Path *current_path = (*iter1);

		std::cout << "Path" << *(current_path->getName()) << " ";
		fout << "Path" << *(current_path->getName()) << " ";
		current_path->ShowPath();
		current_path->ShowPath(fout);
		fout << std::endl << std::endl;
	}

	fout.close();

	return true;
}


/* class Path */

/* new Path from Copy Path make new PathPtr */
Path::Path(Path *copiedPath){

	std::list<wBasicBlock *> *new_pathPtr \
		= new std::list<wBasicBlock *>(*(copiedPath->PathPtr));
	this->PathPtr = new_pathPtr;

	std::list<unsigned int>::iterator iter;

	for(iter = copiedPath->CallBBList.begin(); \
		iter != copiedPath->CallBBList.end(); iter++){

		unsigned int PassingValue = (*iter);
		this->CallBBList.push_back(PassingValue);
	}

}


Path::Path(std::list<wBasicBlock *> *path){
	setPath(path);
}

/* generally path comes from PathsList in wFunction */
/* It should not be modified */
bool Path::setPath(std::list<wBasicBlock *> *path){

	std::list<wBasicBlock *> *new_path = new std::list<wBasicBlock *>(*path);
	PathPtr = new_path;
	setCallBBList();
	return true;
}


bool Path::setName(std::string iname){

	name = new std::string(iname);
	return true; 
}

std::string *Path::getName(){
	return name;
}




std::list<wBasicBlock *> *Path::getPath(){
	return PathPtr;
}
	
bool Path::setNumCallBB(unsigned int NUM){
	NumCallBB = NUM;
	return true;
}

unsigned int Path::getNumCallBB(){
	
	std::list<wBasicBlock *>::iterator iter;
	
	unsigned int count = 0;
	for(iter = PathPtr->begin(); iter != PathPtr->end(); iter++){ 

		wBasicBlock *currentBB = (*iter);
		
		if(currentBB->hasCall()){
			count++;
		}
	}

	setNumCallBB(count);
	
	return NumCallBB;
}


bool Path::setNumCallBBToBeProcessed(unsigned int num){
	CallBBNumToBeProcessed = num;
	return true;
}

unsigned int Path::getNumCallBBToBeProcessed(){

	setNumCallBBToBeProcessed(CallBBList.size());
	return CallBBList.size();
}


bool Path::setCallBBList(){

	std::list<wBasicBlock *>::iterator iter;
	
	unsigned int count = 0;
	unsigned int numbering = 0;
	for(iter = PathPtr->begin(); iter != PathPtr->end(); iter++, numbering++){ 

		wBasicBlock *currentBB = (*iter);
		
		if(currentBB->hasCall()){
			count++;
			CallBBList.push_back(numbering);
		}
	}

	return true;
}


std::list<unsigned int> *Path::getCallBBList(){
	return &CallBBList;
}

void Path::ShowCallBBList(){

	std::list<unsigned int> *temp_CallBBNL = getCallBBList();
	std::list<unsigned int>::iterator iter;
	
	std::cout << "Show CallingBBNumbering: ";
	for(iter = temp_CallBBNL->begin(); iter != temp_CallBBNL->end(); iter++){ 

		std::cout << (*iter) << " "; 
	}
	std::cout << std::endl;
	
}

int Path::getdeleteNextNumberInCallBBList(){

	if(CallBBList.empty()){
		return -1;
	}

	unsigned int next_number;
	next_number = CallBBList.front();
	CallBBList.pop_front();

	return next_number;
}


int Path::getjustNextNumberInCallBBList(){

	if(CallBBList.empty()){
		return -1;
	}

	unsigned int next_number;
	next_number = CallBBList.front();

	return next_number;
}


wBasicBlock *Path::SearchCallBBListWithIterNumber(unsigned int numbering){

	std::list<wBasicBlock *>::iterator iter;
	std::list<wBasicBlock *> *path = getPath();

	unsigned int count = 0;

	for(iter = path->begin(); iter != path->end(); iter++, count++){

		if(count == numbering){

			break;
		}

	}

	return (*iter);
}

bool Path::deleteNextNumberInCallBBList(unsigned int Numbering){

	std::list<unsigned int> *temp_CallBBNL = getCallBBList();
	std::list<unsigned int>::iterator iter;
	
	for(iter = temp_CallBBNL->begin(); iter != temp_CallBBNL->end(); iter++){ 

		if(Numbering == (*iter)){
			CallBBList.erase(iter);
		}
	}

	return true;
}


std::list<Path *> *Path::SearchNextCallBBandReturnPath(){

	int next_callBB_number = getjustNextNumberInCallBBList();

	/* No CallBB */
	if(next_callBB_number == -1){
		return nullptr;
	}

	wBasicBlock *CallBB = SearchCallBBListWithIterNumber(next_callBB_number);

	wFunction *CallF = CallBB->getFuncCall();

	std::list<Path *> *found_function_path_list = CallF->getPATHSLIST();

	return found_function_path_list;
}

bool Path::ShowPath(){
	
	std::list<wBasicBlock *>::iterator iter;

	for(iter = PathPtr->begin(); iter != PathPtr->end(); iter++){
	
		wBasicBlock *bb = (*iter);
		
		/* why? only llvm.dbg.declare%0 ? A. non-traverse function only have one BB(%0) */
		if(*(bb->getName()) == "llvm.dbg.declare%0")
		{
			continue;
		}
		std::cout << " -> " << *(bb->getName());
	}
	std::cout << std::endl;

	return true;
}

bool Path::ShowPath(std::ofstream& fout){
	
	std::list<wBasicBlock *>::iterator iter;

	for(iter = PathPtr->begin(); iter != PathPtr->end(); iter++){
	
		wBasicBlock *bb = (*iter);

		/* why? only llvm.dbg.declare%0 ? A. non-traverse function only have one BB(%0) */
		if(*(bb->getName()) == "llvm.dbg.declare%0")
		{
			continue;
		}
		std::cout << " -> " << *(bb->getName());
		fout << " -> " << *(bb->getName());
	}
	std::cout << std::endl;

	return true;
}
