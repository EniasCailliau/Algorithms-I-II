#include "schijf.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

typedef unsigned int blokindex;

template <class Sleutel,class Data>
class Schijfpagina;

template<typename Sleutel, typename Data>
class ExtHash : public vector<blokindex>{
	private:
		int d;
		int currsize;
		Schijf<Schijfpagina<Sleutel,Data>> schijf;
	public:
		unsigned int berekenidebit(unsigned int index , int i);
		bool voegToe(const Sleutel& sleutel, const Data& data);
		ExtHash(Schijf<Schijfpagina<Sleutel, Data>>& schijf):d(2),currsize(4){
			this->schijf = schijf;
			this->resize(4);
			Schijfpagina<Sleutel, Data> nieuw(0);
			blokindex nieuwindex = this->schijf.schrijf(nieuw);

			for(int i=0; i<this->size();i++){
				this->operator[](i)=nieuwindex;
			}
		}
		void schrijf();
};
template<typename Sleutel, typename Data>
unsigned int ExtHash<Sleutel,Data>::berekenidebit(unsigned int index ,int i){
		i--;
		return (index & 1<< i)>>i;
}



template<typename Sleutel, typename Data>
void ExtHash<Sleutel,Data>::schrijf(){
	for(int i=0; i<this->size(); i++){
		blokindex bloki = this->operator[](i);
		cout<<"lezen van bloki: "<<bloki<<endl;
		Schijfpagina<Sleutel,Data> buffer;
		this->schijf.lees(buffer, bloki);
		buffer.schrijf();
	}
}
template<typename Sleutel, typename Data>
bool ExtHash<Sleutel,Data>::voegToe(const Sleutel& sleutel, const Data& data){
	unsigned int grote_index = sleutel.geefLinhashindex();
	// kan ook currsize zijn. 
	int plaatsnummer = grote_index % (int) pow(2.0,d);
	blokindex bloki = this->operator[](plaatsnummer);
//	cout<<"ik gebruik bloki: "<<bloki<<endl;
//	if(bloki == 0){
//		Schijfpagina<Sleutel,Data> nieuwebuffer;
//		bloki = schijf.schrijf(nieuwebuffer);
//		this->operator[](plaatsnummer) = bloki;
//	}
	Schijfpagina<Sleutel,Data> buffer;
	schijf.lees(buffer, bloki);
//	cout<<"ik heb een buffer ingelezen"<<endl;
//	buffer.schrijf();
	
	if(buffer.isVol()){
//		cout<<"ik ben vol"<<endl;
		int k = ++buffer.k;
		Schijfpagina<Sleutel,Data> linksebuffer(k);
		Schijfpagina<Sleutel,Data> rechtsebuffer(k);

//		cout<<"nieuwe k: "<<k<<endl;
		if(k<=d){
			// eerste geval
//			cout<<"eerste geval"<<endl;
			// beter zou zijn dat we sorteren op k+1 en dan zoeken naar deze grenswaarde --> alles erna weg.
			for(int i=0; i<buffer.indexteller; i++){
				if(berekenidebit(buffer.sleutels[i].geefLinhashindex(),k)){
//					cout<<"ik heb een 1 "<<endl;
//					cout<<"sleutel"<<buffer.sleutels[i]<<endl;
					linksebuffer.voegDataToe(buffer.sleutels[i],buffer.data[i]);
				}else{
//					cout<<"ik heb 0"<<buffer.sleutels[i]<<endl;
					rechtsebuffer.voegDataToe(buffer.sleutels[i],buffer.data[i]);
				}
				//nieuwe sleutel toevoegen
			
			}
			if(berekenidebit(sleutel.geefLinhashindex(),k)){
//					cout<<"ik heb een 1 "<<endl;
//					cout<<"sleutel"<<sleutel<<endl;
					linksebuffer.voegDataToe(sleutel,data);
			}else{
//					cout<<"ik heb 0 nieuwe "<<sleutel<<endl;
					rechtsebuffer.voegDataToe(sleutel,data);
			}
			blokindex nieuwe_index = schijf.schrijf(rechtsebuffer);
			schijf.herschrijf(linksebuffer, bloki);
			if((d-k) <= 0){
				cout<<"ik ben hier";
				this->operator[](plaatsnummer% (int) pow(2.0,k-1)) = nieuwe_index;
			}else{
				for(int i=0; i<this->size();i++){
//					rechtse buffer bevat alles met een 0!!!!
//					cout<<"mijn k is"<<k<<"met index"<<buffer.sleutels[i]<<endl;
//					cout<<"voorwaarde2: "<<(buffer.sleutels[i].geefLinhashindex() % (int) pow(2.0,(k-1)))<<endl;
//					cout<<"voorwaarde3: "<<(plaatsnummer% (int) pow(2.0,(k-1)))<<endl;
				if(berekenidebit(i,k)==0 && (i % (int) pow(2.0,(k-1))) == (plaatsnummer% (int) pow(2.0,(k-1)) ) ){
					this->operator[](i) = nieuwe_index;

				}else{
				}
				}
			}
		
		}else{
//			cout<<"resizen"<<endl;
			d++;
			this->resize(pow(2.0,d));
			for(int i=0; i<buffer.indexteller; i++){
				if(berekenidebit(buffer.sleutels[i].geefLinhashindex(),k)){
//					cout<<"ik heb een 1 "<<endl;
//					cout<<"sleutel"<<buffer.sleutels[i]<<endl;
					linksebuffer.voegDataToe(buffer.sleutels[i],buffer.data[i]);
				}else{
//					cout<<"ik heb 0"<<buffer.sleutels[i]<<endl;
					rechtsebuffer.voegDataToe(buffer.sleutels[i],buffer.data[i]);
				}
			}
			if(berekenidebit(sleutel.geefLinhashindex(),k)){
//					cout<<"ik heb een 1 "<<endl;
//					cout<<"sleutel"<<sleutel<<endl;
					linksebuffer.voegDataToe(sleutel,data);
			}else{
//					cout<<"ik heb 0 nieuwe "<<sleutel<<endl;
					rechtsebuffer.voegDataToe(sleutel,data);
			}
			blokindex nieuwe_index = schijf.schrijf(rechtsebuffer);
			schijf.herschrijf(linksebuffer, bloki);
			
			for(int i= this->size()/2 ; i<this->size(); i++){
				if(this->operator[](i)==0){
					this->operator[](i)=this->operator[](i-this->size()/2);
				}
			}
			this->operator[](plaatsnummer)=nieuwe_index;
			this->operator[](plaatsnummer+this->size()/2)=bloki;			
			
		}
		
	}else{
		buffer.voegDataToe(sleutel, data);	
		schijf.herschrijf(buffer, bloki);
		schijf.lees(buffer, bloki);
		Schijfpagina<Sleutel,Data> nieuweBuffer;
		schijf.lees(nieuweBuffer, bloki);
//		cout<<"ik schrijf de pas ingelezen schijfpagina uit"<<endl;
//		nieuweBuffer.schrijf();
	}
}



