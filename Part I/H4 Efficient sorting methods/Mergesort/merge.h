#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
void Print (const vector<T>& v){
  for (int i=0; i<v.size();i++){
    cout << v[i]<<" ";
  }
  cout<<endl;
}

template <typename T>
void merge(vector<T>& res, int start, int mid, int end, vector<T>& hulp){
	//int mid = start+(end-start)/2;
	// Eerst moet de links gesorteerde elementen in een hulptabel
	// Anders worden deze elementen overschreven
	for(int i=start; i<=mid; i++){
		hulp[i-start] = res[i];
	}
	int links = 0; //links neem je uit de hulptabel
	int rechts = mid+1;
	int i=start; //deze index wordt gebruikt voor het opvullen in res;
	while(links <= (mid-start) && rechts <= end){
		if(hulp[links] <= res[rechts]){
			res[i] = hulp[links];
			links++;
		}else{
			res[i] = res[rechts];
			rechts++;
		}
		i++;
	}
		while(rechts <= end){
			res[i++] = res[rechts++];
		}
		while(links <= (mid-start)){
			res[i++] = hulp[links++];
		}
}

template <typename T>
void mergesort(vector<T>& v, int l, int r, vector<T>& h){
	if(l < r){
		int m = l+(r-l)/2;
		mergesort(v,l,m,h);
		mergesort(v,m+1,r,h);
		merge(v,l,m,r,h);
	}
}

template <typename T>
void mergesort(vector<T>& v){
	vector<T> h(v.size()/2);
	mergesort(v, 0, v.size()-1, h);
}

// merge bottom up. Hier te vinden; met mediaan zie andere

template <typename T>
void mergesortbu(vector<T>& v){
	int grootte= 2; 
	vector<T> h(v.size());
	while(grootte/2 < v.size()){
		
		for(int i=0; i<v.size(); i+=grootte){
			int next= i+grootte-1;
			
			if(i+grootte>= v.size()){
				next= v.size()-1;
			}
			int m = i+ grootte/2-1;
			cout<<"grootte= "<<grootte<<" next = "<<next;
			merge(v, i, m, next, h);
		}
	grootte*=2;
	}
	
	
}


