CC := g++
CCFLAGS:= -std=c++11 -Wall -g
ROOT_FLAGS := $(shell root-config --cflags)
ROOT_LIBS := $(shell root-config --libs)
INCLUDE := -I src/ -I $(shell root-config --libdir)

SRC1 := $(notdir $(wildcard *.cpp)) \
        $(notdir $(wildcard *.cc)) \
        $(notdir $(wildcard *.C))

EXE_1 := $(SRC1:.cpp=.exe)
EXE_2 := $(EXE_1:.cc=.exe)
EXE := $(addprefix bin/, $(EXE_2:.C=.exe))

SRC2 := $(notdir $(wildcard src/*.cpp))\
  	$(notdir $(wildcard src/*.cc)) \
  	$(notdir $(wildcard src/*.C))

OBJS_1 := $(SRC2:.cpp=.o)
OBJS_2 := $(OBJS_1:.cc=.o)
OBJS := $(addprefix bin/, $(OBJS_2:.C=.o))

PROTECT := $(addprefix bin/, $(notdir $(EXE:.exe=.o)))
VPATH := src/

.PRECIOUS: $(OBJS) $(PROTECT)

all: $(EXE)

bin/%.exe: bin/%.o $(OBJS)
	@echo "compiling $^  [$@]"
	@$(CC) $(CCFLAGS) $(ROOT_FLAGS) $^  -o $@ $(INCLUDE) $(ROOT_LIBS)

bin/%.o: %.C
	@echo "compiling $^  [$@]"
	@$(CC) -c $(CCFLAGS) $(ROOT_FLAGS) $^ $(INCLUDE) -o $@ $(ROOT_LIBS)

bin/%.o: %.cpp
	@echo "compiling $^  [$@]"
	@$(CC) -c $(CCFLAGS) $(ROOT_FLAGS) $^ $(INCLUDE) -o $@ $(ROOT_LIBS)

bin/%.o: %.cc
	@echo "compiling $^  [$@]"
	@$(CC) -c $(CCFLAGS) $(ROOT_FLAGS) $^ $(INCLUDE) -o $@ $(ROOT_LIBS)


clean:
	rm -fv bin/*.o bin/*.exe

test:
	@echo "Testing..."
	@echo "\nEXE:"
	@echo $(EXE)
	@echo "\nOBJS:"
	@echo $(OBJS)
	@echo "\nPROTECT:"
	@echo $(PROTECT)
