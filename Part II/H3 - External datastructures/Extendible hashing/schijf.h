#ifndef __SCHIJF
#define __SCHIJF
#include <map>
#include <iostream>

using namespace std;
using std::map;
typedef unsigned int blokindex;

template<class Data, class Sleutel>
class Bloklijst;

//naamgeving gaat uit van de gebruiker: schrijf is een schrijfoperatie naar
//de schijf, enzovoorts
template<class T>
class Schijf: private map<blokindex,T>{

public:
//schrijf: voegt een T toe aan de schijf. Geeft de index terug
    blokindex schrijf(const T& b){
        ++indexteller;
//this-> is nodig (bij sommige compilers) omdat de parametrisatie
//niet afgeleid kan worden uit de argumenten.
//		cout<<"ik ga een indexteller teruggeven: "<<indexteller<<endl;
        this->operator[](indexteller)=b;
        return indexteller;
    }
    void verwijder(blokindex bi){
        this->erase(bi);
    }
    void herschrijf(const T& b, const blokindex bi){
        this->operator[](bi)=b;
    }
    void lees(T& b, const blokindex bi){
        b=this->operator[](bi);
    }
    blokindex getIndex(){
    	return indexteller;
	}
//
//  einde interface
//
    Schijf(): map<blokindex,T >(),indexteller(666){
	};
private:
    blokindex indexteller;
    int id;
    
};


#endif
