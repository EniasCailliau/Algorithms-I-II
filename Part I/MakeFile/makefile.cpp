#include "graaf.h"
#include <string>
	using std::string;
#include <fstream>
	using std::ifstream;
#include <map>
	using std::map;
#include <sstream>
#include <stdio.h>


using namespace std;

void printmap(map<string,int>& m){
	for(map<string,int>::const_iterator d=m.begin();d!=m.end();d++){
		//printf("%10s | %3d ",d->first,d->second);
		cout<<"file= "<<d->first<<" | "<<d->second<<endl;
	}
}

template <class T>
void printvector(vector<T>& v){
	// cout<<v.size();
	for(int i=v.size()-1; i>=0; i--){
		cout<<v.size()-i<<"component: "<<v[i]<<"\t";
	}
	cout<<endl;
}

void maakgraaf(map<string,int>& knopen,vector<string>& knopeninv,const char* bestandsnaam){
	printmap(knopen);
	ifstream in(bestandsnaam);
	Graaf<GERICHT> graaf(knopen.size());
	string line;
	getline(in,line);
	while(!in.fail()){
		int pos = line.find(':');
		string first = line.substr(0,pos-1);
		string second = line.substr(pos+1);
		//cout<<first;	
		int naar = knopen[first];
		istringstream iss(second);
		string word;
		while(iss>>word){
			// cout<<word<<endl;
			graaf.voeg_verbinding_toe(knopen[word],naar);
		}
		getline(in,line);	
	}
	vector<int> postnummers = graaf.bepaal_postnummering();
	printvector(postnummers);
	graaf.schrijf(cout);

}

void lees(const char* bestandsnaam){
	map<string,int> knopen;
	vector<string> knopeninv;
	ifstream in(bestandsnaam);
	if(!in.is_open()){
		cout<<"fout bij inlezen"<<endl;
	}
	string woord;
	int knoopnr=0;
	while(!in.fail()){
		in>>woord;
		if(knopen.find(woord)==knopen.end() && woord!=":"){
			knopen[woord]=knoopnr++;
			knopeninv.push_back(woord);
		} 	
	}
	// printmap(knopen);
	// nu kan ik bestand nogmaals inlezen en verwerken
	maakgraaf(knopen,knopeninv,bestandsnaam);	
}

int main(){
	string file="makefile.txt";
	lees(file.c_str());
	return 0;
}
