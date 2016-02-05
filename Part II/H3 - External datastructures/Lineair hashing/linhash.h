#include <vector>
#include <memory>
#include <math.h>
#ifndef __BLOKLIJST
#define __BLOKLIJST
#include "bloklijst.h"
#endif 



using namespace std;

template<typename Sleutel, typename Data>
class Linhash : public vector<unique_ptr<Bloklijst<Sleutel,Data>>>{
	private:
		int d;
		int volgende_te_splitsen;
		int currsize;
		Schijf<Schijfpagina<Sleutel,Data>> schijf;
	public:	
		bool voegToe(const Sleutel& sleutel, const Data& data);
		~Linhash(){
			cout<<"Destructor"<<endl;
		}
		Linhash(Schijf<Schijfpagina<Sleutel, Data>>& schijf):d(2), volgende_te_splitsen(0){
			this->schijf = schijf;
			this->resize(4);
		}
		void schrijf();
	
};
template<typename Sleutel, typename Data>
//TD niet vergeten bij declaratie
bool Linhash<Sleutel,Data>::voegToe(const Sleutel& sleutel,const Data& data){
	cout<<"hier1" <<endl;
	unsigned int index = sleutel.geefLinhashindex();
	// todo laatste x bits gebruiken ???? 
	int plaatsnummer = index % (int) pow(2.0,d);
	cout<<"hier1" << plaatsnummer <<endl;
	
	int aantalbits = plaatsnummer < d ? d+1 : d;
	cout<<"aantal bits te bekijken "<<aantalbits<<endl;
	unique_ptr<Bloklijst<Sleutel,Data>>* plaats;

	plaats = &(this->operator[](plaatsnummer));
	if(*plaats == nullptr || plaats->get() == nullptr){
		cout<<"hier ik ga een nieuwe toevoegen"<<endl;
		*plaats = std::move(unique_ptr<Bloklijst<Sleutel,Data>>(new Bloklijst<Sleutel,Data>(&schijf)));
		cout<<"hier ik ga een nieuwe toevoegen"<<endl;

	}
	bool splitsen = plaats->get()->voegToe(sleutel, data);

	if(splitsen){
		// Eerst een nieuw blok aanmaken
		cout<<"Ik ga een nieuwe ptr naar bloklijst maken"<<endl;
//		*plaats = std::move(unique_ptr<Bloklijst<Sleutel,Data>>(new Bloklijst<Sleutel,Data>(&schijf)));
		this->resize(currsize+1);
		if(currsize >= pow(2,d+1)){
			//volgende bit nemen
			d++;
		}
		this->operator[](volgende_te_splitsen++)->splits([&] (const Sleutel& sl) { return (sl.geefLinhashindex() >> d) & 1;});
	}	
}

template<typename Sleutel, typename Data>
void Linhash<Sleutel,Data>::schrijf(){
	cout<<"size= "<<this->size()<<endl;
	for(int i=0 ; i<this->size(); i++){
		if(this->operator[](i).get()){
			cout<<"hier"<<endl;
			this->operator[](i)->schrijf();
		}
	}
}
