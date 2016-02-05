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
    vector<bool> tweede_keer(V);
 	vector<int> aantal_iteraties(V);
 	bool negatievelus = false;
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    
    for(int i = 0; i < V; i++){
      afstanden[i]   = INT_MAX;
      tweede_keer[i] = false;
      aantal_iteraties[i] = 0;
	}
    afstanden[src] = 0;
 
    std::deque<int> q;     
           
	q.push_back(src);
	while(!q.empty()){
		int knoopnr = q.front();
		q.pop_front();
		// alle buren controleren of ze een betere waarde krijgen.
		 for (Knoop::const_iterator it=graaf.knopen[knoopnr].begin(); it!=graaf.knopen[knoopnr].end(); ++it){
        	cout << "controle van verbinding: " << it->first<<endl;
        	int van = knoopnr;
        	int naar = it->first;
        	if(afstanden[naar] > *graaf.geefTakdata(van, naar)+afstanden[van]){
        		afstanden[naar] = *graaf.geefTakdata(van, naar)+afstanden[knoopnr];
        		cout<<"ik heb een betere afstand gevonden: "<<afstanden[naar]<<endl;
        		if(aantal_iteraties[naar]++ > V){
        			negatievelus = true;
        			cout<<"!!!!!!!!!!!!!!!!!"<<endl;
        			break;
				}
        		// wanneer dat een betere afstand gevonden werd voor een knoop dan gaan we die toevoegen aan de que
        		if(tweede_keer[naar]){
        			cout<<"het is de tweede keer dat dit punt hier komt"<<endl;
        			q.push_front(naar);
				}else{
					tweede_keer[naar] = true;
					q.push_back(naar);
				}
			}
//        schrijfVerbinding(os, it->second);
    	}
			
	}
	if(negatievelus){
		cout<<"ik heb een negatieve lus gevonden aantaliteraties= "<<endl;
	}

}
 
int main(){
//	GraafMetTakdata<GERICHT,int> graaf(4);
//    graaf.voegVerbindingToe(0,2, -2);
//    graaf.voegVerbindingToe(0,3,-4);
//    graaf.voegVerbindingToe(0,1,3);
//    graaf.voegVerbindingToe(1,3,5);
//    graaf.voegVerbindingToe(3,2,-1);
//    graaf.schrijf(cout);
//	BellmanFord(graaf, 3);
	
	
/*
Tweede poging: zie figuur op blad
*/	

GraafMetTakdata<GERICHT,int> graaf(6);
graaf.voegVerbindingToe(0,1,5);
graaf.voegVerbindingToe(2,1,2);
graaf.voegVerbindingToe(0,2,-2);
graaf.voegVerbindingToe(1,3,1);
graaf.voegVerbindingToe(3,2,3);
graaf.voegVerbindingToe(4,2,3);
graaf.voegVerbindingToe(3,4,-7);
graaf.voegVerbindingToe(3,5,3);
graaf.voegVerbindingToe(4,5,10);
    graaf.schrijf(cout);
	BellmanFord(graaf, 0);


}
