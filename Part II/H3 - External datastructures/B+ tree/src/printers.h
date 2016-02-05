#ifndef __PRINTERS
#define __PRINTERS

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

template <typename T>
void Print(vector<T> & v){
	for(int i=0; i < v.size();i++){
		cout<<v[i]<<"\t";
	}
	cout<<endl;
}


void printspecial(const char* s){
	cout<<"------------"<<s<<"------------"<<endl;
}

#endif
