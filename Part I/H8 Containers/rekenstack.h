#include <stack>
	using std::stack;
#include <iostream>
	using std::ostream;
	using std::istream;
	using std::cin;
	using std::cout;
	using std::endl;
#include <vector>
#include <string>
	using std::string;
#include <math.h>

template<typename T>
class Rekenstack:protected std::vector<T>{
	public:
			void pop(){
				this->pop_back();
			}
			T& top(){
				return this->back();
			}
			bool isempty()const{
				return this->empty();
			}
			void push(T el){
				this->push_back(el);
			}	
			friend ostream & operator<<(ostream& os, const Rekenstack<T>& rs){
				rs.schrijf(os);
				return os;
			}
			friend istream & operator>>(istream& is, Rekenstack<T>& rs){
				rs.lees(is);
				return is;
			}
			void lees(istream& is);
	protected:
			void som();
			void verschil();
			void vermenigvuldig();
			void deel();
			void wortel();
			void kwadraat();
	private:
			void schrijf(ostream & os)const{
				os<<"==================Stack====================="<<endl;
				for(int i=this->size()-1; i>=0; i--){
					os<<this->at(i)<<endl;
				}
				os<<"============================================"<<endl;
			}
};

template<typename T>
void Rekenstack<T>::som(){
	if(this->size()<2){
		cout<<"Fout bij bewerking!"<<endl;
	}else{
		int a = top();pop();
		int b = top();pop();
		push(a+b);
	}
}

template<typename T>
void Rekenstack<T>::verschil(){
	if(this->size()<2){
		cout<<"Fout bij bewerking!"<<endl;
	}else{
		int a = top();pop();
		int b = top();pop();
		push(a-b);
	}
}

template<typename T>
void Rekenstack<T>::vermenigvuldig(){
	if(this->size()<2){
		cout<<"Fout bij bewerking!"<<endl;
	}else{
		int a = top();pop();
		int b = top();pop();
		push(a*b);
	}
}

template<typename T>
void Rekenstack<T>::deel(){
	if(this->size()<2){
		cout<<"Fout bij bewerking!"<<endl;
	}else{
		int a = top();pop();
		int b = top();pop();
		if(b==0){
			cout<<"Devide by zero!"<<endl;
		}
		else push(a/b);
	}
}

template<typename T>
void Rekenstack<T>::kwadraat(){
	if(this->size()<1){
		cout<<"Fout bij bewerking!"<<endl;
	}else{
		int a = top();pop();
		
		 push(a*a);
	}
}

template<typename T>
void Rekenstack<T>::wortel(){
	if(this->size()<1){
		cout<<"Fout bij bewerking!"<<endl;
	}else{
		int a = top();pop();	
		 push(sqrt(a));
	}
}
		

template<typename T>
void Rekenstack<T>::lees(istream& is){
	string line;
	getline(is, line);
	while(line[0]!='e'){
		if(line.size()==1 && !isdigit(line[0])){
			switch(line[0]){
				case 'c':
					pop();
					break;
				case 'V':
					wortel();
					break;
				case 's':
					kwadraat();
					break;
				case '+':
					som();
					break;
				case '-':
					verschil();
					break;
				case '*':
					vermenigvuldig();
					break;
				case '/':
					deel();
					break;
				default: 
					cout<<"ongeldige optie"<<endl;
			}			
		}else{
			// Hier is het dus een getal
			push(atoi(line.c_str()));
		}
		schrijf(cout);
		
		
		getline(is,line);
	}
	
}

