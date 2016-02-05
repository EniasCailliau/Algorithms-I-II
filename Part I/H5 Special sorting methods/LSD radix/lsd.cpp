#include "lsd.h"
#include "printers.h"


int main(){
	vector<int> v {3537,7099,3669,4069,9037,3049,5233,5333,5343,8999};
	lsdsort(v);
	Printspecial("Uitvoer van lsd sort:");
	Print(v);
	return 0;
}
