#include "mergelist.h"

int main(){
	Lijst<int>l1;
	


	
	l1.VoegToeAchteraan(3);
	l1.VoegToeAchteraan(6);
		l1.VoegToeAchteraan(11);	l1.VoegToeAchteraan(33); l1.VoegToeAchteraan(44);
		Lijst<int>l2;

	
	l2.VoegToeAchteraan(2); l2.VoegToeAchteraan(5);
		l2.VoegToeAchteraan(14);
	merge(&l1, &l2);
	//l1.Print();
	//l2.Print();
	
	return 0;
	
}
