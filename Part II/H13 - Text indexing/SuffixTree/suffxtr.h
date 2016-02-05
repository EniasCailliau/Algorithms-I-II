#ifndef __SUFFIXTREE_H
#define __SUFFIXTREE_H
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <deque>
#include "bitpatroon.h"
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;
using std::map;
using std::deque;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;


class Sknoop;
class InwendigeKnoop;
class Blad;
class Presuffix;
class Sboom;

/**********************************************************************

   Class: Kind
   
    Klassieke trie heeft een tabel; ternaire boom een map.
    Het doel van Kind is ook om het eigenaardige gedrag van een map op te vangen dat maakt
    dat het opvragen van van een mapelement de map kan veranderen. Zorgt ook voor een
    nette destructor en verbergt de manier om de meerwegstrie te implementeren.
    
***************************************************************************/

class Kind: public map<char, Sknoop*>{
public:
    ~Kind();
    void set(char a, Sknoop* p);
    //geeft nulpointer terug als a geen beeld heeft in de map
    Sknoop* get(char a) const;
    
};

/**********************************************************************

   Class: Presuffix
   
   De klasse Presuffix heeft alleen belang bij het opstellen van de Sboom.
   Beschrijving: Verwijst naar een expliciete knoop, anders gezegd naar
   het prefix van een suffix. De  expliciet-pointer wijst naar een expliciete knoop, de string
   die het zoekpad vanaf de wortel geeft wordt aangegeven door zijn lengte lengteTotExpliciet
   en beginpositie plaatsInHooiberg.

   De parameternaam i is voorbehouden voor het doorgeven van de huidige verwerkingsplaats in de hooiberg

   Het Presuffix is canoniek als het suffix (beginnend op plaatsInHooiberg
   en eindigend VOOR i) ofwel eindigt in *expliciet (hooiberg[i] duidt dan dus het kind
   van expliciet aan waarlangs we verder gaan; i= plaatsInHooiberg + lengteTotExpliciet
   en explicietEinde() = true )
   ofwel in een impliciete knoop die als expliciete ouder *expliciet heeft.
   
***************************************************************************/
class Presuffix{
    friend class Sboom;
public:
    Presuffix(InwendigeKnoop* _expliciet=0, int _plaats=0);
    void init(InwendigeKnoop* _expliciet=0, int _plaats=0);
    void verzet();
    //noot explicietEinde werkt alleen als het Presuffix canonisch van vorm is
    bool explicietEinde(int i) const{
        return lengteTotExpliciet ==i-plaatsInHooiberg;
    };
    //volgende functie ontploft (soms) als knoopwijzer niet canonisch is
    bool heeftKind(int i, const char* hooiberg) const;
    //als het stuk van plaatsInHooiberg tot i gekend is,
    //ga zo ver mogelijk naar beneden in de boom
    void maakCanoniek(int i, const char* hooiberg);
    bool isCanoniek(int i, const char* hooiberg) const;
    int geefPlaatsInHooiberg(){return plaatsInHooiberg;};
protected:
//lidvelden
    InwendigeKnoop* expliciet;//laatste expliciete knoop, voor zover bekend, in pad van suffix.
    int plaatsInHooiberg;
    int lengteTotExpliciet;//lengte van string die tot expliciete knoop leidt. 0 als Expliciet naar wortel leidt
};

/**********************************************************************

   einde class Presuffix
   
***************************************************************************/



