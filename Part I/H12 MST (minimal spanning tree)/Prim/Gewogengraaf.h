#ifndef __GEWOGENGRAAF_H
#define __GEWOGENGRAAF_H
#include "graaf.h"
#include <queue>

using namespace std;

enum Kleur { WIT,ZWART,GRIJS};

template<class Takdata>
class GewogenGraaf: public virtual Graaf<ONGERICHT>{
public:
    GewogenGraaf(int n=0):Graaf<ONGERICHT>(n){};
    //Noot: toevoegfunctie zonder takdata op te geven kan alleen gebruikt als de klasse
    //      Takdata een defaultconstructor heeft.
    
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

    // Schrijft de gegevens van de verbinding met verbindingsnummer v naar outputstream os.
    virtual void schrijf_verbinding(ostream &os, int v) const;
    
    void wordMOBvan(const GewogenGraaf& g);
    
    void onderzoek_buren(const GewogenGraaf& g,int knoopnr,	priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>>&pq);

protected:
    vector<Takdata> takdatavector;
    vector<int> ouders; //afspraak: -2 is ouder nog niet bepaald en -1 is geen ouder
    vector<Kleur> kleuren;   
};


template < class Takdata>
void GewogenGraaf<Takdata>::GewogenGraaf::wordMOBvan(const GewogenGraaf& g){
	wis();
	knopen.resize(g.aantal_knopen());
	ouders.resize(g.aantal_knopen()); // -2 wilt zeggen ouder nog niet bepaald
	kleuren.resize(g.aantal_knopen());
	for(int i=0;i<g.aantal_knopen();i++){
		kleuren[i] = WIT;
		ouders[i] = -2;
	}
	priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>>pq;
	
	//start met de eerst knoop (startknoop is willekeurig bij Prim)
	ouders[0] = -1;
	// eigenlijk moet deze grijs zijn maar hij wordt toch per direct zwart
	onderzoek_buren(g,0,pq);
	
	while(!pq.empty()){
		pair<double,int> p = pq.top();
		pq.pop();
		if(kleuren[p.second]!=ZWART){
				voeg_verbinding_toe(ouders[p.second],p.second,p.first);		
				 cout<<"gg.h: voeg verbinding toe van: "<<ouders[p.second]<<" naar "<<p.second<<"\n";
				onderzoek_buren(g,p.second,pq);
		}
		
	}
}

template<class Takdata>
void GewogenGraaf<Takdata>::onderzoek_buren(const GewogenGraaf& g,int knoopnr,	priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>>&pq){
	kleuren[knoopnr] = ZWART;
	for(map<int,int>::const_iterator it = g.knopen[knoopnr].begin();it!=g.knopen[knoopnr].end();it++){
		if(kleuren[it->first]!=ZWART){ 
//zwarte buren zitten al in de MOB
//knoop wordt voor de eerste keer tegengekomen of
//knoop is al grijs, maar kan nu mogelijks via een lichtere verbinding met mob verboven worden
			if(kleuren[it->first] == WIT || *g.geef_takdata(knoopnr,it->first) < *g.geef_takdata(ouders[knoopnr],knoopnr) ){ 
				kleuren[it->first] = GRIJS;
				ouders[it->first] = knoopnr;
				pair<double,int> p(*g.geef_takdata(knoopnr,it->first),it->first);
				pq.push(p);
			}
		}
	}	
}

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
void  GewogenGraaf<Takdata>::schrijf_verbinding(ostream &os, int v) const{
    os << " via verbinding nr. " << v <<" (Data: "<<takdatavector[v]<<")"<< endl;
}

#endif

