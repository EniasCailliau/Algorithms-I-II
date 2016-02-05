#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>

using namespace std;

template<typename T>
void Print(const vector<T>& tab){
	for(int i=0; i<tab.size(); i++){
		cout<<tab[i]<<" ";
	}
	cout<<endl;
}

// Deze hebben we nodig in de slotfase
void insertionsort(vector<int>& v){
	for(int i=1; i<v.size(); i++){
		int h = v[i];
		int j=i-1;
		while(j>=0 && h<v[j]){
			v[j+1] = v[j];   
			j--;
		}
		v[j+1] = h;
	}	
	
} 

// quicksort met mediaan!
void quicksort(vector<int>& v, int start, int eind){
	if(start < eind){
		vector<int> medsect = {v[start], v[start+(eind-start)/2], v[eind]};
		insertionsort(medsect);
		//	Print(medsect);
		//v[0]= medsect[0];
		int pivot= medsect[1];
		//cout<<"pivot= " <<pivot<<endl;
		//v[eind]=medsect[2];		
	int i=start, j=eind;
	while(v[j] > pivot){
			j--;
		}
	while(v[i] < pivot){
		i++;
	}		
	while(i < j){
		int h=v[i]; v[i]=v[j]; v[j]=h;
		i++;
		while(v[i] < pivot){
			i++;
		}
		j--;
		while(v[j] > pivot){
			j--;
		}		
	}
	quicksort(v, start, j);
	quicksort(v, j+1, eind);
	}
	
}


void quicksort(vector<int>& v){
	quicksort(v, 0, v.size()-1);
}
