#include <iostream>
#include <vector>

#include "printers.h"

using namespace std;

template <typename T>
void Print (const vector<T>& v){
  for (int i=0; i<v.size();i++){
    cout << v[i]<<" ";
  }
  cout<<endl;
}


void swap(vector<int>& v, int i, int j){
	int h = v[i];
	v[i] = v[j];
	v[j] = h;
}

int getk(vector<int>& v, int start, int eind, int k){
	if(start<eind){
		int pivot=v[eind];
		cout<<"pivot="<<pivot<<"ik zoek naar "<<k<<endl;
		int i=start; int j=eind-1;
	while(v[i] < pivot){
			i++;
	}
	while(v[j] > pivot){
		j--;
	}
	while(i < j){
			swap(v,i,j);
			i++; j--;
			while(v[i] < pivot){
				i++;
			}
			while(v[j] > pivot){
				j--;
			}
	}
		swap(v,eind,i);
		// Print(v);
		// cout<<"spil="<<i<<endl;
	// nu het stuk van de selectie
	// i = spilpostie
	// k = gezochte waarde
		if(k < i){
			return getk(v,start,i-1,k);
		}else if(k > i){
	// cursus klopt niet helemaal hier moet k-i+1 staan ofwel gebruiken we de j
			return getk(v,i+1,eind,k);
		}else{
			return v[k];
		}				
	}else{
		return v[start];
	}
}

int getk(vector<int>&v, int k){
// eigenlijk geven we een getal tellende vanaf 1 maar programma telt van 0
	return getk(v,0,v.size()-1,k-1);
}
	
int main(){
	//vector<int> v{6,2,5,9,9,6,8,10,11,16};
	vector<int> v{2,4,8,3,1,4};
	Print(v);
	Printspecial("Nu beginnen zoeken");
	int res = getk(v,0,v.size()-1,3);
	Printspecial("Uitschrijven van het k-de element");
	cout << res;
	
}
