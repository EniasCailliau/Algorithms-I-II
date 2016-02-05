#ifndef __SORTVECTOR
#define __SORTVECTOR

//sortvector is een klasse van sorteerbare vectoren

#include <iostream>
   using std::istream;
   using std::ostream;
#include <iomanip>   // voor setw
#include <cstdlib>   // voor rand - opletten!! 
#include "sorteermethode.h"

template<class T>
class Sortvector{                                       
  public:

    // Constructor: het argument geeft de grootte aan
    // bij constructie zal de tabel opgevuld worden met 
	// n verschillende getallen in random volgorde
    // (zie hulplidfunctie)
    Sortvector(int);
    
    // Geeft onderstaande code compileerfouten of warnings?
    // Zorg dat de compiler C++11-code aankan.
    // In Dev-C++: 
	// in menubalk: Tools - compiler options - general - 
	// 'add the following commands when calling the compiler': -std=c++11
    Sortvector(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(Sortvector<T>&& v) = delete;
    Sortvector(Sortvector<T>&& v) = delete;

    const T &operator[](int i) const { return tab[i]; }  // voor rechterlid
          T &operator[](int i)       { return tab[i]; }  // voor linkerlid
    
    void vul_range();
    void draai_om();
    void vul_omgekeerd();
    void shuffle();
    void vul_random_zonder_dubbels();
    void vul_random(); // nog niet implementeren
    
    // Hier komen eigenschappen
    bool is_gesorteerd() const;
	bool is_range() const;
	int size() const;

	// Dit is een key feature!! Dit zorgt ervoor dat de INTERNE vector gesorteerd wordt!
	// sorteer sorteert de tabel.
    // Het argument geeft de sorteermethode aan
	void Sorteer(const Sorteermethode<T>& sm);

    friend ostream& operator<<(ostream& os, const Sortvector<T>& s){
  	    s.schrijf(os);
  	    return os;
    }

  private: 
    vector<T> tab;
    void schrijf(ostream & os)const;
    
};

template <class T>
void Sortvector<T>::schrijf(ostream & os)const{
	for(int i=0; i<tab.size(); i++){
		os<<tab[i]<<" ";
	}
	os<<endl;
}
template <class T>
Sortvector<T>::Sortvector(int d):tab(d) {
	vul_random_zonder_dubbels();
}

template <class T>
void Sortvector<T>::vul_range(){
	for(int i=0; i<tab.size(); i++){
		tab[i]=i;
	}
}
template <class T>
void Sortvector<T>::draai_om(){
	std::reverse(tab.begin(),tab.end());	
}
template <class T>
void Sortvector<T>::vul_omgekeerd(){
	for(int i=0; i<tab.size(); i++){
		tab[i]= tab.size()-1-i;
	}
}
template <class T>
void Sortvector<T>::shuffle(){
	for(int i=tab.size()-1; i > 0 ; i--){
	int j = rand()%i;
	//T h= tab[i];
	//tab[i]= tab[j];
	//tab[j]= h;
	std::swap(tab[i],tab[j]);
	}
	
}

template <class T>
void Sortvector<T>::vul_random_zonder_dubbels(){
	vul_range();
	shuffle();
}
template <class T>
bool Sortvector<T>::is_gesorteerd() const{
	T vorig= tab[0];
	for(int i=1; i<tab.size(); i++){
		if(tab[i] < vorig) return 0;
		vorig = tab[i];
	}
	return 1;
}
template <class T>
bool Sortvector<T>::is_range() const{
	for(int i=0; i<tab.size(); i++){
		if(tab[i]!=i) return 0;
	}
	return 1;
}

template <class T>
void Sortvector<T>::Sorteer(const Sorteermethode<T>& sm){
	sm(tab);
}

template <class T>
void Sortvector<T>::vul_random(){
	for(int i=0; i<tab.size(); i++){
		tab[i]= rand()%80;
	}
}
template <class T>
int Sortvector<T>::size() const{
	 return tab.size();
}


// Het volgende is geen lidfunctie van een klasse.
// Deze externe procedure schrijft naar os een overzicht (met de nodige ornamenten) 
// met de snelheid van de opgegeven sorteermethode sm. Er wordt 1 lijn uitgedrukt voor elke mogelijke
// grootte. Deze groottes zijn kleinste, 10*kleinste, 100*kleinste,
// enzovoorts, tot aan grootste.
// Op een lijn staat de snelheid van de methode toegepast op
// (1) een random tabel
// (2) een al gesorteerde tabel.
// (3) een omgekeerd gesorteerde tabel.

// Deze functie werkt alleen als T een toekenning van een int toelaat,
// zodat bv.
//    T a=5;
// geldig is.
template<class T>
void meet(int kortste, int langste, const Sorteermethode<T> &  sm, ostream& os);




#endif