/**********************************************************************

   Class: Sknoop
   
   beschrijving: Vermits een Sboom gecomprimeerd is moet er een plaats zijn waar
   de gecomprimeerde takdata worden opgeslagen. Dit gebeurt door de indices startc en
   eindc die respectievelijk het eerste karakter en de plaats na het laatste karakter in
   de hooiberg aangeven. Als er geen impliciete knopen zijn dan is
   eindc==startc;
   Als we in de ouder van een Sknoop k zitten dan is ouder->kind[k.startc] de pointer naar k.
   Deelklasse: een InwendigeKnoop heeft kinderen; een Blad niet.
   
   
***************************************************************************/
class Sknoop{
friend class Sboom;
friend class Presuffix;
public:
    Sknoop();
    virtual ~Sknoop(){};
    virtual bool isBlad()=0;
    //sluitmap: beeldt afsluitkarakters af op een bitpatroon met een 1 op de juiste plaats..
    //verz: de verzameling strings waar de huidige string in zit, wordt
    // op nul gezet door oproeper.
    //uit: de tot nu toe langste string
    //int diepte: de lengte van het prefix tot aan knoop die deze functie oproept. (eigenlijk overbodig, volgt uit startp en eindp)
    //enen: Bitpatroon met enen dat de complete gezochte verzameling aanduidt
    virtual void vulEindkarakterpatroon(const map<char,Bitpatroon> &sluitmap ,Bitpatroon&  verz,
                    string& uit,int diepte,const Bitpatroon& enen,
                    const char* hooiberg)=0;
    void geefLGDrec(const map<char,Bitpatroon> &sluitmap ,Bitpatroon&  verz,
                    string& uit,int diepte,const Bitpatroon& enen,
                    const char* hooiberg);
    virtual void print(ostream & os)const{}
	
protected:
    int startp; //p staat voor prefix: startp en eindp duiden begin en einde aan in hooiberg van prefix
    int eindp;  //nuttig voor toepassingen zoals lgd
    int startc;
    int eindc;


};

class Blad: public Sknoop{
friend class Sboom;
public:
    virtual bool isBlad();
    virtual void vulEindkarakterpatroon(const map<char,Bitpatroon> &sluitmap ,Bitpatroon&  verz,
                    string& uit,int diepte,const Bitpatroon& enen,
                    const char* hooiberg);
    virtual void print(ostream& os)const{
			os<<startc<<endl;
	}
};



class InwendigeKnoop: public Sknoop{
friend class Sboom;
friend class Presuffix;
public:
    InwendigeKnoop();
    virtual bool isBlad();
    virtual void vulEindkarakterpatroon(const map<char,Bitpatroon> &sluitmap ,Bitpatroon&  verz,
                    string& uit,int diepte,const Bitpatroon& enen,
                    const char* hooiberg);
    virtual void print(ostream& os){
    	for (map<char, Sknoop*>::iterator it=kind.begin(); it != kind.end(); it++){
    		cout<<"ik print kinderen "<<it->first<<endl;
	        it->second->print(os);
	    }
	}
protected:
//datavelden
    Kind kind;
    InwendigeKnoop* cdr;
};


/**********************************************************************

   Class: Sboom
   
   beschrijving: Suffixboom. Wordt opgebouwd vanuit een cstring die uiteraard
   geen nulkarakter bevat.
   Noteer: de wortelknoop representeert de lege string, die uiteraard een
   geldige suffix is van een willekeurige string en dus steeds aanwezig is.
   
***************************************************************************/
class Sboom{
public:
    Sboom(const char* c=0, char afsluiter=-1);                  ;
    ~Sboom();
    void voegtoe (const char* c, char afsluiter=-1);
	void geefLGD(const vector<char>& sluit, string& uit) const;
	void print(ostream& os)const;
protected:
//datavelden
    char* hooiberg;//let op: niet afgesloten met nulkarakter
    int lengte;//lengte van de hooiberg.
    InwendigeKnoop* wortel;
};


/**********************************************************************


    Implementatie


*********************************************************************/


/**********************************************************************
     Klasse Presuffix
*********************************************************************/
void Presuffix::verzet(){
    plaatsInHooiberg++;
    if (lengteTotExpliciet > 0)//we zitten niet in wortel
        lengteTotExpliciet--;
    expliciet=expliciet->cdr;
};

bool Presuffix::heeftKind(int i, const char* hooiberg) const{
    bool gevonden;
    if (explicietEinde(i))
        gevonden=expliciet->kind.get(hooiberg[i]) != 0;
    else{
        Sknoop* kind=expliciet->kind.get(hooiberg[plaatsInHooiberg+lengteTotExpliciet]);
        int verder= i - lengteTotExpliciet - plaatsInHooiberg;//hoeveel impliciete knopen verder?
        char c=hooiberg[kind->startc+verder];
        gevonden=(hooiberg[i]==c);
    }
    return gevonden;
}



Presuffix::Presuffix(InwendigeKnoop* _expliciet,int _plaats):expliciet(_expliciet),plaatsInHooiberg(_plaats),
                                    lengteTotExpliciet(0){
                                    }
