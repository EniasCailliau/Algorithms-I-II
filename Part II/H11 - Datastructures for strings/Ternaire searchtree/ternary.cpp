#include <fstream>
#include "ternaireboom11.h"
#include <vector>
#include <algorithm>
#include "SString.h"
#include <string>

using namespace std;

int main(){
	std::ifstream infile("test.txt");
	string a;
	vector<Tboom> v(50);
	while (infile >> a)
	{	std::transform(a.begin(), a.end(), a.begin(), ::tolower);

		cout<<"ik heb net ingelezen: "<<a<<endl;
		if(a.size()>2){
			    	v[a.size()].voegtoe(a);

		}
	}	


	
	
////	for(int i=0; i<v.size(); i++){
////		cout<<"Ik shrijf ternaire boom met index: " << i<<" uit."<<endl;
////		cout<<v[i]<<endl;
////	}
//	
//	v[12].traverseTST();
//	cout<<endl;
//	cout<<v[12];
//
//	Tboom test;
//	test.voegtoe("cute");
//	test.voegtoe("cats");
//	test.traverseTST();
//	cout<<endl;
//	cout<<test;

SString ss(string("the"));
vector<string> result = ss.genereerwildcards();
for(int i=0; i<result.size(); i++){
	cout<<result[i]<<endl;

}

	Tboom test;
	test.voegtoe("cute");
	test.voegtoe("cats");
	test.zoekgelijkenden("cu?e");


return 0;
}



