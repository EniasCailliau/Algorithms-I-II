#ifndef __STROOMNET_H
#define __STROOMNET_H
#include "graaf.h"
#include <cassert>
#include <iostream>
using std::vector;
using std::ostream;

template< class T >
class Pad:public std::vector< int >{
public:
    T geefCapaciteit() const{
        return capaciteit;
    }
    void zetCapaciteit(const T& _capaciteit){
        capaciteit=_capaciteit;
    }
friend ostream& operator<<(ostream& os, const Pad& p){
    os<<"Capaciteit= "<<p.capaciteit<<" :: ";
    if (p.size() > 0){
        os<<p[0];
    }
    for (int i=1; i<p.size(); i++ ){
        os<<"->"<<p[i];
    }
    os<<"\n";
}
protected:
    T capaciteit;
};
/**********************************************************************

   Class:Vergrotendpadzoeker
   
   beschrijving: Methodeklasse die, gegeven een stroomnetwerk,
                 een vergrotend pad teruggeeft.
                 van en naar zijn de knoopnummers van bron en doel.

   
***************************************************************************/
template <class T>
class Vergrotendpadzoeker{
public:
    Vergrotendpadzoeker(const GraafMetTakdata<GERICHT,T>& stroomnetwerk, int van, int naar, Pad<T>& pad);
protected:
    virtual void foo(int t, int x);
    const GraafMetTakdata<GERICHT,T>& graaf;
    Pad<T>& p;
    vector<int> l;
    vector<bool> m;
    int v,v2;
};


template <class T>
Vergrotendpadzoeker<T>::Vergrotendpadzoeker(const GraafMetTakdata<GERICHT ,T>& gr,int _v,int _v2,Pad<T>& _p):
                    p(_p), graaf(gr),v(_v),v2(_v2),
                    l(graaf.aantalKnopen()), m(graaf.aantalKnopen(),false){
    p.clear();
    assert(v != v2);
    foo(v,0);
    assert(p.size()!=1);
    if (p.size() > 1){
//    	bepaal het minimun capaciteit van het pad
        T min=*graaf.geefTakdata(p[0],p[1]);
        for (int i=2; i<p.size(); i++ ){
            T data=*graaf.geefTakdata(p[i-1],p[i]);
            if (data<min)
                min=data;
        }
        p.zetCapaciteit(min);
    }
}

template <class T>
void Vergrotendpadzoeker<T>::foo(int knoop,int niveau){
    m[knoop]=true;
    const typename GraafMetTakdata<GERICHT,T>::Knoop& a=graaf[knoop];
    int huidigniveau=niveau+1;
    for (typename GraafMetTakdata<GERICHT,T>::Knoop::const_iterator it=a.begin();it!=a.end();it++){
        int buur=it->first;
        if (*graaf.geefTakdata(knoop,buur)> 0){ // verbinding bestaat
            if (buur==v2){
                l[buur]=knoop;
                p.resize(huidigniveau+1);
                int tmpbuur=buur;
                int i=huidigniveau;
                while (tmpbuur!=v){
                    p[i]=tmpbuur;
                    i=i-1;
                    tmpbuur=l[tmpbuur];
                }
                p[0]=tmpbuur;
            }
            else if(!m[buur]){
                l[buur]=knoop;
                foo(buur,huidigniveau);
            }
        }
    }
}

/**********************************************************************

   Class: Stroomnetwerk
   
   beschrijving: Een stroomnetwerk gaat uit van een gewogen gerichte graaf
                 die in de constructor wordt opgegeven
   
***************************************************************************/

template <class T>//T = takdata
class Stroomnetwerk:public GraafMetTakdata<GERICHT, T >{
public:
	//Copyconstructor. Let op: Graaf<GERICHT>(gr) moet toegevoegd,
	//anders roept de copyconstructor van GraafMetTakdata de defaultconstructor
	//van Graaf op en krijgen we een lege graaf.
	Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr):
	                    Graaf<GERICHT>(gr),GraafMetTakdata<GERICHT, T>(gr){};


	Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr, int _van, int _naar):
    	                Graaf<GERICHT>(gr.aantalKnopen()),van(_van),naar(_naar){
	    Stroomnetwerk<T> restnetwerk(gr);
	    Pad<T> vergrotendpad;
	    Vergrotendpadzoeker<T> vg(restnetwerk, van, naar, vergrotendpad);
	    while(vergrotendpad.size() !=0 ){
	    	this->cap += vergrotendpad.geefCapaciteit();
	        restnetwerk-=vergrotendpad;
	        *this+=vergrotendpad;
	        Vergrotendpadzoeker<T> vg(restnetwerk, van, naar, vergrotendpad);
	    }
	}

	Stroomnetwerk<T> operator-=(Pad<T> pad){
		//verwijderVerbinding()
		int van = pad[0];
		for(int i=1;i<pad.size();i++){
			int naar = pad[i];
			T *data = this->geefTakdata(van,naar);
			*data-=pad.geefCapaciteit();
//			this->verwijderVerbindingUitDatastructuur(van,naar);
			data = this->geefTakdata(naar,van);
			if(data != 0){
				*data += pad.geefCapaciteit();
			}else{
				this->voegVerbindingToe(naar,van,pad.geefCapaciteit());
			}
			van = naar;
		}
		return *this;
	}

	Stroomnetwerk<T> operator+=(Pad<T> pad){
		//verwijderVerbinding()
		int van = pad[0];
		for(int i=1;i<pad.size();i++){
			int naar = pad[i];
			//takdatavector[vn]-=pad.geefCapaciteit();
			T *data = this->geefTakdata(van,naar);
			if(data != 0){
				*data += pad.geefCapaciteit();
			}else{
				data = this->geefTakdata(naar,van);
				if(data != 0){
					T tmp = *data - pad.geefCapaciteit();
					if(tmp < 0){
						this->verwijderVerbinding(naar,van);
						this->voegVerbindingToe(van,naar,-tmp);
					}else{
						*data -= pad.geefCapaciteit();
						if(*data == 0){
							this->verwijderVerbinding(naar,van);
						}
					}
				}else{
					this->voegVerbindingToe(van,naar,pad.geefCapaciteit());
				}
			}
//			this->voegVerbindingToe(naar,van,pad.geefCapaciteit());
			van = naar;
		}
		return *this;
	}

	T geefCapaciteit(){
		return cap;
	}

protected:
	int van,naar;
	T cap = 0;
};
#endif
