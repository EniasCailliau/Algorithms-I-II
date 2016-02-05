#include "quick.h"


int main(){
	vector<int> v {1,4,5,6,10,2,3};
	Print(v);
	//quicksort(v);
	quicksort(v);
	Print(v);
	return 0;
}
