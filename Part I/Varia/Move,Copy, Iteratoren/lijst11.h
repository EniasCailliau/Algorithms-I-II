//C++11-compatibele lijst. Ontbrekende elementen: move en copy, iterator
#ifndef __LIJST11_H
#define __LIJST11_H
//
// speciale code voor debuggen
//
#define DEBUG
//
//
//speciale code voor iteratoren
#define ITERATOR




#include <iostream>
#include <memory>
#include <algorithm>
using std::endl;
using std::ostream;

template<class T>
class Lijstknoop;
template<class T>
class Lijst;

template<class T>
using Lijstknoopptr=std::unique_ptr<Lijstknoop<T> >;
template<class T>
ostream& operator<<(ostream& os, const Lijst<T>& l);

template<class T>
class Lijst: private Lijstknoopptr<T>{
public:
//toekenning, constructoren
//overname constructoren van unique_ptr
using Lijstknoopptr<T>::Lijstknoopptr;

	public:
		Lijst(): Lijstknoopptr<T>(){}
		Lijst<T>(Lijstknoop<T>* lk): Lijstknoopptr<T>(lk){}
		Lijst(Lijst<T>&& l): Lijstknoopptr<T>(std::move(l)){}
		Lijst(const Lijst<T>& l){
			if(l){
				*this = new Lijstknoopptr<T>(new Lijstknoop<T>(l->sl));
				this->get()->volgend = l->volgend;		
			}
		}
		Lijst<T>& operator=(const Lijst<T>& l){
			if(l){
				if(this!=&l){
				//	*this=nullptr;	
					*this =  Lijst<T>(new Lijstknoop<T>(l->sl));
					(*this)->volgend = l->volgend;
				}
			}else{
				this->reset();
			}
		}		
		Lijst<T>& operator=(Lijst<T>&& l){
			Lijstknoopptr<T>::operator=(std::move(l));
			return *this;
		}

//operaties
//duplicaten zijn toegelaten.
    public: void voegToe(const T&);
//geefaantal geeft het aantal keer dat de sleutel voorkomt.
//gebruikt de zoekfunctie om door de lijst te lopen!
//zonder argument: geef lengte lijst
    public: int geefaantal(const T&) const;
    public: int geefaantal() const;
//verwijder verwijdert slechts het eerste exemplaar met de gegeven
//T, en geeft geen fout als de T niet gevonden wordt.
//gebruik de zoekfunctie om door de lijst te lopen!
    public: void verwijder(const T&);
//verwijder eerste knoop.
    public: void verwijderEerste();
    public: void insertionsort();
    void insertionsort2();
    void insertionsort3();
    protected: Lijst* zoek3(const T&);
// zoek geeft een pointer naar de Lijst die de sleutelwaarde bevat,
// en geeft een pointer naar de lege lijst op het einde als de sleutel niet
// voorkomt.
    protected: const Lijst* zoek(const T&) const;
    protected: Lijst* zoek(const T&);
//preconditie zoekgesorteerd: lijst is gesorteerd
//teruggeefwaarde: wijst naar Lijst waar sl staat/zou moeten staan.
    protected: Lijst<T>* zoekGesorteerd(const T& sl);


//uitschrijven: voor elke knoop de T-waarde, gescheiden door komma's
    friend ostream& operator<< <>(ostream& os, const Lijst& l);
    public: void schrijf(ostream & os) const;
//iterator; gaat ervan uit dat alles const is
    public: class iterator{
        public:
            iterator(Lijstknoop<T>* l=0){
            	huidigeknoop=l;
			}
            const T& operator*() const{
				return huidigeknoop->sl;
			}
            const iterator& operator++(){
            	iterator back(huidigeknoop);
            	huidigeknoop = huidigeknoop->volgend.get();
            	return back;
			}
            bool operator!=(const iterator& i){
            	return huidigeknoop != i.huidigeknoop;
			}
		private:
			Lijstknoop<T>* huidigeknoop;
    };
    iterator begin() const{
		return iterator(this->get());
	};
    iterator end() const{
		Lijstknoop<T>* loper = this->get();
		while(loper->volgend.get()){
			loper= loper->volgend.get();
		}
		return iterator(loper);
	};

};

template<class T>
class Lijstknoop{
    friend class Lijst<T>;
    public:
        Lijst<T> volgend;
        Lijstknoop(const T&);
        ~Lijstknoop();
    protected:
        T sl;
#ifdef DEBUG
public:
        static bool controle (int gemaakt, int verwijderd);
protected:
        static int aantalGemaakt;
        static int aantalVerwijderd;
#endif
};

template<class T>
int Lijstknoop<T>::aantalGemaakt=0;
template<class T>
int Lijstknoop<T>::aantalVerwijderd=0;

template<class T>
Lijstknoop<T>::Lijstknoop(const T& _sl):sl(_sl){
//    std::cerr<<"Knoop met sleutel "<<sl<<" wordt gemaakt\n";
    aantalGemaakt++;
}

template<class T>
Lijstknoop<T>::~Lijstknoop(){
//    std::cerr<<"Knoop met sleutel "<<sl<<" wordt verwijderd\n";
    aantalVerwijderd++;
}
#ifdef DEBUG
template<class T>
bool Lijstknoop<T>::controle (int gemaakt, int verwijderd){
    if (aantalGemaakt==gemaakt && aantalVerwijderd==verwijderd)
        return true;
    else{
        std::cerr<<"Fout bij controle:\n";
        std::cerr<<"Aantal gemaakte knopen   : "<<aantalGemaakt<<" (moet zijn: "<<gemaakt<<")\n";
        std::cerr<<"Aantal verwijderde knopen: "<<aantalVerwijderd<<" (moet zijn: "<<verwijderd<<")\n";
        throw "Mislukte controle";
    };

};
#endif

