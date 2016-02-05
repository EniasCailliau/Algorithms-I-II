#include "graaf.h"
#include "mygraph.h"

void schrijf(const std::vector<string> & v){
	for(int i=0;i<v.size();i++){
		std::cout<<v[i]<<" ";
	}
	std::cout<<"\n";
}

int main(){
	Graaf<GERICHT> gg(7);
	gg.voeg_verbinding_toe(0,1);
	gg.voeg_verbinding_toe(0,2);
	gg.voeg_verbinding_toe(2,6);
	gg.voeg_verbinding_toe(1,3);
	gg.voeg_verbinding_toe(1,4);
	gg.voeg_verbinding_toe(1,5);
	cout<<gg;
	Printspecial("nu postnummering bepalen");
	gg.diepte_eerst_zoeken();
	
	
	
	
//	
//	MijnGraaf g("makefile.txt");
//	std::vector<string> v;// = g.rangschik_topologisch2();
//	schrijf(v);
//	v = g.rangschik_topologisch1();
//	schrijf(v);
//	std::vector<string> compileer_volgorde = g.compileer_volgorde("timestamps.txt");
//	schrijf(compileer_volgorde);
}


