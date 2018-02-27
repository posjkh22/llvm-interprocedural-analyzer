SRC				=./src
LIB				=./lib
INCLUDE			=./include
BIT				=./bit
CHECK			=./check

TEST			= test

run: all
	./test $(TEST).bc > test_out

run2: 
	./test $(TEST).bc > test_out

all: clean main printIRcode wrapper wTask wFunction wBasicBlock wInstruction path pathImpl checker
	clang++ -std=c++11 \
	$(LIB)/test.o \
	$(LIB)/wrapper.o \
	$(LIB)/wTask.o \
	$(LIB)/wFunction.o \
	$(LIB)/wBasicBlock.o \
	$(LIB)/wInstruction.o \
	$(LIB)/Path.o \
	$(LIB)/PathImpl.o \
	$(LIB)/checker.o \
	$(LIB)/printIRcode.o \
	-o test \
	`llvm-config --cxxflags --libs --ldflags --system-libs`
	
main:
	clang++ -std=c++11 -c test.cpp  \
	-o $(LIB)/test.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

wrapper:
	clang++ -std=c++11 \
	-c $(SRC)/wrapper.cpp \
	-o $(LIB)/wrapper.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

wTask:
	clang++ -std=c++11 \
	-c $(SRC)/wTask.cpp \
	-o $(LIB)/wTask.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

wFunction:
	clang++ -std=c++11 \
	-c $(SRC)/wFunction.cpp \
	-o $(LIB)/wFunction.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)
	
wBasicBlock:
	clang++ -std=c++11 \
	-c $(SRC)/wBasicBlock.cpp \
	-o $(LIB)/wBasicBlock.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

wInstruction:
	clang++ -std=c++11 \
	-c $(SRC)/wInstruction.cpp \
	-o $(LIB)/wInstruction.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

path:
	clang++ -std=c++11 \
	-c $(SRC)/Path.cpp \
	-o $(LIB)/Path.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

pathImpl:
	clang++ -std=c++11 \
	-c $(SRC)/PathImpl.cpp \
	-o $(LIB)/PathImpl.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

checker:
	clang++ -std=c++11 \
	-c $(SRC)/checker.cpp \
	-o $(LIB)/checker.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

bcall: bcclean bcmain bcwrapper bcwTask bcwFunction bcwBasicBlock bcwInstruction
	llvm-link \
	-o $(BIT)/RUN/run.bc \
	$(BIT)/test.bc \
	$(BIT)/wrapper.bc \
	$(BIT)/wTask.bc \
	$(BIT)/wFunction.bc \
	$(BIT)/wBasicBlock.bc \
	$(BIT)/wInstruction.bc
	

bcmain:
	clang++ -std=c++11  -emit-llvm \
	-c test.cpp  \
	-o $(BIT)/test.bc \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

bcwrapper:
	clang++ -std=c++11  -emit-llvm \
	-c $(SRC)/wrapper.cpp \
	-o $(BIT)/wrapper.bc \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

bcwTask:
	clang++ -std=c++11  -emit-llvm \
	-c $(SRC)/wTask.cpp \
	-o $(BIT)/wTask.bc \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

bcwFunction:
	clang++ -std=c++11  -emit-llvm \
	-c $(SRC)/wFunction.cpp \
	-o $(BIT)/wFunction.bc \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)
	
bcwBasicBlock:
	clang++ -std=c++11  -emit-llvm \
	-c $(SRC)/wBasicBlock.cpp \
	-o $(BIT)/wBasicBlock.bc \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

bcwInstruction:
	clang++ -std=c++11  -emit-llvm \
	-c $(SRC)/wInstruction.cpp \
	-o $(BIT)/wInstruction.bc \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`


printIRcode:
	clang++ -std=c++11 \
	-c $(SRC)/printIRcode.cpp \
	-o $(LIB)/printIRcode.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

foo:
	clang -cc1 -emit-llvm cg_example.c -o cg_example.ll
	clang -S  -emit-llvm -o $(CHECK)/cg_example.bc -c $(CHECK)/cg_example.c
	clang -S  -emit-llvm -o $(CHECK)/check1.bc -c $(CHECK)/check1.c
	clang -S  -emit-llvm -o $(CHECK)/check2.bc -c $(CHECK)/check2.c
	clang -S  -emit-llvm -o $(CHECK)/check3.bc -c $(CHECK)/check3.c
	

clean:
	rm -f test test_out $(LIB)/*.o

bcclean:
	rm -f $(BIT)/*.bc
