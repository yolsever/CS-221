
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

/* given */
 twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
 	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
 	{}

 /* given */
 twoDtree::~twoDtree(){
 	clear();
 }

 /* given */
 twoDtree::twoDtree(const twoDtree & other) {
 	copy(other);
 }

 /* given */
 twoDtree & twoDtree::operator=(const twoDtree & rhs){
 	if (this != &rhs) {
 		clear();
 		copy(rhs);
 	}
	return *this;
 }

twoDtree::twoDtree(PNG & imIn){ /* your code here */
  stats s (imIn);
	height = imIn.height();
	width = imIn.width();
	pair<int,int> ul = make_pair(0,0);
	pair<int,int> lr = make_pair(imIn.width() - 1,imIn.height() - 1);
	root = buildTree(s,ul,lr);
}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr) {
	/* your code here */
	int x1= ul.first;
	int x2= lr.first;
	int y1= ul.second;
	int y2 = lr.second;
	long bestSoFarScore = LONG_MAX;
	pair<int,int> best_ul;
	pair<int,int> best_lr;

	Node * ruut = new Node(ul,lr,s.getAvg(ul,lr)) ;

	if(ul==lr) return ruut;

		for(int x = x1; x< x2; x++){
			pair<int,int> ul_rightCorner = make_pair(x,y2);
			pair<int,int> lr_leftCorner = make_pair(x+1,y1);
			long s1 = s.getScore(ul,ul_rightCorner);
			long s2 = s.getScore(lr_leftCorner,lr);
			if(s1+s2 <= bestSoFarScore){
			bestSoFarScore = s1+s2;
			best_ul = ul_rightCorner;
			best_lr = lr_leftCorner;
		}
		}
		for(int y = y1; y < y2; y++){
			pair<int,int> ul_rightCorner = make_pair(x2,y);
			pair<int,int> lr_leftCorner = make_pair(x1,y+1);
			long s1 = s.getScore(ul,ul_rightCorner);
			long s2 = s.getScore(lr_leftCorner,lr);
			if(s1+s2 <= bestSoFarScore){
			bestSoFarScore = s1+s2;
			best_ul = ul_rightCorner;
			best_lr = lr_leftCorner;
		}
	}


		ruut->left = buildTree(s, ul, best_ul);
		ruut->right = buildTree(s, best_lr, lr);
	return ruut;
	}


void twoDtree::prune(double pct, int tol){
	/* your code here */
	pruneTree(root, pct, tol);
}

void twoDtree::pruneTree(Node * toPrune, double pct, int tol){

	if (toPrune) {
		RGBAPixel avg = toPrune->avg;
		double validPixels = 0;
		double numPixels = 0;

		updateMT(validPixels, numPixels, toPrune, tol , avg);
		if ((validPixels / numPixels) >= pct) {
			clear(toPrune->left);
			clear(toPrune->right);
			toPrune->left = toPrune->right = NULL;
		} else {
			pruneTree(toPrune->left, pct, tol);
			pruneTree(toPrune->right, pct, tol);
		}
	}
}

void twoDtree::updateMT(double & validPixels, double & numPixels, Node * toCheck, int tol, RGBAPixel avg) {
	
	if (toCheck->right == NULL or toCheck->left == NULL) {
		if (toCheck->right == NULL and toCheck->left == NULL) {
			if (iswithinBoundary(toCheck->avg, tol, avg)) {
				numPixels++;
				validPixels++;
			} else {
				numPixels++;
			}
		} else {
			if (toCheck->right == NULL) {
				updateMT(validPixels, numPixels, toCheck->left, tol, avg);
			} else {
			updateMT(validPixels, numPixels, toCheck->right, tol, avg);
			}
		}
	} else {
		updateMT(validPixels, numPixels, toCheck->right, tol, avg);
		updateMT(validPixels, numPixels, toCheck->left, tol, avg);
	}
}



bool twoDtree::iswithinBoundary(RGBAPixel pixel, int tol, RGBAPixel avg) {

		return (((pixel.r - avg.r) * (pixel.r - avg.r)) +
						((pixel.g - avg.g) * (pixel.g - avg.g)) +
						((pixel.b - avg.b) * (pixel.b - avg.b)) <= tol);
}


void twoDtree::clear() {
	/* your code here */
	clear(root);
	root = NULL;
}

void twoDtree::clear(Node * ruut) {

	if (ruut) {
		clear(ruut->left);
		clear(ruut->right);
		delete ruut;
		ruut = NULL;
	}
}


void twoDtree::copy(const twoDtree & orig){
	/* your code here */
	height = orig.height;
	width = orig.width;
	root = copyNode(orig.root);
}

twoDtree::Node * twoDtree::copyNode(Node * toCopy) {
	if (toCopy == NULL) return NULL;

	Node * toReturn = new Node(toCopy->upLeft, toCopy->lowRight, toCopy->avg);
	toReturn->left = copyNode(toCopy->left);
	toReturn->right = copyNode(toCopy->right);
	return toReturn;
}



PNG twoDtree::render(){

	PNG pic = PNG(width,height);
	renderNodes(pic, root);
	return pic;
}



void twoDtree::renderNodes(PNG & pic, Node* curr){

	if (curr != NULL) {
		if (curr->left != NULL or curr->right != NULL) {
			renderNodes(pic, curr->left);
			renderNodes(pic, curr->right);
		} else {
			for (int x = curr->upLeft.first; x <= curr->lowRight.first; x++) {
				for (int y = curr->upLeft.second; y <= curr->lowRight.second; y++) {
					RGBAPixel* p = pic.getPixel(x, y);
					*p = curr->avg;
				}
			}
		}
	}
}
