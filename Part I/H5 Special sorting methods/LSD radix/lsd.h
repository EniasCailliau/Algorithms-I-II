#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

void lsdsort(vector<int>& v){
	// eerst max bepalen
	int max = v[0];
	for(int i=1; i < v.size(); i++){
		if(v[i] > max) max = v[i];
	}
//	cout<< "max= "<<max<<endl;
	int radix = 1;
	while(max/radix >= 1){
// geen recursieve oproepen dus ook geen parttab nodig
		vector<int> posities(10);
		for(int i=0; i < v.size(); i++){
			posities[(v[i]/radix)%10]++;
		}
		for(int i=1; i<10; i++){
			posities[i] = posities[i]+posities[i-1];
		}
		vector<int> tijd(v.size());
		for(int i=v.size()-1; i>=0; i--){
			tijd[posities[(v[i]/radix)%10]-1]= v[i];
			posities[(v[i]/radix)%10]--;
		}
		
		for(int i=0; i < v.size(); i++){
			v[i]= tijd[i];
		}
		radix*=10;
	}
	
	
	
}
