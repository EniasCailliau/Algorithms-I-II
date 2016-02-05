#include "gewogengraaf.h"

int main(){
	GewogenGraaf<int> gg(6);
	gg.voeg_verbinding_toe(0,1,4);
	gg.voeg_verbinding_toe(1,2,6);
	gg.voeg_verbinding_toe(2,3,3);
	gg.voeg_verbinding_toe(3,4,2);
	gg.voeg_verbinding_toe(4,5,4);
	gg.voeg_verbinding_toe(5,0,2);
	gg.voeg_verbinding_toe(1,5,5);
	gg.voeg_verbinding_toe(2,5,1);
	cout<<gg;
	
	GewogenGraaf<int>mob;
	mob.wordMOBvan(gg);
	cout<<mob;
	
	return 0;
}
