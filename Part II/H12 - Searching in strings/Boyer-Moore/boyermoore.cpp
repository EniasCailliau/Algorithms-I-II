#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned int uint;
typedef unsigned char uchar;
using namespace std;
class BoyerMoore {
public:
    BoyerMoore(const uchar* pattern, uint m);
    int search(const uchar* text, uint n);

//private:
    uint d; // ASCI
    uint m; //lengte van naald
    const uchar* pattern;

    int heuristiek_1[256];//voor elk mogelijk karakter
    int* prefix_tabel;
    int* suffix_tabel;
    uint * verschuivings_tabel;
    void heuristiek_1_simple(){
    for (uint i = 0; i < d; i++)
        heuristiek_1[i] = 0;
    for (uint i = 0; i < m; i++)
        heuristiek_1[pattern[i]] = i;//meest rechtse karakter, van klein naar groot zo altijd meest rechts
	}
	
	void heuristiek_1_horspool(int m){
    for (uint i = 0; i < d; i++)
        heuristiek_1[i] = -1;//negatief expliciet

    for (uint i = 0; i < m; i++)
        heuristiek_1[pattern[i]] = m-i-1;
	}

    int heuristiek_verkeerde_karakter_simple(const uchar* text, uint k, uint i);
    int heuristiek_verkeerde_karakter_horspool(const uchar* text, uint k, uint i);
	int heuristiek_verkeerde_karakter_sunday(const uchar* text, uint k, uint i);

    int heuristiek_juiste_suffix(uint j);
  	 void  bereken_preffix( const uchar* str, uint lengte);
    void bereken_suffix( const uchar* str, uint lengte);
};

BoyerMoore::BoyerMoore(const uchar* pattern, uint m)
        : d(256), pattern(pattern), m(m) {

    // Heuristiek 1 : Verkeerde karakter.
    // We bepalen voor ieder mogelijk karakter zijn meest rechtse voorkomen in het patroon.
    // Als het niet voorkomt in het patroon dan: -1
 	heuristiek_1_simple	()	;
 

    // Heuristiek 2: Juiste suffix.
    suffix_tabel = new int[m];
    prefix_tabel = new int[m];

    
      bereken_suffix(pattern, m);
        //	 std::cout<<  "s"<<suffix_tabel[j] <<std::endl;
  
 
    // Verschuivings tabel berekenen v in theorie
    // Deze heeft initieel de waarde m - s(1)
    verschuivings_tabel = new uint[m];
    for (int i = m - 1; i >= 0; i--)
        verschuivings_tabel[i] = m - suffix_tabel[1]; //p-s(1)

std::cout<<"suffixtabel"<<endl;
    for(int i=0; i<m; i++)
       cout<< suffix_tabel[i];;
       cout<<endl;
    // v[i] berekenen
    // v[i] = minimuum van het v[i] en i + 1 - j
    for (int j = m - 1; j >= 0; j--) {
        uint i = m - suffix_tabel[j]; // i =p-s(j)
        verschuivings_tabel[i] = std::min(verschuivings_tabel[i], i + 1 - j);
    }
    std::cout<<"verschuivingstabel"<<endl;
    for(int i=0; i<m; i++){
    	std::cout<<verschuivings_tabel[i];
	}
	cout<<endl;
    
}


void BoyerMoore::bereken_preffix( const uchar* str, uint lengte  ){
	prefix_tabel[0] =-1;
	prefix_tabel[1] =0;
	bool gevonden ;
	for(int i=1; i<lengte; i++){
		gevonden = false;
		int eindeprefix = prefix_tabel[i] ;
		while(!gevonden ){		
			if(str[eindeprefix] == str[i]){
				prefix_tabel[i+1] = eindeprefix +1 ;
				gevonden =true;
			
			}else if(eindeprefix ==0 ){			
			prefix_tabel[i+1]=0;
			gevonden = true;
			}else{
					eindeprefix = prefix_tabel[eindeprefix];	
			}		
		}
					
	}
	

}


//void BoyerMoore::bereken_suffix(const uchar* str, uint lengte){
//	uint tijdelijk[lengte] ;
//	uchar omgekeerd [lengte];
//	for(int i=0; i<lengte;i++){
//		omgekeerd[i] = str[lengte-i-1];
//	}
//
//		bereken_preffix(omgekeerd,lengte);
//		for(int i=0; i<lengte;i++){
//		suffix_tabel[i] = prefix_tabel[lengte-i-1];
//	}
//
//}


