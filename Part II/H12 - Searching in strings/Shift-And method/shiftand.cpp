#include "shiftand.h"
// string wordt gebruikt voor conversie van char* naar een woord met naaldlengte.
#include <string>
using std::string;
#include "printers.h"

int main(){
	 unsigned char naald[] = "abc";
	 int naaldlengte = 3;
	 unsigned char tekst[] = "afcabc";
	 int hooiberglengte = 6;
	ShiftAnd sa(naald,naaldlengte);
	std::queue<const uchar*> resultaat = sa.zoek(tekst, hooiberglengte);
	printspecial("resultaat van zoek FIFO");
	while(!resultaat.empty()){
		const uchar* print = resultaat.front();
		resultaat.pop();
		//bij gewoon
//		cout<< string(print, print+naaldlengte);
		// bij verlengen
//		cout<< string(print, print+naaldlengte+1);
		// bij verwijderen
		cout<<string(print, print+naaldlengte);
		cout<<endl;
	}
	return 0;
}
