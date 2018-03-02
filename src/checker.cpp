
#include "checker.hpp"


//#define DEBUG_CHECKER				

bool Checker::setCheckerTy(Checker::checker_ty ty){
	type = ty;
	return true;
}


/* checker creator */

Checker::Checker(PathList *pathlist){

	if(attachPathList(pathlist)){
		std::cout << "Checker(PathList) create! " << std::endl;
	}
}

Checker::Checker(Path *path){

	if(attachPath(path)){
		std::cout << "Checker(Path) create! " << std::endl;
	}

}


/* PathList */

bool Checker::attachPathList(PathList *pathlist){


	setCurrentPathList(pathlist);

	Path *entry_path = pathlist->getPathList()->front();

	setCurrentPath(entry_path);

	wBasicBlock *entry_BB = entry_path->getPath()->front();

	setCurrentBB(entry_BB);

	/*
	   More specific to Target
	*/

	return true;
}

bool Checker::setCurrentPathList(PathList *pathlist){

	currentPathList = pathlist;

	return true;
}


PathList *Checker::getCurrentPathList(){

	return currentPathList;
}


/* 
   	In this function, 
	Implement movePath at the end of PathList
	is Not considered(also return false).

*/
bool Checker::movePath(){

	PathList *currentPathList = getCurrentPathList();

	std::list<Path *>::iterator iter;
	std::list<Path *> *CurrentPathList = currentPathList->getPathList();

	int found_flag = 0;

	for(iter = CurrentPathList->begin(); 
			iter != CurrentPathList->end(); iter++){

		Path *currentPath = (*iter);

		/* if found, break when next iter */
		if(currentPath == getCurrentPath()){

			found_flag = 1;
			iter++;
			break;
		}
	}

	/* No found */
	if(!found_flag){
		return false;
	}

	/* update currentPath */
	return setCurrentPath(*iter);
}

bool Checker::setCheckerState(){

	reset_flag = 1;
	return true;
}

bool Checker::ResetCheckerState(){


	if(ResetCheckerVariable() == true
		&& ResetTraceValState() == true
		&& ResetPassingReturnVal() == true
		&& ResetPassingArgument() == true){

		return true;
	}
	else{

		return false;
	}
}


bool Checker::ResetCheckerVariable(){

	trace_flag = 0;
	trace_new_func_flag = 0;
	reset_flag = 1;	

	return true;
}


bool Checker::ResetTraceValState(){

	if(traceValState.empty() == true){

		return true;
	}
	else{

		int num = traceValState.size();
		for(int i = 0 ; i < num; i++){
			traceValState.pop_front();
		}

		return true;
	}

}
	
bool Checker::ResetPassingReturnVal(){
	
	if(PassingReturnVal.empty() == true){

		return true;
	}
	else{

		int num = PassingReturnVal.size();
		for(int i = 0 ; i < num; i++){
			PassingReturnVal.pop_front();
		}

		return true;
	}

}

bool Checker::ResetPassingArgument(){
	
	if(PassingArgument.empty() == true){

		return true;
	}
	else{

		int num = PassingArgument.size();
		for(int i = 0 ; i < num; i++){
			PassingArgument.pop_front();
		}

		return true;
	}

}


/* Path */

bool Checker::attachPath(Path *path){

	setCurrentPath(path);
	
	wBasicBlock *entry_BB = path->getPath()->front();

	setCurrentBB(entry_BB);
	
	/*

	More specific to Target

	*/

	return true;
}


bool Checker::setCurrentPath(Path *path){

	currentPath = path;

	return true;
}


Path *Checker::getCurrentPath(){

	return currentPath;
}

bool Checker::move(){

	Path *currentPath = getCurrentPath();
	
	std::list<wBasicBlock *> *CurrentPath = currentPath->getPath();

	std::list<wBasicBlock *>::iterator iter;
	
	int found_flag = 0;

	for(iter = CurrentPath->begin(); 
			iter != CurrentPath->end(); iter++){

		wBasicBlock *currentBB = (*iter);

		if(currentBB == getCurrentBB()){
			found_flag = 1;
			iter++;
			break;
		}
	}

	if(!found_flag){
		return false;
	}

	return setCurrentBB(*iter);
}


/* BB */

wBasicBlock *Checker::getCurrentBB(){

	return currentBB;
}

bool Checker::setCurrentBB(wBasicBlock *BB){
	
	currentBB = BB;
	return true;
}

wBasicBlock *Checker::getNextBB(){

	Path *currentPath = getCurrentPath();
	
	std::list<wBasicBlock *> *CurrentPath = currentPath->getPath();

	std::list<wBasicBlock *>::iterator iter;
	
	int found_flag = 0;

	for(iter = CurrentPath->begin(); 
			iter != CurrentPath->end(); iter++){

		wBasicBlock *currentBB = (*iter);

		if(currentBB == getCurrentBB()){
			found_flag = 1;
			iter++;
			break;
		}
	}

	if(!found_flag){
		return nullptr;
	}

	return (*iter);

}