void BoyerMoore::bereken_suffix(const uchar* str, uint length, uint j) {
	std::cout<<" bereken suffix "<<std::endl;
    if (j == m - 1) //laatste element heeft geen suffix
        return 0;

    uint pi = suffix_tabel[j + 1];
    std::cout<<  "vorige"<<suffix_tabel[j+1] <<std::endl;
    while (pi != 0) {
    		 std::cout<<" loop "<<std::endl;
    		 std::cout<<pi<<std::endl;
        if (str[m - pi - 1] == str[j]){ //de positie voor de langste positie van volgende letter die zoveel elementen van de sufix voor hem kan leggen
              		std::cout<<" if "<<std::endl;
        	return pi + 1; //een karakater meer dan u voorganger
		}

        else{
        	pi = suffix_tabel[m - pi - 1];
        		std::cout<<" else "<<std::endl;
		}
         
    }
    
 std::cout<<" bereken suffix 2 "<<std::endl;
    if (str[m - pi - 1] == str[j])
        return pi + 1;
    else
        return pi;
}


int BoyerMoore::heuristiek_verkeerde_karakter_simple(const uchar* text, uint k, uint i) {
// k is de positie in de text, i is de positie in het patroon.

// Dit is de eerste (simpele) heuristiek.
// Dit zoekt de meest rechtse positie van het karakter op text[pos].
// We bepalen de verschuiving zodat er een gelijkaardig karakter ligt op text[pos]
    int j = heuristiek_1[text[k]];
    int verschuiving = i - j; //cursus 
	cout<<"meest rechtse "<<text[k]<< " "<<j <<endl;
// Aangezien j (de meest rechtse index waar dit karakter voorkomt) _rechts_ van pos
// kan liggen, zou dit een negatieve (of 0) verschuiving inhouden.
// Dan verschuiven we gewoon met 1.

//MOET UIT COMMENTAAR ALS HEURISTIEK NIET 2 WORDT GEBRUIKT
    if (verschuiving < 1){
	//simpele verschuiving met één stap
        verschuiving = 1; 
        cout<<"probleem opgelost met heuristieke 2"<<endl;
    }

    std::cout << " H1 simpel: " << verschuiving<<std::endl;
    return verschuiving;
}


int BoyerMoore::heuristiek_verkeerde_karakter_horspool(const uchar* text, uint k, uint i) {
// k is de positie in de text, i is de positie in het patroon.
// m is lengte van het patroon

// Dit is de eerste (simpele) heuristiek.
// Dit zoekt de meest rechtse positie van het karakter op text[pos].
// We bepalen de verschuiving zodat er een gelijkaardig karakter ligt op text[pos]
    int j = heuristiek_1[text[k+m-i]];
    	cout<<"meest rechtse "<<text[k+m-i]<< " "<<j <<endl;
    int verschuiving = m - j; //cursus 


    std::cout << " H1 horpsool: " << verschuiving;
    return verschuiving;
}

int BoyerMoore::heuristiek_verkeerde_karakter_sunday(const uchar* text, uint k, uint i) {
    int j = heuristiek_1[text[k+m-i]+1];
    int verschuiving = m - j; //cursus 


    std::cout << " H1 horpsool: " << verschuiving;
    return verschuiving;
}


int BoyerMoore::heuristiek_juiste_suffix(uint j) {
    // We hebben suffix van lengte m - i -1 gevonden. (-1 omdat c++ zero based is, de cursus is 1-based)
    // Situaties
    std::cout << " H2: " << verschuivings_tabel[j]<<endl;
    return verschuivings_tabel[j];
}

int BoyerMoore::search(const uchar* text, uint n) {

    std::vector<int> locaties;

    uint skip = 0;
    for (uint i = 0; i < n - m+1; i += skip) {
        skip = 0;
		cout<<"i"<<i<<endl;
        // Van achter naar voor over het pattern lopen en vergelijken met overeenkomstig karakter in de text.
        for (int j = m - 1; j >= 0; j--) {
        	cout<<"text "<<text[i + j]<<" patroon "<<pattern[j]<<endl;
            if (text[i + j] != pattern[j]) {
                // We hebben een fout gevonden.
                int heur1 = heuristiek_verkeerde_karakter_sunday(text, i + j, i);
                 int heur2 = heuristiek_verkeerde_karakter_horspool(text, i + j, i);
                
               // int heur2 = heuristiek_juiste_suffix(j);
                std::cout << "heur1 "<<heur1<<" heur2 "<<heur2<<std::endl;
               // skip = std::max(heur1, heur2);
                skip = heur1;
                break;
            }
        }

        if (skip == 0) {
            // We hebben het patroon gevonden!
            locaties.push_back(i);
            return i;
        }

    }

    return -1;
}

int main() {
   	const uchar text[] = "dxababab";
	const uchar pattern[] = "abcabcabc";

   	uint n = sizeof(text)/sizeof(text[0]) -1;
	uint m = sizeof(pattern)/sizeof(pattern[0]) -1;

//cout<<"m "<<m<<endl;
    BoyerMoore bm(pattern, m);

//	std::cout<<"suffix" <<std::endl;
// 	for(int i=0; i<m; i++){
// 		std::cout<<bm.suffix_tabel[i]<<" ";
// 	}


//    int pos = bm.search(text, n);
//   std::cout <<"gevonden positie"<< pos;

}
