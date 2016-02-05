#include "hash.h"
#include "printers.h"

int main(){
	Hashtabel<int> h(13);
	h.add(2, 33);
	h.Print();
	Printspecial("nu voor een botsing zorgen (34)");
	h.add(15,34);
	h.Print(false,true);
	Printspecial("Ophalen van data (2)");
	cout<<h.get(2)<<endl;
	Printspecial("Verwijderen van data (2)");
	h.remove(2);
	h.Print(true);
	// nu moet hij deze niet vinden want is een andere sleutel;
	cout<<h.get(2)<<endl;
	Printspecial("Rehashing");
	h.rehashtest();
	h.Print();
	
	
	Printspecial("-----FINAL TEST-----");
	Hashtabel<int>hh(6);
	hh.add(2,33);
	hh.add(23,40);
	hh.add(1,22);
	hh.add(24,23);
	hh.add(21,25);
	hh.Print(true,true);
	hh.add(7,50);
	hh.Print();



	return 0;
}
