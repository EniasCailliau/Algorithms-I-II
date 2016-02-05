#include "rztree.h"
#include "printers.h"

int main(){
	RoodZwarteBoom<int,int> zb;
	zb.voegtoe(6,1);
	zb.voegtoe(3,2);
	zb.voegtoe(9,3);
	zb.voegtoe(1,0);
	cout<<zb;
//	Printspecial("Testen van verwijderen");
//	zb.verwijder(6);
//	cout<<zb;
	return 0;
}
