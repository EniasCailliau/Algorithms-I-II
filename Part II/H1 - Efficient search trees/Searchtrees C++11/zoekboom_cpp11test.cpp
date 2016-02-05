#include "zoekboom_Cpp11.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "csv.h"
#include <vector>

using std::cout;

int main(){
	
//	CsvData grafiek("dieptedata",',');
//    std::vector<double> gemiddeldedieptedata;
//    
//	//excel gedeelte
//	const int aantal=1000;
//	Zoekboom<int,int> zb;
//	for(int i=0;i<aantal;i++){
//		zb.voegtoe(i,i);
//	}
//	srand(time(NULL));
//	for(int i=0;i<aantal;i++){
//		zb.deBinboom.splay(rand()%aantal);
//		gemiddeldedieptedata.push_back(zb.deBinboom.gemiddelde_diepte());
//	}
//	grafiek.voegDataToe(gemiddeldedieptedata);
//	
	
	Zoekboom<int,int> zb;
	zb.voegtoe(5,2);
	zb.voegtoe(8,2);
	zb.voegtoe(2,2);
	zb.voegtoe(4,2);
	zb.voegtoe(3,69);
//	zb.voegtoe(4,2);
//	zb.voegtoe(6,2);
//	zb.voegtoe(7,2);
//	zb.voegtoe(9,2);
//	zb.voegtoe(10,2);
//	zb.voegtoe(11,2);
	cout<<zb;
	
//	cout<<"totaal aantal knopen "<< zb.deBinboom.aantal_knopen()<<std::endl;
//	cout<<"totale diepte"<< zb.deBinboom.totale_diepte(0)<<std::endl;
//	cout<<"gemidelde diepte "<< zb.deBinboom.gemiddelde_diepte()<<std::endl;
	
	//test splay op wortel
//	zb.deBinboom.splay(5);	
//	cout<<"na splay"<<std::endl;
//	cout<<zb<<std::endl;

	//test splay op rechter kind van wortel
//	zb.deBinboom.splay(8);	
//	cout<<"na splay"<<std::endl;
//	cout<<zb<<std::endl;
	
//	test splay op rechter kind van wortel DIE NAAR LINKS WORDT GEROTEERD
//	zb.deBinboom.splay(3);	
//	cout<<"na splay"<<std::endl;
//	cout<<zb<<std::endl;
		 
		 
//	//test roteren naar rechts
//	zb.deBinboom.roteer(false); 

	//cout<<std::endl<<zb;
//	
//	//test roteren naar links
//	Binboom<int,int> * bb;
//	Binknoop<int,int> *bk;
//	zb.zoekplaats(8,bb,bk);
//	bb->roteer(true);
//	cout<<std::endl<<zb;
	
	//test verwijderen
	std::cout<<"test verwijderen"<<std::endl;
	zb.verwijder(5);
	cout<<zb;

	
	
//	int diepte = zb.diepte();
//	cout<<"diepte= "<<diepte<<std::endl;
//	int * d = zb.zoekdata(3);
//	cout<<"data= "<<*d<<std::endl;
//	
//	Binboom<int,int> * bb;
//	Binknoop<int,int> *bk;
//	zb.zoekplaats(8,bb,bk);
//	cout<<"plaats= "<<(*bb)->sl<<" "<<(*bb)->data<<std::endl;
//	
//	Binboom<int,int> * voorganger = zb.ondervoorganger(&(*(*bb)));
//	cout<<"voorganger= "<<(*voorganger)->sl<<std::endl;
	
	
	
	return 0;
}
