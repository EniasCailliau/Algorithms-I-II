#include "btree.h"
#include "schijf.h"
#include "printers.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(){
	Schijf<Bknoop<int, int, 4> > schijf;
    Btree<int, int, 4> tree(schijf);
	tree.put(1,1);
	tree.put(2,2);
	tree.put(3,3);

	tree.put(4,4);
	tree.put(5,5);
	tree.schrijf(cout);

//	tree.put(8,8);
//	tree.put(7,7);
//	int res = tree.get(1);

	printspecial("uitschrijven van tree");
	tree.schrijf(cout);


return 0;
}
    
