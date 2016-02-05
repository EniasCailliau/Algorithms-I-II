#include <vector>
#include <iostream>
#include "printers.h";
using namespace std;


template<typename T>
void verwissel(vector<T>& v,int i, int j){
	if(i!=j){
		T hulp = v[i];
		v[i]=v[j];
		v[j]=hulp;
	}
}

template<typename T>
void Insertionsort(vector<T>& v, int l, int r){
	// opletten! Je moet hier wel tot en met r gaan!
	for(int i=1; i<=r ; i++){
		T hulp = v[i];
		int pos=i;
		while(pos > 0 && hulp < v[pos-1]){
			
			pos--;
		}
	}
}

template<typename T>
void Merge(vector<T>&v, int l, int m, int r, vector<T>&h){
	// hulptabel opvullen
	for(int i=l; i<=m; i++){
		h[i-l]=v[i];
	}

	int eerste=0,tweede=m+1;
	int pos=l;
	while(eerste<=(m-l) && tweede<=r){
		if(h[eerste] > v[tweede]){
			v[pos]=v[tweede];
			pos++; tweede++;
		}else{
			v[pos]=h[eerste];
			pos++; eerste++;	
		}
	}
	while(eerste<=(m-l)){
		v[pos]=h[eerste];
		pos++; eerste++;	
	}
	while(tweede<=r){
		v[pos]=v[tweede];
		pos++; tweede++;
	}
}

template<typename T>
void Mergesort(vector<T>&v, int l, int r, vector<T>& h){
	if(l < r){		
//		if((r-l) < 8){
//			Insertionsort(v,l,r);
//		}
		int m=l+(r-l)/2;
		Mergesort(v,l,m,h);
		Mergesort(v,m+1,r,h);
		Merge(v,l,m,r,h);
	}
}

template<typename T>
void Mergesort(vector<T>& v){
	vector<T> hulp(v.size()/2);
	Mergesort(v,0,v.size()-1,hulp);
}


/**
Met een alternerende hulptabel
**/

template<typename T>
void Mergealt(vector<T>&v, int l, int m, int r, vector<T>&h){
	Printspecial("mergen:");
	Print(h);
	Printspecial("f");
	cout<<endl;
	int eerste=l,tweede=m+1;
	int pos=l;
	while(eerste<=m && tweede<=r){
		if(h[eerste] > h[tweede]){
			v[pos]=h[tweede];
			pos++; tweede++;
		}else{
			v[pos]=h[eerste];
			pos++; eerste++;	
		}
	}
	while(eerste<=m){
		v[pos]=h[eerste];
		pos++; eerste++;	
	}
	while(tweede<=r){
		v[pos]=h[tweede];
		pos++; tweede++;
	}
}

template<typename T>
int Mergesortalt(vector<T>&v, int l, int r, vector<T>& h){
	if(l < r){		
		int m=l+(r-l)/2;
		int ret = Mergesortalt(h,l,m,v);
		Mergesortalt(h,m+1,r,v);
		Mergealt(h,l,m,r,v);
		return ret+1;
	}else{
		return 0;
	}
}

template<typename T>
void Mergesortalt(vector<T>& v){
	vector<T> hulp(v);
//	Print(hulp);
	int ret= Mergesortalt(v,0,v.size()-1,hulp);
	if(ret%2==0){
		cout<<"hello";
		for(int i=0; i<hulp.size();i++){
		v[i]=hulp[i];
		}
	}
//	cout<<ret<<endl;
//	Print(hulp);
	
}
