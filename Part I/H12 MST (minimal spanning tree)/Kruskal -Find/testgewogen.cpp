#include "Kruskal_Find.h"
#include "printers.h"
#include <fstream> 

using namespace std;

int main(){
	GewogenGraaf<double> gg(6);
//	std::string type;
//    int n, m;
//	ifstream is("gewogen.txt");
//    is >> n;
//    gg.init(n);
//    is >> m;
//    for (int j=0; j<m; j++){
//	
//        int van;
//		int naar;
//        double gewicht;
//    	is >> van >> naar >> gewicht;
//    	gg.voeg_verbinding_toe(van, naar,gewicht);
//	}

	gg.voeg_verbinding_toe(0,1,4);
	gg.voeg_verbinding_toe(1,2,6);
	gg.voeg_verbinding_toe(2,3,3);
	gg.voeg_verbinding_toe(3,4,2);
	gg.voeg_verbinding_toe(4,5,4);
	gg.voeg_verbinding_toe(5,0,2);
	gg.voeg_verbinding_toe(1,5,5);
	gg.voeg_verbinding_toe(2,5,1);
	gg.schrijf(cout);
	Printspecial("nu kruskal efficiente find");
	GewogenGraaf<double>mob;
	mob.wordMOBvan(gg);
	mob.schrijf(cout);
	Printspecial("clustering");
	GewogenGraaf<double> gg2;
	gg2.Cluster(gg,2);
	gg2.schrijf(cout);
}
