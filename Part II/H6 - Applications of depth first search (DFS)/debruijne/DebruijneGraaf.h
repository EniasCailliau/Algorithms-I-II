#ifndef __DebruijneGraaf
#define __DebruijneGraaf

#include "graaf.h"
#include <string>
#include "woord.h"
#include "LinkedList.h"

using namespace std;


template<int m,int n>
class DebruijneGraaf: public virtual GraafMetKnoopdata<GERICHT,Woord<m,n-1>>{
	public: 
		DebruijneGraaf(){
			int bovengrens = berekenmacht(2,n-1);
			
			for(int i=0; i< bovengrens ; i++){
				this->voegKnoopToe(Woord<m,n-1>(i));
			}
			// nu alle buren berekenen
			int radix = berekenmacht(2, n-2);
			for(int i=0; i< bovengrens; i++){
				for(int j=0; j < m; j++){
					int buur = (i % radix)*m+j;
					this->voegVerbindingToe(i,buur);
				}
				
			}
		};
		string resolve();
	protected:
		vector<bool> bezocht;
//		map<string,int> reeksen;
		
	private: 
		void geefNaburigeString(string&, vector<int>&);
		int berekenmacht(const int&,const int&);
		bool heeftnogburen(vector<map<int,int>::iterator>& knopenmetburen);

//		vector<string> get_all_words(int length);

};
template<int m, int n>
string DebruijneGraaf<m,n>::resolve(){	
	vector<map<int,int>::iterator> onbezochteburen(this->aantalKnopen());
	for(int i=0; i<this->aantalKnopen(); i++){
		onbezochteburen[i] = this->knopen[i].begin();
	}
	cout<<"hier"<<endl;
//	vector<int> pad;
	LinkedList<int> pad;
	int startknoop = 0;
//	int loper= startknoop;
	int loper;
//				int positie_in_vector;
//	vector<int> bijvoegsel;
	
	while(heeftnogburen(onbezochteburen)){
//		cout<<"hier"<<endl;
		if(pad.empty()){
//			Het pad is leeg dat betekent dat ik bij een willekeurig punt mag beginnen.
// 			Willekeurig betekent hier eender welke knoop aangezien zeker elke knoop een verbinding heeft (samenhangende graaf)
//			Hierbij gebruiken we de waarde van startknoop als startknoop.
			loper= onbezochteburen[startknoop]->first;
			onbezochteburen[startknoop]++;
			positie_in_vector=0;

		}else{
//			for(int i=0; i<pad.size(); i++){
			LinkedList<int> * loper = &pad;
				if(this->knopen[i].end() != onbezochteburen[i]){
					startknoop = pad[i];
					loper = onbezochteburen[pad[i]]->first;
					onbezochteburen[pad[i]]++;
//					positie_in_vector=i;
//					bijvoegsel.clear();
//					for(int j=i+1; j<pad.size();j++){
//						bijvoegsel.push_back(pad[j]);
//					}
					break;
//					cout<<"loper:"<<loper<<"startknoop:"<<startknoop;
				}
			}
		}
		pad.push_back(startknoop);
		pad.push_back(loper);
		vector<int> subpad;
		subpad.push_back(startknoop);
		subpad.push_back(loper);
//		while(onbezochteburen[loper] != this->knopen[loper].end()){	
		while(loper != startknoop){
			int buur = onbezochteburen[loper]->first;
			onbezochteburen[loper]++;
//			pad.push_back(buur); 
			subpad.push_back(buur);
			loper = buur;	
//			cout<<"loper="<<loper<<"buur="<<buur<<endl; 
		}
		cout << "Pad: ";
		for(int i=0 ; i<subpad.size(); i++){
			Woord<m,n-1>::printlaatstechar(subpad[i]);
		}
		for(int i=0; i<subpad.size(); i++){
			pad[i+positie_in_vector]=subpad[i];
		}
		for(int i=0; i<bijvoegsel.size(); i++){
			pad[positie_in_vector+subpad.size()]=bijvoegsel[i];
		}	
			cout<<endl<<"finaal:"<<endl;

		for(int i=0 ; i<pad.size(); i++){
			Woord<m,n-1>::printlaatstechar(pad[i]);
		}
	}
	
	
//	for(int i=0 ; i<pad.size(); i++){
//		Woord<m,n-1>::printlaatstechar(pad[i]);
//	}	
	
//	cout<<endl;
	return "dd";
}


// Deze methode wordt gebruikt binnen Dijkstra; 
// returnwaarden: 
// - true: er is nog steeds een knoop die over buren beschikt
// - false: geen enkele knoop beschikt nog over een buur (alle iteratoren zijn op het einde)
template<int m, int n>
bool DebruijneGraaf<m,n>::heeftnogburen(vector<map<int,int>::iterator>& onbezochteburen){
	for(int i=0; i<onbezochteburen.size(); i++){
		if(this->knopen[i].end() != onbezochteburen[i]){
			return true;
		}
	}
	return false;
}


template<int m, int n>
int DebruijneGraaf<m,n>::berekenmacht(const int& basis,const int& macht){
	if(macht == 0){
		return 1;
	}
	int resultaat = basis;
	for(int i=1; i<macht; i++){
		resultaat *= basis;
	}
	return resultaat;
}





//vector<string> DebruijneGraaf::get_all_words(int length)
//{
//	
//char alphabet[] = {'a', 'b', 'c', 'd'};
//  vector<int> index(length, 0);
//  vector<string> words;
//
//  while(true)
//  {
//    string word;
//    for(int i=0;i<length;i++){
//    	word+="";
//    }
//    for (int i = 0; i < length; ++i)
//      word[i] = alphabet[index[i]];
//    words.push_back(word);
//
//    for (int i = length-1; ; --i)
//    { 
//      if (i < 0) return words;
//      index[i]++;
//      if (index[i] == 4)
//        index[i] = 0;
//      else
//        break;
//    }
//  }
//}


#endif

