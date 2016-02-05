#ifndef __SORTEERMETHODE
#define __SORTEERMETHODE

#include <iostream>
    using std::endl;
    using std::cout;
#include <vector>
	using std::vector;
#include <algorithm>   // voor sort()-methode uit STL

#include <cmath>


#include <stdlib.h>     /* srand, rand */
#include <time.h> 

template <typename T>
void Print (const vector<T>& v){
  for (int i=0; i<v.size();i++){
    cout << v[i]<<" ";
  }
  cout<<endl;
}


template <typename T>
class Sorteermethode{
	public:
		virtual void operator()(vector<T> & v) const = 0;
};

/*
 *   STANDARD TEMPLATE LIBRARY SORT
 */
template <typename T>
class STLSort : public Sorteermethode<T>{
	public:
		void operator()(vector<T> & v) const;
};

template <typename T>
void STLSort<T>::operator()(vector<T> & v) const{
	sort(v.begin(),v.end());
}

/*
 *   INSERTION SORT
 */
template <typename T>
class InsertionSort : public Sorteermethode<T>{
	public:
		void operator()(vector<T> & v) const;	
};

template <typename T>
void InsertionSort<T>::operator()(vector<T> & v) const{
	for(int i=1; i<v.size(); i++){
		T h = v[i];
		int j=i-1;
		while(j>=0 && h<v[j]){
			v[j+1] = v[j];   
			j--;
		}
		v[j+1] = h;
	}
}

/*
 *   SHELLSORT 
 */
 
template <typename T>
class ShellSort : public Sorteermethode<T>{
	public:
		void operator()(vector<T> & v) const;
};

template <typename T>
void ShellSort<T>::operator()(vector<T> & v) const{
	int k= floor(v.size()/2);
	while(k >= 1){
		for(int i=1; i < v.size(); i++){
			T h = v[i];
			int j= i-k;
			while(j>=0 && h < v[j] ){
				v[j+k]=v[j];
				j-=k;
			}	  
		v[j+k]=h;	
	}
	k= floor(k/2);
	}
}

/*
 *   SELECTIONSORT (max) 
 */
template <typename T>
class SelectionSort : public Sorteermethode<T>{
	public:
		void operator()(vector<T>& v)const;
};

template <typename T>
void SelectionSort<T>::operator()(vector<T>& v)const{
	for(int i=v.size()-1; i > 0; i--){
		int imax=i;
		for(int j=0; j < i; j++){
			if(v[j] > v[imax]) imax=j;
		}
		T h = v[i];
		v[i]=v[imax];
		v[imax]= h;
	}
}

/*
 *   SELECTIONSORT (min) 
 */
template<typename T>
class MinSelectionSort: public Sorteermethode<T>{
	public: 
		void operator()(vector<T>& v)const;
};

// starten links --> rechts
template<typename T>
void MinSelectionSort<T>::operator()(vector<T>& v)const{
	for(int i=0; i<v.size()-1; i++){
		int imin = i;
		for(int j=v.size()-1; j > i; j-- ){
			if(v[j] < v[imin]) imin=j;
		}
		T h = v[i];
		v[i] = v[imin];
		v[imin] = h;
	}	
}

template<typename T>
class Quicksort: public Sorteermethode<T>{
	public:
		void operator()(vector<T>& v)const;
	private:
		void quicksort(vector<T>& v, int l, int r)const;
};

/*
 *   QUICKSORT 
 */
template<typename T>
void  Quicksort<T>::quicksort(vector<T>& v, int l, int r)const{
	if(l < r){
	T pivot= v[l];
	int i=l; int j=r;
	// we zoeken element kleiner dan de pivot
	while(v[j] > pivot){
		j--;
	}
	while(i < j){
		T h= v[i]; v[i]=v[j]; v[j]=h;
		i++;
		while(v[i] < pivot){
			i++;
		}
		j--;
		while(v[j] > pivot){
			j--;
		}
		quicksort(v, l, j);
		quicksort(v, j+1, r);
	}				
	}
}

template<typename T>
void Quicksort<T>::operator()(vector<T>& v)const{
	this->quicksort(v, 0, v.size()-1);
}

/*
 * COUNTINGSORT
 */
