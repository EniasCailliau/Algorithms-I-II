#ifndef __GEWOGENGRAAF_H
#define __GEWOGENGRAAF_H
#include "graaf.h"

#include <queue> 
	using namespace std;
#include <limits.h>
#include <iostream>   // voor test/debugfase
	using std::cin;
	using std::cout;
	using std::cerr;
	using std::endl;
#include <fstream>
	using std::ostream;
	using std::istream;
#include <string>
	using std::string;
#include <memory>
	using std::unique_ptr;
	
using namespace std;


enum Kleur{
	wit,zwart,grijs
};

struct entry{
	int knoop;
	unique_ptr<struct entry> volgend;
};


template<class Takdata>
class GewogenGraaf: public virtual Graaf<ONGERICHT>{
public:
    GewogenGraaf(int n=0):Graaf<ONGERICHT>(n){};
    //Noot: toevoegfunctie zonder takdata op te geven kan alleen gebruikt als de klasse
    //      Takdata een defaultconstructor heeft.
    
    void wordMOBvan(const GewogenGraaf& g);
    void Cluster(const GewogenGraaf& g, int clusters);
    virtual int voeg_verbinding_toe(int van, int naar); 
    virtual int voeg_verbinding_toe(int van, int naar, const Takdata&);

    //Noot: verwijder_verbinding niet voorzien; wordt ongewijzigd overgenomen van Graaf
	//      indien daar bekend.

    //TakData vrijgeven (eventueel voor wijziging). Geeft nullpointer als tak niet bestaat
    //Noot: pointers teruggegeven door geef_takdata worden ongeldig
    //door toevoegen van een tak.
    const Takdata* geef_takdata(int van,int naar) const;
          Takdata* geef_takdata(int van,int naar)      ;

    // wist alle gegevens uit de graaf; aantal knopen is dan ook nul!
    virtual void wis();
	int Find(int knoop);
	void Union(int kn1, int kn2);
	void MakeSet(int kn);

    // Schrijft de gegevens van de verbinding met verbindingsnummer v naar outputstream os.
    virtual void schrijf_verbinding(std::ostream &os, int v) const;

protected:
    std::vector<Takdata> takdatavector;
    std::vector<int> vertegenwoordiger;
    std::vector<int> grootte;
	std::vector<unique_ptr<struct entry>> lijsten;
private :
	void initieer(const GewogenGraaf& g,priority_queue< pair<int,string>,vector<pair<int,string>>, greater<pair<int,string>>>& q);
};


template< class Takdata>
int GewogenGraaf<Takdata>::voeg_verbinding_toe(int van, int naar){
    return this->voeg_verbinding_toe(van,naar,Takdata());
}


template< class Takdata>
int GewogenGraaf<Takdata>::voeg_verbinding_toe(int van, int naar, const Takdata& td){
    int taknummer=Graaf<ONGERICHT>::voeg_verbinding_toe(van,naar);
    takdatavector.push_back(td);
    return taknummer;
}



template< class Takdata>
const Takdata* GewogenGraaf<Takdata>::geef_takdata(int van,int naar) const{
    int taknummer=this->verbindingsnummer(van,naar);
    if (taknummer!=-1)
        return &takdatavector[taknummer];
    else
        return 0;
}

template< class Takdata>
Takdata* GewogenGraaf<Takdata>::geef_takdata(int van,int naar){
    int taknummer=this->verbindingsnummer(van,naar);
    if (taknummer!=-1)
        return &takdatavector[taknummer];
    else
        return 0;
}


template< class Takdata>
void GewogenGraaf<Takdata>::wis(){
    Graaf<ONGERICHT>::init(0); 
    takdatavector.clear();
}

template< class Takdata>
void  GewogenGraaf<Takdata>::schrijf_verbinding(std::ostream &os, int v) const{
    os << " via verbinding nr. " << v <<" (Data: "<<takdatavector[v]<<")"<< std::endl;
}