void Presuffix::init(InwendigeKnoop* _expliciet,int _plaats){
    expliciet=_expliciet;
    plaatsInHooiberg=_plaats;
    lengteTotExpliciet=0;
}

bool Presuffix::isCanoniek(int i, const char* hooiberg) const{
    int overschot=i-lengteTotExpliciet-plaatsInHooiberg;//gaat voorbij expliciete knoop; 0 --> einde in expliciete knoop
    if (overschot > 0){
        Sknoop* kind=expliciet->kind.get(hooiberg[i-overschot]);
        return(kind->isBlad() || kind->eindc - kind->startc >= overschot);
    }
    else
        return true;
};

void Presuffix::maakCanoniek(int i, const char* hooiberg){
    int overschot=i-lengteTotExpliciet-plaatsInHooiberg;//gaat voorbij expliciete knoop; 0 --> einde in expliciete knoop
    if (overschot > 0){
        Sknoop* kind=expliciet->kind.get(hooiberg[i-overschot]);
        while (overschot > 0 && !kind->isBlad() && kind->eindc - kind->startc < overschot){
            expliciet=(InwendigeKnoop*) kind;
            lengteTotExpliciet=lengteTotExpliciet + (kind->eindc -kind->startc) +1 ;
            overschot=i-lengteTotExpliciet-plaatsInHooiberg;//gaat voorbij expliciete knoop; 0 --> einde in expliciete knoop
            kind=expliciet->kind.get(hooiberg[i-overschot]);
        };
    }
}

/**********************************************************************
     Klasse Sknoop
*********************************************************************/


Sknoop::Sknoop():startc(eindc){}

void Sknoop::geefLGDrec(const map<char,Bitpatroon> &sluitmap ,Bitpatroon&  verz,
                string& uit,int diepte,const Bitpatroon& enen,
                const char* hooiberg){
//    vulEindkarakterpatroon(sluitmap ,verz,uit,diepte,enen,hooiberg);
//    int nudiepte=eindp-startp;
//    if (verz==enen && nudiepte > uit.size()){
//        //nogal wat lijmcode tussen string en cstring;
//        char* uitc=new char[nudiepte+1];
//        strncpy(uitc,hooiberg+startp,nudiepte);
//        uitc[nudiepte]=0;
//        uit=uitc;
//        delete []uitc;
//    }
};
bool Blad::isBlad(){return true;}
bool InwendigeKnoop::isBlad(){return false;}

void Blad::vulEindkarakterpatroon(const map<char,Bitpatroon> &sluitmap ,Bitpatroon&  verz,string& uit,int diepte,const Bitpatroon& enen,const char* hooiberg){
    map<char,Bitpatroon>::const_iterator it= sluitmap.find(hooiberg[eindc-1]);
    if (it!=sluitmap.end())
        verz=it->second;
    else
        verz=0;
}
InwendigeKnoop::InwendigeKnoop():Sknoop(),cdr(0){}


void InwendigeKnoop::vulEindkarakterpatroon(const map<char ,Bitpatroon> &sluitmap ,Bitpatroon&  verz,string& uit,int diepte,const Bitpatroon& enen,const char* hooiberg){
    map<char,Sknoop*>::const_iterator it= kind.begin();
    int nudiepte=diepte+eindc-startc+1;
    while (it !=kind.end() ){
        Bitpatroon kindverz;
        it->second->geefLGDrec(sluitmap, kindverz, uit, nudiepte, enen, hooiberg);
        verz|=kindverz;
        it++;
    }
}

/**********************************************************************
     Klasse Kind
*********************************************************************/

Kind::~Kind(){
    for (map<char, Sknoop*>::iterator it=this->begin(); it != this->end(); it++){
        delete it->second;
    }
}

void Kind::set(char a,Sknoop* p){
    map<char, Sknoop*>::operator[](a)=p;
}

Sknoop* Kind::get(char a) const{
    map<char, Sknoop*>::const_iterator plaats=find(a);
    if (plaats==map<char,Sknoop*>::end())
        return 0;
    else
        return plaats->second;
}


/**********************************************************************
     Klasse Sboom
*********************************************************************/

