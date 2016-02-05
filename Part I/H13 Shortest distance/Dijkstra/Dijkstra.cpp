#include "Gewogengraaf.h"

int main(){
//	GewogenGraaf<int> gg(4);
//	gg.voeg_verbinding_toe(0,1,5);
//	gg.voeg_verbinding_toe(1,3,11);
//	gg.voeg_verbinding_toe(1,2,4);
//	gg.voeg_verbinding_toe(0,2,10);
//	gg.voeg_verbinding_toe(3,2,5);
//	gg.schrijf(cout);
//	
//	GewogenGraaf<int>d;
//	vector<int> v = d.Dijkstra(gg,0);
	GewogenGraaf<int> d(5);
	d.voeg_verbinding_toe(0,2,10);
	d.voeg_verbinding_toe(0,4,5);
	d.voeg_verbinding_toe(0,1,20);
	d.voeg_verbinding_toe(3,1,3);
	d.voeg_verbinding_toe(4,3,4);
	d.voeg_verbinding_toe(2,3,10);
	d.voeg_verbinding_toe(4,2,2);
	
	GewogenGraaf<int>test;
	vector<int> v = test.Dijkstra(d,0);
	Printspecial("Einde van deijkstra");
	Print(v);
	
	return 0;
}
