#ifndef __BINBOOM_H
#define __BINBOOM_H

#include <iostream>
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
#include <stack>
	using std::stack;
	
template <class T>
class Binknoop;


template<class T>
using Binknoopptr=std::unique_ptr<Binknoop<T> >;


template <class T>
class BinaireBoom: public Binknoopptr<T> {
	using Binknoopptr<T>::Binknoopptr;
	public:
		static int aantal_boom_constructor;
		static int aantal_boom_destructor;
	
	private:
		void lees(const string &);  
		bool verwijderhaakjes(string& s, int l, int r);
		void lees();
		void schrijf_inorder(ostream & os) const;
		void schrijf_preorder(ostream & os) const;
		void schrijf_postorder(ostream & os) const;
				
    public:
	    BinaireBoom<T>(){aantal_boom_constructor++;}
	    BinaireBoom<T>(const string &); 
	    BinaireBoom<T>(const BinaireBoom &);
	    BinaireBoom<T>(BinaireBoom<T>&& b): Binknoopptr<T>::Binknoopptr(std::move(b)){}
	    BinaireBoom<T>(string& s, int l, int r);
		BinaireBoom<T>& operator=(BinaireBoom<T>&& b){
			Binknoopptr<T>::operator=(std::move(b));
			return *this;
		}
	    ~BinaireBoom<T>(){
	    	aantal_boom_destructor++;
	    	//...
	    }
	    void schrijf(ostream & os, const string & volgorde="post")const{
	    	if(volgorde == "inorder" || volgorde == "in") schrijf_inorder(os);
	    	else if(volgorde == "preorder" || volgorde == "pre") schrijf_preorder(os);
	    	else schrijf_postorder(os);
		}	    
	    
	    friend ostream& operator<< (ostream & os, const BinaireBoom<T> & b){
	    	b.schrijf(os,"post");
	    	return os;
	    }

};

template <class T>
class Binknoop{
	
	public:
		static int aantal_knoop_constructor_default;
		static int aantal_knoop_constructor_param;
		static int aantal_knoop_destructor;
	
	friend class BinaireBoom<T>;
	const T inhoud;
	BinaireBoom<T> left,right;
	
	Binknoop<T>(){aantal_knoop_constructor_default++;}
	Binknoop<T>(const T & geg):inhoud(geg){aantal_knoop_constructor_param++;}
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
	

#endif


void zoekoperator(string& s, int l, int r);
template<class T>
void BinaireBoom<T>::lees(){
	string formule;
	getline(cin,formule);
	//cout<<formule;
	zoekoperator(formule,0,formule.size()-1);
}
template<class T>
bool BinaireBoom<T>::verwijderhaakjes(string& s, int l, int r){
	
}

template<class T>
BinaireBoom<T>::BinaireBoom(string& s, int l, int r){
	cout<<s.substr(l,r-l+1)<<"l= "<<l<<"r= "<<r<<endl;
	stack<int> st;
	//cout<<s<<endl;
	for(int i=l; i<r ; i++){
	//	cout<<"hier"<<endl;
		if(s[i]=='(') st.push(i);
		if(s[i]==')') st.pop();
	}
	if(s[r]==')' && st.top()==l){
		cout<<"haakjes verwijderd"<<endl;	
		 l=l+1;  r=r-1;
	}
	// haakjes zijn verwijderd we kunnen zoeken naar een operator;
	char op=' ';
	int oppos=-1;
	stack<int>hooks;
	for(int i=l; i<=r; i++){
		if(s[i]=='(') hooks.push(i);
		if(s[i]==')') hooks.pop();
		if(hooks.empty()){
			// hier zitten we niet tussen haakjes
				if(s[i]=='*'|| s[i]=='/'){
				if(op==' '){
					oppos=i;
					op=s[i];
				} 
				}
				if(s[i]=='+' || s[i]=='-'){
					op=s[i];
					oppos=i;
				} 				
		}
	
	}
	if(oppos==-1){
		cout<<"getal="<<s.substr(l,r-l+1)<<endl; // vroeger s[l]
		BinaireBoom<string> b((Binknoopptr<string> ) new Binknoop<string>(s.substr(l,r-l+1)));
		*this=std::move(b);
	}else{
		cout<<"hoofdoperator= "<<op<<" op positie: "<<oppos<<endl;	
		BinaireBoom<string> b((Binknoopptr<string> ) new Binknoop<string>(string(1,op)));
		// std::move is hier optioneel
		b->left = std::move(BinaireBoom(s,l,oppos-1));
		b->right = std::move(BinaireBoom(s,oppos+1,r));
		*this=std::move(b);
	}
	
}

template <class T>
void BinaireBoom<T>::schrijf_inorder(ostream & os) const{
	if(this->get()->left) this->get()->left.schrijf_inorder(os);
	cout<< this->get()->inhoud<<endl;
	if(this->get()->right) this->get()->right.schrijf_inorder(os);	
}

template <class T>		
void BinaireBoom<T>::schrijf_preorder(ostream & os) const{
	cout << this->get()->inhoud<<endl;
	if(this->get()->left) this->get()->left.schrijf_preorder(os);
	if(this->get()->right) this->get()->right.schrijf_preorder(os);
}

template <class T>		
void BinaireBoom<T>::schrijf_postorder(ostream & os) const{
	if(this->get()->left) this->get()->left.schrijf_postorder(os);
	if(this->get()->right) this->get()->right.schrijf_postorder(os);
	cout << this->get()->inhoud<<"\t";

}

