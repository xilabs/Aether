GEN_SRC := universe/Universe.cpp aether.cpp inih/ini.c inih/cpp/INIReader.cpp 
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

INC := -IEigen/ -Iclasses/ -Iinih/cpp/

all: aether

aether: aether.o  $(GEN_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib  -Wl,-Bstatic -lthrift -lthriftnb -lthrift -Wl,-Bdynamic -lboost_thread -levent


%.o: %.cpp 
	$(CXX) -msse2 -Wall $(INC) -c $< -o $@

clean:
	$(RM) *.o aether inih/cpp/*.o gen-cpp/*.o services/*.o universe/*.o

