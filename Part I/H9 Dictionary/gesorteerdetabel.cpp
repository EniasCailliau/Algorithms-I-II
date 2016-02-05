#include "gesorteerdetabel.h"

int main(){
	Gesorteerdetabel<int> tab;
	tab.voegtoe(2);
	tab.voegtoe(4);
	tab.voegtoe(1);
	tab.voegtoe(9);
	cout<<tab;
	
	cout<<tab.zoek(4);
	
	return 0;
}
