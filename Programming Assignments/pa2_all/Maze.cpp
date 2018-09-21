
/**
 * Implemented for CPSC 221 Summer 2018


* Nothing should need to be modified in this file, but


* you many add any helper functions you want.
 */




#include "Maze.h"


#include <fstream>



Maze::Maze(ifstream& in) {

int startRow, startCol, finishRow, finishCol;
	in >> rows >> cols >> startRow >> startCol >> finishRow >> finishCol;
	in.ignore(5,'\n');
// just in case input files have extra white space before new line

start = MazeLocation(startRow, startCol);

finish = MazeLocation(finishRow, finishCol);


mazeData = new char*[rows];

for (int i = 0; i < rows; i++) {

mazeData[i] = new char[cols+5]; // just in case input files have extra white space before new line

in.getline(mazeData[i], 256); // should handle mazes up to 256 characters longs
	}

}



Maze::Maze(int rows, int cols, MazeLocation s, MazeLocation f) {

	this->rows = rows;
	this->cols = cols;
	mazeData = new char*[rows];

for (int i = 0; i < rows; i++) {
		mazeData[i] = new char[cols];
	}

start = s;
	finish = f;
}

/**


* Overloading << operator so Mazes can be
 * printed with cout << m;
 */
std::ostream& operator<<(std::ostream &strm, const Maze &m) {

	for (int i = 0; i < m.rows; i++) {

		for (int j = 0; j < m.cols; j++) {

			strm << m.mazeData[i][j];

}

strm << endl;
	}

return strm;
}



bool Maze::invalidLocation(MazeLocation cur) {

	return (cur.row < 0) || (cur.row >= rows) || (cur.col < 0) || (cur.col >= cols) || mazeData[cur.row][cur.col] == 'H';
}



bool Maze::visited(MazeLocation cur) {

	return (!invalidLocation(cur) && mazeData[cur.row][cur.col] == '*');
}



bool Maze::isOpen(MazeLocation cur) {

	return (!invalidLocation(cur) && mazeData[cur.row][cur.col] == ' ');
}

bool Maze::isSemiColon(MazeLocation cur){
	return (!invalidLocation(cur) && mazeData[cur.row][cur.col] == ':');
}

bool Maze::isStart(MazeLocation cur){
	return cur.equals(start);
}



bool Maze::isFinished(MazeLocation cur) {

	return cur.equals(finish);
}



void Maze::setChar(MazeLocation loc, char c) {

	mazeData[loc.row][loc.col] = c;
}



int Maze::getSize() {

	return rows*cols;
}



MazeLocation Maze::getStart() {

	return start;
}



Maze::~Maze() {

	for(int i = 0; i < rows; ++i) {

		delete[] mazeData[i];
	}

delete[] mazeData;
}
