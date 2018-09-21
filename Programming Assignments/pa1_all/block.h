
#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
using namespace std;
using namespace cs221util;

class Block{

public:
   /**
	* Builds a block by grabbing values at 'im' starting at upLeftX
	* and upRightX and copying all values high rows by cols long to 
	* to create a block holding the image data
   */
   void build(PNG & im, int upLeftX, int upLeftY, int rows, int cols);
   
   /**
    * Renders the block into image beginning at upLeftX and upLeftY
    * by overwriting any pixels values at that location in the
    * image and moving down and right for the size of block
   */
   void render(PNG & im, int upLeftX, int upLeftY ) const ;
   
   /**
    * Returns the width of the block, in number of pixels
    */
   int width() const ;
   
   /**
	* Returns the height of the block, in number of pixels
	*/
   int height() const ;

private:

   vector< vector < HSLAPixel > > data;

};
#endif
