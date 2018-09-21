
/**
 * Implemented for CPSC 221 Summer 2018
 * Nothing should need to be modified in this file, but
 * you many add any helper functions you want.
 */



#include "MazeLocation.h"

MazeLocation::MazeLocation() {
	row = 0;
	col = 0;
}

MazeLocation::MazeLocation(int r, int c) {
	row = r;
	col = c;
}

/**
 

* Overloading << operator so MazeLocations can be 
 * printed with cout << m;
 */


std::ostream& operator<<(std::ostream &strm, const MazeLocation &m) {
	return strm << "row:" << m.row << ", col:" << m.col << endl;
}



bool MazeLocation::equals(MazeLocation other) {
	return (row == other.row && col == other.col);
}



MazeLocation MazeLocation::upOne() {
	return MazeLocation(row-1, col);
}



MazeLocation MazeLocation::downOne() {
	return MazeLocation(row+1, col);
}



MazeLocation MazeLocation::leftOne() {
	return MazeLocation(row, col-1);
}



MazeLocation MazeLocation::rightOne() {
	return MazeLocation(row, col+1);
}

