#ifndef __BLOKLIJST
#define __BLOKLIJST
#include "bloklijst.h"
#endif 

#include <string>

#include "linhash.h";
#include "Nieuwestring.h"



/* opgeloste problemen: 
1.Schijfpagina had geen default constructor --> itereren was niet mogelijk ==> default constructor maken
2.Schijfpagina moet over een capaciteit, indexteller een volgende beschikken ==> velden invullen OOK BIJ DEFAULTCONSTRUCTOR (toch allemaal zelfde)
	--> reden: we schrijven steeds een nieuwe buffer weg naar schijf wanneer we toevoegen--> indien default niet juist is dan resultaat isVol() in foute waarden
	-->op meerdere plaatsen voor een probleem
3.Om juist te zijn moeten de blokken ook verwijderd worden. Binnen splits: 	schijf->verwijder(loper);

*/

using namespace std;

void printspecial(const char* s){
	cout<<"<<<<<<<<<<<<<<"<<s<<">>>>>>>>>>>>"<<endl;
}

int main(){
	Schijfpagina<int, int> temp(10);
//	temp.voegDataToe(1,1);
//	temp.voegDataToe(2,2);
//	temp.voegDataToe(3,3);
//	temp.schrijf();
//	cout<<"ik ben vol? "<<temp.isVol()<<endl;
	
	
	Schijf<Schijfpagina<int, int> > s;
//	blokindex index = s.schrijf(temp);
//	cout<<"index "<<index;
	
//	printspecial("Testen van lezen schijf (ok)");
//	Schijfpagina<int,int> buffer;
//	s.lees(buffer, 667);
//	buffer.schrijf();
//	printspecial("Testen van schrijven bloklijst (ok)");
//	Bloklijst<int,int> bloklijst(&s);
//	bloklijst.voegToe(1,1);
//	bloklijst.voegToe(2,2);
//	bloklijst.voegToe(3,3);
//	bloklijst.schrijf();
//	bloklijst.voegToe(7,7);
//	bloklijst.voegToe(5,5);
//	bloklijst.schrijf();
//	printspecial("Testen van split (ok)");
//	unique_ptr<Bloklijst<int,int>> res = bloklijst.splits([&] (const int& sl) { return (sl >> 2) & 1;});
//	cout<<"Dit is de eerste bloklijst"<<endl;
//	bloklijst.schrijf();
//	cout<<"Dit is tweede bloklijst"<<endl;
//	res.get()->schrijf();
//	
//	printspecial("Testen van een overvolle blokschijf (nok)");
//	// ook getest op zelfde schijf om te kijken of correct omgaat met opeenvolgende blijklijsten op dezelfde schijf
//	Bloklijst<int,int> bloklijst2(&s);
//	for(int i=0; i<12; i++){
//		bloklijst2.voegToe(i,i);
//	}
//	bloklijst2.schrijf();
	
	
	printspecial("Testen van linhash (nok)");
	Schijf<Schijfpagina<String, String>> schijf;
	Schijfpagina<String, String> temp1(10);
	temp1.voegDataToe(String("Sleutel"),String("Data"));
	blokindex index2 = schijf.schrijf(temp1);
	
	Linhash<String, String> linhash(schijf);
	linhash.schrijf();
	linhash.voegToe(String("Sleutel1"),String("Data1"));
	linhash.voegToe(String("Sleutel2"),String("Data2"));
	linhash.voegToe(String("Sleutel3"),String("Data3"));
	linhash.voegToe(String("key1"),String("Data3"));
		linhash.voegToe(String("key2"),String("Data3"));
			linhash.voegToe(String("key3"),String("Data3"));
	linhash.schrijf();
	
	
	return 0;
}



