#include <iostream>

#include <fstream>

#include "Stack.h"

#include "Maze.h"

// bool findPath(Stack& s, MazeLocation cur, Maze& m) {
// 	if (m.invalidLocation(m.getStart())) {
// 		return false;
// 	} else {
// 			if (m.isFinished(cur))	 {
// 				m.setChar(cur, '*');
// 				cout << m << endl;
// 				s.push(cur);
// 				return true;
// 			}
// 			int flag = 2;
// 			if (m.isOpen(cur)) {
// 				m.setChar(cur, '*');
// 				cout << m << endl;
// 				s.push(cur);
// 				bool notStuck;
// 				notStuck = findPath(s, cur.upOne(),m) ||
// 									findPath(s, cur.leftOne(),m) ||
// 									findPath(s, cur.rightOne(),m) ||
// 									findPath(s, cur.downOne(),m);
// 				if (notStuck) {
// 					flag = 1;
// 				}	else {
// 					flag = 0;
// 				}
// 			}
//
// 			if (flag == 0) {
// 				m.setChar(cur, ':');
// 				cout << m << endl;
// 				s.pop();
// 			}
//
// 			return (flag == 1) ? (true) : false;
// 	}
// 	return false;
// }


bool findPath(Stack& s, MazeLocation cur, Maze& m) {
	if(m.isFinished(cur)){
		s.push(cur);
		m.setChar(cur,'*');
		cout << m << endl;
		return true;
		}
	if(m.invalidLocation(cur) || (m.isSemiColon(cur) && m.isStart(cur)) || m.isSemiColon(cur)) {
		return false;
	}
else if(m.isOpen(cur)) {
	MazeLocation upone = cur.upOne();
	MazeLocation leftone = cur.leftOne();
	MazeLocation rightone = cur.rightOne();
	MazeLocation downone = cur.downOne();
	s.push(cur);
	m.setChar(cur,'*');
	cout << m << endl;
	if(m.isOpen(leftone)){findPath(s,leftone,m);}
else if(m.isOpen(rightone)){findPath(s,rightone,m);}
else if(m.isOpen(upone)){findPath(s,upone,m);}
else if(m.isOpen(downone)){findPath(s,downone,m);}
else if(m.visited(leftone)){findPath(s,leftone,m);}
else if(m.visited(rightone)){findPath(s,rightone,m);}
else if(m.visited(upone)){findPath(s,upone,m);}
else if(m.visited(downone)){findPath(s,downone,m);}
}
else if(m.visited(cur)){
	MazeLocation upone = cur.upOne();
	MazeLocation leftone = cur.leftOne();
	MazeLocation rightone = cur.rightOne();
	MazeLocation downone = cur.downOne();
	m.setChar(cur,':');
	cout << m << endl;
	s.pop();
			 if(m.isOpen(leftone)){findPath(s,leftone,m);}
	else if(m.isOpen(rightone)){findPath(s,rightone,m);}
	else if(m.isOpen(upone)){findPath(s,upone,m);}
	else if(m.isOpen(downone)){findPath(s,downone,m);}
	else if(m.visited(leftone)){findPath(s,leftone,m);}
	else if(m.visited(rightone)){findPath(s,rightone,m);}
	else if(m.visited(upone)){findPath(s,upone,m);}
	else if(m.visited(downone)){findPath(s,downone,m);}
}
else {
 return false;
}
}



int main(int argc, char* argv[]) {


	// Simple stack test. Do this first. You should probably test more thoroughly

Stack test(8);
	for (int i = 1; i <= 10; i++) {

		test.push(MazeLocation(i, i+1)); // should only be able to add 8
	}


while(!test.isEmpty()) {

test.printTop();
		test.pop();
	}

// You may remove this test after you are finished testing



// Main maze program


// Consumes the maze data file as a command line argument.

if (argc < 2) {
		cerr << "ERROR" << endl << "usage: ./pa2 maze.txt" << endl;
		return 1;
	}


ifstream inputFile(argv[1]);

	// Calls maze constructor linked to input file.
	Maze m(inputFile);
	// Creates a stack with enough space to hold every location in m

Stack s(m.getSize());

	if (findPath(s, m.getStart(), m)) {

		cout << "Maze solved" << endl;
	}
else {
		cout << "Ahhh, couldn't get out!" << endl;
	}



// Stack should contain only locations on path to finish (not dead-ends)

// or be empty if no solution was found (as everything was popped off).

while(!s.isEmpty()) {

		s.printTop();
		s.pop();
	}


}
