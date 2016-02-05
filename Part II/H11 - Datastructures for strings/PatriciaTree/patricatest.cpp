#include "sleutel2.h"
#include "patriciatest.h"
#include <iostream>
using namespace std;
int main(){
		Sleutel sl(3);
		Sleutel sl2(4);
		Patriciatrie pt;
		pt.voegtoe(sl);
		pt.voegtoe(sl2);
		cout<<pt;

	return 0;
}


