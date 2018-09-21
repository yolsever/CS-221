#include "path.h"
#include <queue>
#include <stack>
using namespace std;

path::path(const PNG & im, pair<int,int> s, pair<int,int> e) {
	start = s;
	end = e;
	image = im;
	BFS();
}

/**
	 * called by constructor. initializes member variable pathPts 
	 * to create path if it exists. 
	 * 
     * @requires: neighbors, good, assemble helpers
     *
     * See documentation for good and assemble to get a hint on two auxiliary 
	 * structures you will want to build: predecessor table, and visited table.
	 */
void path::BFS(){
	vector<vector<bool>> V(image.height(), vector<bool> (image.width(),false));
	vector<vector<pair<int,int>>> P(image.height(), vector<pair<int,int>> (image.width(),end));
	queue<pair<int,int>> locationQ;

	V[start.second][start.first] = true;
	P[start.second][start.first] = start;
	locationQ.push(start);

	/* your code here */
	pair<int,int> curr = start;

	while(!locationQ.empty() && curr != end) {
		curr = locationQ.front();
		locationQ.pop();
		vector<pair<int,int>> paths = neighbors(curr);
		for (auto i = paths.begin(); i != paths.end(); ++i) {
			if (good(V, curr, *i)) {
				locationQ.push(*i);
				V[i->second][i->first] = true;
				P[i->second][i->first] = curr;
			}
		}
	}
	pathPts = assemble(P,start,end);
}

/**
	 * draws path points in red on a copy of the image and returns it
	 */
PNG path::render(){
	/* your code here */
	PNG toReturn = image; // Get a local copy of the image
	;
	// Loop through every node
	for (auto it = pathPts.begin() ; it != pathPts.end(); ++it) {
		*toReturn.getPixel((*it).first,(*it).second) = RGBAPixel(255,0,0);\
	}
	return toReturn;

	}

/** 
	 * tests a neighbour (adjacent vertex) to see if it is (1) within the image; 
	 * (2) unvisited; and (3) close in colour to curr. An entry in table V is true 
	 * if a cell has previously been visited.
	 */
bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
    /* your code here */
    if (next.first < 0 or next.second >= (signed int)image.height()) return false;
	if (next.second < 0 or next.first >= (signed int)image.width()) return false;
	// Check if next vector is close in colour to curr
	RGBAPixel * now = image.getPixel(curr.first, curr.second);
	RGBAPixel * before = image.getPixel(next.first, next.second);
	if (!closeEnough(*now, *before)) return false;

	// Check if next vector is unvisited
	return (v[next.second][next.first] == false);

}

vector<pair<int,int>> path::neighbors(pair<int,int> curr) {
	vector<pair<int,int>> n;
	
    /* your code here */
    pair<int,int> left = make_pair(curr.first-1,curr.second);
    pair<int,int> right = make_pair(curr.first+1,curr.second);
    pair<int,int> above = make_pair(curr.first,curr.second+1);
    pair<int,int> below = make_pair(curr.first,curr.second-1);

    n.push_back(left);
    n.push_back(right);
    n.push_back(above);
    n.push_back(below);

   return n;
}

 /**
	 * Assumes the predecessor table, built in the BFS as follows: 
	 * For each location in the image reachable from the start vertex, "loc", 
	 * the table contains the location "pred" from which "loc" was first seen.
	 * ("pred", "loc") is thus an edge in the shortest path from s to "loc".
	 *
	 * @returns the set of points on the shortest path from s to e, if 
     * it exists. Call this vector P.
     *
     * if there is a shortest path: position 0 should contain s, 
     * and for all 0 < i < size, P[0] to P[i] is the set of points
     * on the shortest path from s to point P[i]. P[size-1] == e.
     *
     * if no path from s to e exists, then just return a single element
     * vector P with P[0] == s.
	 */  
vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p,pair<int,int> s, pair<int,int> e) {
	vector<pair<int,int>> allPts;
	stack<pair<int,int>> resultStack;
	pair<int,int> curr = e;

	/* your code here */

	if (p[curr.second][curr.first] == e) {
		resultStack.push(s);
	} else {
		resultStack.push(curr);
		// Get the previous and add it to the array
		while (curr != s) {
			curr = p[curr.second][curr.first];
			resultStack.push(curr);
			if (curr == end) break;
		}
	}

	while (!resultStack.empty()) {
		allPts.push_back(resultStack.top());
		resultStack.pop();
	}
	
	return allPts;
}


/* PA4 - Completed for you for 2018S Semester */

bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
	int dist = (p1.r-p2.r)*(p1.r-p2.r);
	dist    += (p1.g-p2.g)*(p1.g-p2.g);
	dist    += (p1.b-p2.b)*(p1.b-p2.b);
	return (dist <= 80);
}

vector<pair<int,int>> path::getPath() { 
	return pathPts;
}

int path::length() { 
	return pathPts.size();
}
