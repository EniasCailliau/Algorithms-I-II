#include "LinkedList.h"
#include <iostream>

using namespace std;

int main(){
	LinkedList<int> lijst;
	lijst.add(2);
	lijst.add(3);
	lijst.schrijf(cout);
	
	return 0;
}
