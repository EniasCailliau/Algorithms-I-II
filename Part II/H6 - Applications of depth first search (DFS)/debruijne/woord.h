#ifndef __Woord
#define __Woord

#include <iostream>
#include <string.h>
using namespace std;

template<int radix, int woordlengte>
class Woord{
	public:
		Woord(int getal){
			this->d=getal;
		}
		Woord(){
			this->d=0;
		}
		friend inline std::ostream& operator<<(std::ostream &out,const Woord &b) {
			b.schrijf(out);
			return out;
		}
		schrijf(ostream& os)const{
			os<<convertToBase();
		}
		
		static void printlaatstechar(int);
		static char geeflaatstechar(int);
	private:
		char * convertToBase()const;
		unsigned int d;
		
};

template<int radix, int woordlengte>
void Woord<radix,woordlengte>::printlaatstechar(int i){
	 cout << (char) ((i % radix) + 'a');
	 return;
}

template<int radix, int woordlengte>
char Woord<radix,woordlengte>::geeflaatstechar(int i){
	 return (char) ((i % radix) + 'a');	 
}

template<int radix, int woordlengte>
char * Woord<radix,woordlengte>::convertToBase()const{
	int i;
    char buf[66];   /* enough space for any 64-bit in base 2 */
	int num = d;

    /* null terminate buf, and set i at end */
    buf[65] = '\0';
    i = 65;

    if (num >= 0) {  /* if positive... */
        while (num) { /* until num is 0... */
            /* go left 1 digit, divide by radix, and set digit to remainder */
            buf[--i] = 'a'+ (num % radix);
            num /= radix;
        }
    } else {    /* same for negative, but negate the modulus and prefix a '-' */
        while (num) {
            buf[--i] = 'a'+ (num % radix);
            num /= radix;
        }
        buf[--i] = '-';
    }  
	while(i > (65-woordlengte)){
		buf[--i] = 'a';
	} 
    /* return a duplicate of the used portion of buf */
    return strdup(buf + i);
}


#endif
    
