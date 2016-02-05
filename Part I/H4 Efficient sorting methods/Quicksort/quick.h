#include <vector>
#include <iostream>
using namespace std;

template<typename T>
void Print(const vector<T>& tab){
	for(int i=0; i<tab.size(); i++){
		cout<<tab[i]<<" ";
	}
	cout<<endl;
}


template<typename T>
void quicksort(vector<T>& v, int l, int r){

if(l < r){
	int pivot = v[l];
	// cout<<"pivot= "<<pivot<<endl;
	int i=l; int j=r;
	while(v[j] > pivot){
		j--;
	}
	int posp = j;
	while(i < j){
		T h = v[i]; v[i]=v[j]; v[j]=h;
		i++;
		while(v[i] < pivot){
			i++;
		}
		j--;
		while(v[j] > pivot){
			j--;
		}
	}
	// cout<<"i= "<<i<<"j= "<<j<<endl;
	
	// cout<<"swapke"<<endl;
	std::swap(v[i], v[posp]);
	Print(v);
	quicksort(v, l, j);
	quicksort(v, j+1, r);
}
}



template<typename T>
void quicksort(vector<T>& v){
	quicksort(v, 0, v.size()-1);
}


template<typename T>
void quicksort2(vector<T>& v, int l, int r){

if(l < r){
	int pivot = v[r];
	int i=l; int j=r;
	while(v[i] < pivot){
		i++;
	}
	while(i < j){
		T h = v[i]; v[i]=v[j]; v[j]=h;
		j--;
		while(v[j] > pivot){
			j--;
		}
		i++;
		while(v[i] < pivot){
			i++;
		}
	}
	quicksort(v, l, j);
	quicksort(v, j+1, r);
}
}



template<typename T>
void quicksort2(vector<T>& v){
	quicksort2(v, 0, v.size()-1);
}

