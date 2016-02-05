#include <vector>
#include <iostream>
#include <cmath>

#define BASIS 10

using namespace std;

template <typename T>
void Print (const vector<T>& v){
  for (int i=0; i<v.size();i++){
    cout << v[i]<<" ";
  }
  cout<<endl;
}

template <typename T>
void swap(vector<T>& v, int i, int j){
	T h = v[i];
	v[i] = v[j];
	v[j] = h;
}


template <typename T>
void countingsort(vector<T>& v, int start, int eind, int pos){
	int radix= pow(BASIS,pos);
	if(pos >= 0 && start < eind){		
	//cout<<"radix= "<<radix<<endl;
	
	vector<int> tellen(BASIS);
	
	for(int i=start; i<=eind; i++){
		tellen[(v[i]/radix)%10]++;
	}
	// tellen normaliseren
	vector<int> back(10);
	for(int i=1; i<10; i++){
		tellen[i] = tellen[i]+tellen[i-1];
	}
	
	for(int i=0; i<10; i++){
		back[i]= tellen[i]-1;
	}
//	Print(back);
	Print(tellen);
	
	
	vector<T> tijd(v.size());
	for(int i=eind; i>=start; i--){
		tijd[tellen[(v[i]/radix)%10]+start-1] = v[i];
		tellen[(v[i]/radix)%10]--;
	}
	
	for(int i=start; i <=eind; i++){
		v[i] = tijd[i];
	}
	Print(v);
	pos=pos-1;
	for(int j=0; j < 10 ; j++){
		int vorige;
		if(j==0){
			vorige = 0;
		}else vorige = back[j-1]+1;
		//cout<<"hier"<<vorige<<" "<<"back"<<back[j];
// belangrijk hier moet er start bij staan anders geld het niet
		countingsort(v, vorige+start, back[j]+start, pos);		
		}
	}
	
}

template <typename T>
int msd(vector<T>& v, int start, int eind, int pos, vector<T>& h){
	int radix= pow(BASIS,pos);
	if(pos >= 0 && start < eind){		
	cout<<"radix= "<<radix<<endl;
	
	vector<int> tellen(BASIS);
	
	for(int i=start; i<=eind; i++){
		tellen[(v[i]/radix)%10]++;
	}
	// tellen normaliseren
	vector<int> back(10);
	for(int i=1; i<10; i++){
		tellen[i] = tellen[i]+tellen[i-1];
	}
	
	for(int i=0; i<10; i++){
		back[i]= tellen[i]-1;
	}
//	Print(back);
	Print(tellen);
	for(int i=eind; i>=start; i--){
		h[tellen[(v[i]/radix)%10]+start-1] = v[i];
		tellen[(v[i]/radix)%10]--;
	}
	Print(v);
	pos=pos-1;
	int ret;
	for(int j=0; j < 10 ; j++){
		int vorige;
		if(j==0){
			vorige = 0;
		}else vorige = back[j-1]+1;
		//cout<<"hier"<<vorige<<" "<<"back"<<back[j];
// belangrijk hier moet er start bij staan anders geld het niet
		 ret = msd(h, vorige+start, back[j]+start, pos,v);		
		}
		return ret+1;
	}else{
		return 0;
	}
	
}


template <typename T>
void msdsort(vector<T>& v){
		T max= v[0];
	for(int i=1; i<v.size(); i++){
		if(v[i] > max) max = v[i]; 
	}
	int exp = log10(max);
	//cout<<exp;
	vector<T>h(v.size());
	int ret = msd(v, 0, v.size()-1, exp,h);
	if(ret%2==1){
		cout<<"hier"<<endl;
	}else{
		
	}
	
}
