#include "shiftand.h"
#include "bitpatroon.h"
#include <iostream>
#include <queue>

using namespace std;

int main(){
	Bitpatroon bp(10);
//	cout<<bp;
//cout<<sizeof(uint)*8<<"is lengte\n";
//	uchar naald[] = { 'b', 'b', 'b', 'b', '\0' };
	unsigned char naald[20] = "announce";
//	uchar hooiberg[] = { 'b', 'b', 'a', 'a', 'a', 'b', 'b', 'b', 'b', '\0' }; 
	unsigned char hooiberg[20] = "annual_announce";
	ShiftAnd sa(naald, 8);
//	cout<<sa.letterpatroon['b'];
	queue<const unsigned char*> q = sa.zoek(hooiberg,15);
	cout<<"aantal: "<<q.size();
	return 0;
}



    
