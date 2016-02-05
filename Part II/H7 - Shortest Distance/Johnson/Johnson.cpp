#include "graaf.h"
#include "printers.h"
//#include "bellman-ford.cpp"
#include <iostream>
#include <map>

typedef std::map<int,int> Knoop;

using namespace std;

void Johnson(GraafMetTakdata<GERICHT,int>& graaf){
	
	int V = graaf.aantalKnopen()+1;
    int E = graaf.aantalVerbindingen();
    vector<int> afstanden(V);
 
    // Initialiseren van de afstanden vanuit src als 0.
    for(int i = 0; i < V; i++){
      afstanden[i]   = 0;
	}
 
    std::queue<int> q;                 // empty queue
    int aantaliteraties = -1;
    // alle buren van S toevoegen (dus alle knopen)
    for(int i=0; i< graaf.aantalKnopen(); i++){
    	q.push(i);
	}
//	q.push(src);
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
    	}
			
	}
	if(aantaliteraties > V){
		cout<<"ik heb een negatieve lus gevonden aantaliteraties= "<<aantaliteraties<<endl;
	}
	
	
	
	// eerste stap is een NIEUWE graaf te maken met een extra knoop (S)
	// Hierbij heeft S een verbinding met alle andere knopen
	// copy zou ook mogelijk zijn, en daarna een verbinding toevoegen.
//	GraafMetTakdata<GERICHT,int> nieuwegraaf(graaf);
//	nieuwegraaf.schrijf(cout);
//	int S = nieuwegraaf.voegKnoopToe();
//	for(int i=0; i<nieuwegraaf.aantalKnopen()-1 ; i++){
//		nieuwegraaf.voegVerbindingToe(S,i,0);
//	}
	// zou hier beter zijn om afstanden door te geven naar belmanford
//	vector<int> afstanden = BellmanFord(nieuwegraaf,S);
	Print(afstanden);	
	
	GraafMetTakdata<GERICHT,int> positievegewichtenGraaf(graaf.aantalKnopen());
	for(int i=0; i<graaf.aantalKnopen(); i++){
		for(map<int,int>::const_iterator it= graaf.knopen[i].begin(); it!=graaf.knopen[i].end(); ++it){
			int van = i;
			int naar= it->first;
			int pos_gewicht = *graaf.geefTakdata(van,naar)+afstanden[van]-afstanden[naar];
			positievegewichtenGraaf.voegVerbindingToe(van,naar,pos_gewicht);
		}	
	}
	positievegewichtenGraaf.schrijf(cout);
	vector<vector<int>> distancematrix;
	distancematrix.resize(positievegewichtenGraaf.aantalKnopen());
	for(int i=0; i<positievegewichtenGraaf.aantalKnopen(); i++){
		distancematrix[i]=positievegewichtenGraaf.Dijkstra(i);
	}
	// nu corrigeren van distancematrix met omgekeerde regel
	for(int i=0; i<positievegewichtenGraaf.aantalKnopen(); i++){
		for(int j=0; j<positievegewichtenGraaf.aantalKnopen(); j++){
			distancematrix[i][j]= distancematrix[i][j]-afstanden[i]+afstanden[j];
		}
	}
	
	cout<<"\t";
	for(int i=0; i<distancematrix.size(); i++){
		cout<<i<<"\t";
	}
	cout<<endl<<"----------------------------------------------------------------"<<endl;
	for(int i=0; i<distancematrix.size(); i++){
		cout<<i<<": ";
		Print(distancematrix[i]);
	}
	
	
};

void testDijkstra(){
	GraafMetTakdata<GERICHT,int> d(5);
	d.voegVerbindingToe(0,2,10);
	d.voegVerbindingToe(0,4,5);
	d.voegVerbindingToe(0,1,20);
	d.voegVerbindingToe(3,1,3);
	d.voegVerbindingToe(4,3,4);
	d.voegVerbindingToe(2,3,10);
	d.voegVerbindingToe(4,2,2);
	
	vector<int> distances = d.Dijkstra(0);
	Print(distances);
}

int main(){	
	Printspecial("testen van Dijkstra");
//	testDijkstra();

	GraafMetTakdata<GERICHT,int> graaf(6);
	graaf.voegVerbindingToe(0,1,-2);
	graaf.voegVerbindingToe(1,2,-1);
	graaf.voegVerbindingToe(2,0,4);
	graaf.voegVerbindingToe(2,3,-3);
	graaf.voegVerbindingToe(4,3,-4);
	graaf.voegVerbindingToe(4,5,1);
	graaf.voegVerbindingToe(2,5,2);
	graaf.schrijf(cout);
	Printspecial("Uitvoer van het Johnson algoritme");
	Johnson(graaf);
	return 0;
}