template<typename T>
class Countingsort: public Sorteermethode<T>{
	public:
		void operator()(vector<T>& v)const;
	private:
		void maakFrequentieTabel(vector<T>& v, vector<int>& freqtabel, int min)const;
		void maakPositieTabel(vector<int>& freqtab)const;
		
};
template<typename T>
void Countingsort<T>::maakFrequentieTabel(vector<T>& v, vector<int>& freqtabel, int min)const{
	//frequentietabel is nu gemaakt nu kan ik deze invullen	
	for(int i=0; i<v.size(); i++){
		freqtabel[v[i]-min]++;
	}
}

template<typename T>
void Countingsort<T>::maakPositieTabel(vector<int>& freqtab)const{
	for(int i=1; i < freqtab.size(); i++){
		freqtab[i]= freqtab[i]+freqtab[i-1];
	}
}

template<typename T>
void Countingsort<T>::operator()(vector<T>& v)const{
		// zo optimaal mogelijk minimum en maximum bepalen
	int max= v[0];
	int min = v[0];
	for(int i=1; i < v.size(); i+=2){
		if(i+1 <v.size()){
			if(v[i] > v[i+1]){
				if(v[i] > max) max=v[i];
				if(v[i+1] < min) min=v[i+1];
			}else{
				if(v[i+1] > max) max=v[i+1];
				if(v[i] < min) min=v[i];
			}
		}else{
			if(v[i] < min) min=v[i];
			if(v[i] > max) max=v[i];	
		}
	}
	cout << "minimum = "<<min<<";maximum= "<<max<<endl;
	vector<int> freqtab = vector<int>(max-min+1);	
	maakFrequentieTabel(v,freqtab, min);
	maakPositieTabel(freqtab);
	Print(freqtab);
	vector<T> res(v.size());
	for(int i=0; i<v.size(); i++){
		// normaal moet hiet gewerkt worden met min!!!!
		res[freqtab[v[i]]-1]=v[i];
		freqtab[v[i]]--;
	}
	v=res;
}
/*
 * BucketSort
 */
template<typename T>
class Bucketsort: public Sorteermethode<T>{
	public:
		void operator()(vector<T>& v)const;
	private:
		void Insertionsort(vector<T>& v)const;

	
};

template<typename T>
void Bucketsort<T>::operator()(vector<T>& v)const{
	// Hier word er gebruik gemaakt van 6 buckets
	int m= 6;
	int max= v[0];
	int min = v[0];
	for(int i=1; i < v.size(); i+=2){
		if(i+1 <v.size()){
			if(v[i] > v[i+1]){
				if(v[i] > max) max=v[i];
				if(v[i+1] < min) min=v[i+1];
			}else{
				if(v[i+1] > max) max=v[i+1];
				if(v[i] < min) min=v[i];
			}
		}else{
			if(v[i] < min) min=v[i];
			if(v[i] > max) max=v[i];	
		}
	}
	cout << "minimum = "<<min<<";maximum= "<<max<<endl;
	
	int bucket_size = (max-min)/m+1;
	vector<int> buckets[m];
	
	//opvullen van de buckets
	for(int i=0; i<v.size(); i++){
		buckets[v[i]/bucket_size].push_back(v[i]);
	}
	
	for(int i=0; i<m; i++){
		Insertionsort(buckets[i]);
	}
	// nu is elke bucket afzonderlijk gesorteerd--> nu kan ik ze naast elkaar in de originele vector steken
	int pos=0;
	for(int i=0; i<m ; i++){
		for(int j=0; j<buckets[i].size(); j++){
			v[pos++]=buckets[i][j];
		}
	}
	
	
}

