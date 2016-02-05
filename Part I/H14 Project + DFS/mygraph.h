#include "graaf.h"
#include <cmath>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <string>
	using std::string;
#include <fstream>
	using std::stringstream;
	using std::ifstream;
/**
*	MijnGraaf is een gerichte lusloze graaf, gebaseerd op de oplossing van Miguel De Strooper en Enias Cailliau met een vleugje magie van Bavo Devocht
*/
class MijnGraaf : protected Graaf<GERICHT> {
	public:
		//bouw een graaft op uit een bestand waarvan de bestandsnaam wordt meegegeven
		MijnGraaf(const std::string & );
		
		//topologisch rangschikken door postorder nummering
		std::vector<string> rangschik_topologisch1();
		//topologisch rangschikken door ingraden
		std::vector<string> rangschik_topologisch2(); 
		
		std::vector<string> compileer_volgorde(const string & );
	protected:
		void schrijf_tijden(std::map<string,double> & tijden); //hulpmethode voor tijdens het coderen
		
		void lees_tijden(std::map<string,double> &, const string &);
		
//zijn virtual in bovenliggende klassen (template method: hook) 
		void postbehandel_knoop(int) ;
		void prebehandel_knoop(int) ;
		
		//controleert of de graaf een lus bevat m.b.v. diepte eerst zoeken
		bool bevat_lus();
		
		//voeg een bestand toe en geeft zijn index terug, geeft alleen index terug als het al bestaat
		int voeg_bestand_toe(const string & s);
		
		std::map<string,int> knoopnummers; // naam -> knoopindex
		std::vector<string> bestandsnamen;  // knoopindex -> naam
		
		std::vector<string> postorder_nummering; //volgorde waarin de bestande gecompileerd moeten worden van links naar rechts
		std::vector<int> ingraden; //geeft voor elke knoop aan hoeveel 'pijlen' er toe komen, dat wil zeggen hoeveel bestanden er van dit bestand afhankelijk zijn
};

MijnGraaf::MijnGraaf(const string & s){
	ifstream ifs(s);
	stringstream ss;
	string afhankelijk_bestand,bestand,lijn,andere_bestanden;
	int index_afhankelijk_bestand,index_bestand;
	while(getline(ifs,lijn)){
		int index = lijn.find(":");
		if(index!=-1){
			afhankelijk_bestand = lijn.substr(0,index-1);
			int index_afhankelijk_bestand = voeg_bestand_toe(afhankelijk_bestand);
			andere_bestanden = lijn.substr(index+2);
			ss.clear();
			ss<<andere_bestanden;
			while(ss>>bestand){
				index_bestand = voeg_bestand_toe(bestand);
				ingraden[index_afhankelijk_bestand]++;
				//voeg_verbinding_toe(index_bestand,index_afhankelijk_bestand);
				knopen[index_bestand][index_afhankelijk_bestand] = 0; //voegt een verbinding toe van het bestand dat afhankelijk is naar het bestand waarvan het afhankelijk is, verbindingsnummer is niet belanrijk (=0)
			}
		}	
	}
}

int MijnGraaf::voeg_bestand_toe(const string & s){
	std::map<string,int>::iterator it = knoopnummers.find(s);
	if(it!=knoopnummers.end()){ //betand bestaat al
		return knoopnummers[s];
	}
	else{
		Knoop k;
		knoopnummers[s] = knopen.size();
		knopen.push_back(k);
		bestandsnamen.push_back(s);
		// ingraden klaarzetten voor later gebruik
		ingraden.push_back(0);
		return knopen.size()-1;	
	}
}

// Let op de postorder volgorde moet omgedraaid worden!!!
void MijnGraaf::postbehandel_knoop(int i) {
	postorder_nummering.push_back(bestandsnamen[i]);
}

void MijnGraaf::prebehandel_knoop(int i) {
	
}

