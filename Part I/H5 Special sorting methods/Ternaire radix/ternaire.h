#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

template <typename T>
void swap(vector<T>& v, int i, int j){
	T h = v[i];
	v[i] = v[j];
	v[j] = h;
}




template <typename T>
void ternairsort(vector<T>& v, int start, int eind, int radix){
	// cout<<"eind= "<<eind<<" start= "<<start<<endl;	
	if(radix >= 1 && start<eind ){
		
	T pivot = (v[eind]/radix)%10;
	// cout<<"pivot= "<<pivot<<endl;
	int l=start, m=start;
	int g=eind;
	while(m < g){
		if( ((v[m]/radix)%10) < pivot){
			swap(v, l ,m);
			m++;
			l++;
		}else if( ((v[m]/radix)%10) > pivot){
			swap(v, m, g-1);
			g--;
			//g++; niet verplaatsen want niew onbekend gehad
		}else{
			// gelijk aan pivot
			m++;		
		}
	}
	cout<<"hier"<<";"<<"";
	swap(v, g, eind);
//	Print(v);
	
	ternairsort(v, start, l-1, radix);
	// reden hier g want ik heb net met g gewisselt.
	ternairsort(v,l,g, radix/10 ); 
	ternairsort(v, g+1, eind, radix);	
	}
}

template <typename T>
void ternairsort(vector<T>& v){
	T max= v[0];
	for(int i=1; i<v.size(); i++){
		if(v[i] > max) max = v[i]; 
	}
	int exp = log10(max);
	cout<<exp;		
	ternairsort(v,0, v.size()-1,pow(10,exp));	
}



