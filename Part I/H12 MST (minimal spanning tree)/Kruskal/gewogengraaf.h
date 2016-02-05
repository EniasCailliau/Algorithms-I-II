#ifndef __GEWOGENGRAAF_H
#define __GEWOGENGRAAF_H
#include "graaf.h"

#include <queue> 
	using namespace std;
#include <limits.h>

enum Kleur{
	wit,zwart,grijs
};


template<class Takdata>
class GewogenGraaf: public virtual Graaf<ONGERICHT>{
public:
    GewogenGraaf(int n=0):Graaf<ONGERICHT>(n){};
    //Noot: toevoegfunctie zonder takdata op te geven kan alleen gebruikt als de klasse
    //      Takdata een defaultconstructor heeft.
    
    void wordMOBvan(const GewogenGraaf& g);
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
    std::vector<int> PARENT;
    std::vector<int> HOOGTE;
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

// Deze zoekt snel naar vertegenwoordiger van de partitie waar de knoop inzit
// Bij efficiënte Union is dit dus het stijgen in de partitieboom (via ouderwijzers)
template< class Takdata>
int GewogenGraaf<Takdata>::Find(int knoop){
	if(PARENT[knoop]==knoop){
		return knoop;
	}
	else{
		return Find(PARENT[knoop]);
	}	
}
template< class Takdata>
void GewogenGraaf<Takdata>::Union(int kn1, int kn2){
	// Bij de efficiënte vorm van een union gaan we altijd de kleinste bij de hoogste plaatsen
	if(HOOGTE[kn1]>HOOGTE[kn2]){
		PARENT[kn2]=kn1;
	}else if(HOOGTE[kn2]>HOOGTE[kn1]){
		PARENT[kn1]=kn2;
	}else{
		PARENT[kn1]=kn2;
		HOOGTE[kn2]++;
	}
}

template< class Takdata>
void GewogenGraaf<Takdata>::MakeSet(int kn){
	PARENT[kn]=kn;
	HOOGTE[kn]=0;
}

template< class Takdata>
void GewogenGraaf<Takdata>::wordMOBvan(const GewogenGraaf& gg){
	init(gg.aantal_knopen());
	// volgende code moet eigenlijk in init ///
	PARENT.resize(aantal_knopen());
	HOOGTE.resize(aantal_knopen());
	///////
	priority_queue< pair<int,string>,vector<pair<int,string>>, greater<pair<int,string>>> q;
	for(int i=0; i<gg.knopen.size(); i++){
		MakeSet(i);
// alle verbindingen moeten overlopen worden en in de wachtrij geplaatst worden. (gewicht van de verbinding als prioriteit)	
		for(std::map<int,int>::const_iterator it=gg.knopen[i].begin(); it!=gg.knopen[i].end(); ++it){
			int gewicht = gg.takdatavector[it->second];
			int naar = it->first;
			int van=i;
			string s; s.append(to_string(van)); s.append("."); s.append(to_string(naar));
			q.push(pair<int,string>(gewicht,s));
		}
	}	
	int aantalverbindingen=0;

// we stoppen bij n-1 want na n-1 unions hebben we slechts 1 cluster --> 1 MOB
	while(aantalverbindingen < gg.aantal_knopen()-1){
		pair<int,string> p = q.top(); q.pop();
		int pos = p.second.find(".");
		int van = atoi(p.second.substr(0,pos).c_str());
		int naar= atoi(p.second.substr(pos+1).c_str());
		cout<<van<<"."<<naar<<endl;
		int root1=Find(van);
		int root2=Find(naar);
		if(root1!=root2){
			// Ze behoren niet tot dezelfde partitieboom dus moeten we ze samenvoegen
			// Gewicht van de verbinding is hier eigenlijk niet belangrijk
			voeg_verbinding_toe(van,naar);
			cout<<"ik voeg toe: "<<van<<"."<<naar<<endl;
			// we voegen ze samen in onze mob maar moeten ook de "boekhouding" op orde brengen
			Union(root1,root2);
			aantalverbindingen++;

		}
	}
}



#endif

