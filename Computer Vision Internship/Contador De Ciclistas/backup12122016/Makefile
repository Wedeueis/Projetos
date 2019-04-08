CPP = g++

SRC = src
INCLUDES = include
BUILD = build
MODULES_INCLUDES = include/modules
BIN = bin
DOC = doc/gen
OPENCV=OPENCV3
#-D$(OPENCV)
#-DDEBUG

CPPFLAGS = -g -D$(OPENCV) -DLB_MOG --std=c++11 -I$(INCLUDES) -isystem/usr/local/include
LDFLAGS = `pkg-config --libs opencv` -lconfig++ -lsqlite3 -L/usr/local/lib

EXEC = $(BIN)/EOC
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

MODULES = $(shell find modules/ -iname "*.cpp")
MODULES_OBJECTS = $(MODULES:.cpp=.o)

code: createDirs $(SRC)/Factory.cpp $(EXEC)

all: code doc

createDirs:
	mkdir -p $(BIN)
	mkdir -p $(MODULES_INCLUDES)
	mkdir -p $(DOC)


$(SRC)/Factory.cpp: $(MODULES)
	cd build && python makeFactory.py

$(EXEC): $(OBJECTS) $(SRC)/Factory.o $(MODULES_OBJECTS)
	$(CPP) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) $< -c -o $@
	
clean:
	find . -iname "*.o" -exec rm -f {} \;
	rm -Rf $(BIN)
	rm -f $(INCLUDES)/Factory.hpp
	rm -f $(SRC)/Factory.cpp
	rm -Rf $(MODULES_INCLUDES)
	rm -Rf $(DOC)
	rm times.csv
	
doc: createDirs $(SRC)/Factory.cpp
	cd doc && doxygen

.PHONY: all update createDirs doc clean
