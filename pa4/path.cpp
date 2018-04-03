#include "path.h"
#include <queue>
#include <stack>
using namespace std;

path::path(const PNG & im, pair<int,int> s, pair<int,int> e)
   :start(s),end(e),image(im){
    BFS();
}

void path::BFS(){
	// initialize working vectors
	vector<vector<bool>> V(image.height(), vector<bool> (image.width(),false));
	vector<vector<pair<int,int>>> P(image.height(), vector<pair<int,int>> (image.width(),end));

    /* your code here */

	pathPts = assemble(P,start,end);
}

PNG path::render(){

    /* your code here */
	if (pathPts.size() <= 1) {
		return image;
	}
	else {
		for (int i = 0; i < pathPts.size(); i++) {
			pair<int, int> curr = pathPts[i];
			RGBAPixel* currPixel = image.getPixel(curr.first, curr.second);
			currPixel->r = 0xff;
			currPixel->g = 0;
			currPixel->b = 0;
		}
	}
}

vector<pair<int,int>> path::getPath() { return pathPts;}

int path::length() { return pathPts.size();}

bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
	if (next.first < 0 || next.first > image.width() - 1 || next.second < 0 || next.second > image.height() - 1)
		return false;
	else if (v[next.first][next.second])
		return false;
	else if (!closeEnough(*image.getPixel(curr.first, curr.second), *image.getPixel(next.first, next.second)))
		return false;
	else
		return true;
}

vector<pair<int,int>> path::neighbors(pair<int,int> curr) {
	vector<pair<int,int>> n;

    /* your code here */
	pair<int, int> above = make_pair(curr.first, curr.second - 1);
	pair<int, int> right = make_pair(curr.first + 1, curr.second);
	pair<int, int> bottom = make_pair(curr.first, curr.second + 1);
	pair<int, int> left = make_pair(curr.first - 1, curr.second);
	n.push_back(above);
	n.push_back(right);
	n.push_back(bottom);
	n.push_back(left);
	return n;
}

vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p,pair<int,int> s, pair<int,int> e) {

    /* hint, gold code contains the following line:
	stack<pair<int,int>> S; */

    /* your code here */

}

bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
   int dist = (p1.r-p2.r)*(p1.r-p2.r) + (p1.g-p2.g)*(p1.g-p2.g) +
               (p1.b-p2.b)*(p1.b-p2.b);

   return (dist <= 80);
}
