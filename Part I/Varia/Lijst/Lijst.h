#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
class Lijstknoop;

template <typename T>
class Lijst{
	public:
		Lijst();
		Lijst(const Lijst<T>& l);
		~Lijst();
		Lijst<T>& operator=(const Lijst<T>& l);
		void VoegToeAchteraan(const T& d);
		void VoegToeVooraan(const T& d);
		void Append(const Lijst<T>* l);
		void Print();
		int size();
		void PrintRecursief(ostream & os);
		Lijst<T>* zoek_gerangschikt(const T& d);
		void insertion_sort();
		Lijst<T>* ZoekMax();
		T ZoekMaxwaarde();
		void selection_sort();
		Lijst<T>* ZoekMin();
		void selection_sort2();
		void ShellSort();
		
		ostream & operator<<(ostream & os){
			this->PrintRecursief(os);
			return os;
		}
	//private:
		Lijstknoop<T>* k;	
};

template <typename T>
class Lijstknoop{
	friend class Lijst<T>;
	public:
		Lijstknoop(const T& d=T());
		void Print(ostream& os);
	//private:
		T sl;
		Lijst<T> volgend;
};



template <typename T>
Lijst<T>::Lijst(){
	k= nullptr;
}



// Idee van een copy constructor:
// *this bestaat al, ik ga steeds een naar een nieuw gemaakte lijstknoop wijzen.
// KEUZE: ofwel maak ik een copyconstructor voor lijst, ofwel haal ik de lijst uit
// Merk op dat ik hier niet 2 lopende pointers naar lijst nodig heb
// Maar enkel een pointer naar lijst en een pointer naar lijstknoop (om te copieren)

template <typename T>
Lijst<T>::Lijst(const Lijst<T>& l){
	Lijst<T> * loper = this;
	Lijstknoop<T> * tocopy = l.k;
	while(tocopy){
		loper->k = new Lijstknoop<T>(tocopy->sl);
		loper = &(loper->k->volgend);
		tocopy = tocopy->volgend.k;
	}
	
}

// DESTRUCTOR : delete op een pointer zorgt dat de data waarnaar verwezen wordt
// automatsich verwijderd wordt.
template <typename T>
Lijst<T>::~Lijst(){
	delete k;
}

// COPY ASSIGNMENT : Belangrijk! controleren of ik niet mijzelf assigneer,
// Indien ja, dan doe ik niets. Anders ga ik alle lijstknopen kopiëren zoals hierboven.
// Merk op!! Eerst delete k; stel l is een lege lijst-> while lus niet gebruikt
// Maar ik wijs nog naar verkeerde elementen. --> delete k nodig
template <typename T>
Lijst<T>& Lijst<T>::operator=(const Lijst<T>& l){
	if(this != &l){
		delete k;
		Lijst<T> * loper = this;
		Lijstknoop<T> * tocopy = l.k;
		while(tocopy){
		loper->k = new Lijstknoop<T>(tocopy->sl);
		loper = &(loper->k->volgend);
		tocopy = tocopy->volgend.k;
		}
	
	}
	return *this;
}

template<typename T>
void Lijst<T>::Append(const Lijst<T>* l){
	if(this!=l){
	Lijst<T>* loper = this;
	while(loper->k){
		loper = &(loper->k->volgend);
	}
	// loper wijst nu naar laatste
	loper->k = l->k;
	}
}

template <typename T>
void Lijst<T>::VoegToeAchteraan(const T& d){
	Lijst<T> * loper= this;
	while(loper->k){
		loper = &(loper->k->volgend);
	}
	loper->VoegToeVooraan(d);
}


// zie tekening!!!
template <typename T>
void Lijst<T>::VoegToeVooraan(const T& d){
	Lijstknoop<T> * nieuw = new Lijstknoop<T>(d);
	nieuw->volgend.k = this->k;
	this->k = nieuw;
}


template <typename T>
void Lijst<T>::Print(){
	Lijst<T> * loper= this;
	while(loper->k){
		cout<<loper->k->sl<<" ";
		loper = &(loper->k->volgend);
	}
}

template <typename T>
void Lijst<T>::PrintRecursief(ostream & os ){
	if(this->k){
		os << this->k->sl;
		this->k->volgend.PrintRecursief(os);	
	}
}

template <typename T>
Lijst<T>* Lijst<T>::zoek_gerangschikt(const T& d){
	Lijst<T> * loper = this;
	while(loper->k && loper->k->sl < d){
		loper= &(loper->k->volgend);
	}
	return loper;
}



