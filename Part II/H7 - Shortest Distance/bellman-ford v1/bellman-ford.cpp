#include "graaf.h"
#include <queue>

using namespace std;

typedef std::map<int, int>  Knoop;      // beeldt knoopnummer (van buur) af op verbindingsnummer


// ik zeg dat het gewicht hier integers zijn, src wijst naar de beginknoop waar de afstanden van vertrekken
// opmerking ik heb alle dataleden van graaf publiek gezet zodat ik hier aan kan
// voorlopig: implementatie zonder voorloper vector
void BellmanFord(GraafMetTakdata<GERICHT, int>& graaf, int src)
{
    int V = graaf.aantalKnopen();
    int E = graaf.aantalVerbindingen();
    vector<int>afstanden(V);
 
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for(int i = 0; i < V; i++){
      afstanden[i]   = INT_MAX;
	}
    afstanden[src] = 0;
 
    std::queue<int> q;                 // empty queue
    int aantaliteraties = -1;
	q.push(src);
	while(!q.empty()){
		aantaliteraties++;
		int knoopnr = q.front();
		q.pop();
		// alle buren controleren of ze een betere waarde krijgen.
		 for (Knoop::const_iterator it=graaf.knopen[knoopnr].begin(); it!=graaf.knopen[knoopnr].end(); ++it){
        	cout << "controle van verbinding: " << it->first;
        	int van = knoopnr;
        	int naar = it->first;
        	if(afstanden[naar] > *graaf.geefTakdata(van, naar)+afstanden[van]){
        		afstanden[naar] = *graaf.geefTakdata(van, naar)+afstanden[knoopnr];
        		cout<<"ik heb een betere afstand gevonden: "<<afstanden[naar]<<endl;
        		// wanneer dat een betere afstand gevonden werd voor een knoop dan gaan we die toevoegen aan de que
        		q.push(naar);
			}
//        schrijfVerbinding(os, it->second);
    	}
			
	}
	if(aantaliteraties > V){
		cout<<"ik heb een negatieve lus gevonden aantaliteraties= "<<aantaliteraties<<endl;
	}
 
}
 
int main(){
	 GraafMetTakdata<GERICHT,int> graaf(4);
    graaf.voegVerbindingToe(0,2, -2);
    graaf.voegVerbindingToe(0,3,-4);
    graaf.voegVerbindingToe(0,1,3);
    graaf.voegVerbindingToe(1,3,5);
    graaf.voegVerbindingToe(3,2,-1);
    graaf.schrijf(cout);
	BellmanFord(graaf, 0);
	
}
