#include<vector>
#include<memory>
#include<map>
#include<iostream>
#include "schijf.h"

using namespace std;


typedef unsigned int blokindex;

template <class Sleutel,class Data>
class Schijfpagina;


template<class Sleutel, class Data>
class Bloklijst{
	private:
		int aantalblokken;
		blokindex blokopschijf;
		Schijf<Schijfpagina<Sleutel,Data>> schijf;
	public:
		Bloklijst(Schijf<Schijfpagina<Sleutel,Data>>* schijf):aantalblokken(0){
			this->schijf = schijf;
		}
    template<typename Func>
Bloklijst<Sleutel,Data> splits(Func func){
	cout<<"hello"<<endl;
	Bloklijst<Sleutel,Data>* bblok = new Bloklijst<Sleutel,Data>(schijf);
	cout<<"dit is blok op schijf"<<endl;	

	Schijfpagina<Sleutel,Data> buffer;
//	cout<<"BEGIN"<<endl;
	blokindex loper = blokopschijf;
	cout<<"\n blokopschijf:"<<blokopschijf;
	aantalblokken = 0;
	schijf->lees(buffer, loper);	
	while(loper != 0){
//		cout<<"hier"<<endl;
		// beter met iterator maar hier zelf geïmplementeerd.
		for(auto it = buffer.dataMap.begin(); it != buffer.dataMap.end(); ++it){
  			std::cout << it->first << " " << it->second<< "\n";
  			if(func(it->first)){
  				// moeten we in andere bloklijst toevoegen.
  				cout<<"ik heb een ja"<<endl;
//  				b.voegToe(it->first, it->second);  				
//				schijf->herschrijf(buffer, loper);  	
			}else{
				voegToe(it->first, it->second);
				cout << "split" << endl;
			}
		}
		schijf->verwijder(loper);
		loper = buffer.getVolgende();
		schijf->lees(buffer, loper);	
	}
	cout<<"END"<<endl;
//	return b;
};
		// De methode voeg toe geeft aan linhash door indien er gesplit moet worden. 
		// Dit op basis van het aantal blokken: aantalblokken>1 ==> splitsen nodig.
		bool voegToe(const Sleutel& sl,const Data& data);
		void schrijf();
	
};
template<class Sleutel, class Data>
void Bloklijst<Sleutel,Data>::schrijf(){
	cout<<"BEGIN schrijven"<<endl;
	Schijfpagina<Sleutel,Data> buffer;
	blokindex loper = blokopschijf;
	schijf->lees(buffer, loper);	
	for(int i = 0; i < aantalblokken; i++){	
		cout<<"blokopschijf: "<<blokopschijf<<endl;
		buffer.schrijf();
		loper = buffer.getVolgende();
		schijf->lees(buffer, loper);	
	}
//	cout<<"END"<<endl;
}

template<class Sleutel, class Data>
bool Bloklijst<Sleutel,Data>::voegToe(const Sleutel& sl,const Data& data){
	Schijfpagina<Sleutel,Data> buffer;
	cout<<"hier"<<endl;
	if(aantalblokken == 0){
		aantalblokken++;
//		cout << "nog geen blokken: hier voegtoe " << sl << endl;
		blokopschijf = schijf->schrijf(buffer);
//		cout<<"ik krijg blokschijf binnen "<<blokopschijf << endl;
	}
	blokindex loper = blokopschijf;
	schijf->lees(buffer, loper);	
	int i = 0;
	while(buffer.isVol() && i < aantalblokken){
//		cout<<"buffer is vol, ik ga naar volgende "<<endl;
		loper = buffer.getVolgende();
		schijf->lees(buffer, loper);	
		i++;		
	}
	if(i == aantalblokken){
//		cout<<"Ik ben aan het einde van mijn bloklijst"<<endl;
		aantalblokken++;	
		Schijfpagina<Sleutel,Data> nieuwebuffer;
		blokindex index = schijf->schrijf(nieuwebuffer);
		buffer.setVolgende(index);
	}else{
		buffer.voegDataToe(sl,data);		
//		cout << "hier voegtoe " << sl << endl;
	}
//	cout<<"ik ga een nieuwe waarde schrijven op loper: "<<loper<<endl;
	schijf->herschrijf(buffer,loper);
	return aantalblokken > 1;
}




/*
Schijfpagina kan geen duplicate sleutels bevatten. vb. sleutel 1 twee maal toevoegen zorgt voor 1 waarde op de schijf.
--> correctie moeten uitvoeren bij voegtoe om te vermijden dat de indexteller opgehoogd word.

Indexteller geeft weer hoeveel waarden er aanwezig zijn. 
Indien gewerkt wordt met een dubbele vector kan deze waarde gebruikt worden om deze op te vullen. (ongesorteerde versie)

Er kan ook een gesorteerde versie gebruikt worden van sleutels. Dit kan ook met de map.
*/
template <typename Data, typename Sleutel>
class Schijfpagina{
	friend class Bloklijst<Sleutel,Data>;
	protected:
		map<Sleutel, Data> dataMap;
		unsigned int capaciteit;
		//blokken intern
		blokindex indexteller;
		//blokken extern
		blokindex volgende;
	public:
		Schijfpagina():capaciteit(2),volgende(0),indexteller(0){};
		Schijfpagina(const unsigned int & cap):capaciteit(cap),volgende(0),indexteller(0){};
		void schrijf(){
			for(auto it = dataMap.cbegin(); it != dataMap.cend(); ++it){
  				  std::cout << it->first << " " << it->second<< "\n";
			}
		}		
		Schijfpagina<Sleutel, Data>& operator=(const Schijfpagina<Sleutel, Data>& t){
			this->capaciteit = t.capaciteit;
			this->dataMap = t.dataMap;
			this->indexteller = t.indexteller;
			this->volgende = t.volgende;
			*this;
		}
		blokindex getVolgende(){
			return volgende;
		}
		void setVolgende(blokindex index){
			volgende=index;
		}
		bool isVol(){
			return indexteller >= capaciteit;
		}
		
		void voegDataToe(const Sleutel & sl,const Data& data){
			++indexteller;
			dataMap.insert(std::pair<Sleutel,Data>(sl,data));
		}				

};