// belangrijk!! Unsorted al toegekend aan plaats->k DUS mag je de waarde van unsorted reeds veranderen. 
// Dus geen probleem
template <typename T>
void Lijst<T>::insertion_sort(){
	Lijstknoop<T>* unsorted = k;
	k = nullptr;
	while(unsorted){
//		Lijst<T>* plaats = zoek_gerangschikt(unsorted->sl); 
//		Lijstknoop<T>* h = plaats->k;
//		plaats->k = unsorted;
//		unsorted = unsorted->volgend.k;
//		plaats->k->volgend.k = h;

		Lijst<T>* plaats= zoek_gerangschikt(unsorted->sl);
		Lijstknoopptr<T> hulp=std::swap(plaats->get()->volgend);
		std::swap(*plaats,ongesorteerd);
		ongesorteerd=std::move(plaats->get()->volgend);
		plaats->get()->volgend=std::move(hulp);
	}
}

template <typename T>
void Instertionsort(vector<T>& v){
	for(int i=1 ; i<v.size(); i++){
		T h = v[i];
		int j = i-1;
		while(j >= 0 && h < v[j] ){
			v[j+1] = v[j];
			j--;
		}
		v[j+1]=h;
	}
}

template <typename T>
Lijst<T>* Lijst<T>::ZoekMax(){
	Lijst<T> * loper = this;
	Lijst<T> * max = this;
	while(loper->k){
		if(loper->k->sl > max->k->sl) max=loper;
		loper = &(loper->k->volgend);
	}
	return max;
}

template <typename T>
T Lijst<T>::ZoekMaxwaarde(){
	Lijst<T>* maxl = ZoekMax();
	return maxl->k->sl;
}


// Dit is een implementatie van selectionsort door het maximum steeds achteraan te plaatsen.
template<typename T>
void Lijst<T>::selection_sort(){
	//Lijst<T> * unsorted = this;
	Lijstknoop<T> * sorted = nullptr;
	while(k){
		Lijst<T> * max = this->ZoekMax(); //mag gewoon ZoekMax zijn
		Lijstknoop<T>* futsorted = max->k;
		max->k = max->k->volgend.k;
		futsorted->volgend.k = sorted;
		sorted = futsorted;
	}
	k = sorted;
}

template <typename T>
Lijst<T>* Lijst<T>::ZoekMin(){
	Lijst<T>* loper = this;
	Lijst<T>* min = this;
	while(loper->k){
		if(loper->k->sl < min->k->sl) min=loper;
		loper = &(loper->k->volgend);
	}
	return min;
}

// Dit is een implementatie van selectionsort door het minimum steeds vooraan te plaatsen
template<typename T>
void Lijst<T>::selection_sort2(){
	Lijst<T>* unsorted = this;
	while(unsorted){
		cout<<"stap";
		Lijst<T>* min = unsorted->ZoekMin();
		Lijstknoop<T>*h = unsorted->k;
		unsorted->k = h->volgend.k;
		h->volgend.k = min->k->volgend.k;
		unsorted->k->volgend.k = h;
		unsorted= &(h->volgend);
		this->Print();	
	}
}



template <typename T>
void Print(const vector<T> & v){
	for(int i=0; i<v.size(); i++){
		cout<< v[i] << " ";
	}
	cout<< endl;
}


template<typename T>
int Lijst<T>::size(){
	if(k==0) return 0;
	return k->volgend.size()+1; 
}

//// TODO
//template <typename T>
//void Lijst<T>::shell_sort(){
//	int gap=6;
//	while(gap>=1 ){
//		 shell_sort(this , gap);
//		 gap = gap/2;
//	}
//
//}

//template <typename T>
//void Lijst<T>::shell_sort(Lijst<T> * begin, int gap){
//	Lijst<T>* vorige = begin;
//	Lijst<T>* loper = begin;
//	// ik moet gap stappen naar voor
//	for(int i=0 ; i<gap ; i++){
//		loper=&(loper->k->volgend);
//	}
//	
//	
//	
//}




//template <typename T>
//void Lijst<T>::shell_sort( Lijst<T> *begin, int gap){
//
//Lijst<T> *vorige = begin;
//Lijst<T> * loper = &(vorige->k->opv) ;
//	//int gap=;
//	int i=0;
//	while(loper->k!=0 && i<=gap ){
//	i++	;
//	//gewoon lijst afgaan	
//		if(i==gap  ){
//			cout<<vorige->k->data<<" "<<loper->k->data <<endl;
//			if(vorige->k->data < loper->k->data)
//			swapt(vorige,loper) ;
//			cout<<vorige->k->data<<" "<<loper->k->data <<endl<<endl;
//	
//		this->print();
//		i=0;
//				}			
//			loper = &(loper->k->opv);			
//	}
//		
//int	j=0;
//		while(vorige->k!=0 && j<gap ){
//				j++;
//			vorige = &(vorige->k->opv);
//		
//		
//		}
//	cout<<j<<" hier "<<gap<<endl;
//		
//	if( vorige->k!=0 && j == gap  ){
//	
//			shell_sort(vorige, gap);		
//		}
//	
//
//
//}


//lijstknoop
template <typename T>
Lijstknoop<T>::Lijstknoop(const T&d){
	sl=d;
}

template <typename T>
void Lijstknoop<T>::Print(ostream& os){
	os<<sl;
}



