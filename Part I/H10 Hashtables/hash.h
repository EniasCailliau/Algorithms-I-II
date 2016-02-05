#include <vector>
#include <iostream>
#include <iomanip>
	using namespace std;
#include <cmath>
#include <cstdlib>
#include <time.h>

template <class T>
class Hashtabel;

// ik maak hier een klasse element, hierin zit een sleutel van een type en een bijhorende informatie van type. 
// dit element gebruik ik voor mijn hashtabellen

template <class T>
class Element{
	// hashtabel moet friend zijn anders kan hij niet zomaar aan de dataleden en moet ik getters en setters programmeren
	// luiaard!
	friend class Hashtabel<T>;
	public:
		Element():empty(true),removed(false),sl(0),b_info(0){}
		Element(const T& _sl,const T& info):sl(_sl),b_info(info),empty(false),removed(false){}
		// geen destructor nodig want geen pointers
	private:
		T sl;
		T b_info;
		bool empty;
		bool removed;
		
};

using namespace std;

template <class T>
class Hashtabel{
	public:
		Hashtabel(int _m=0):v(_m),m(_m){}
		void add(const T& sl,const T& info);
		T get(const T& sl);
		bool remove(const T& sl);
		// voor dev:
		void rehashtest(){rehash();
		}
		void Print(bool removed=false,bool empty=false){
			cout<<setw(10)<<"index:";
			for(int i=0;i<v.size(); i++){
				cout<<setw(4)<<i;
			}
			cout<<endl<<setw(10)<<"sleutel:";

			for(int i=0;i<v.size(); i++){
				cout<<setw(4)<<v[i].sl;
			}
			cout<<endl<<setw(10)<<"info:";
			for(int i=0;i<v.size(); i++){
				cout<<setw(4)<<v[i].b_info;
			}
			cout<<endl;
			if(empty){
			cout<<setw(10)<<"empty:";
			for(int i=0;i<v.size(); i++){
				cout<<setw(4)<<v[i].empty;
			}
			cout<<endl;	
			}
			if(removed){
			cout<<setw(10)<<"delete:";
			for(int i=0;i<v.size(); i++){
				cout<<setw(4)<<v[i].removed;
			}
			cout<<endl;	
			}
		
		}
	private:
		vector<Element<T>> v;
		int m; 
		int n=0;
		// voor universele
		int a,b,p;
	protected:	
		int hash(const T& sl);
		int sechash(const T& sl, int poging);
		int zoek(const T& sl);
		void rehash();
		// voor universele
		void bepaaluniversele();
		int zoek_priem(int l,int r);
};

// deze methode zoekt naar de lege of naar een aanwezig getal.
// wordt zowel gebruikt bij remove,get
// let op niet bij add want gaat niet ver genoeg zoeken en negeert verwijderd (zoals moet)
// met deze hashing kan de eerste if weggelaten worden. (commentaar)
template <class T>
int Hashtabel<T>::zoek(const T& sl){
	int poging=0;
	int index;
	while(poging < m){
		index = sechash(sl,poging++);
		// mag niet verwijderd zijn!
			if(!v[index].removed && (v[index].empty || v[index].sl==sl)){
				return index;
			}	
	}
}


template <class T>
void Hashtabel<T>::add(const T& sl, const T& info){
// Eerst controleren of de bezettingsgraad niet te groot wordt
	n++;
	if((double)n/m > 0.5){
		cout<<"ik ga rehashen, ik ben te dik (n="<<n<<",m="<<m<<")"<<endl;
		rehash();
	}	
	int index = hash(sl);
	if(v[index].empty || v[index].removed){
		v[index].sl=sl;
		v[index].b_info=info;
		v[index].empty=false;
	}else{
		//verder zoeken
		int poging=1;
		while(poging!=m){
			index = sechash(sl,poging++);
			if(v[index].empty || v[index].removed){
				v[index].sl=sl;
				v[index].b_info=info;
				v[index].empty=false;
				break; //belangrijk, het is geplaatst we gaan stoppen
			}
			poging++;	
		}
	}
}

template <class T>
int Hashtabel<T>::hash(const T& sl){
	///METHODE 1////
	return sl%m; // indien dit gebruikt wordt mag m niet 10^i, 2^i, even
	
	///METHODE 2////
//neemt altijd alleen meest beduidende deel door convertie naar int
	//double C=0.3;
	//return m*(C*sl-floor(C*sl));
	
	///METHODE 3////
	//return ((a*sl+b)%p)%m;
	
}

template <class T>
int Hashtabel<T>::sechash(const T& sl, int poging){
	///METHODE 1////
		//cout<<"index bepalen"<<endl;
	return (hash(sl)+poging)%m;
	///METHODE 2////
//		int c1=2,c2=3;
//		return (hash(sl)+c1*poging*poging+c2*poging)%m;
	///METHODE 3////
		//TODO
}

// Dit is eigenlijk hetzelfde als toevoegen van een waarde
// geeft -1 terug indien niet gevonden
template <class T>
T Hashtabel<T>::get(const T& sl){
	int index = zoek(sl);
	return v[index].sl==sl ? v[index].b_info : -1;
}


template <class T>
bool Hashtabel<T>::remove(const T& sl){
	n--;
	int index= zoek(sl);
	if(!v[index].empty && !v[index].removed){
		v[index].removed=true;
		return true;
	}
	return false;	
}

// voor de eenvoud heb ik hier in andere tijdelijke tabel gestopt zodat alle functies werken op de nieuwe tabel
// ook voor de eenvoud is hier m*2 genomen (moet hier eingelijk priemgetallen zijn)
template <class T>
void Hashtabel<T>::rehash(){
	vector<Element<T>>backup(v);
	v=vector<Element<T>>(m*2);
// de m waarde moet vooraf veranderd worden anders werkt de hashfunctie verkeerd
	m=m*2;
	bepaaluniversele();

// alle elementen overlopen en rehashen
// ik ga enkel elementen overhevelen die niet removed zijn (lazy) of leeg zijn
	for(int i=0; i<backup.size(); i++){
		if(!backup[i].empty && !backup[i].removed){
			add(backup[i].sl,backup[i].b_info);	
		}
	}
}

template <class T>
void Hashtabel<T>::bepaaluniversele(){
	srand (time(NULL));
	p = zoek_priem(m,2*m);
	a = rand()%p+1;
	b = rand()%p;	
}

template <class T>
int Hashtabel<T>::zoek_priem(int l,int r){
	bool test=true;
	for(int j=l;j<r;j++){
		for(int i=2; i < j; i++){
			if (j%i==0){
				break;
			}	
		}
	return j;
	}
}

