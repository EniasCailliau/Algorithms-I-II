#include "rekenstack.h"

#include "rekenboom.h"




int main(){
	Rekenstack<int> grm;
	
	//grm.lees(cin);
	//lees();
	string d= "10*(7+8)-50";
	BinaireBoom<string> b(d,0,d.size()-1);
	b.schrijf(cout,"post");	
	return 0;
}
