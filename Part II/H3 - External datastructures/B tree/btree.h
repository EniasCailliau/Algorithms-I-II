#ifndef __BTREE
#define __BTREE

#include "schijf.h"
#include <iostream>
#include <stack>
#include <cmath>
#include <vector>
#include <queue>          
using std::endl;
using std::vector;
using std::cerr;
using std::ostream;

using namespace std;

/*
TODO: verwijderen
*/


//Dit bestand bevat code en hoofdingen van
template<class T, class D, unsigned int m>
class Btree;
template<class T, class D, unsigned int m>
class Bknoop;
//betekenis m: orde van de B-tree (maximaal m kinderen en m-1 sleutels)

template<class T, class D, unsigned int m>
class Bknoop {
	// zo kan een Btree rechtstreeks aan zijn kinderen
    friend class Btree<T, D, m> ;
public:
	Bknoop():k(0),isblad(true){
		sleutels.resize(m);
		data.resize(m);
		index.resize(m+1);
	}
	//copy assignment
    const Bknoop<T, D, m>& operator=(const Bknoop<T, D, m>& b) {
		cout<<"in copy sl's'"<<sleutels.size()<<endl;
        k = b.k;
        isblad = b.isblad;
        for (unsigned int i = 0; i < k; i++) {
            sleutels[i] = b.sleutels[i];
            data[i] = b.data[i];
        }
        if (!isblad) {
            for (unsigned int i = 0; i <= k; i++) {
                index[i] = b.index[i];
            }
        }
        return *this;
    }
    Bknoop(const Bknoop<T,D,m>& b):k(b.k),isblad(b.isblad){
    	sleutels.resize(m);
		data.resize(m);
		index.resize(m+1);
    	for (unsigned int i = 0; i < k; i++) {
            sleutels[i] = b.sleutels[i];
            data[i] = b.data[i];
        }
        if (!isblad) {
            for (unsigned int i = 0; i <= k; i++) {
                index[i] = b.index[i];
            }
        }
    	
	}
    //Eeen B-tree reserveert altijd m plaatsen voor sleutels en m plaatsen voor data.
    //TODO: wijzigen noormaal m-1 en m kinderen (want graad is m)
    vector<T> sleutels;
    vector<D> data;
    vector<blokindex> index;
    // huidig aantal sleutels; aantal kinderen = k+1. 
    // reden niet het aantal kinderen opslaan: niet elke knoop heeft kinderen (zoals een blad)
    unsigned int k;
    // in cursus: b
    bool isblad;

    // Voeg een waarde tussen in de array van sleutels/data
    // Gebruik dit enkel als er voldoende plaats is!
    int insert(T key, D val, blokindex bi);
};

template<class T, class D, unsigned int m>
class Btree {
	// Dit zorgt voor een kortere notatie
    typedef Bknoop<T, D, m> Knoop;
public:
    Btree(Schijf<Knoop>& s)
            : schijf(s) {
        // wortel is hierbinnen al aangemaakt a.d.h.v. default constructor (eig'n konden ook in default constructor geplaatst worden)
        wortel.k = 0;
        wortel.isblad = true;
        wortelindex = schijf.schrijf(wortel);
    }
	// toevoegen
    void put(T key, D val);
    // zoeken
    D get(T key);
    
    // hier werd gekozen om in-leven te overlopen.
	void schrijf(ostream& os){
		Knoop knoop;
  		std::queue<blokindex> q; 
  		q.push(wortelindex);
		while(!q.empty()){
			blokindex index = q.front();
			q.pop();
			schijf.lees(knoop, index);

			for(int i=0; i<knoop.k; i++){
			os << knoop.sleutels[i]<<"; ";
			}
			cout<<"-------"<<endl;
			if(!knoop.isblad){
				// indien knoop geen blad is dan heeft hij kinderen.
				for(int i=0; i<=knoop.k; i++){
					q.push(knoop.index[i]);
				}	
			}
		}
	
//		os<<endl;
//		cout<<"indexen schrijven "<<endl;
//		for(int i=0; i<=knoop.k; i++){
////			schijf.lees(knoop, knoop.index[i]);
////			for(int i=0; i<knoop.k; i++){
////				os << knoop.sleutels[i]<<", ";
////			}
//			os << knoop.index[i]<<";";
//		}
	}
private:
    Schijf<Knoop>& schijf;
    Knoop wortel;
    blokindex wortelindex;

    // Zoekt een waarde in de sleutels van knoop die bij key past.
    // Returned de waarde.
    // path het pad waarlangs we lopen om tot aan knoop te geraken.
    D search(T key, stack<blokindex>& path);

};

