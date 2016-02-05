#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

template<typename T>
void Print(const vector<T>& tab){
	for(int i=0; i<tab.size(); i++){
		cout<<tab[i]<<" ";
	}
	cout<<endl;
}

template<typename T>
void swap(vector<T>&v, int i, int j){
	T h = v[i];
	v[i] = v[j];
	v[j] = h;	
}



template<typename T>
void insertionsort(vector<T>& v){
	for(int i=1; i<v.size(); i++){
		T h= v[i];
		int j= i-1;
		while(j>=0 && v[j] > h){
			v[j+1]=v[j];
			j--;
		}
		v[j+1]=h;
	}
}

template<typename T>
void insertionsort(vector<T>& v, int start, int eind){
	for(int i=start; i<=eind; i++){
		T h= v[i];
		int j= i-1;
		while(j >= start && v[j] > h){
			v[j+1]=v[j];
			j--;
		}
		v[j+1]=h;
	}
}


template<typename T>
void jdksort(vector<T>& v, int start, int eind){
	if( start < eind){
		cout<<"hier";
		if((eind-start)<8){
			insertionsort(v,start,eind);
		}else{
			
		
	int k = start+1;
	int g = eind;
	int m = start+1;
	
	// mediaan bepalen (gebruikt vereenvoudigde formules
	vector<T> medselect;
	vector<int> posities;
	int gap = (eind-start)/5;
	for(int i=0 ; i<5 ; i++){
		posities.push_back(start+gap*i);
		medselect.push_back(v[start+gap*i]);
	}
	insertionsort(medselect);
//	Print(medselect);
	T p1 = medselect[1];
	T p2 = medselect[3];
//	cout << "p1= "<<p1<< " p2= "<<p2<< endl;
// p1 bij start plaatsen en p2 bij het einde (stopelementen)
	for(int i=0; i<posities.size(); i++){
		if(v[posities[i]]==medselect[1]){
			swap(v, posities[i], start);
		}else if(v[posities[i]]==medselect[3]){
			swap(v, posities[i], eind);
		}
	}
	while(m < g){
		if(v[m] < p1){
			swap(v, m, k);
			k++;
			m++;
		}else if(v[m] > p2){
			swap(v, m, g-1);
			g--;
		}else{
			m++;
		}			
	}
// op het einde van het algoritme moeten we de elementen ook op de correcte positie plaatsen
	swap(v, start, k-1);
	swap(v, eind, g);
	
	jdksort(v,start,k-2);
	jdksort(v,k-1,g);
	jdksort(v,g+1,eind);
	}}
}