std::vector<string> MijnGraaf::rangschik_topologisch1(){
	postorder_nummering.clear();
	diepte_eerst_zoeken();
	std::reverse(postorder_nummering.begin(),postorder_nummering.end()); //dit is nodig want ons pijlen wijzen in de 'omgekeerde' volgorde
	return postorder_nummering;
}

std::vector<string> MijnGraaf::rangschik_topologisch2(){
	std::vector<string> rangschikking;
	//waarom niet de vector overlopen en steeds een knoop met ingraad 0 zoeken? is niet efficiënt zie cursus pagina 141
	
	//zet alle knoopindexen van knopen met ingraad 0 in een wachtrij (kan ook met stapel), dat zijn bestanden waar niemand afhankelijk van is
	std::queue<int> knoopindexen; 
	for(int i=0;i < knopen.size();i++){
		if(ingraden[i]==0){
			knoopindexen.push(i);
		}
	}
	while(!knoopindexen.empty()){
		int knoop_index = knoopindexen.front();
		knoopindexen.pop();
		//ingraden van de buren verminderen met één en in de queue zetten als in de ingraad hierdoor 0 wordt
		for(std::map<int,int>::iterator it = knopen[knoop_index].begin(); it!=knopen[knoop_index].end();it++){
			ingraden[it->first]--; //na uitvoeren van deze methode is de vector ingraden niet meer geldig .. probleem??
			if(ingraden[it->first]==0){
					knoopindexen.push(it->first);
			}
			it++;
		}
		rangschikking.push_back(bestandsnamen[knoop_index]);
	}
	return rangschikking;
}

//geeft de bestanden die gehercompileerd moeten worden in volgorde, van links naar rechts (leeg indien er niet gecompileerd moet worden)
//een bestand moet gehercompileerd worden als het geen timestamp heeft, of ouder is dan een bestand dat er afhankelijk van is
std::vector<string> MijnGraaf::compileer_volgorde(const string & bestand){
	std::vector<string> compileer_volgorde;
	// gaat elk bestand op tijden gaan mappen
	std::map<string,double> tijden;
	std::vector<string> bestanden = rangschik_topologisch1(); //kan ook met rangschik_topologisch2()
	for(int i=0;i<bestanden.size();i++){
		tijden[bestanden[i]] = INFINITY;
	}
	lees_tijden(tijden,bestand);
	//schrijf_tijden(tijden);
	int index = knopen.size()-1;
	bool gevonden = false;
	//opverloop de volgorde van rechts naar links, zodra een bestand gevonden jonger is dan zijn voorloper (kleinere timestamp), die dus voor hem gemaakt moet zijn dan
	//moeten alle bestanden ervoor in volgorde hermaakt worden (afhankelijkheden zijn impliciet meer dan transitief)
	while(index>0 && !gevonden){
		if(tijden[bestanden[index-1]]>tijden[bestanden[index]]){
			gevonden = true;
		}
		index--;
	}
	if(gevonden==true){
		for(int i=0;i<=index;i++) {
			compileer_volgorde.push_back(bestanden[i]);	
		}	
	}
	return compileer_volgorde;
}

void MijnGraaf::lees_tijden(std::map<string,double> & tijden,const string & bestand){
	char line[BUFSIZ];
	float h;
	float min;
	float tijd;
	FILE * pFile;
  	pFile = fopen ("timestamps.txt","r");
  	while(fscanf(pFile,"%s" ,&line) != EOF){
  		fscanf(pFile,"%f:%f" ,&h,&min);
 		tijd = h*60+min;
		std::string naam(line);
		//!!
		tijden[naam]=tijd
		//!!
	}
}

void MijnGraaf::schrijf_tijden(std::map<string,double> & tijden){
	std::map<string,double>::iterator it = tijden.begin();
	while(it!=tijden.end()){
		std::cout<<it->first<<" "<<it->second<<"\n";
		it++;
	}
}