template<class T, class D, unsigned int m>
void Btree<T, D, m>::put(T key, D val) {
    // De juiste knoop zoeken.
    stack<blokindex> path;
    search(key, path);

    T key_to_add = key;
    D val_to_add = val;
    blokindex bi_to_add = 0;
    bool toegevoegd = false;
    blokindex  bi;
    while (!toegevoegd && !path.empty()) {
        // Haal de knoop van de stack.
        bi = path.top();
        cout<<"blokindex toevoegen"<<bi<< endl;
        path.pop();
        Knoop knoop;
        schijf.lees(knoop, bi);

        // Toevoegen.
        if (knoop.k < m) {
        	cout<<"nog voldoende plaats, ik voeg hem ertussen"<<endl;
            // Als er nog genoeg plaats is, voegen we hem er gewoon tussen.
            knoop.insert(key_to_add, val_to_add, bi_to_add);
            schijf.herschrijf(knoop, bi);
            toegevoegd = true;
            // Hiermee is alles opgelost!
        }

        // Bummer, de knoop zit vol.
        // We splitsen deze knoop.
        // - Nieuwe broerknoop maken met de helft van de waardes.
        // - De value toevoegen (kan ook in broer knoop zijn!)
        // - de middenste waarde omhoog schuiven.
        else {

            // Broerknoop voor de helft vullen, zie default constructor
            Knoop broer;
            unsigned int midden = m / 2;
            T middensleutel = knoop.sleutels[midden];
            D middenwaarde = knoop.data[midden];
            
            cout<<"gekozen midden = "<<midden<<endl;
            // let op met grootte's, indien knoop.k - midden dan klopt de formule niet
            broer.k = knoop.k - midden-1;
            for (unsigned int i = midden+1; i < knoop.k; i++) {
                broer.sleutels[i - midden-1] = knoop.sleutels[i];
                broer.data[i - midden-1] = knoop.data[i];
            }
             if (!knoop.isblad) {
             	cout<<"knoop is geen blad"<<endl;
              	for (unsigned int i = midden+1; i <= knoop.k; i++) {
                    broer.index[i - midden-1] = knoop.index[i];
                }
			}

            // De linkerknoop bevat nu maar de helft van zijn data/kinderen meer.
            knoop.k = midden;

            // We voegen de nieuwe waarde toe.
            // Dit kan nu perfect, want beide knopen bevatten maar de helft van hun sleutels meer.
            if (key_to_add < knoop.sleutels[midden]) {
                knoop.insert(key_to_add, val_to_add, bi_to_add);
            }
            else {
                broer.insert(key_to_add, val_to_add, bi_to_add);
            }

            // We schuiven nu de grootste waarde van het linker kind omhoog (in-order correctheid)
            key_to_add = middensleutel;
            val_to_add = middenwaarde;

            // Knopen wegschrijven
            schijf.herschrijf(knoop, bi);
            bi_to_add = schijf.schrijf(broer);
        }
    }

    if (!toegevoegd && path.empty()) {
    	cout<<"--nieuwe wortel aanmaken: sl="<<key_to_add<<" data="<<val_to_add<<endl;
        // Nieuwe wortel met 1 sleutel,
        Knoop wortel;
 		wortel.k = 1;
 		// opgelet!!! nieuwe knoop is een wortel, maar zeker geen blad aangezien hij kinderen krijgt.
        wortel.isblad = false;
        wortel.sleutels[0]= key_to_add;
        wortel.data[0]= val_to_add;
        cout<<"--- links:"<<bi<<" rechts:"<<bi_to_add<<endl;
//        bi is de laatste van de stack en deze is zeker nog niet veranderd
        wortel.index[0]=bi;
//        Altijd nieuwe knoop rechts toevoegen
        wortel.index[1]=bi_to_add;
        // wortelindex wordt gewijzigd.
        wortelindex = schijf.schrijf(wortel);
        cout<<"--- nieuwe wortelindex: "<<wortelindex<<endl;
    }
}

// hier returnen we de waarde maar eigenlijk moeten we een pair<blokindex, int> teruggeven.
// Deze duid aan waar de gezochte sleutel (en dus zijn data) zich bevind binnen dat blok.
template<class T, class D, unsigned int m>
D Btree<T, D, m>::get(T key) {
    // De blokindex boeit hier weinig...
    stack<blokindex> path;
    return search(key, path);
}

template<class T, class D, unsigned int m>
D Btree<T, D, m>::search(T key, stack<blokindex>& path) {
    Knoop knoop;
    schijf.lees(knoop, wortelindex);
    path.push(wortelindex);
    bool gevonden = false;

    while (!gevonden) {
        unsigned int i = 0;
        // Lineair zoeken
        while (i < knoop.k && knoop.sleutels[i] < key) {
            i++;
        }

        if (i < knoop.k) {
        	// We zijn niet buiten de grenzen gelopen
            if (key == knoop.sleutels[i]) {
            	// We hebben de correcte sleutel gevonden.
                return knoop.data[i];
            }
            else if (knoop.isblad) {
                // we hebben niks gevonden
                return 0;
            }
            else {
                // Nog niet tot het einde geitereerd en de sleutel is ook nog niet gevonden.
                // Dit wil zeggen dat we naar het kind moeten op pos i-1 !!! (want we zijn
                // eentje verder gegaan.)

                // Knoop van de schijf lezen.
                blokindex bindex = knoop.index[i - 1];
                path.push(bindex);
                schijf.lees(knoop, bindex);

                // Heel het proces opnieuw starten.
            }
        }
        else {
            return 0;
        }
    }
}

template<class T, class D, unsigned int m>
int Bknoop<T, D, m>::insert(T key, D val, blokindex bi) {
    // Zoek waar de sl moet komen
    unsigned int j = 0;
    while (j < k && sleutels[j] < key) {
        j++;
    }

    // Schuif alles erachter 1 plaats op.
    for (unsigned int v = k; v > j; v--) {
        sleutels[v] = sleutels[v - 1];
        data[v] = data[v - 1];
        if (!isblad) {
            index[v + 1] = index[v];
        }
    }

    // Plaats de sl daar.
    sleutels[j] = key;
    data[j] = val;
    if (!isblad && bi != 0) {
        index[j + 1] = bi;
    }
    k++;
    return j;
}

#endif
