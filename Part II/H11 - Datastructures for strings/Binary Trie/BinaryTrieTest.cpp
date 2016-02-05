#include "binarytrie.h"
#include "printers.h"
int main(){
	uint kar = 'a';
//	Bitpatroon b(kar);
//	Bitpatroon b2 = b.shiftlinks();
//	cout<<b<<endl;
	BTrie bt;
//	bt.voegToe('a');
	uint bitteller;
//	Knoop** retu = bt.zoek('a', bitteller);
//	cout<<"bitteller:"<<bitteller;
//	Blad* bl  = (Blad*) *retu;
//	cout<<bl->sl<<endl;
	Bitpatroon b = Bitpatroon::eenbit(1);
	cout<<b<<endl;
	bt.voegToe(b);
	Bitpatroon c = Bitpatroon::eenbit(2);
	cout<<c<<endl;
	bt.voegToe(c);
	BTrie* retu = bt.zoek(b, bitteller);
	cout<<"bitteller "<<bitteller<<endl;
	printspecial("uittesten van toevoegen duplicaat");
	Bitpatroon b1 = Bitpatroon::eenbit(1);
	cout<<b1<<endl;
	bt.voegToe(b1);
	printspecial("uittesten van toevoegen duplicaat");
	Bitpatroon a1 = Bitpatroon::eenbit(2);
	Bitpatroon a2 = Bitpatroon::eenbit(3);
	a1|=a2;
	cout<<a1<<endl;
	bt.voegToe(a1);
	bt.zoek(c,bitteller);
	cout<<"bitteller "<<bitteller<<endl;

	
	return 0;
}
