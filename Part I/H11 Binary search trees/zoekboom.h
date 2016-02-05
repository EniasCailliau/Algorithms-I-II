#ifndef __ZOEKBOOM_H
#define __ZOEKBOOM_H

#include <iostream>   // voor test/debugfase
	using std::cin;
	using std::cout;
	using std::cerr;
	using std::endl;
#include <fstream>
	using std::ostream;
	using std::istream;
#include <string>
	using std::string;
#include <memory>
	using std::unique_ptr;
#include "sortvector.h"
#include "sorteermethode.h"

#include <queue>
	using std::queue;
	
#include <cstdlib>

template <class T>
class Knoop;

template <class T>
class Zoekboom: protected unique_ptr<Knoop<T> > {
	using unique_ptr<Knoop<T> >::unique_ptr;
	public:
		Zoekboom();
		Zoekboom(Sortvector<T>&);
		Zoekboom(const Zoekboom &) = delete;
// move constructor
		Zoekboom(Zoekboom && zb):  unique_ptr<Knoop<T> >(std::move(zb)){}
		Zoekboom& operator=(const Zoekboom<T> &) = delete;
// move assignment
		Zoekboom& operator=(Zoekboom<T> && zb){
			 unique_ptr<Knoop<T> >::operator=(std::move(zb));
			 return *this;
		}
		~Zoekboom();
		
		bool voeg_toe(const T & sl);  // return false indien sl al aanwezig was in de boom
		
        int max_diepte()const;		
        double gem_diepte()const;		
		double gem_diepte2()const;		
	
        int aantal_knopen()const;
        int som_dieptes(int diepte)const;
        
        Zoekboom<T>* zoek(T sl);
        			T opvolger(const T& sl);
		void printlevelorder()const;


		void verwijderknoop(const T& sl);
		void verwijderknoop(Zoekboom<T>* plaats);

        T min();
        T max(); 
        Zoekboom<T>* zoekmax();
        
        // tijdelijk in public gedefiniëert om code te testen;
        void schrijf(ostream & out) const;  // zal inorder uitschrijven; 
		                                    // enkel sleutels (zelfs zonder linker/rechterkind - 
											// best aan te passen als je structuur wil controleren!)
	                                        // hier nog zonder iterator geimplementeerd
		
	protected:
		void voeg_midden_toe(Sortvector<T>&, int, int);
	    Zoekboom* plaats_van_sleutel(const T & sl);	  // geen const-pointer, anders kan je op die plaats niets toevoegen...
	    void voeg_wortel_toe(const T & sl);
	     Zoekboom<T>* zoekmin();
	
	friend ostream& operator<<(ostream & out, const Zoekboom<T> & b){
		b.schrijf(out);
		out<<" X";
		return out;
	}		
};

//________________________________________________________________

template <class T>
class Knoop{

    friend class Zoekboom<T>;
    
	public:
		Knoop(const T & sl_):sl(sl_){};
		
	private:
		T sl;
		Zoekboom<T> links,rechts;
		
};

//////////////////////////////////////////////////////////////////
/////////   GEGEVEN IMPLEMENTATIE                    /////////////

template <class T>
Zoekboom<T>::Zoekboom(){
	//cout<<" --defaultconstructor-- ";
}
// moet niets speciaals in



	
		
template <class T>
Zoekboom<T>::~Zoekboom(){
}
// moet niets speciaals in

template <class T>
bool Zoekboom<T>::voeg_toe(const T & sl){
	Zoekboom * hier = plaats_van_sleutel(sl);
	if(*hier == nullptr){
		hier->voeg_wortel_toe(sl);
		return true;
	}
	return false;
}

// wordt alleen opgeroepen als *this == nullptr
template <class T>
void Zoekboom<T>::voeg_wortel_toe(const T & sl){	
	*this = Zoekboom<T>( (unique_ptr<Knoop<T> >) (new Knoop<T>(sl)));
}


template <class T>
Zoekboom<T>* Zoekboom<T>::plaats_van_sleutel(const T & sl){
	if(*this == nullptr){
		return this;
	}
	if(this->get()->sl == sl){   
		return this;
	}
	if(this->get()->sl < sl){
		return this->get()->rechts.plaats_van_sleutel(sl);
	}
	else{
		return this->get()->links.plaats_van_sleutel(sl);
	}
}

// inorder uitschrijven geeft de gesorteerde volgorde
template <class T>
void Zoekboom<T>::schrijf(ostream & out) const {
	if(*this != nullptr){
		this->get()->links.schrijf(out);
		out<<this->get()->sl<<" ";
		this->get()->rechts.schrijf(out);
	}
}

//////////////////////////////////////////////////////////////////
/////////   EIGEN IMPLEMENTATIE                      /////////////
template <class T>
Zoekboom<T>::Zoekboom(Sortvector<T>& v){
	const InsertionSort<T> is;
	v.Sorteer(is);
	// NIET VERGETEN OPROEPEN OP ZELF!
	this->voeg_midden_toe(v,0,v.size()-1);
}

template <class T>
void Zoekboom<T>::voeg_midden_toe(Sortvector<T>& v, int begin, int eind){
	if(begin<=eind){
		int midden = begin+(eind-begin)/2;
		voeg_toe(v[midden]);
		this->get()->links.voeg_midden_toe(v,begin,midden-1);
		this->get()->rechts.voeg_midden_toe(v,midden+1,eind);
	}
}


