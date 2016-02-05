#include "Mergesort.h"
//#include "printers.h"

int main(){
	vector<int> v{4,7,3,11,9,22,14,24};
	Print(v);
	Printspecial("Testen van mergesort");
	Mergesort(v);
	Print(v);
	vector<int> w{4,7,3,11,9,22,14};
	Printspecial("Testen van selectionsort");
	Insertionsort(w,0,v.size()-1);
	Print(w);
	vector<int> x{4,7,3,11,9,22,14,1,2,8,23,44,444};
	Printspecial("Testen van mergesort (alt)");
	Mergesortalt(x);
	Print(x);	
	
	
	return 0;
}