unsigned int Checker::check_checker_state_flag(){

	unsigned int sumAbsolValue = 0;

	for(auto iter = traceValState.begin();
			iter != traceValState.end(); iter++){

		TraceData *current = (*iter);

		sumAbsolValue += std::abs(*(current->checker_state_flag));
	}

	return sumAbsolValue;

}



bool Checker::BugReport(){

	/* trace_flag check */
	/* if the value is not set, the error is detected */

	std::ofstream fout;
	fout.open("AnalysisResults", std::ofstream::out | std::ofstream::app);

	if(check_checker_state_flag() != 0 
			&& ((type == Checker::checker_ty::FilePointerAnalysisC) || (type == Checker::checker_ty::MemoryAllocationC))){

		std::cout << "[Checker: Error Detected]" << std::endl;
		fout << "[Checker: Error Detected]" << std::endl;

		for(auto iter = traceValState.begin();
				iter != traceValState.end(); iter++){

			TraceData *current = (*iter);
			
			if(*(current->checker_state_flag) < 0 
					&& current->bug_location_flag == 1){
				
				if(type == Checker::checker_ty::FilePointerAnalysisC){
					std::cout << " - FILE Double close";
					fout << " - FILE Double close";
				}
				else if(type == Checker::checker_ty::MemoryAllocationC){
					std::cout << " - Improper free";
					fout << " - Improper free";
				}
				std::cout << "(" << current->traceVal << "/";
				std::cout << *(current->checker_state_flag) << "/";
				std::cout << current->f->getName().str() << "/";
				std::cout << current->bug_location_flag << "/";
				std::cout << current->unique_number << ")"; 
				std::cout << std::endl;
				
				fout << "(" << current->traceVal << "/";
				fout << *(current->checker_state_flag) << "/";
				fout << current->f->getName().str() << "/";
				fout << current->bug_location_flag << "/";
				fout << current->unique_number << ")"; 
				fout << std::endl;
				
				
				m_BugReport->AddBugLocation(current->Location);
				m_BugReport->showBugLocation(current->Location, fout);
				
				fout << " - BasicBlock: " << *(current->LocationBB->getName());
				fout << std::endl << std::endl;
			}

			/*
			if(*(current->checker_state_flag) > 0 
				|| ( (*(current->checker_state_flag) > 0 
					&& current->bug_location_flag == 1) )
			*/

			if(( (*(current->checker_state_flag) > 0 
					&& current->bug_location_flag == 1) )
				
				){

				if(type == Checker::checker_ty::FilePointerAnalysisC){
					std::cout << " - FILE is Not close";
					fout << " - FILE is Not close";
				}
				else if(type == Checker::checker_ty::MemoryAllocationC){
					std::cout << " - Allocated Memory is Not freed";
					fout << " - Allocated Memory is Not freed";
				}
				std::cout << "(" << current->traceVal << "/";
				std::cout << *(current->checker_state_flag) << "/";
				std::cout << current->f->getName().str() << "/";
				std::cout << current->bug_location_flag << "/";
				std::cout << current->unique_number;
				std::cout << ")";
				std::cout << std::endl;
				
				fout << "(" << current->traceVal << "/";
				fout << *(current->checker_state_flag) << "/";
				fout << current->f->getName().str() << "/";
				fout << current->bug_location_flag << "/";
				fout << current->unique_number;
				fout << ")";
				fout << std::endl;
				
				m_BugReport->AddBugLocation(current->Location);	
				m_BugReport->showBugLocation(current->Location, fout);

				fout << " - BasicBlock: " << *(current->LocationBB->getName());
				fout << std::endl << std::endl;
			}

		}

	}
	/* If error is not found */
	else{
		std::cout << "[No Error Code was Found] " << std::endl;
		fout << "[No Error Code was Found] " << std::endl;
	}

	fout.close();

	return true;
}


bool Checker::check(PathList *pathlist){


	attachPathList(pathlist);

	PathList *targetPathlist = getCurrentPathList();

	std::list<Path *>::iterator iter;
	std::list<Path *> *TargetPathList;

	TargetPathList = targetPathlist->getPathList();

	for(iter = TargetPathList->begin();
			iter != TargetPathList->end(); iter++){

		Path* currentPath = (*iter);
		check(currentPath);
	}

	return true;
}

