
#ifndef _MAZE_H_
#define _MAZE_H_

#include "MazeLocation.h"

class Maze {
  private:
    int rows;
    int cols;
    char** mazeData;
    MazeLocation start;
    MazeLocation finish;

  public:

Maze(int r, int c, MazeLocation s, MazeLocation f);

Maze(ifstream& in);

    friend ostream& operator<<(ostream& os, const Maze& m);

bool isSemiColon(MazeLocation cur);
bool isStart(MazeLocation cur);

    bool isFinished(MazeLocation cur);
    bool invalidLocation(MazeLocation cur);
	bool visited(MazeLocation cur);
	bool isOpen(MazeLocation cur);
    void setChar(MazeLocation loc, char c);
	int getSize();
	MazeLocation getStart();
    ~Maze();
};

#endif
