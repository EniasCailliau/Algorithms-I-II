#include "DebruijneGraaf.h"
//#include "woord.h"
#include <iostream>
using namespace std;

int main() {
	DebruijneGraaf<2,2> g;
//	Woord<2,3> w(10);
//	cout<<w<<endl;
	
	cout<<endl<<endl;
	cout<<g;
	g.resolve();
		
	return 0;
}