template< class Takdata>
int GewogenGraaf<Takdata>::Find(int knoop){
		return vertegenwoordiger[knoop];
}
template< class Takdata>
void GewogenGraaf<Takdata>::Union(int kn1, int kn2){
	//voeg de lijsten samen afhankelijk van de grootte
	if(grootte[kn1]<grootte[kn2]){
		//overloop eerst de kleinste om de vertwegenwoordiger tabel aan te passen
		unique_ptr<struct entry>* laatste=&lijsten[kn1];
		while(*laatste!=nullptr){
			vertegenwoordiger[laatste->get()->knoop]=kn2;
			laatste=&(laatste->get()->volgend);
		}
		//hang dan de rest van 1 aan twee
		laatste=&lijsten[kn2];
		while(*laatste!=nullptr){
			laatste=&(laatste->get()->volgend);
		}
		*laatste=std::move(lijsten[kn1]);
	}
	else{
		unique_ptr<struct entry>* laatste=&lijsten[kn2];
		while(*laatste!=nullptr){
			vertegenwoordiger[laatste->get()->knoop]=kn1;
			laatste=&(laatste->get()->volgend);
		}
		laatste=&lijsten[kn1];
		while(*laatste!=nullptr){
			laatste=&(laatste->get()->volgend);
		}
		*laatste=std::move(lijsten[kn2]);
	}
}

template< class Takdata>
void GewogenGraaf<Takdata>::MakeSet(int kn){
	//de knopen zijn eerst deelverzamelingen op zich, allemaal met grootte 1
	// cout<<kn<<endl;
	vertegenwoordiger[kn]=kn;
	grootte[kn]=1;
	unique_ptr<struct entry> lijst(new struct entry);
	lijst->knoop=kn;
	lijsten[kn].swap(lijst);
}

template< class Takdata>
void GewogenGraaf<Takdata>::initieer(const GewogenGraaf& gg, priority_queue< pair<int,string>,vector<pair<int,string>>, greater<pair<int,string>>>& q){
	init(gg.aantal_knopen());
	
	vertegenwoordiger.resize(aantal_knopen());
	grootte.resize(aantal_knopen());
	lijsten.resize(aantal_knopen());
	
	for(int i=0; i<gg.knopen.size(); i++){
		MakeSet(i);
		for(std::map<int,int>::const_iterator it=gg.knopen[i].begin(); it!=gg.knopen[i].end(); ++it){
			int gewicht = gg.takdatavector[it->second];
			int naar = it->first;
			int van=i;
			string s; s.append(to_string(van)); s.append("."); s.append(to_string(naar));
			q.push(pair<int,string>(gewicht,s));
		}
	}	
}




template< class Takdata>
void GewogenGraaf<Takdata>::wordMOBvan(const GewogenGraaf& gg){
	
	priority_queue< pair<int,string>,vector<pair<int,string>>, greater<pair<int,string>>> q;
	initieer(gg,q);
	int aantalverbindingen=0;

	while(aantalverbindingen < gg.aantal_knopen()-1){
		pair<int,string> p = q.top(); q.pop();
		int pos = p.second.find(".");
		int van = atoi(p.second.substr(0,pos).c_str());
		int naar= atoi(p.second.substr(pos+1).c_str());
		// cout<<van<<"."<<naar<<endl;
		int root1=Find(van);
		// cout<<root1<<endl;
		int root2=Find(naar);
		// cout<<root2<<endl;
		if(root1!=root2){
			 voeg_verbinding_toe(van,naar);
			// cout<<"union"<<endl;
			Union(root1,root2);
			aantalverbindingen++;
		}
	}
}

template< class Takdata>
void GewogenGraaf<Takdata>::Cluster(const GewogenGraaf& gg, int clusters){
	priority_queue< pair<int,string>,vector<pair<int,string>>, greater<pair<int,string>>> q;
	initieer(gg,q);
	
	int aantalverbindingen=0;
	//identiek aan Kruskal maar zonder laatste k-1 zwaarste verbindingen met k clusters
	while(aantalverbindingen < (gg.aantal_knopen()-clusters)){
		pair<int,string> p = q.top(); q.pop();
		int pos = p.second.find(".");
		int van = atoi(p.second.substr(0,pos).c_str());
		int naar= atoi(p.second.substr(pos+1).c_str());
		// cout<<van<<"."<<naar<<endl;
		int root1=Find(van);
		// cout<<root1<<endl;
		int root2=Find(naar);
		// cout<<root2<<endl;
		if(root1!=root2){
			voeg_verbinding_toe(van,naar);
			// cout<<"union"<<endl;
			Union(root1,root2);
			aantalverbindingen++;

		}
	}
}

#endif
