#include <string.h>
#include <iostream>

using namespace std;

class Nummer{
	friend bool operator < (const Nummer & s1, const Nummer & s2){
		return s1.d<s2.d;
	}
	friend bool operator > (const Nummer & s1, const Nummer & s2){
		return s1.d > s2.d;
	}
	friend ostream& operator<<(ostream& os, const Nummer& s){
		os<<s.d;
		return os;
	}
	public:
	 unsigned int geefLinhashindex()const;
		Nummer(const int& d){
			this->d = d;
		}
//		Nummer(const Nummer& n){
//			this->d = d;
//		}
//		Nummer& operator=(const Nummer& n){
//			this->d=d;
//			return *this;
//		}
		Nummer(){
			this->d=0;
		}
		bool operator<(const Nummer& s2){
			return this->d < s2.d;
		}
	private : 
		unsigned int d;
		void schrijf(ostream& os)const{
			os<<d;
		}
};

unsigned int Nummer::geefLinhashindex()const{
	return d;
};