bool Checker::check(Path *path){

	std::ofstream fout;
	fout.open("AnalysisResults", std::ofstream::out | std::ofstream::app);
	
	std::cout << std::endl;
	std::cout << "[Checker is running on Path ";
	std::cout << *(path->getName());
	std::cout << "..]" << std::endl;
	
	fout << "[Checker is running on Path ";
	fout << *(path->getName());
	fout << "..]" << std::endl;

	fout.close();

	/* Initialize CheckerState */
	setCheckerState();

	attachPath(path);

	Path *targetPath = getCurrentPath();

	std::list<wBasicBlock *>::iterator iter;
	std::list<wBasicBlock *> *TargetPath;

	TargetPath = targetPath->getPath();

	for(iter = TargetPath->begin();
			iter != TargetPath->end(); iter++){

		wBasicBlock *currentBB = (*iter);
		check(currentBB);	
	}
	
	std::cout << "[Path ";
	std::cout << *(currentPath->getName());
	std::cout << "]";

	BugReport();
		
	/* Reset Checker State */	
	if(ResetCheckerState() == true){

#ifdef DEBUG_CHECKER				
		std::cout << "Checker state is reset" << std::endl;
#endif
	}
	else{
#ifdef DEBUG_CHECKER				
		std::cout << "[ERROR] Checker state is not reset" << std::endl;
#endif
	}
	

	return true;
}

Checker::Checker(IPA::BugReport *bugReport, IPA::ArgumentPass *argument)
{
	trace_flag = 0;
	trace_new_func_flag = 0;
	basic_checker_state_flag = 0;
	reset_flag = 1;
	//checker_state_flag = 0;
	//traceVal = nullptr;
	m_BugReport = bugReport;
	m_ArgumentPass = argument;

	checkerTyDetermination();
};


bool Checker::checkerTyDetermination()
{
	if(m_ArgumentPass->getArgument()->getAnalysisTy() 
			== IPA::Argument::analysisTy::MemoryAllocationC)
	{
		setCheckerTy(Checker::checker_ty::MemoryAllocationC);	
	}
	else if(m_ArgumentPass->getArgument()->getAnalysisTy() 
			== IPA::Argument::analysisTy::FilePointerAnalysisC)
	{
		setCheckerTy(Checker::checker_ty::FilePointerAnalysisC);	
	}
	else if(m_ArgumentPass->getArgument()->getAnalysisTy() 
			== IPA::Argument::analysisTy::Deadlock)
	{
		setCheckerTy(Checker::checker_ty::Deadlock);	
	}
	else if(m_ArgumentPass->getArgument()->getAnalysisTy() 
			== IPA::Argument::analysisTy::SemaphoreIntegrity)
	{
		setCheckerTy(Checker::checker_ty::SemaphoreIntegrity);	
	}
	else if(m_ArgumentPass->getArgument()->getAnalysisTy() 
			== IPA::Argument::analysisTy::SharedVariables)
	{
		setCheckerTy(Checker::checker_ty::SharedVariables);	
	}
	else if(m_ArgumentPass->getArgument()->getAnalysisTy() 
			== IPA::Argument::analysisTy::SharedFunctions)
	{
		setCheckerTy(Checker::checker_ty::SharedFunctions);	
	}
	else 
	{
		setCheckerTy(Checker::checker_ty::UnknownCheckerTy);	
		return false;
	}

	return true;
}


bool Checker::check(wBasicBlock *BB){

	std::list<wInstruction *>::iterator iter;
	std::list<wInstruction *> *InstList;


	InstList = BB->getwInstList();

	for(iter = InstList->begin();
			iter != InstList->end(); iter++){

		wInstruction *currentInst = (*iter);

		/* checker set */
		//check1(BB, currentInst);
		//check2(BB, currentInst, comp_gv);
		//check3(BB, currentInst, comp_gv);
		//setCheckerTy(Checker::checker_ty::FilePointerAnalysisC);
		//check4(BB, currentInst); 
		//setCheckerTy(Checker::checker_ty::MemoryAllocationC);
		check5(BB, currentInst); 
	}

	return true;
}


/* checker set */

bool Checker::check1(wBasicBlock *BB, wInstruction *Inst){

	llvm::Instruction *bare_inst = Inst->getInstruction();

	if(bare_inst->getOpcodeName() == std::string("call")){
		std::cout << *(BB->getName()) << " ";
		std::cout << "[CheckF: " << bare_inst->getOpcodeName() << "]" << std::endl;
	}

	return true;
}


bool Checker::check2(wBasicBlock *BB, wInstruction *Inst, GlobalVariable *gv){
	
	llvm::Instruction *bare_inst = Inst->getInstruction();

	if(bare_inst->getOpcodeName() == std::string("store")){
		

		for(unsigned int i = 0; i < bare_inst->getNumOperands(); i++){
			if(bare_inst->getOperand(i) == reinterpret_cast<Value *>(gv)){
			
				std::cout << i <<": ";
				std::cout << *(BB->getName()) << " ";
				std::cout << "[CheckF: " << bare_inst->getOpcodeName() << "]";
				std::cout << " " << gv->getName().str() << std::endl;
			}
		}
	}
	
	return true;
}

