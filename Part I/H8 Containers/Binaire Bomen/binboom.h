#ifndef __BINBOOM_H
#define __BINBOOM_H

#include <iostream>
	using std::cin;
	using std::cout;
	using std::cerr;
	using std::endl;
	using std::flush;
#include <fstream>
	using std::ostream;
	using std::istream;
	using std::ifstream;
#include <string>
	using std::string;
#include <memory>
#include <vector>
	using std::vector;
#include <queue>
	using std::queue;

typedef struct{
	int links;
	int rechts;
}linksrechts;

template <class T>
class Binknoop;


template<class T>
using Binknoopptr=std::unique_ptr<Binknoop<T> >;


template <class T>
class BinaireBoom: protected Binknoopptr<T> {
	
	using Binknoopptr<T>::Binknoopptr;
	
	public:
		static int aantal_boom_constructor;
		static int aantal_boom_destructor;
		void lees(const string &);  // leest bestand in en bouwt boom op
		void schijfinlevel();

	private:
		void schrijf_inorder(ostream & os) const;
		void schrijf_preorder(ostream & os) const;
		void schrijf_postorder(ostream & os) const;
				
    public:
	    BinaireBoom<T>(){aantal_boom_constructor++;}
	      // construeert boom aan de hand van gegevens in bestand
	    BinaireBoom<T>(BinaireBoom && boom): Binknoopptr<T>(std::move(boom)){}
	    BinaireBoom<T>& operator=(BinaireBoom<T>&& boom){
			Binknoopptr<T>::operator=(std::move(boom));
			return *this;
		}
		
	    ~BinaireBoom<T>(){
	    	aantal_boom_destructor++;
	    	//...
	    }
	    void schrijf(ostream & os, const string & volgorde="in")const{
	    	if(volgorde == "inorder" || volgorde == "in") schrijf_inorder(os);
	    	else if(volgorde == "preorder" || volgorde == "pre") schrijf_preorder(os);
	    	else schrijf_postorder(os);
		}	    
	    
	    friend ostream& operator<< (ostream & os, const BinaireBoom<T> & b){
	    	b.schrijf(os,"inorder", true);
	    	return os;
	    }

};

template <class T>
class Binknoop{
	
	public:
		static int aantal_knoop_constructor_default;
		static int aantal_knoop_constructor_param;
		static int aantal_knoop_destructor;
	// Dit zodat binaireboom aan dataleden kan voor schrijfoperatie.
	friend class BinaireBoom<T>;
	const T inhoud;
	// verwijzingen naar deelbomen
	BinaireBoom<T> left,right;
	
	Binknoop<T>(){aantal_knoop_constructor_default++;}
	Binknoop<T>(const T & geg):inhoud(geg){aantal_knoop_constructor_param++;left=nullptr; right=nullptr;}
	~Binknoop<T>(){aantal_knoop_destructor++;}
	
};

//________________________________________________________________________________________________



template <class T>
int BinaireBoom<T>::aantal_boom_constructor = 0;
template <class T>
int BinaireBoom<T>::aantal_boom_destructor = 0;


//________________________________________________________________________________________________

template <class T>
int Binknoop<T>::aantal_knoop_constructor_default = 0;
template <class T>
int Binknoop<T>::aantal_knoop_constructor_param = 0;
template <class T>
int Binknoop<T>::aantal_knoop_destructor = 0;
	
	
template <class T>	
void BinaireBoom<T>::lees(const string & bestand){
	ifstream is(bestand);
	string word;
	string left;
	string right;
	is>>word;
	int aantal=atoi(word.c_str());
	linksrechts tabel[aantal];
	bool noroot[aantal];
	vector<BinaireBoom<T> *> v(aantal);
	for(int i=0 ; i<aantal; i++){
		
		is>>word>> left>>right;
	//	cout<<word<<endl;
	 	v[i] = new BinaireBoom<T>();
	 // Aanmaken met new --> pointer terug geven dus Binaire boom gemaakt.
   		 BinaireBoom<T> temp(new Binknoop<T>(word));
        v[i]->swap(temp);
		tabel[i].links=atoi(left.c_str());
		tabel[i].rechts=atoi(right.c_str());
		noroot[atoi(left.c_str())]=true;
		noroot[atoi(right.c_str())]=true;
	}
	// cout<<v.size()<<endl;
	// nu rootknoop zoeken
	int root=-1;
	for(int i=0; i<aantal; i++){
		if(!noroot[i]) root=i;
	}
	// cout<<root<<endl;
	// cout<<v[tabel[root-1].links]->get()->inhoud<<endl;
	for(int i=0; i<v.size(); i++){
		if(tabel[i].links!=0){
			v[i]->get()->left.swap(*v[tabel[i].links-1]);
			v[tabel[i].links-1] = &(v[i]->get()->left);
		}
		if(tabel[i].rechts!=0){
			v[i]->get()->right.swap(*v[tabel[i].rechts-1]);
			v[tabel[i].rechts-1] = &(v[i]->get()->right);
		}
		
	}
	//cout<<"crazy"<<flush;
    this->swap(*v[root-1]);

	
}
		
template <class T>
void BinaireBoom<T>::schrijf_inorder(ostream & os) const{
	if(*this){
		this->get()->left.schrijf_inorder(os);
		cout<< this->get()->inhoud<<endl;
		this->get()->right.schrijf_inorder(os);
	}
}

template <class T>		
void BinaireBoom<T>::schrijf_preorder(ostream & os) const{
	//cout<<"haaalooo";
	if(*this != nullptr){
		cout << this->get()->inhoud<<endl;
		this->get()->left.schrijf_preorder(os);
		 this->get()->right.schrijf_preorder(os);
	}
}

template <class T>		
void BinaireBoom<T>::schrijf_postorder(ostream & os) const{
	if(this->get()->left) this->get()->left.schrijf_preorder(os);
	if(this->get()->right) this->get()->right.schrijf_preorder(os);
		cout << this->get()->inhoud<<endl;

}

template <class T>		
void BinaireBoom<T>::schijfinlevel(){
	queue<const BinaireBoom<T>*> q;
	q.push(this);
	while(!q.empty()){
		const BinaireBoom<T>* b = q.front();
		q.pop();
		cout<<b->get()->inhoud<<endl;
		if(b->get()->left) q.push(&(b->get()->left));
		if(b->get()->right) q.push(&(b->get()->right));
	}	
}


#endif


