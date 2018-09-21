
#include "stats.h"

/**
 *
 * stats (pa3)
 * This file will be used for grading.
 *
 */

stats::stats(PNG & im){

	sumRed.clear();
	sumRed.resize(im.height(), vector<long> (im.width(),0));
	sumGreen.clear();
	sumGreen.resize(im.height(), vector<long> (im.width(),0));
	sumBlue.clear();
	sumBlue.resize(im.height(), vector<long> (im.width(),0));
	sumsqRed.clear();
	sumsqRed.resize(im.height(), vector<long> (im.width(),0));
	sumsqGreen.clear();
	sumsqGreen.resize(im.height(), vector<long> (im.width(),0));
	sumsqBlue.clear();
	sumsqBlue.resize(im.height(), vector<long> (im.width(),0));


	for (unsigned int y = 0; y < im.height(); y++) {
		for (unsigned int x = 0; x < im.width(); x++) {

			RGBAPixel * pix = im.getPixel(x,y);

			if ((y == 0) && (x == 0)) {
				sumRed[y][x] = pix->r;
				sumGreen[y][x] = pix->g;
				sumBlue[y][x] = pix->b;
				sumsqRed[y][x] = pix->r * pix->r;
				sumsqGreen[y][x] = pix->g * pix->g;
				sumsqBlue[y][x] = pix->b * pix->b;
			}
			else if (y==0) {
				sumRed[y][x] = sumRed[y][x-1] + pix->r;
				sumGreen[y][x] = sumGreen[y][x-1] + pix->g;
				sumBlue[y][x] = sumBlue[y][x-1] + pix->b;
				sumsqRed[y][x] = sumsqRed[y][x-1] + pix->r * pix->r;
				sumsqGreen[y][x] = sumsqGreen[y][x-1] + pix->g * pix->g;
				sumsqBlue[y][x] = sumsqBlue[y][x-1] + pix->b * pix->b;
			}
			else if (x==0) {
				sumRed[y][x] = sumRed[y-1][x] + pix->r;
				sumGreen[y][x] = sumGreen[y-1][x] + pix->g;
				sumBlue[y][x] = sumBlue[y-1][x] + pix->b;
				sumsqRed[y][x] = sumsqRed[y-1][x] + pix->r * pix->r;
				sumsqGreen[y][x] = sumsqGreen[y-1][x] + pix->g * pix->g;
				sumsqBlue[y][x] = sumsqBlue[y-1][x] + pix->b * pix->b;
			}
			else {
				sumRed[y][x] = sumRed[y][x-1] + sumRed[y-1][x] - sumRed[y-1][x-1] + pix->r;
				sumGreen[y][x] = sumGreen[y][x-1] + sumGreen[y-1][x] - sumGreen[y-1][x-1] + pix->g;
				sumBlue[y][x] = sumBlue[y][x-1] + sumBlue[y-1][x] - sumBlue[y-1][x-1] + pix->b;
				sumsqRed[y][x] = sumsqRed[y][x-1] + sumsqRed[y-1][x] - sumsqRed[y-1][x-1] + pix->r * pix->r;
				sumsqGreen[y][x] = sumsqGreen[y][x-1] + sumsqGreen[y-1][x] - sumsqGreen[y-1][x-1] + pix->g * pix->g;
				sumsqBlue[y][x] = sumsqBlue[y][x-1] + sumsqBlue[y-1][x] - sumsqBlue[y-1][x-1] + pix->b * pix->b;
			}
		}
	}
}

long stats::getScore(pair<int,int> ul, pair<int,int> lr){
  /* your code here */
	long area = rectArea(ul,lr);
	long sumG = getSum('g',ul, lr);
	long sumR = getSum('r',ul, lr);
	long sumB =	getSum('b',ul, lr);
	long sqSum = getSumSq('r', ul , lr) + getSumSq('g', ul , lr) + getSumSq('b', ul , lr);
  long sumSqr = (sumR *sumR) + (sumG * sumG) + (sumB * sumB);
	return sqSum - sumSqr / area;
}


RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
  /* your code here */
	int g= getSum('g',ul,lr) / rectArea(ul,lr);
	int r = getSum('r',ul,lr) / rectArea(ul,lr);
	int b = getSum('b',ul,lr) / rectArea(ul,lr);
	return RGBAPixel(r,g,b);
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
  /* your code here */
	return (lr.first - ul.first+1)*(lr.second - ul.second+1);
}


long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

	vector< vector< long >> * vect;
	switch(channel) {
		case 'r' : vect = & sumRed;
							break;
		case 'g' : vect = & sumGreen;
							break;
		case 'b' : vect = & sumBlue;
							break;
	}

	vector< vector< long >> & curr = *vect;
	int xa = ul.first;
	int ya = ul.second;
	int xb = lr.first;
	int yb = lr.second;


	long a = 0;
	long b = 0;
	long c = 0;
	if (xa > 0) a = curr[yb][xa - 1];
	if (ya > 0) c = curr[ya - 1][xb];
	if (a > 0 and c > 0) b = curr[ya - 1][xa - 1];
	return b + curr[yb][xb] - c - a;
}



long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){
 	vector< vector< long >> * vect;
 	switch(channel) {
 		case 'r': vect = & sumsqRed;
 							break;
 		case 'g': vect = & sumsqGreen;
 							break;
 		case 'b': vect = & sumsqBlue;
 							break;
 	}
 	vector< vector< long >> & curr = *vect;
 	int xa = ul.first;
 	int ya = ul.second;
 	int xb = lr.first;
 	int yb = lr.second;

 	long a = 0;
 	long b = 0;
 	long c = 0;
 	if (xa > 0) a = curr[yb][xa - 1];
 	if (ya > 0) c = curr[ya - 1][xb];
 	if (a > 0 and c > 0) b = curr[ya - 1][xa - 1];
 	return b + curr[yb][xb] - c - a;
 }
