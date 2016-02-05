#include "extendiblehashing.h"
#include <iostream>
#include "Nieuwestring.h"
#include "Integer.h"
#include "printers.h"

using namespace std;

int main(){
//	Schijfpagina<int,int> schijfp;
//	schijfp.voegDataToe(1,1);
//	schijfp.voegDataToe(2,2);
//	cout<<"is vol? "<<schijfp.isVol()<<endl;
//	schijfp.schrijf();
	Nummer s(1);
	cout<<s;
	Printspecial("Testen van linhash (nok)");
	int i = 1;
	Schijf<Schijfpagina<Nummer, Nummer>> schijf;
//	Schijfpagina<Nummer,Nummer> buffer;
	//einde test
	
	
	
	ExtHash<Nummer, Nummer> hash(schijf);
//	Printspecial("Testen van de macht (ok)");
//	cout<<hash.berekenidemachtt(2,3);
//	Printspecial("Testen van i-de bit (ok)");
//	cout<<hash.berekenidebit(3,3);
	hash.voegToe(Nummer(1),Nummer(2));
	hash.schrijf();
	cout<<"-----------------------------------------"<<endl;
	hash.voegToe(Nummer(5),Nummer(3));
	hash.schrijf();
	cout<<"-----------------------------------------"<<endl;
	hash.voegToe(Nummer(4),Nummer(4));
	hash.schrijf();
	cout<<"-----------------------------------------"<<endl;
	hash.voegToe(Nummer(3),Nummer(3));
	hash.schrijf();
	cout<<"-----------------------------------------"<<endl;
	hash.voegToe(Nummer(9),Nummer(3));
	hash.schrijf();
	cout<<"-----------------------------------------"<<endl;
	hash.voegToe(Nummer(2),Nummer(2));
	hash.schrijf();
	cout<<"-----------------------------------------"<<endl;
	hash.voegToe(Nummer(6),Nummer(6));
	hash.schrijf();
	cout<<"-----------------------------------------"<<endl;
	hash.voegToe(Nummer(25),Nummer(6));
	hash.schrijf();
	cout<<"-----------------------------------------"<<endl;
	
	Printspecial("Testen van de recursieve aanroep (nok)");
	Schijf<Schijfpagina<Nummer, Nummer>> schijf2;
	ExtHash<Nummer, Nummer> recursiehash(schijf2);
	
	recursiehash.voegToe(Nummer(1),Nummer(2));
	recursiehash.schrijf();
	cout<<"-----------------------------------------"<<endl;
	recursiehash.voegToe(Nummer(5),Nummer(3));
	recursiehash.schrijf();
	cout<<"-----------------------------------------"<<endl;
	recursiehash.voegToe(Nummer(9),Nummer(4));
	recursiehash.schrijf();
	cout<<"-----------------------------------------"<<endl;
	
	
	return 0;
}
