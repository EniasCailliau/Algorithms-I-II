#include "ternaire.h"
#include "printers.h"


int main(){
	//vector<int> v {1,2,3,5,8,8,7,4,22,23,43};
	vector<int> v {100,344,4020,10,1,6,2,12,43,24,3,22};
	Print(v);
	Printspecial("Nu sorteren met Ternaire radix sort");
	ternairsort(v);
	//ternairsort(v,0,v.size()-1,1);
	Print(v);
	return 0;
}
