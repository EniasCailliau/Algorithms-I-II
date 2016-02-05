#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

class Heap{
		public: Heap():v(){}
				Heap(vector<int> &v);
		void VoegToe(int sl);
		void VervangTop(int sl);
		void Print();
		void MaakHeap(vector<int> & v);
		void TransformToHeap(vector<int> &v);
		int PopTop();
		void Sort();
	private: 
		vector<int> v;
};

Heap::Heap(vector<int> &v){
	for(int i=0; i<v.size(); i++){
		VoegToe(v[i]);
	}
}

int Heap::PopTop(){
	int top = v[0];
	int back = v.back();
	v.pop_back();
	VervangTop(back);
	return top;
}

void Heap::Sort(){
int top, back;
for(int i=0; i<2; i++){
	top=v[0];
	back= v[v.size()-i-1];
	v[v.size()-i-1]=top;
	VervangTop(back);
}		
}

void Heap::MaakHeap(vector<int> &v){
	for(int i=1; i<v.size(); i++){
		int sl= v[i];
		int prevpos= i;
		int pos= floor((i-1)/2);
		while(pos>=0 && v[pos]<sl){
		//schuiven naar beneden
			v[prevpos]=v[pos];
			prevpos=pos;
			pos=floor((pos+1)/2)-1;
		}
		v[prevpos]=sl;
	}	
}
////void Heap::TransformToHeap(vector<int> &v){
////	int i=(v.size()-2)/2;
////	while(i>=0){
////		while(1){		
////		int prevpos=i;
////		int pos;
////		if(2*i+1<v.size() && (2*i+2>=v.size() || v[2*i+1]>=v[2*i+2])){
////			if(v[2*i+1]>v[i]) pos=2*i+1;
////			else{break;}
////		}else{
////			if(v[2*i+2]>v[i]) pos=2*i+2;
////			else break;
////		}
////		int h=v[pos];
////		v[pos]=v[prevpos];
////		v[prevpos]=h;
////		prevpos=pos;
////		}
////		i--;
////	}
////}

void Heap::VoegToe(int sl){
	v.push_back(sl);
	int prevpos= v.size()-1;
	int pos= floor(v.size()/2)-1;
	// dubbele voorwaarde nodig anders buiten tabel
	while(pos>=0 && v[pos] < sl){
		//schuiven naar beneden
		v[prevpos]=v[pos];
		prevpos=pos;
		pos=floor((pos+1)/2)-1;
	}
	v[prevpos]=sl;
}

void Heap::VervangTop(int sl){
	//cout << v.size()<<endl;
	
	// kijken of het bestaat en of het groter is dan nieuwe waarde sl;
	if(v[0] && v[0] > sl){
		int pos= 0;
		int prevpos;
		while(pos*2+1 < v.size()){
			if(pos*2+2 >= v.size() || v[pos*2+2] < v[pos*2+1]){
				//linkse is baas
				if(sl < v[pos*2+1]){
					prevpos=pos;				
					pos=pos*2+1;
				}else break;					
			}else if(pos*2+2 < v.size() && sl < v[pos*2+2]){
					prevpos=pos;
					pos=pos*2+2;
				}else	break;				
			v[prevpos]=v[pos];	
			}
		v[pos]=sl;			
	}else{
		//geen probleem is het grootste
		v[0]=sl;
	}
}

void Heap::Print(){
	for(int i=0; i<v.size(); i++){
		cout<< v[i] <<" ";
	}
	cout<< endl;
}