template<typename T>
void Bucketsort<T>::Insertionsort(vector<T>& v)const{
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

/*
 * MERGESORT
 */
template <typename T>
class Mergesort: public Sorteermethode<T>{
	public:
		void operator()(vector<T>& v)const;
	private:
		void sort(vector<int>&, int, int, vector<int>&)const;
		void Merge(vector<int>&, int, int, int, vector<int>&)const;
};
template <typename T>
void  Mergesort<T>::operator()(vector<T>& v)const{
	vector<T> hulp(v.size()/2);
	sort(v,0,v.size()-1,hulp);
	
}
template <typename T>
void  Mergesort<T>::sort(vector<int>& res, int start, int end, vector<int>& hulp)const{
	if(start < end){
		if((end-start)<5){
			// optimalisatie: voor kleine tabellen is het beter insertionsort te gebruiken
			InsertionSort<int> is;
			is(res);
			//cout<<"ik doe insertion"<<endl;
		}else{
			int m= start + (end-start)/2;
			sort(res, start, m, hulp);
			sort(res, m+1, end, hulp);
			Merge(res, start, m, end, hulp);		
		}

	}	
}

template <typename T>
void  Mergesort<T>::Merge(vector<int>& v, int start, int mid, int end, vector<int>& hulp)const{
	// Eerst moet de kleinste tabel (linkse tabel) in hulpvector geplaatst worden
	// Dit moet gedaan worden anders worden de waarden overschreven bij het mergen
	for(int i=start; i<=mid; i++){
		hulp[i-start]=v[i];
	}
	
	int links=0; //links die vindt plaats in hulptabel!
	int rechts=mid+1;
	int i=start;
	while(links <= (mid-start) && rechts <= end){
		if(hulp[links] <= v[rechts]){
			v[i]=hulp[links];
			links++;
		}else{
			v[i]=v[rechts];
			rechts++;
		}	
		i++;
	}
	// Eens uit de voorgaande while=> Minstens 1 deeltabel volledig overlopen
	if(links > (mid-start)){ //hulptabel volledig overlopen
		while(rechts <= end){
			v[i++]=v[rechts++];
		}
	}else{
		while(links <= (mid-start)){
			v[i++]=hulp[links++];
		}
	}
	// nu zijn alle deeltabellen in de resultaattabel gemerged
}

/*
 * QUICKSORT (mediaan/random)
 */

template <typename T>
class MQuicksort: public Sorteermethode<T>{
	public:
		void operator()(vector<T> &v) const;
	private:
		void quicksort(vector<T>& v, int left, int right)const;
		T mediaan(vector<T>& v, int left, int right)const;
};

// Een optionele optimalisatie is om de recursie te stoppen bij voldoende kleine tabellen
// (Hier wordt 5 genomen als grootte) en op laatste insertion sort op deze half gesorteerde tabel
// uit te voeren

template <typename T>
void MQuicksort<T>::operator()(vector<T>& v)const{
	quicksort(v, 0, v.size()-1);
	Print(v);
	InsertionSort<T> is;
	is(v);
}
template <typename T>
void MQuicksort<T>::quicksort(vector<T>& v, int left, int right)const{
	if(left < right){
		if((right-left) < 5){
			// recursie stoppen
			cout<<"ik stop recursie";
		}
		else{
		
		
		//T pivot = v[rand()%(right-left)+left];
		T pivot = mediaan(v, left, right);
		cout << "pivot="<<pivot;
		int i=left; int j=right;
		cout<< "hier";
		while(i < j){
			while(v[i] < pivot){
				i++;
			}
			while(v[j] > pivot){
				j--;
			}
			if(i<j){
				std::swap(v[i],v[j]);
				i++; j--;
			}
			
		}
		MQuicksort<T>::quicksort(v, left, j);
		MQuicksort<T>::quicksort(v, j+1, right);		
	}	}
}
template <typename T>
T MQuicksort<T>::mediaan(vector<T>& v, int left, int right)const{
	vector<T> medselect {v[left], v[left+(right-left)/2], v[right]};
	//Print(medselect);
	InsertionSort<T> is;
	is(medselect);
	return medselect[1]; //we nemen het middenste element

}

/*
 * HEAPSORT (minheap)
 */
template <typename T>
class Heapsort: public Sorteermethode<T>{
	public:
		void operator()(vector<T>& v)const;
	private:
		void MaakHeap(vector<int> & v, int size)const;
		void MaakHeap(vector<int> & v, int size, int top)const;
};

template <typename T>
void  Heapsort<T>::operator()(vector<T>& v)const{
	// Eerst moet hij een heap maken van de vector
	
	//Print(v);
	for(int i=v.size(); i>1 ; i--){
		MaakHeap(v, i);
		T h = v[i];
		v[i]=v[0];
		v[0]=h;		
	}
}

template <typename T>
void Heapsort<T>::MaakHeap(vector<int> & v, int size)const{
	int i = size/2 - 1;
	while(i >= 0){
		cout << "Heap voor top="<<i<<endl;
		MaakHeap(v, size, i);
		i--;
	}
}
template <typename T>
void Heapsort<T>::MaakHeap(vector<int> & v, int size, int top)const{
	int kind1 = 2*top+1;
	int kind2 =	2*top+2;
	if(kind1 < size){
		int min= kind1;
		if(kind2 < size && v[kind2] < v[kind1]) min=kind2;
		if(v[top] > v[min]){
			T h = v[top];
			v[top] = v[min];
			v[min] = h;
			MaakHeap(v, size, min);  
		}
	}	
}





#endif 
