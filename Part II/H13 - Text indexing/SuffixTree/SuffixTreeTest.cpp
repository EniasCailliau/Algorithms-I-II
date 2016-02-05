#include <ostream>
#include "suffxtr.h"

using namespace std;

int main(){
//	char * text = "";
	char myword[] = { 'H', 'e', 'l','l', 'l', 'o', '\0' }; 
	Sboom d(myword,'%');
	d.print(cout);
	return 0;
}
