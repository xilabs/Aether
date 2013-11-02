#GEN_SRC := tests.cpp example.cpp
#DEP_HEAD := Fastcache.h
#gGEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

#THRIFT_DIR := /usr/local/include/thrift
INC := -IEigen/ -Iclasses/

all: aether

aether: aether.o 
	$(CXX) $^ -o $@ -L/usr/local/lib  -lboost_thread

%.o: %.cpp 
	$(CXX) -msse2 -Wall $(INC) -c $< -o $@

clean:
	$(RM) *.o aether

