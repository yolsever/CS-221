#ifndef _MAZELOC_H_
#define _MAZELOC_H_

#include <iostream>
using namespace std;
class Maze;

class MazeLocation {
  private: 
    int row;
    int col;

  public:
    MazeLocation();
    MazeLocation(int r, int c);

    friend ostream& operator<<(ostream& os, const MazeLocation& m);  
    friend class Maze;

    bool equals(MazeLocation other);
    void printLocation();
    MazeLocation upOne();
    MazeLocation downOne();
    MazeLocation leftOne();
    MazeLocation rightOne();
    
};

#endif