bool Checker::check3(wBasicBlock *BB, wInstruction *Inst, GlobalVariable *gv){
	
	llvm::Instruction *bare_inst = Inst->getInstruction();

	if(bare_inst->getOpcodeName() == std::string("store")){
		

		for(unsigned int i = 0; i < bare_inst->getNumOperands(); i++){
			if(bare_inst->getOperand(i) == reinterpret_cast<Value *>(gv)){
			
				std::cout << i <<": ";
				std::cout << *(BB->getName()) << " ";
				std::cout << "[CheckF: " << bare_inst->getOpcodeName() << "]";
				std::cout << " " << gv->getName().str() << std::endl;

				std::cout << "size: " << bare_inst->getNumOperands() << std::endl;
				std::cout << "0: " << bare_inst->getOperand(0) << std::endl;

				Value *load_val = bare_inst->getOperand(0);
				llvm::Instruction *load_inst = reinterpret_cast<llvm::Instruction *>(load_val);
				std::cout << load_inst->getOpcodeName() << std::endl;			

			}
		}
	}
	return true;
}


Checker::TraceData *Checker::SearchTraceVal(unsigned int iter_count){

	unsigned int count = 0;
	int found_flag = 0; 
	
	std::list<Checker::TraceData *>::iterator iter;

	for(iter = traceValState.begin();
			iter != traceValState.end(); iter++, count++){

		if(count == iter_count){
			found_flag = 1;
			break;
		}

	}

	if(found_flag == 0){

		return nullptr;
	}

	return (*iter);

}

/* Backward search: C lang is run sequentially. */
Checker::TraceData *Checker::SearchTraceVal(llvm::Value *cmp_val){

	std::list<TraceData *>::reverse_iterator iter;

	int found_flag = 0;

	for(iter = traceValState.rbegin(); 
			iter !=traceValState.rend(); iter++){

		if( (*iter)->traceVal == cmp_val){
			found_flag = 1;
			break;
		}

	}

	if(found_flag == 0){
		return nullptr;
	}

	return (*iter);
}


bool Checker::ShowTraceData(){

	int i = 1;
	for(auto iter = traceValState.begin();
			iter != traceValState.end(); iter++, i++){

		TraceData *current = *iter;

		std::cout << "[" << std::setw(2) << i << "] ";
		std::cout << "(" << current->traceVal << "/";
		std::cout << std::setw(2) << *(current->checker_state_flag) <<"/";
		std::cout << current->f->getName().str() <<  "/"; 
		std::cout << current->bug_location_flag << "/";
		std::cout << current->unique_number << ") ";

		if(i != 0 && i %3 == 0){
			std::cout << std::endl;
		}

	}
	std::cout << std::endl;
	return true;
}

bool Checker::ShowPassingReturnVal(){

	int i = 1;
	for(auto iter = PassingReturnVal.begin();
			iter != PassingReturnVal.end(); iter++, i++){

		TraceData *current = *iter;

		std::cout << "ShowPassingReturnVal" << std::endl;
		std::cout << "[" << std::setw(2) << i << "] ";
		std::cout << "(" << current->traceVal << "/";
		std::cout << std::setw(2) << *(current->checker_state_flag) <<"/";
		std::cout << current->f->getName().str() <<  "/"; 
		std::cout << current->bug_location_flag << ") ";

		if(i != 0 && i %3 == 0){
			std::cout << std::endl;
		}

	}
	std::cout << std::endl;
	return true;
}

bool Checker::deleteTraceValwithReturn(llvm::Function *fid){

	
	std::list<TraceData *>::iterator iter;

	iter = traceValState.begin();
	while(iter != traceValState.end()){
		
		TraceData *current = (*iter);
		/* 
		   	if checker_state_flag is Not normal, 
		 	leave the traceVal.
		*/
		if(current->f == fid  
			&& !(*(current->checker_state_flag) > 0
				|| *(current->checker_state_flag) < 0)		
				
			){
#ifdef DEBUG_CHECKER				
			std::cout << "[TraceData DEL]: ";
			std::cout << "(" << current->traceVal << "/";
			std::cout << *(current->checker_state_flag) <<"/";
			std::cout << current->f->getName().str() << ")";
			std::cout << std::endl;
#endif
			traceValState.erase(iter++);
		}
		else{
			++iter;
		}
		
	}
	return true;
}

bool Checker::setBugLocationFlag(llvm::Function *fid){

	
	std::list<TraceData *>::iterator iter;

	iter = traceValState.begin();
	while(iter != traceValState.end()){
		
		TraceData *current = (*iter);
		/* 
		   	if checker_state_flag is Not normal, 
		 	leave the traceVal.
		*/
		if(current->f == fid  
			&& (*(current->checker_state_flag) > 0)
//			&& (*(current->checker_state_flag) > 0
//				|| *(current->checker_state_flag) < 0)		
				
			){
			current->bug_location_flag = 1;
#ifdef DEBUG_CHECKER				
			std::cout << "[SetBugLocationFlag]: ";
			std::cout << "(" << current->traceVal << "/";
			std::cout << *(current->checker_state_flag) <<"/";
			std::cout << current->f->getName().str() << ")";
			std::cout << std::endl;
#endif
		}
		
		++iter;
	}
	return true;
}