template<class T>
int Zoekboom<T>::max_diepte()const{
	int ld,rd;
	if(*this == nullptr){
		return 0;
	}else{
		ld=this->get()->links.max_diepte();
		rd=this->get()->rechts.max_diepte();
		return ld>rd ? ld+1 : rd+1; 
	}
}

template<class T>
double Zoekboom<T>::gem_diepte2()const{
	return (double)som_dieptes(0)/aantal_knopen();

}

template<class T>
double Zoekboom<T>::gem_diepte()const{
	queue<const Zoekboom<T> *> q;
	q.push(this);
	int count=0;
	double totaal=0;
	while(!q.empty()){
		const Zoekboom<T> * b = q.front();
		q.pop();
		totaal+=b->max_diepte();
		if(b->get()->links) 
			q.push(&(b->get()->links));
		if(b->get()->rechts) 
			q.push(&(b->get()->rechts));
		count++;
	}
	cout<<totaal<<endl;
	cout<<count<<endl;
	return totaal/count;
}

template <class T>
int Zoekboom<T>::aantal_knopen()const{
    if(*this==nullptr){
        return 0;
    }
    int aantal_links = (*this)->links.aantal_knopen();
    int aantal_rechts = (*this)->rechts.aantal_knopen();
    return aantal_links+aantal_rechts+1;
}

template <class T>
int Zoekboom<T>::som_dieptes(int diepte)const{
    if((*this)!=nullptr){
        int diepte_links = (*this)->links.som_dieptes(diepte+1);
        int diepte_rechts = (*this)->rechts.som_dieptes(diepte+1);
        return diepte_links+diepte_rechts+diepte;
    }
    else{
        return 0;
    }
}

template <class T>
Zoekboom<T>*  Zoekboom<T>::zoek(T sl){	
	if(this->get()->sl==sl){
		return this;
	}else if(sl < this->get()->sl){
		// zoek in linkerboom
		return this->get()->links.zoek(sl);
	}else{
		// zoek in rechterboom
		return this->get()->rechts.zoek(sl);
	}
}




template <class T>
T  Zoekboom<T>::min(){
	Zoekboom<T>* zoek = zoekmin();
	return zoek->get()->sl;
}

template <class T>
T  Zoekboom<T>::max(){
	Zoekboom<T>* loper = this;
	while(loper->get()->rechts){
		loper=&(loper->get()->rechts);
	}
	return loper->get()->sl;
}
    
	
	    
template <class T>
Zoekboom<T>*  Zoekboom<T>::zoekmin(){
	Zoekboom* loper = this;
	while(loper->get()->links){
		loper=&loper->get()->links;
	}
	return loper;
}
template <class T>
Zoekboom<T>*  Zoekboom<T>::zoekmax(){
	Zoekboom<T>* loper = this;
	while(loper->get()->rechts){
		loper=&(loper->get()->rechts);
	}
	return loper;
}


template <class T>
T Zoekboom<T>::opvolger(const T& sl){
	// normaal ook naar boven navigeren maar hier kan dat niet.
	Zoekboom<T>* plaats = zoek(sl);
	if(plaats->get()->rechts==nullptr){
		cout<<"ik moet naar boven"<<endl;
		return 0;
	}else{
		return plaats->get()->rechts.min();
	}	
}

template <class T>
void Zoekboom<T>::printlevelorder()const{
	queue<const Zoekboom<T>*> q;
	q.push(this);
	while(!q.empty()){
		const Zoekboom<T>* boom = q.front();
		q.pop();
		cout<<boom->get()->sl<<"\t";
		// nu mijn kinderen op de stack duwen het is nu onmogelijk om meerdere keren dezelfde knoop tegen te komen 
		// want de deelbomen overlappen elkaar niet (is een boom, geen graaf)
		if(boom->get()->links) q.push(&(boom->get()->links));
		if(boom->get()->rechts) q.push(&(boom->get()->rechts));	
	}
}

template <class T>
void Zoekboom<T>::verwijderknoop(const T& sl){
	srand(sl);
	Zoekboom<T>* plaats=plaats_van_sleutel(sl);
	// drie scenario's
	if(plaats->get()->rechts && plaats->get()->links){
		//3. beide kinderen
		if(rand()%2==1){
			Zoekboom<T>* opvolger = plaats->get()->rechts.zoekmin();
			plaats->get()->sl=opvolger->get()->sl;
			verwijderknoop(opvolger);
		}else{
			Zoekboom<T>* opvolger = plaats->get()->links.zoekmax();
			plaats->get()->sl=opvolger->get()->sl;
			verwijderknoop(opvolger);
		}		
	}else if(plaats->get()->links || plaats->get()->rechts){
		//2. één kind
		if(plaats->get()->links) *plaats=std::move(plaats->get()->links);
		else *plaats=std::move(plaats->get()->rechts);
		
	}else{
		//1. geen kinderen
		*plaats=nullptr;
	}
}
template <class T>
void Zoekboom<T>::verwijderknoop(Zoekboom<T>* plaats){
	cout<<"hier"<<endl;
	if(plaats->get()->links || plaats->get()->rechts){
		//2. één kind
		if(plaats->get()->links) *plaats=std::move(plaats->get()->links);
		else *plaats=std::move(plaats->get()->rechts);
		
	}else{
		//1. geen kinderen
		*plaats=nullptr;
	}
}





#endif 

