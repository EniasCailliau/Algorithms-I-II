#include "PRQuadtrees.h"


int main(){
	Quadtree<Point,int> quadtree(0,128,0,128);
//	quadtree.schrijf(cout);
	Point p(1,1);
//	Quadtree<Point,int>* ouder;
//	Quadtree<Point,int>* resultaat = quadtree.zoek(p, ouder);
//	resultaat->schrijf(cout);
	quadtree.voegToe(p,30);
//	cout<<"uitschrijven"<<endl;
//	quadtree.schrijf(cout);
	Point p2(2,2);
	quadtree.voegToe(p2,40);
	cout<<"!!!!!!!!!!!!!!!!!!!ik begin te schrijven"<<endl;
	quadtree.schrijf(cout);

	
	return 0;
}
