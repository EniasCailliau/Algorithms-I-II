#include "jdk.h"
#include "printers.h"

int main(){
	vector<int> v {9,4,10,5,3,20,7,120,44,99,88,2022};
	Print(v);
	Printspecial("Nu JDK sort toepassen");
	jdksort(v, 0, v.size()-1);
	Print(v);
	return 0;
}