Sboom::Sboom(const char* c, char afsluiter):wortel(new InwendigeKnoop){
    wortel->cdr=wortel;
    wortel->startp=wortel->eindp=0;
    wortel->startc=wortel->eindc=666;
    hooiberg=0;
    if (c !=0)
        voegtoe(c, afsluiter);
}

Sboom::~Sboom(){
    delete []hooiberg;
    delete wortel;
}

void Sboom::geefLGD(const vector<char>& sluit,string& uit) const{
    assert (sluit.size()<=patroonlengte);
    Bitpatroon verz;//verzameling waar suffix inzit
    map<char,Bitpatroon> sluitmap;
    Bitpatroon enen;
    for (int i=0; i<sluit.size(); i++ ){
        sluitmap[sluit[i]]=Bitpatroon::eenbit(i);
        enen|=Bitpatroon::eenbit(i);
    }
    wortel->geefLGDrec(sluitmap,verz,uit,0,enen, hooiberg);
}


void Sboom::voegtoe (const char* c,char afsluiter){
    int oudelengte;
    if (hooiberg==0){
        oudelengte=0;
        lengte=strlen(c)+1;
        hooiberg=new char[lengte];
        strcpy(hooiberg,c);
        hooiberg[lengte-1]=afsluiter;
    }
    else{
        oudelengte=lengte;
        lengte+=strlen(c)+1;
        char* nieuw=new char[lengte];
        strncpy(nieuw,hooiberg,oudelengte);
        delete []hooiberg;
        hooiberg=nieuw;
        strcpy(hooiberg+oudelengte,c);
        hooiberg[lengte-1]=afsluiter;
    }
    Presuffix actief(wortel,oudelengte);
    for (int i=oudelengte; i<lengte ; i++ ){
        InwendigeKnoop* cdrUpdate=0;//wijst eventueel naar knoop met nog in te vullen cdrpointer
//eyecandy voor grote teksten
        if (i%1000==1)
            cerr<<"*";
        actief.maakCanoniek(i,hooiberg);
        Presuffix laatstecdr=actief;//verwijst naar de laatste knoop op het pad van het actief suffix
                                    //dat zeker een ingevulde cdr heeft.
        char nuchar=hooiberg[i];
        while (actief.geefPlaatsInHooiberg()<=i && !actief.heeftKind(i, hooiberg)){
            laatstecdr=actief;
            if (!actief.explicietEinde(i)){
            //maak een expliciete knoop om blad aan te hangen
                Sknoop* volgend=actief.expliciet->kind.get(hooiberg[actief.plaatsInHooiberg+actief.lengteTotExpliciet]);
                int overschot=i-actief.plaatsInHooiberg-actief.lengteTotExpliciet;
                InwendigeKnoop* nieuw=new InwendigeKnoop;
                nieuw->startc=volgend->startc;
                nieuw->eindc=nieuw->startc+overschot-1;
                nieuw->startp=actief.plaatsInHooiberg;
                nieuw->eindp=i;
                
                if (cdrUpdate != 0){
                    cdrUpdate->cdr=nieuw;
                }
                cdrUpdate=nieuw;

                volgend->startc=volgend->startc+overschot;
                char oudchar=hooiberg[volgend->startc];
                nieuw->kind.set(oudchar,volgend);
                actief.expliciet->kind.set(hooiberg[i-overschot],nieuw);
                actief.expliciet=nieuw;
                actief.lengteTotExpliciet=i-actief.plaatsInHooiberg;
            }
            else{//actief eindigt in expliciete knoop
                if (cdrUpdate!=0){
                    cdrUpdate->cdr=actief.expliciet;
                    cdrUpdate=0;
                }
            };
            //toevoegen blad
            Blad* blad=new Blad;
            blad->startp=actief.plaatsInHooiberg;
            blad->eindp=lengte;
            blad->startc=i;
            blad->eindc=lengte;
            actief.expliciet->kind.set(hooiberg[i],blad);
            //verzet actief punt
            laatstecdr.verzet();
            laatstecdr.maakCanoniek(i,hooiberg);
            actief=laatstecdr;//oppervlakkige kopie
        };
        if (cdrUpdate!=0){
                cdrUpdate->cdr=actief.expliciet;
                cdrUpdate=0;
        }
    };
}

/*
Eigen
*/

void Sboom::print(ostream& os)const{
	wortel->print(os);
}





#endif

