#ifndef __GEWOGENGRAAF_H
#define __GEWOGENGRAAF_H
#include "graaf.h"
#include <queue>

#include "printers.h"

using namespace std;

enum Kleur { WIT,ZWART,GRIJS
};

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
    
	void onderzoek_buren(const GewogenGraaf& g,int knoopnr,	priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>>&pq, vector<int>& mindist);
    
	vector<int> Dijkstra(const GewogenGraaf& g,int);

protected:
    vector<Takdata> takdatavector;
    vector<int> ouders; //afspraak: -2 is ouder nog niet bepaald en -1 is geen ouder
    vector<Kleur> kleuren;
    // priority_queue<pair<Takdata,int> > wachtrij;
    vector<int> mindist;
};


template < class Takdata>
vector<int> GewogenGraaf<Takdata>::GewogenGraaf::Dijkstra(const GewogenGraaf& g, int startknoop){
	wis();
	knopen.resize(g.aantal_knopen());
	ouders.resize(g.aantal_knopen()); // -2 wilt zeggen ouder nog niet bepaald
	kleuren.resize(g.aantal_knopen());
	vector<int>mindist(g.aantal_knopen());

	for(int i=0;i<g.aantal_knopen();i++){
		kleuren[i] = WIT;
		ouders[i] = -2;
		mindist[i]=-1;
	}	
	priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>>pq;
	//start met de eerst knoop (startknoop is opgegeven)
	ouders[startknoop] = -1;
	mindist[startknoop]=0;
	onderzoek_buren(g,startknoop,pq,mindist);
	
	while(!pq.empty()){
		pair<double,int> p = pq.top();
		pq.pop();
		if(kleuren[p.second]!=ZWART){
				// voeg_verbinding_toe(ouders[p.second],p.second,*g.geef_takdata(ouders[p.second],p.second));	
				 cout<<"gg.h: voeg verbinding toe van: "<<ouders[p.second]<<" naar "<<p.second<<"\n";
				onderzoek_buren(g,p.second,pq,mindist);
		}
		
	}
	return mindist;
}

template<class Takdata>
void GewogenGraaf<Takdata>::onderzoek_buren(const GewogenGraaf& g,int knoopnr,	priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>>&pq, vector<int>& mindist){
	kleuren[knoopnr] = ZWART;
	for(map<int,int>::const_iterator it = g.knopen[knoopnr].begin();it!=g.knopen[knoopnr].end();it++){
		if(kleuren[it->first]!=ZWART){ 
//zwarte buren zitten al in de MOB
//knoop wordt voor de eerste keer tegengekomen (heeft nog geen minimale afstand gekregen TOT BEGINKNOOP)
//knoop is al grijs, maar kan nu een lichtere verbinding krijgen
			int nieuweafstand=mindist[knoopnr]+*g.geef_takdata(knoopnr,it->first);
			if(kleuren[it->first] == WIT || nieuweafstand < mindist[it->first] ){ 
				kleuren[it->first] = GRIJS;
				ouders[it->first] = knoopnr;
				mindist[it->first]=nieuweafstand;
				pair<double,int> p(mindist[it->first],it->first);
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