template <typename Data, typename Sleutel>
class Schijfpagina{
	friend class ExtHash<Sleutel,Data>;
	protected:
		int k;
		vector<Sleutel> sleutels;
		vector<Data> data;
		unsigned int capaciteit;
		//blokken intern
		blokindex indexteller;
		//blokken extern
		blokindex volgende;
	public:
		Schijfpagina():capaciteit(2),volgende(0),indexteller(0),k(0){
			data.resize(2);
			sleutels.resize(2);
		};
		Schijfpagina(const int& k):capaciteit(2),volgende(0),indexteller(0),k(k){
			data.resize(2);
			sleutels.resize(2);
		};
		
		
		void schrijf()const{
			cout<<"---schijf met k="<<k<<endl;
			for(int i=0; i<indexteller; i++){
  				  std::cout << "------"<<sleutels[i] << " " << data[i]<< "\n";
			}
		}		
		Schijfpagina<Sleutel, Data>& operator = (const Schijfpagina<Sleutel, Data>& t){
//			cout<<"Copy assignment"<<endl;
//			cout<<"sleutel t"<<t.sleutels[0]<<endl,
			this->capaciteit = t.capaciteit;
			this->sleutels = t.sleutels;
			this->data = t.data;
			this->indexteller = t.indexteller;
			this->volgende = t.volgende;
			this->k=t.k;
			return *this;
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
		
		void voegDataToe(const Sleutel & sl,const Data& data_){
//			cout<<"starten van toevoegen sl: "<<sl<<endl;
			blokindex loper = indexteller;
//			cout<<"indexteller: "<<loper<<endl;
//			if(loper >= 1) cout<<"sleutel-1: "<< sleutels[loper-1] <<endl;
			while(loper>0 && sleutels[loper-1] > sl){
//				cout<<"lopen"<<endl;
				sleutels[loper]=sleutels[loper-1];
				data[loper]=data[loper-1];
				loper--;
			}
//			cout<<"hier met loper: "<<loper<<endl;
			sleutels[loper] = sl;
			data[loper] =data_;
			++indexteller;
		}				

};