bool Checker::check4(wBasicBlock *BB, wInstruction *Inst){
	

	return true;
}

bool Checker::check5(wBasicBlock *BB, wInstruction *Inst){
	
	int arg = -1; 
	
	if(Inst->getInstruction()->getOpcodeName() == std::string("br")){	
		/* Do not consider "br" instruction */
		//std::cout << "BR" << std::endl;
		return true;
	}


	/* Before starting trace, if there is improper free instruction */
	if(Inst->getInstruction()->getOpcodeName() == std::string("call")){		
		
		llvm::Instruction *bare_inst = Inst->getInstruction();
		Value *get_opnd = bare_inst->getOperand(bare_inst->getNumOperands() - 1);			
		
		/* if free is found */
		if(get_opnd->getName().str() == std::string("free")){
#ifdef DEBUG_CHECKER				
			std::cout << "[First Free]: ";
			std::cout << get_opnd->getName().str() << std::endl;
#endif
		
			#define FFREE_FP_ARG 0
			
#ifdef DEBUG_CHECKER				
			std::cout << "PASSING: (";
			std::cout << bare_inst->getOperand(FFREE_FP_ARG);
			std::cout << ")" << std::endl;
#endif
			TraceData *returnIterPtr
				= SearchTraceVal(bare_inst->getOperand(FFREE_FP_ARG));			
			if(returnIterPtr == nullptr){
#ifdef DEBUG_CHECKER				
				std::cout << "Not allocated Memory is freed" << std::endl;
#endif					
				Value *new_traceVal = bare_inst->getOperand(FFREE_FP_ARG);
				llvm::Function *fid = BB->getParentFunction();	
				int *checker_state_flag = new int(-1);;		

				TraceData *new_trace_data
					= new TraceData(new_traceVal, checker_state_flag, fid);	

				new_trace_data->LocationBB = BB;
				new_trace_data->Location = bare_inst;
				new_trace_data->bug_location_flag = 1;
				new_trace_data->unique_number = -1;
				traceValState.push_back(new_trace_data);

			}
			else{
				/* blank */
			}

			#undef FFREE_FP_ARG
			
		}
		else{
			/* blank */
		}
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


	if(Inst->getInstruction()->getOpcodeName() == std::string("call")){		
		
		llvm::Instruction *bare_inst = Inst->getInstruction();
		
		Value *get_opnd = bare_inst->getOperand(bare_inst->getNumOperands() - 1);
		/* if malloc is found */
		if(get_opnd->getName().str() == std::string("malloc")){
			
			/* First malloc */
			if(traceValState.empty() == true){
				Value *traceVal = reinterpret_cast<llvm::Value *>(bare_inst);
				int *checker_state_flag = new int(1);	
				llvm::Function *fid = BB->getParentFunction();

				TraceData *trace_data
					= new TraceData(traceVal, checker_state_flag, fid);
			
				trace_data->setUniqueNumber(this);

				trace_data->LocationBB = BB;
				trace_data->Location = bare_inst;
				traceValState.push_back(trace_data);
				trace_flag = 1;
#ifdef DEBUG_CHECKER				
				std::cout << "[New malloc]";
				std::cout << trace_data->traceVal << std::endl;
				ShowTraceData();
#endif	
			}
			/* After the second malloc */
			else{
				Value *traceVal = reinterpret_cast<llvm::Value *>(bare_inst);
				
				/* not found & new insert */
				TraceData *returnIterPtr
					= SearchTraceVal(traceVal);

				if(nullptr == returnIterPtr){
					llvm::Function *fid = BB->getParentFunction();
					int *checker_state_flag = new int(1);	
					
					TraceData *trace_data
						= new TraceData(traceVal, checker_state_flag, fid);				
				
					trace_data->setUniqueNumber(this);
			
					trace_data->LocationBB = BB;
					trace_data->Location = bare_inst;
					traceValState.push_back(trace_data);
					trace_flag = 1;
#ifdef DEBUG_CHECKER				
					std::cout << "[New malloc]";
					std::cout << trace_data->traceVal << std::endl;
					ShowTraceData();					
#endif
				}
				
				else{
				
					/* If double open, */
					TraceData *get_trace_data = returnIterPtr;
					*(get_trace_data->checker_state_flag) += 1;
					get_trace_data->bug_location_flag = 1;

					//std::cout << "Double open: (";
					//std::cout << get_trace_data->traceVal << ")";
					//std::cout << std::endl;
					//trace_flag = 0;
				}

			}
		
		}
	}
	
	//if(traceVal != nullptr){
	if(traceValState.empty() == false){

#ifdef DEBUG_CHECKER				
		ShowTraceData();
#endif
	}


	/* if treace_flag == 1 */
	if(trace_flag == 1){
		
		llvm::Instruction *bare_inst = Inst->getInstruction();

		if(trace_new_func_flag == 1){
			
			if(PassingArgument.empty() == false){

				llvm::BasicBlock *bb = BB->getBasicBlock();
				llvm::Function *f = bb->getParent();	
#ifdef DEBUG_CHECKER				
				std::cout << "[Jump to " << f->getName().str() << "]" << std::endl;
#endif
				int tmp_count = 0;

				std::list<llvm::Argument *> temp_arg_list;
				llvm::Argument *argument;

#ifdef DEBUG_CHECKER				
				std::cout << "Func Argument size: (" << f->arg_size() << ") ";
				std::cout << "Passing  Argument size: (" << PassingArgument.size() << ")" << std::endl;
#endif
				for(auto iter = f->arg_begin(); 
						iter != f->arg_end(); iter++, tmp_count++){

					for(auto iter2 = PassingArgument.begin();
							iter2 != PassingArgument.end(); iter2++){

						arg = (*iter2)->number;				
						//arg = PassingArgument.front();
						//PassingArgument.pop_front();

						if(tmp_count == arg){
							argument = &(*iter);
							temp_arg_list.push_back(argument);
#ifdef DEBUG_CHECKER				
							std::cout << "Func Argument (" << argument << ")"  << std::endl;
#endif
						}
					}
				}

				/*
				   	Always
					tem_arg_list.size() >= PassingArgument.size()
	

				*/

				unsigned int tmp_count2 = 0;
				for(auto iter = temp_arg_list.begin();
						iter != temp_arg_list.end(); iter++, tmp_count2++){

					llvm::Argument *passArg = *iter;

					unsigned int passIter = PassingArgument.front()->number;
					
					if(tmp_count2 == passIter){

						//Checker::Argument *argu = PassingArgument.front();


						TraceData *returnIterPtr
							= SearchTraceVal(PassingArgument.front()->traceVal);
						
						//TraceData *returnIterPtr
						//	= SearchTraceVal(passIter);
						
						if(returnIterPtr == nullptr){
#ifdef DEBUG_CHECKER				
							std::cout << "Something Wrong!" << std::endl;
#endif
							PassingArgument.pop_front();
							continue;
						}
						else{


							PassingArgument.pop_front();
							
							int *checker_state_flag 
								= returnIterPtr->checker_state_flag;
							
							int unique_number 
								= returnIterPtr->unique_number;
							
							Value *new_traceVal	
								= reinterpret_cast<Value *>(passArg);
						
							llvm::Function *fid = BB->getParentFunction();

							TraceData *new_trace_data 
								= new TraceData(new_traceVal, checker_state_flag, fid, unique_number);
							new_trace_data->LocationBB = BB;
							new_trace_data->Location = bare_inst;
							traceValState.push_back(new_trace_data);
								
										
							//returnIterPtr->traceVal
							//	= reinterpret_cast<Value *>(passArg);
						}

					}
					
					else{
						continue;
					}

					//Argument *passArg = temp_arg_list.front();
					//temp_arg_list.pop_front();
					//traceVal = reinterpret_cast<Value *>(passArg);
				}
				
				trace_new_func_flag = 0;



			}
			/* No argument */
			else{

#ifdef DEBUG_CHECKER				
				std::cout << "Need to be considered" << std::endl;
#endif
				trace_new_func_flag = 0;
			}		

		}

		if(bare_inst->getOpcodeName() == std::string("ret")){		

			llvm::Function *fid = BB->getParentFunction();
#ifdef DEBUG_CHECKER				
			std::cout << "[RET from ";
			std::cout << fid->getName().str(); 
			std::cout << "] ";
#endif
			/* Pass ReturnVal */
			if(bare_inst->getNumOperands() != 0){

				/* return Not Void */

				#define RET_OPERAND_ITER 0
#ifdef DEBUG_CHECKER				
				std::cout << bare_inst->getOperand(RET_OPERAND_ITER) << std::endl;
#endif
				TraceData *returnIterPtr
					= SearchTraceVal(bare_inst->getOperand(RET_OPERAND_ITER));
			
				if(returnIterPtr == nullptr){
#ifdef DEBUG_CHECKER				
					std::cout <<"[No Pass] "<< std::endl;
#endif	
				}

				else{
				
					Value* new_traceVal = reinterpret_cast<Value *>(bare_inst);
					llvm::Function *fid = BB->getParentFunction();	
					int *checker_state_flag = returnIterPtr->checker_state_flag;		
					int unique_number = returnIterPtr->unique_number;		
					
#ifdef DEBUG_CHECKER				
					std::cout <<"[Pass] " << new_traceVal << std::endl;
#endif
					TraceData *trace_data
						= new TraceData(new_traceVal, checker_state_flag, fid, unique_number);	
					trace_data->LocationBB = BB;
					trace_data->Location = bare_inst;
					traceValState.push_back(trace_data);

					/* Transfer TraceData */
					/* 1. get PassingReturnVal element(TraceData1) & remove it from PassingReturnVal  */
					/* 2. get TraceValState last element(TraceData2) & remove it from TraceValState */
					/* 3. copy TraceData2 to TraceData1 */
					/* 4. Insert the updated TraceData1 to TraceValState */
					/* Delete PassingRetunVal element & insert TraceValState element */
					

#ifdef DEBUG_CHECKER				
					ShowPassingReturnVal();
#endif					
					wFunction *f = BB->getParent();
					if(f->getFuncRetTy() == wFunction::FuncRetTy::NonVoidTy){
						

						TraceData *new_trace_data 
							= PassingReturnVal.back();
						PassingReturnVal.pop_back();

						if(new_trace_data == nullptr){
							std::cout << "RET ERROR1" << std::endl;
						}

						TraceData *ret_trace_data
							= traceValState.back();
						if(ret_trace_data == nullptr){
							std::cout << "RET ERROR2" << std::endl;
						}

						traceValState.pop_back();
						
						new_trace_data->checker_state_flag
							= ret_trace_data->checker_state_flag;
						new_trace_data->bug_location_flag
							= ret_trace_data->bug_location_flag;
						new_trace_data->unique_number
							= ret_trace_data->unique_number;

						traceValState.push_back(new_trace_data);
					

					}
					else{
							std::cout << "RET ERROR3" << std::endl;
					}
					

				}
				#undef RET_OPERAND_ITER


			}

			else{
				/* return Void */
				

#ifdef DEBUG_CHECKER				
				std::cout << std::endl;
#endif
			}


			/* Detach tracer: main function or task function */
			//if(fid->getName().str() != "main"){

			if(fid->getName().str() == "main" 
					|| fid->getName().str() == "task1"					
					|| fid->getName().str() == "task2"					
				){

				setBugLocationFlag(fid);
			}
			else{
				
				deleteTraceValwithReturn(fid);
				/* blank */
			}

			return true;
		}
		else if(Inst->getInstruction()->getOpcodeName() == std::string("br")){	
			/* Do not consider "br" instruction */
#ifdef DEBUG_CHECKER				
			std::cout << "[BR]: SOMETHING WRONG!" << std::endl;
#endif
			return true;
		}

		else if(bare_inst->getOpcodeName() == std::string("call")){		
			Value *get_opnd = bare_inst->getOperand(bare_inst->getNumOperands() - 1);			
			/* if free is found */
			if(get_opnd->getName().str() == std::string("free")){
			
				#define FFREE_FP_ARG 0
				
#ifdef DEBUG_CHECKER				
				std::cout << "PASSING: (";
				std::cout << bare_inst->getOperand(FFREE_FP_ARG);
				std::cout << ")" << std::endl;
#endif
				TraceData *returnIterPtr
					= SearchTraceVal(bare_inst->getOperand(FFREE_FP_ARG));			
				if(returnIterPtr == nullptr){
#ifdef DEBUG_CHECKER				
					std::cout << "Not allocated Memory is freed" << std::endl;
#endif					
					Value *new_traceVal = bare_inst->getOperand(FFREE_FP_ARG);
					llvm::Function *fid = BB->getParentFunction();	
					int *checker_state_flag = new int(-1);;		

					TraceData *new_trace_data
						= new TraceData(new_traceVal, checker_state_flag, fid);

					new_trace_data->LocationBB = BB;
					new_trace_data->Location = bare_inst;
					new_trace_data->bug_location_flag = 1;
					new_trace_data->unique_number = -1;
					traceValState.push_back(new_trace_data);


				}
				else{
#ifdef DEBUG_CHECKER				
					std::cout << "[FREE]: ";
					std::cout << returnIterPtr->traceVal << std::endl;
#endif
					*(returnIterPtr->checker_state_flag) -= 1;
					
					if( *(returnIterPtr->checker_state_flag) < 0){
						returnIterPtr->bug_location_flag = 1;
					}
				}

				#undef FFREE_FP_ARG
				
			}
			/* if FILE ptr is an argument of a function */
			else{

#ifdef DEBUG_CHECKER				
				std::cout << "[call] ";
				std::cout << get_opnd->getName().str();
#endif		

				wFunction *fid = BB->getFuncCall();
				if(fid->getFuncRetTy() == wFunction::FuncRetTy::NonVoidTy){

#ifdef DEBUG_CHECKER				
					std::cout << "(NonVoidTy)" << std::endl;
#endif		

					Value *new_traceVal = reinterpret_cast<Value *>(bare_inst);
					llvm::Function *fid = BB->getParentFunction();	
					int *checker_state_flag = &basic_checker_state_flag;		

					TraceData *trace_data
						= new TraceData(new_traceVal, checker_state_flag, fid);
				
					trace_data->LocationBB = BB;
					trace_data->Location = bare_inst;
					PassingReturnVal.push_back(trace_data);
#ifdef DEBUG_CHECKER				
					ShowPassingReturnVal();
#endif
					
				}
				else {

#ifdef DEBUG_CHECKER				
					std::cout << "(VoidTy)" << std::endl;
#endif
					/* Blink */
				}


				/* arguemnt */
				for(unsigned int i = 0; i < bare_inst->getNumOperands() -1; i++){
				



					TraceData *returnIterPtr
						= SearchTraceVal(bare_inst->getOperand(unsigned(i)));
				
					if(returnIterPtr != nullptr){	
#ifdef DEBUG_CHECKER				
						std::cout << " Passing(before): ";
						std::cout << bare_inst->getOperand(unsigned(i));
						std::cout << std::endl;
#endif
						arg = i;
						
						Checker::Argument *argument = new Argument(arg, bare_inst->getOperand(unsigned(i)));
						PassingArgument.push_back(argument);
						trace_new_func_flag = 1;
					
					}
					else{
	
						continue;
					}
					
				}
			}
		}
		else if( bare_inst->getOpcodeName() == std::string("load") 
				|| bare_inst->getOpcodeName() == std::string("bitcast") 
			){


			//llvm::BasicBlock *bb = BB->getBasicBlock();
			//llvm::Function *f = bb->getParent();	
			
			#define LOADED_VALUE 0			
			TraceData *returnIterPtr
				= SearchTraceVal(bare_inst->getOperand(LOADED_VALUE));

			if(returnIterPtr == nullptr){
#ifdef DEBUG_CHECKER				
				std::cout << "[" << f->getName().str() << "]";
				std::cout << "[load/bitcast] No Pass " << bare_inst->getOpcodeName() << std::endl;
#endif
			}

			else{
				Value* new_traceVal = reinterpret_cast<Value *>(bare_inst);
				llvm::Function *fid = BB->getParentFunction();	
				int *checker_state_flag = returnIterPtr->checker_state_flag;		
				int unique_number = returnIterPtr->unique_number;

				TraceData *trace_data
					= new TraceData(new_traceVal, checker_state_flag, fid, unique_number);
				trace_data->LocationBB = BB;
				trace_data->Location = bare_inst;
				traceValState.push_back(trace_data);

#ifdef DEBUG_CHECKER				
				std::cout << "[" << f->getName().str() << "]";
				std::cout << "[load/bitcast]: ";
				std::cout << bare_inst->getOperand(LOADED_VALUE) << " to " << new_traceVal << std::endl;
#endif
			}
			#undef LOADED_VALUE	

		}

		else if(bare_inst->getOpcodeName() == std::string("store")){	
			//llvm::BasicBlock *bb = BB->getBasicBlock();
			//llvm::Function *f = bb->getParent();	
			
			#define STORED_VALUE 0
			#define STORAGE 1
		
			TraceData *returnIterPtr
				= SearchTraceVal(bare_inst->getOperand(STORED_VALUE));
			
			if(returnIterPtr == nullptr){
#ifdef DEBUG_CHECKER				
				std::cout << "[" << f->getName().str() << "]";
				std::cout <<"[store] No Pass " << bare_inst->getOpcodeName() << std::endl;
#endif
			}

			else{
				
				Value* new_traceVal = bare_inst->getOperand(STORAGE);
				llvm::Function *fid = BB->getParentFunction();	
				int *checker_state_flag = returnIterPtr->checker_state_flag;		
				int unique_number = returnIterPtr->unique_number;

				TraceData *trace_data
					= new TraceData(new_traceVal, checker_state_flag, fid, unique_number);
				trace_data->LocationBB = BB;
				trace_data->Location = bare_inst;
				traceValState.push_back(trace_data);


				/*
				TraceData *get_trace_data = returnIterPtr;
				
				get_trace_data->traceVal
						= bare_inst->getOperand(STORAGE);
				*/
		
#ifdef DEBUG_CHECKER				
				std::cout << "[" << f->getName().str() << "]";
				std::cout << "[store]: ";
				std::cout << bare_inst->getOperand(STORED_VALUE) << " to " << new_traceVal << std::endl;
#endif
			}
			
			#undef STORED_VALUE
			#undef STORAGE


		}else{

				//llvm::BasicBlock *bb = BB->getBasicBlock();
				//llvm::Function *f = bb->getParent();	
#ifdef DEBUG_CHECKER				
				std::cout << "[" << f->getName().str() << "]";
				std::cout <<"[Other instructions] " << bare_inst->getOpcodeName() << std::endl;
#endif
		}


	}

	else{

		/* blank */
	}


	return true;
}

