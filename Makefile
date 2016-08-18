# Makefile for evolution-toolkit

CC := g++ #llvm-g++
LL := ar #llvm-ar-mp-3.7
CPP_FILES := $(wildcard src/*.cpp)
CPP_FILES := $(filter-out src/main.cpp, $(CPP_FILES))
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS  :=  #-lOpenCL
CC_FLAGS  := -Wall -pedantic -O3 -std=c++11 # -g (for debugging)

MAIN_OBJ := obj/main.o

LIB_NAME := lib/evolution-toolkit.a

all: main lib
	@echo "done"
	
lib: $(OBJ_FILES)
	$(LL) rvs $(LIB_NAME) $^

main: $(OBJ_FILES) $(MAIN_OBJ)
	$(CC) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp src/%.hpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

clean:
	@rm -f obj/*.o lib/*.a *.exe main *.stackdump
	@echo project cleaned
