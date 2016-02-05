#include "merge.h"
#include "printers.h"



int main(){
	vector<int> v {10,2,5,7,2,1,4,3,6,8,9,14,22,55,80,99,4,3};
	Print(v);
	mergesort(v);
	Print(v);
	vector<int>h(v.size());
	//mergesortbu(v);
	Print(v);
	
	return 0;
}
