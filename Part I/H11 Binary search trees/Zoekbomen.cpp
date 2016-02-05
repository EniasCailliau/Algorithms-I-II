#include "sortvector.h"
#include "zoekboom.h"
#include "printers.h"

int main(){
	Sortvector<int> sv(10);
	//cout<<sv<<endl;
	Zoekboom<int> zb(sv);
	Printspecial("Zoekboom");
	//cout<<zb<<endl;
	zb.printlevelorder();
	//cout<<zb.max_diepte()<<endl;
	//cout<<zb.gem_diepte2()<<endl;
	//cout<<zb.gem_diepte()<<endl;
	
	
	Printspecial("zoeken naar minimum");
	cout<<zb.min()<<endl;
	Printspecial("zoeken naar maximum");
	cout<<zb.max()<<endl;
	Printspecial("zoeken naar opvolger");
	cout<<zb.opvolger(1)<<endl;
	Printspecial("verwijderen van knoop");
	zb.verwijderknoop(4);
	zb.printlevelorder();
	
	
	
}
