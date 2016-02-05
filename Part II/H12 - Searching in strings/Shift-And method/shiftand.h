#include "bitpatroon.h"
#include <queue>
typedef unsigned int uint;
typedef unsigned char uchar;
using namespace std;
class ShiftAnd{
public:
    ShiftAnd(const uchar* naald,uint _naaldlengte){
    	naaldlengte = _naaldlengte;				 

		for(int i=0; i<_naaldlengte; i++){
			uint kar = naald[i];
			letterpatroon[kar]|=Bitpatroon::eenbit(i);
		}			 					 
	}
    std::queue<const uchar*> zoek(const uchar* hooiberg, uint hooiberglengte);
private:
    Bitpatroon letterpatroon[256]; // zorgt dat deze al bestaan
    uint naaldlengte;
};
    
std::queue<const uchar*> ShiftAnd::zoek(const uchar* hooiberg, uint hooiberglengte){
    Bitpatroon R0[hooiberglengte]; // default zijn dit allemaal nullen
    Bitpatroon R1[hooiberglengte];
    std::queue<const uchar*> q;
	for(int j=0; j<hooiberglengte; j++){
		Bitpatroon res0;
		if(j!=0){
        	res0 = R0[j-1].shiftrechts(1);
    	}
        res0 |= Bitpatroon::eenbit(0);                     				
        uint index = hooiberg[j];
        res0 &= letterpatroon[index];
        R0[j] = res0;
        
        // code voor toevoegen
//        Bitpatroon res1 = R1[j-1].shiftrechts(1);
//        res1 |= Bitpatroon::eenbit(0);
//        res1 &= letterpatroon[index];
//        R1[j] = R0[j-1] | res1;

//		code voor verwijderen
//		Bitpatroon res1 = R1[j-1].shiftrechts(1);
//		res1 |= Bitpatroon::eenbit(0);
//		res1 &= letterpatroon[index];
//		R1[j] = R0[j].shiftrechts(1) | res1;
//        cout<<"endl"<<endl;
        
        // vervangen
        Bitpatroon res1 = R1[j-1].shiftrechts(1);
		res1 |= Bitpatroon::eenbit(0);
		res1 &= letterpatroon[index];
		R1[j] = R0[j-1].shiftrechts(1) | res1;
        
        if(R1[j].en(Bitpatroon::eenbit(naaldlengte -1))){
//                for(int i=j-naaldlengte+1; i <= j; i++){
//                    cout<<hooiberg[i]<<" ";
//				}
//				cout<<endl;
//            q.push(hooiberg+(j-naaldlengte+1)); 
//			cout<<","<<j<<","<<hooiberg-naaldlengte+j+2<<endl;
			cout<<","<<j<<","<<hooiberg-naaldlengte+j<<endl;
			q.push(hooiberg-naaldlengte+j+1); 		
		
		}
    }
    return q;             	
} 
     
     
