#include <string.h>
#include <iostream>

using namespace std;

class String{
	friend bool operator < (const String & s1, const String & s2){
		return strcmp(s1.s,s2.s);
	}
	friend bool operator > (const String & s1, const String & s2){
		return strcmp(s2.s,s1.s);
	}
	friend ostream& operator<<(ostream& os, const String& s){
		s.schrijf(os);
		return os;
	}
	public:
	 unsigned int geefLinhashindex()const;
		String(char* s){
			this->s = s;
		}
		String(){
			this->s=nullptr;
		}
		bool operator<(const String& s2){
			return strcmp(this->s, s2.s);
		}
	private : char* s;
		void schrijf(ostream& os)const{
			os<<s;
		}
};

unsigned int String::geefLinhashindex()const{
	unsigned int even=0;
    int len=strlen(s);
    for (int i=0;i<len;i++){
        unsigned int pl=s[i];
        pl=pl*8+pl/32;//eerste  4 bits achteraan;
        even=even*253+pl;
        //pl*((unsigned int)1 << 24)+even/37;
    }
    unsigned int even2=0;
    int aantbits=sizeof(int)*8;
    for (int i=0;i < aantbits/2;i++)
        even2+=(even>>i)*((unsigned int)1 << (aantbits-1-i));
    return even2^even;
};
