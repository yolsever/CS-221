/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author Anthony Estey - CPSC 221: Basic Algorithms and Data Structures
**/

#include "chain.h"
#include "block.h"
#include "PNGutil.h"
#include "cs221util/PNG.h"
using namespace cs221util;

int main() {
	PNG rose;
	rose.readFromFile("images/rosegarden.png");
	
	PNG rose_grayscale = grayscale(rose);
	rose_grayscale.writeToFile("images/rosegarden-grayscale.png");

	// Testing Block.cpp 
	Block b1;

	PNG grayscale_altered = grayscale(rose);
	// start at x:225, y:150, and go 450 pixels wide, and 300 down
	b1.build(rose, 225, 150, 400, 300);
	// render block b into the grayscale image

	b1.render(grayscale_altered, 250, 150);
	grayscale_altered.writeToFile("images/rosegarden-colour-mid.png");

	// "Stamp" the coloured image all the way to the top left
	PNG multi_stamps = grayscale(rose);
	b1.render(multi_stamps, 225, 150);
	b1.render(multi_stamps, 156, 100);
	b1.render(multi_stamps,  78,  50);
	b1.render(multi_stamps,   0,   0);
	multi_stamps.writeToFile("images/rose-stamp-to-corner.png");
	

	//Testing Chain.cpp
	Chain c1(rose, 4, 3);
	PNG rose_dup = c1.render(4, 3);
	rose_dup.writeToFile("images/rosegarden-duplicate.png");

	//Insert into empty chain and render
	Chain c2;
	c2.insertFront(b1);	// in this case should be same as insertBack
	cout << "test" << endl;
	PNG one_block = c2.render(1, 1);
	cout << "test2" << endl;
	one_block.writeToFile("images/rosegarden-one-block.png");
	
	//Remove a node (in this case the bottom row)
	Chain c3(rose, 5, 1);
	c3.removeBack();
	PNG trim_bottom = c3.render(4, 1);
	trim_bottom.writeToFile("images/rosegarden-bottom-trimmed.png");


	//Replacing a black and white block in the middle with a coloured one
	Chain c4(rose, 3, 3);
	Chain c5(rose_grayscale, 3, 3);
	const Block* temp = c4.getBlock(4);
	c5.replaceBlock(4,*temp); 
	PNG mid_colour = c5.render(3,3);
	mid_colour.writeToFile("images/rosegarden-colour-mid-chain.png");


	//Moving a node to back AND changing dimensions (shown in lecture)
	Chain c6(rose, 4, 3);
	c6.moveToBack(0, 1);
	PNG mutation = c6.render(3,4);
	mutation.writeToFile("images/rosegarden-mutated.png");
	
	//grayscale/colour checkerboard
	Chain c7(rose, 4, 3);
	Chain c8(rose_grayscale, 4, 3);
	c7.checkeredSwap(c8);	
	PNG checker1 = c7.render(4,3);
	PNG checker2 = c8.render(4,3);	
	checker1.writeToFile("images/rosegarden-checker1.png");
	checker2.writeToFile("images/rosegarden-checker2.png");

	return 0;
}
