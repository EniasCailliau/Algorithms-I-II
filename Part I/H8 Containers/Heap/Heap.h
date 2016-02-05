#include <vector>
#include <iostream>
using namespace std;

template<typename T>
void verwissel(vector<T>& v,int i, int j){
	if(i!=j){
		T hulp = v[i];
		v[i]=v[j];
		v[j]=hulp;
	}
}

// O(lg(n))
// voor een maxheap
template <typename T>
void heapvoorwaarde(vector<T>& v, int size, int top){
	int kind1 = 2*top+1;
	int kind2 = 2*top+2;
	int max; 
	if(kind1 < size){
		max = kind1;
		if(kind2 < size && v[kind2] > v[kind1]){
			max=kind2;
		}
		if(v[max] > v[top]){
			verwissel(v,top,max);
			// we gaan hier dus naar beneden
			heapvoorwaarde(v,size,max);
		}
	}
}

template <typename T>
void MaakHeap(vector<T>& v, int size){
// belangrijk te beginnen bij N/2
	int i=size/2-1;
	while(i >= 0){
		heapvoorwaarde(v,size,i);
		i--;
	}	
}



template <typename T>
void MaakHeap(vector<T>& v){
	MaakHeap(v,v.size());
}

// Deze methode is O(log n)
// krijgt index van laatste knoop mee
template <typename T>
T verwijdertop(vector<T>& v,int size){
// Deze methode gaat de top verwijderen (dus de grootte met 1 verlagen)
	T nieuw = v[size-1];
	if(v[0] > nieuw ){
		cout<< "ik verwissel en heapvw"<<v[0]<<","<<v[size-1]<<endl;
		verwissel(v,0,size-1);
// Hier is het belangrijk dat size-1 want de nieuwe size is size-1 nu...
		heapvoorwaarde(v,size-1,0);
	}else{
// wanneer dat nieuw groter is of gelijk aan dan kan het de heapvoorwaarde niet verstoren
		verwissel(v,0,size-1);
	}
}

template <typename T>
void Heapsort(vector<T>& v){
// Eerst heap aanmaken (O(n))
	MaakHeap(v);
// Moet niet gelijk aan nul want laatste staak correct
	for(int i=v.size(); i > 0; i--){
		// verwissel(v,0,i);
		//// cout<<"yes";
		// MaakHeap(v,i);	
		verwijdertop(v,i);
	}	
}


template<typename T>
void MinHeapVoorwaarde(vector<T>& v, int size, int top){
	int kind1 = 2*top +1;
	int kind2 = 2*top + 2;
	int min = kind1;
	if(kind1 < size){
		if(kind2 < size && v[kind2] < v[kind1]) min=kind2;
		if(v[top] > v[min]){
			verwissel(v,top,min);
			MinHeapVoorwaarde(v, size, min);
		}			
	}	
}

template<typename T>
void MaakMinHeap(vector<T>& v, int size){
	int i = size/2 -1;
	while(i >= 0){
		MinHeapVoorwaarde(v,size, i);
		i--;
	} 
}

template<typename T>
void verwijdertopMinHeap(vector<T>& v, int size){
	T nieuw = v[size-1];
// kan enkel verstoren als het groter is dan nieuw
// de verwissel zorgt dat in vector uiteindelijk het eindresultaat komt te staan
	if(nieuw > v[0]){
		verwissel(v,0,size-1);
		MinHeapVoorwaarde(v,size-1,0);
	}else{
		verwissel(v,0,size-1);
	}
}

template<typename T>
void voegelementToeMinHeap(vector<T>& v, T element){
	v.push_back(element);
	int i=v.size()-1;
	while(i > 0){
		int ouder = (i-1)/2;
		if(v[ouder] > v[i]){
			verwissel(v,ouder,i);
			i=ouder;
		}else break;
	}
}



