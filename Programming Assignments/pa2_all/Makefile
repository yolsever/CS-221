EXENAME = pa2
OBJS = main.o Stack.o Maze.o MazeLocation.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp Stack.h Maze.h MazeLocation.h
	$(CXX) $(CXXFLAGS) main.cpp 

Stack.o : Stack.cpp Stack.h MazeLocation.h
	$(CXX) $(CXXFLAGS) Stack.cpp

Maze.o : Maze.cpp Maze.h MazeLocation.h
	$(CXX) $(CXXFLAGS) Maze.cpp
	
MazeLocation.o : MazeLocation.cpp MazeLocation.h
	$(CXX) $(CXXFLAGS) MazeLocation.cpp

clean :
	-rm -f *.o $(EXENAME) test
