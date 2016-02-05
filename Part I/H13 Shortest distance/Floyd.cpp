#include <vector>
using std::vector;
#include <string>
#include <stdexcept>
#include <sstream>
#include <limits>
#include <iostream>
#include <stack>
	using std::stack;
using std::ostream;
using std::cout;
#define ONEINDIG 9999


class GraafExceptie : public std::logic_error {
	public:
		GraafExceptie(const std::string &boodschap_) : std::logic_error(boodschap_) {}
};

std::ostream &operator<<(std::ostream &os, const GraafExceptie& exc){
	return os << exc.what();
}

//voor dichte gewogen grafen, laat ook negatieve gewichten toe
class DichteGraaf{
	public:
		DichteGraaf(int aantal_k);
		~DichteGraaf();
		void voeg_verbinding_toe(int van, int naar, int gewicht);
		void schrijf_buren(ostream &os);
		void schrijf_afstanden(ostream &os);
		void schrijf_voorlopers(ostream &os);
		int** bereken_kortste_afstanden(); //via het algoritme van Floyd Warshall
	private:
		void schrijf(ostream &os,int ** tabel);
		void controleer_knoopnummer(int k);
		int aantal_verbindingen;
		int aantal_knopen;
		int max_aantal_knopen;
		int ** buren;
		//voor floyd
		//int **voorlopers;
		//int **afstanden;
};

DichteGraaf::DichteGraaf(int aantal_k): aantal_knopen(aantal_k){
		aantal_knopen = 0;
		aantal_verbindingen = 0;
		//voorlopers=0;
		//afstanden=0;
		max_aantal_knopen = aantal_k;
		//geheugen ruimte alloceren
		buren = new int *[max_aantal_knopen];
		// voorlopers = new int *[max_aantal_knopen];
		// afstanden = new int *[max_aantal_knopen];
		for(int i=0;i<max_aantal_knopen;i++){
			buren[i] = new int[max_aantal_knopen];
			//voorlopers[i] = new int[max_aantal_knopen];
			//afstanden[i] = new int[max_aantal_knopen];
		}
		for(int i=0;i<max_aantal_knopen;i++){
			for(int j=0;j<max_aantal_knopen;j++){
				if(i!=j){
					buren[i][j]=ONEINDIG; //geen verbinding dus
				}
				else{
					// buur met zichzelf
					buren[i][j]=0;
				}
			}
		}
}
DichteGraaf::~DichteGraaf(){
	for(int i=0;i<aantal_knopen;i++){
		delete [] buren [i];
	//	delete [] voorlopers [i];
	//	delete [] afstanden [i];
	}
	//delete [] afstanden;
	// delete [] voorlopers;
	 delete [] buren;
}

void DichteGraaf::voeg_verbinding_toe(int van, int naar, int gewicht){
	controleer_knoopnummer(van);
	controleer_knoopnummer(naar);
	if(buren[van][naar]==ONEINDIG){
		aantal_verbindingen++;
		buren[van][naar]=gewicht;
	}
	else{
		std::ostringstream out;
        out << "verbinding " << van << "-" << naar << " bestaat al";
        throw GraafExceptie(out.str());
	}
}

void DichteGraaf::controleer_knoopnummer(int k){
	if(k<0 || k>= max_aantal_knopen){
		throw GraafExceptie("ongeldig knoopnummer");
	}
}

//correctie voor voorbeeld +1
void DichteGraaf::schrijf(ostream &os,int ** tabel){
	for(int i=0;i<max_aantal_knopen;i++){
		for(int j=0;j<max_aantal_knopen;j++){
			if(tabel[i][j]<ONEINDIG){
				std::cout<<tabel[i][j]+1<<"\t";
			}
			else{
				std::cout<<"-\t";
			}
		}
		std::cout<<"\n";
	}
}


//void DichteGraaf::schrijf_voorlopers(ostream &os){
//	os<<"voorlopermatrix\n";
//	schrijf(os,voorlopers);
//}
//void DichteGraaf::schrijf_afstanden(ostream &os){
//	os<<"afstandenmatrix\n";
//	schrijf(os,afstanden);
//}
void DichteGraaf::schrijf_buren(ostream &os){
	os<<"burenmatrix\n";
	schrijf(os,buren);
}



int** DichteGraaf::bereken_kortste_afstanden(){
//	geheugen reserveren en tabellen intialiseren
		int** voorlopers = new int *[max_aantal_knopen];
		int** afstanden = new int *[max_aantal_knopen];
		for(int i=0;i<max_aantal_knopen;i++){
			voorlopers[i] = new int[max_aantal_knopen];
			afstanden[i] = new int[max_aantal_knopen];
		}	
//		int voorlopers[max_aantal_knopen][max_aantal_knopen];
//		int afstanden[max_aantal_knopen][max_aantal_knopen];
		for(int i=0;i<max_aantal_knopen;i++){
			for(int j=0;j<max_aantal_knopen;j++){
				if(i==j || buren[i][j] == ONEINDIG ){
					voorlopers[i][j]=0; //geen voorloper
				}
				else {
					voorlopers[i][j] = i;
				}
				// A0 is een exacte kopie van de burenmatrix
				afstanden[i][j]=buren[i][j];
			}
		}
		
		//het eigenlijke algoritme
		for(int k=0;k<max_aantal_knopen;k++){
			for(int j=0;j<max_aantal_knopen;j++){
				for(int i=0;i<max_aantal_knopen;i++){
					int kost = afstanden[i][k] + afstanden[k][j];
					if(kost < afstanden[i][j]){
						afstanden[i][j] = kost;
						voorlopers[i][j] = voorlopers[k][j];
					}
				}
			}
		}
		cout<<"voorlopermatrix\n";
		schrijf(cout,voorlopers);
		cout<<"afstandenmatrix\n";
		schrijf(cout,afstanden);
		// tussen 1 en 2 uitschrijven
		stack<int>st;
		st.push(1);
		int i=0,j=1;
		while(j!=i){
			st.push(voorlopers[i][j]);
			j=voorlopers[i][j];
			cout<<"j is nu="<<j<<std::endl;
			if(j==0){
				 
			}
		} 
		// nu uitschrijven
		cout<<"weg van i naar j"<<std::endl;
		while(!st.empty()){
			cout<<st.top()<<"\t";
			st.pop();
		}
		cout<<std::endl;
	
				
}




int main(){
	DichteGraaf d(5);
	//voor een afbeelding van de graaf zie:
	//https://blog.cedric.ws/c-floyd-warshall-shortest-distance-explanation-code
	
	d.voeg_verbinding_toe(0,2,10);
	d.voeg_verbinding_toe(0,4,5);
	d.voeg_verbinding_toe(0,1,20);
	d.voeg_verbinding_toe(3,1,3);
	d.voeg_verbinding_toe(4,3,4);
	d.voeg_verbinding_toe(2,3,10);
	d.voeg_verbinding_toe(4,2,2);
	d.schrijf_buren(cout);
	int** ret= d.bereken_kortste_afstanden();
//	d.schrijf_afstanden(cout);
//	d.schrijf_voorlopers(cout);
	return 0;
}
