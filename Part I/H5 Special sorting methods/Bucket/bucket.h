#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

#include "lijst.h"

void Insertionsort(vector<int>& v){
	for(int i=1; i<v.size(); i++){
		int h= v[i];
		int j= i-1;
		while(j >= 0 && v[j] > h){
			v[j+1]= v[j];
			j--;
		}
		v[j+1]=h;
	}	
}

void Bucketsort(vector<int>& v){
	int max= v[0];
	for(int i=1; i < v.size(); i++){
		if(v[i] > max) max=v[i];
	}
	// We kiezen hier voor 6 buckets
	int m = 6;
	int bucket_size = max/6+1;
	vector<int> buckets[6];
	// cout<<"tot hier size:"<<bucket_size<<endl;
	for(int i=0; i < v.size(); i++){
		buckets[v[i]/bucket_size].push_back(v[i]);
	}
	// Nu instertion sort op elke bucket uitvoeren.
	for(int i=0; i < m; i++){
		Insertionsort(buckets[i]);
	}
	int pos=0;
	// Nu is elke bucket gesorteerd met insertion sort en kunnnen we ze binnen plaatsen
	for(int i=0; i < m; i++){
		for(int j=0; j < buckets[i].size(); j++){
			v[pos++] = buckets[i][j];
		}
	}
}

// m stelt het aantal buckets voor
// probleem wanneer ik buiten scope ga dan verdwijnen buckets--> maar er wordt naar gerefereerd
void Bucketsort(Lijst<int>& l, int m){
	int max = l.ZoekMaxwaarde();
	int bucket_size = max/m+1;
	
	Lijst<int> buckets[m];
	Lijst<int>* loper = &l;
	while(loper->k){
		buckets[loper->k->sl/bucket_size].VoegToeVooraan(loper);
		// de methode voegtoevooraan zorgt dat hij automatisch naar voor loopt
		//loper = &(loper->k->volgend);
	}
	
	for(int i=0; i < m ; i++){
		buckets[i].insertion_sort();
	}
	cout<<"tot hier";
	int pos=0;
	l.k=nullptr;
	for(int i=0; i <m ; i++){
		cout << "ik voeg: ";
		buckets[i].Print();
		cout<< "toe \n";
		l.VoegToeAchter(buckets[i]);		
	}
	
}




