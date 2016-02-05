#ifndef __DebruijneGraaf
#define __DebruijneGraaf

#include "graaf.h"
#include <string>
#include "woord.h"

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
		vector<int> bezocht;
		map<string,int> reeksen;
		
	private: 
		void geefNaburigeString(string&, vector<int>&);
		int berekenmacht(const int&,const int&);

//		vector<string> get_all_words(int length);

};
template<int m, int n>
string DebruijneGraaf<m,n>::resolve(){
	
	
	
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

