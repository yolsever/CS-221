EXE = pa3

OBJS_EXE = RGBAPixel.o lodepng.o PNG.o main.o twoDtree.o stats.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
#LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm

all : pa3

$(EXE) : $(OBJS_EXE)
	$(LD) $(OBJS_EXE) $(LDFLAGS) -o $(EXE)

TEST_EXE = test
TEST_OBJS = RGBAPixel.o lodepng.o PNG.o test.o stats.o #twoDtree.o

$(TEST_EXE) : $(TEST_OBJS)
	$(LD) $(TEST_OBJS) $(LDFLAGS) -o $(TEST_EXE)

test.o : test.cpp cs221util/PNG.h cs221util/RGBAPixel.h #twoDtree.h
	$(CXX) $(CXXFLAGS) test.cpp -o test.o


#object files
RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp -o $@

stats.o : stats.h stats.cpp cs221util/RGBAPixel.h cs221util/PNG.h
	$(CXX) $(CXXFLAGS) stats.cpp -o $@

twoDtree.o : twoDtree.h twoDtree.cpp stats.h cs221util/PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) twoDtree.cpp -o $@

main.o : main.cpp cs221util/PNG.h cs221util/RGBAPixel.h twoDtree.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.o

clean :
	-rm -f *.o $(EXE)