template<class T>
ostream& operator<<(ostream& os,const Lijst<T>& l){
#ifdef ITERATOR
    for (auto sleutel: l)
        os<<sleutel<<", ";
#else
    if (l.get()){
        os<<l.get()->sl<<", ";
        os<<l.get()->volgend;
    }
#endif
    return os;
};

template<class T>
void Lijst<T>::schrijf(ostream & os) const{
#ifdef ITERATOR
    if (this->get()!=0){
        os<<this->get()->sl;
        std::for_each (++begin(),end(),[&](const T& sl){ os<<" . "<<sl;} );
    }
#else
		// Hier hebben we een ruwe pointer nodig.
        Lijstknoop<T>* kn=this->get();
        if (kn!=0){
            os<<kn->sl;
            kn=kn->volgend.get();
        };
        while (kn != 0){
            os<<" . "<<kn->sl;
            kn=kn->volgend.get();
        };
    
#endif
};
//oplossing:


template<class T>
const Lijst<T>* Lijst<T>::zoek(const T& sl) const{
    const Lijst<T>* pl=this;
    while (*pl && pl->get()->sl !=sl)
        pl=&(pl->get()->volgend);
    return pl;
}
template<class T>
int Lijst<T>::geefaantal(const T& sl) const{
    const Lijst<T>* plaats=zoek(sl);
    //noot: plaats==0 is false zelfs als plaats een nulpointer is
    if (*plaats)
        return 1+plaats->get()->volgend.geefaantal(sl);
    else
        return 0;
};

template<class T>
int Lijst<T>::geefaantal() const{
    if (*this)
        return 1+this->get()->volgend.geefaantal();
    else
        return 0;
};

template<class T>
Lijst<T>* Lijst<T>::zoek(const T& sl){
    Lijst* pl=this;
    while (*pl && pl->get()->sl !=sl)
        pl=&(pl->get()->volgend);
    return pl;
}

template<class T>
void Lijst<T>::voegToe(const T& sl){
    Lijstknoopptr<T> nieuw(new Lijstknoop<T>(sl));
    Lijstknoopptr<T>::swap(nieuw->volgend);
    *this=std::move(nieuw);
}

template<class T>
void Lijst<T>::verwijderEerste(){
    if (this->get()!=0){
        Lijstknoopptr<T> staart(std::move(this->get()->volgend));
        this->reset();
        Lijstknoopptr<T>::swap(staart);
    }
}

template<class T>
void Lijst<T>::verwijder(const T& sl){
    zoek(sl)->verwijderEerste();
}

template<class T>
Lijst<T>* Lijst<T>::zoekGesorteerd(const T& sl){
    Lijst* plaats=this;
    while (*plaats && plaats->get()->sl < sl)
        plaats=&plaats->get()->volgend;
    return plaats;
};

template<class T>
void Lijst<T>::insertionsort(){
    Lijstknoopptr<T> ongesorteerd=std::move(*this);
    while (ongesorteerd){
        Lijst *plaats=zoekGesorteerd(ongesorteerd.get()->sl);
        Lijstknoopptr<T> dummy=std::move(ongesorteerd);
        //vermits ongesorteerd een nullpointer is, is het equivalent van volgende lijnen ongeveer
        //ongesorteerd=std::move(dummy.get()->volgend);
        //std::swap(*plaats,dummy.get()->volgend);
        std::swap(ongesorteerd,dummy.get()->volgend);
        dummy.get()->volgend=std::move(*plaats);
        *plaats=std::move(dummy);

    };
    
  
}

template<class T>
void Lijst<T>::insertionsort2(){
    Lijstknoopptr<T> ongesorteerd=std::move(*this);
    while (ongesorteerd){
//        Lijst<T>* plaats = zoekGesorteerd(ongesorteerd->sl);
//        Lijst<T> h= std::move(*plaats);
//        *plaats = std::move(ongesorteerd);
//        ongesorteerd = std::move(plaats->get()->volgend);
//        plaats->get()->volgend = std::move(h);

		Lijst<T>* plaats= zoekGesorteerd(ongesorteerd->sl);
		Lijstknoopptr<T> hulp(std::move(*plaats));
		std::swap(*plaats,ongesorteerd);
		ongesorteerd=std::move(plaats->get()->volgend);
		plaats->get()->volgend = std::move(hulp);
		
    }
}




template <class T>
void Lijst<T>::insertionsort3(){
 	Lijstknoopptr<T> ongesorteerd=std::move(*this);
 	while(ongesorteerd){
 		Lijst<T>* positie = zoek3(ongesorteerd->sl);
 		Lijst<T> tijd = std::move(*positie);
 		*positie = std::move(ongesorteerd);
 		ongesorteerd = std::move(positie->get()->volgend);
 		positie->get()->volgend = std::move(tijd);
	 }
 	
 }
template <class T>
Lijst<T>* Lijst<T>::zoek3(const T& sl){
    Lijst<T>* loper = this;
	while(*loper && loper->get()->sl < sl){
		loper=&(loper->get()->volgend);
	}
	return loper;
}












































#endif

