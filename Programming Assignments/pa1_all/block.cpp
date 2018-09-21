#include "block.h"

int Block::width() const{
	return data.size();
}
int Block::height() const{
	return data[0].size();
}

void Block::build(PNG & im, int upLeftX, int upLeftY, int cols, int rows) {
	for (int i = upLeftX; i < upLeftX + cols; i++) {
		vector<HSLAPixel> temp;
		for (int j = upLeftY; j < upLeftY + rows; j++) {
			HSLAPixel* p = im.getPixel(i, j);
			temp.push_back(*p);
		}
		data.push_back(temp);
	}
	return;
}

void Block::render(PNG & im, int upLeftX, int upLeftY) const {
   	for (int i = upLeftX; i < upLeftX + width(); i++) {
		for (int j = upLeftY; j < upLeftY + height(); j++) {
			HSLAPixel* p = im.getPixel(i, j);
			*p = data[i-upLeftX][j-upLeftY];
		}
	}
}


