/*
 * bplustree.h
 *
 *  Created on: Oct 12, 2012
 *      Author: ahluntang
 */

#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include "schijf.h"
#include <iostream>
#include <vector>
using std::vector;
using std::endl;
using std::cerr;
using std::cout;
using std::ostream;
#include <stack>
using std::stack;
typedef unsigned int uint;
//Dit bestand bevat code en hoofdingen van
template<class T, class D, uint mtussen, uint mblad>
class Bplustree;
template<class T, class D, uint mtussen, uint mblad>
class Bplusknoop;
template<class T, class D, uint mtussen, uint mblad>
class Bplustussenknoop;
template<class T, class D, uint mtussen, uint mblad>
class Bplusblad;

const bool VERBOSE = false;
const bool VERYVERBOSE = false;

//betekenis m: zie cursus. Bplustrees maken onderscheid tussen
//mtussen (voor tussenknopen) en mblad.

template<class T, class D, uint mtussen, uint mblad>
class Bplustussenknoop {
	friend class Bplustree<T, D, mtussen, mblad> ;
public:
	Bplustussenknoop():k(0){
		sleutel.resize(mtussen);
		index.resize(mtussen+1);
	}
	const Bplustussenknoop<T, D, mtussen, mblad>& operator=(const Bplustussenknoop<T, D, mtussen, mblad>& b) {
		k = b.k;
		sleutel.resize(mtussen);
		index.resize(mtussen+1);
		for (uint i = 0; i < k; i++) {
			sleutel[i] = b.sleutel[i];
			index[i] = b.index[i];
		}
		index[k] = b.index[k];
		return *this;
	}
	vector<T> sleutel;
	vector<blokindex> index;
	uint k;
};

template<class T, class D, uint mtussen, uint mblad>
class Bplusblad {
	friend class Bplustree<T, D, mtussen, mblad> ;
public:
	Bplusblad():k(0){
		sleutel.resize(mblad);
		data.resize(mblad);
	}
	// deze zou ook een voeg toe functie kunnen krijgen met een sleutel en data.
	const Bplusblad<T, D, mtussen, mblad>& operator=(const Bplusblad<T, D, mtussen, mblad>& b) {
		k = b.k;
		sleutel.resize(mblad);
		data.resize(mblad);
		for (uint i = 0; i < k; i++) {
			sleutel[i] = b.sleutel[i];
			data[i] = b.data[i];
		}
		volgendBlad = b.volgendBlad;
		return *this;
	}
	vector<T> sleutel;
	vector<D> data;
	// Sequence set: gelinkte lijst van Bplusbladeren
	blokindex volgendBlad;
	uint k;
};

template<class T, class D, uint mtussen, uint mblad>
class Bplusknoop {
	friend class Bplustree<T, D, mtussen, mblad> ;
public:
	const Bplusknoop<T, D, mtussen, mblad>& operator=(const Bplusknoop<T, D, mtussen, mblad>& b) {
		isblad = b.isblad;
		if (isblad){ blad = b.blad; }
		else{ tussen = b.tussen; }
		return *this;
	}
	bool isblad;
	// deze klasse bevat steeds een van de twee 
	Bplustussenknoop<T, D, mtussen, mblad> tussen;
	Bplusblad<T, D, mtussen, mblad> blad;
};

template<class T, class D, uint mtussen, uint mblad>
class Bplustree {
	typedef Bplusknoop<T, D, mtussen, mblad> Knoop;
public:
	Bplustree(Schijf<Knoop>& s):schijf(s) {
		wortel.isblad = true;
		wortel.blad.k = 0;
		wortel.blad.volgendBlad = 0;
		wortelindex = schijf.schrijf(wortel);
	}

	D zoek(const T & sleutel) const;
	void voegtoe(const T & sleutel, const D & data);
	void overloop_gelinktelijst() const;

protected:
	Schijf<Knoop>& schijf;
	Knoop wortel;
	blokindex wortelindex;
	D zoek(const T & sleutel, bool & gevonden) const;
	void zoek_blad(const T & sleutel, Knoop & gezochte_knoop,
			stack<blokindex> & blokindices) const;
	void voeg_toe_in_blad(const T & sleutel, const D & data, Knoop & blad_knoop,
			blokindex blad_index);
	void splits_blad(Knoop & blad_knoop, blokindex& blad_index,
			stack<blokindex> & blokindices, const T & sleutel);
	void voegtoe_aan_ouder(const T & kind_sleutel, Knoop & kindknoop,
			blokindex & kind_index, stack<blokindex> & blokindices);
	void splits_tussenknoop(const T & sleutel, Knoop & tussenknoop,
			blokindex & tussen_index, stack<blokindex> & blokindices);
	void maak_nieuwe_wortel(stack<blokindex> & blokindice, blokindex & links, blokindex& rechts, T& sleutel);
	void zoek_kleinste_blad(Knoop & gezochtblad) const;
};
/* ========================================================================= *\
							IMPLEMENTATIE
 \* ========================================================================= */

/** zoekt de sleutel in de bplustree
 * @param sleutel T (IN) dat gezocht moet worden
 * @return data D dat bij sleutel hoort, 0 als sleutel niet gevonden is
 */
template<class T, class D, uint mtussen, uint mblad>
D Bplustree<T, D, mtussen, mblad>::zoek(const T & sleutel) const {
	bool gevonden = false;
	D data = zoek(sleutel, gevonden);
	if (gevonden) {
		return data;
	} else {
		return 0;
	}
}

/** zoek sleutel in bplustree
 * @param sleutel T (IN) dat gezocht moet worden
 * @param gevonden bool (OUT) dat aangeeft of data wel gevonden werd of niet
 * @return data D dat bij sleutel hoort
 */
template<class T, class D, uint mtussen, uint mblad>
D Bplustree<T, D, mtussen, mblad>::zoek(const T & sleutel, bool & gevonden) const {

	// stack bijhouden om om gevolgde weg te bewaren
	stack<blokindex> blokindices;

	// knoop bewaren in gezochte_knoop
	Knoop gezochte_knoop;

	// blad zoeken
	zoek_blad(sleutel, gezochte_knoop, blokindices);

	// sleutels in blad overlopen en vergelijken met gezochte sleutel
	uint i = 0;
	while (i < gezochte_knoop.blad.k && gezochte_knoop.blad.sleutel[i] < sleutel) {
		i++;
	}

	if (i < gezochte_knoop.blad.k) {
		gevonden = (sleutel == gezochte_knoop.blad.sleutel[i]) ? true : false;
		if (VERYVERBOSE && gevonden){
			std::cout << "gevonden: " << gezochte_knoop.blad.sleutel[i] << " "
								<< gezochte_knoop.blad.data[i] << endl;
		}
		return gezochte_knoop.blad.data[i]; // 
	} else {
		return 0; // blad gevonden, maar sleutel zit er nog niet in, wijst dus naar de plaats waar sleutel in moet zitten
	}
}

/** zoek blad waar sleutel zich in moet bevinden
 * @param sleutel T (IN) dat gezocht moet worden
 * @param gezochte_knoop Knoop (OUT) waar blad in moet gezet worden
 * @param blokindices stack<blokindex> (OUT) waar de afgelegde weg in wordt bewaard
 */
template<class T, class D, uint mtussen, uint mblad>
void Bplustree<T, D, mtussen, mblad>::zoek_blad(const T & sleutel, Knoop & gezochte_knoop, stack<blokindex> & blokindices) const {
	// knopen overlopen tot je een blad vindt
	schijf.lees(gezochte_knoop, wortelindex);
	// wortelindex bewaren in een stack.
	blokindices.push(wortelindex);
	blokindex huidigeindex = wortelindex;
	// wortel wordt bewaard in het geheugen, niet nodig om in te lezen
	//schijf.lees(gezochte_knoop, wortelindex);
	while (!gezochte_knoop.isblad) {
		// geen blad, dus naar tussenliggende/inwendige knoop kijken
		// niet verder dan k gaan, sleuteltabel overlopen tot je
		// plaats vindt waar sleutel kan
		uint i = 0;
		while (i < gezochte_knoop.tussen.k	&& gezochte_knoop.tussen.sleutel[i] <= sleutel) {
			i++;
		}
//		cout<<"ik onderzoek nu een knoop met index: "<<huidigeindex<<endl;
		blokindex blad_index;
		if (i == 0) {
			// als i kleiner is dan k, dan ligt de gezochte sleutel bij
			// knoop op index i.
			blad_index = gezochte_knoop.tussen.index[i];
		} else {
			// als i niet kleiner is dan k, dan moet je in de laatst bestaande
			// index gaan, dan kan je daar de nieuwe sleutel toevoegen.
//			cout<<"ik heb het blad gevonden op index"<<i<<" dat verwijst naar "<<gezochte_knoop.tussen.index[i]<<endl;
			blad_index = gezochte_knoop.tussen.index[i];
		}
		// knoop lezen vanop schijf.
		huidigeindex = blad_index;
		schijf.lees(gezochte_knoop, blad_index);
		// blad index bewaren in een stack.
		blokindices.push(blad_index);
	}
//	cout<<"de knoop waar ik ben is een blad"<<endl;
}

/** voegt sleutel met data toe in btree
 * @param sleutel T (IN) sleutel dat toegevoegd wordt
 * @param data D (IN) data dat hoort bij sleutel
 */
template<class T, class D, uint mtussen, uint mblad>
void Bplustree<T, D, mtussen, mblad>::voegtoe(const T & sleutel, const D & data) {
	Knoop blad_knoop;
	stack<blokindex> blokindices;
	// blad zoeken waar de sleutel aan toegevoegd kan worden
	zoek_blad(sleutel, blad_knoop, blokindices);
	blokindex blad_index = blokindices.top(); // na zoeken zal blokindices minstens wortelindex bevatten
	//huidig blad_index verwijderen van stack:
	blokindices.pop();
//	cout<<"blokindeces: "<<blad_index<<endl;
	// in blad moet sleutel met data toegevoegd worden.
	// als blad geen vrije plaats meer heeft, eerst splitsen.
//	cout<<"is dit een blad?"<<blad_knoop.isblad<<endl;
	if (blad_knoop.isblad && blad_knoop.blad.k + 1 > mblad) {
//		cout<<"ik ga toevoegen aan een vol blad!!"<<endl;
		// geen vrije plaats, blad splitsen: stack nodig met weg naar blad.
		// stack bevat volledige weg startend vanaf bladindex.
		// in blad_knoop het blad zetten waarin toegevoegd kan worden
		// afhankelijk van waarde van middelste sleutel in blad, kan dit
		// het huidig blad zijn, of het nieuwe blad.
		splits_blad(blad_knoop, blad_index, blokindices, sleutel);
	}
	// als blad vrije plaats heeft, sleutel en data toevoegen (insertion sort)
	voeg_toe_in_blad(sleutel, data, blad_knoop, blad_index);
	// terug wortel inlezen, wortel is steeds ingelezen. 
	schijf.lees(wortel, wortelindex);
}

/** splitst opgegeven blad en kopieert helft van sleutels met data naar nieuw blad
 *  plaatst nieuw blad in ouderknoop
 * @param blad_knoop Knoop (OUT) blad dat gesplitst moet worden, op einde wordt hierin
 * 	de juiste blad geselecteerd om nieuwe sleutel in toe te voegen
 * @param blad_index blokindex (OUT) blokindex op schijf van blad dat gesplitst moet worden
 *  ook hier wordt de juiste index teruggegeven.
 * @param blokindices stack<blokindex> (OUT) wordt gebruikt om nieuw blad in ouder te zetten,
 *  uitparameter: als ouder gesplitst moet worden kan weg aangepast worden.
 * @param sleutel T (IN) sleutel waarmee je kan controleren in welk blad de sleutel moet komen
 */
template<class T, class D, uint mtussen, uint mblad>
void Bplustree<T, D, mtussen, mblad>::splits_blad(Knoop & blad_knoop, blokindex& blad_index, stack<blokindex> & blokindices, const T & sleutel) {
//	if (VERBOSE)
//		std::cout << "splits blad" << endl;
	// splitsen blad:
	// nieuw blad aanmaken
	// helft data, vanaf (inclusief) m verplaatsen naar nieuw blad.
	// nieuw blad op schijf opslaan om nieuw_blad blad_index te weten.
	// gelinkte lijst herstellen
	// sleutel en wijzer van m naar ouder kopieren
	// kijken in welk blad de sleutel moet staan
	// die dan toewijzen aan blad_knoop, alsook zijn index aan blad_index
	blokindex bestaande_index = blad_index;
	Knoop nieuw_blad;
	nieuw_blad.isblad = true;
	nieuw_blad.blad.k = 0;
	// helft kopieren
	uint k = blad_knoop.blad.k;
	uint midden = mblad/2;
	T midden_sleutel = blad_knoop.blad.sleutel[midden];
//	cout<<"ik kies het midden_index: "<<midden<<endl;
	for (uint i = midden; i < k; i++) {
		// nieuw blad opvullen vanaf links, index 0 = i - mblad/2
		// kopieren van oud blad vanaf midden = i
		nieuw_blad.blad.sleutel[i - midden] = blad_knoop.blad.sleutel[i];
		nieuw_blad.blad.data[i - midden] = blad_knoop.blad.data[i];
		// eentje weg 
		blad_knoop.blad.k--;
		nieuw_blad.blad.k++;
	}
	// gelinkte lijst (laatste niveau, sequence set) fixen
	nieuw_blad.blad.volgendBlad = blad_knoop.blad.volgendBlad;
	blokindex nieuw_index = schijf.schrijf(nieuw_blad); // nieuw_blad wegschrijven
//	cout<<"ik heb een nieuw blad weggeschreven op index: "<<nieuw_index;
	blad_knoop.blad.volgendBlad = nieuw_index;
//	cout<<"Eerste van gelinke lijst wijst nu naar"<<blad_knoop.blad.volgendBlad<<endl;
	schijf.herschrijf(blad_knoop, bestaande_index); // veranderingen aan bestaand blad doorvoeren
	// als blad wortel was, nieuwe knoop maken,
	// wegschrijven en toevoegen aan stack als ouder.
	if (blad_index == wortelindex) {
		T sleutel = midden_sleutel;
		blokindex links = bestaande_index;
//		cout<<"nieuwe index ="<<nieuw_index<<endl;;
//		cout<<"oude index ="<<bestaande_index<<endl;;
		blokindex rechts = nieuw_index;
//		cout<<"ik wil een nieuwe wortel met sleutel: "<<sleutel;
		maak_nieuwe_wortel(blokindices, links, rechts, sleutel);	
	}else{
//		cout<<"HIER BEN IK"<<endl;
		voegtoe_aan_ouder(midden_sleutel, nieuw_blad, nieuw_index, blokindices);		
	}
	// nieuw blad aan ouder toevoegen
	// ouder te vinden in blokindices
//	if (VERYVERBOSE) std::cout << "nieuw_blad.blad.k=" << nieuw_blad.blad.k << endl;
	// bepalen als nieuwe sleutel in buur moet gestoken worden of niet.
	// is het zelfde als midden_sleutel
	if (sleutel > nieuw_blad.blad.sleutel[0]) {
		// indexen veranderen waar we toevoegen
		blad_knoop = nieuw_blad;
		blad_index = nieuw_index;
	}
}

/** maakt nieuwe wortel
 * plaatst vorige wortel als eerste element in nieuwe wortel.
 * @param blokindices stack<blokindex> (OUT) om wortel toe te voegen aan nieuwe weg
 
 * OK
 */
template<class T, class D, uint mtussen, uint mblad>
void Bplustree<T, D, mtussen, mblad>::maak_nieuwe_wortel(stack<blokindex> & blokindices, blokindex & links, blokindex& rechts, T& sleutel) {
	if (VERBOSE)
		std::cout << "nieuwe wortel" << endl;
	Knoop ouder;
	ouder.isblad = false;
	ouder.tussen.sleutel[0] = sleutel;
	ouder.tussen.index[0] = links;
	ouder.tussen.index[1] = rechts;
	ouder.tussen.k = 1;
	blokindex ouderindex = schijf.schrijf(ouder);
//	cout<<"---nieuwe wortel terug inlezen ter controler"<<endl;
	schijf.lees(ouder,ouderindex);
//	cout<<"wortel met links: "<<ouder.tussen.index[0]<<" rechts: "<<ouder.tussen.index[1]<<"en sleutel"<<ouder.tussen.sleutel[0]<<endl;
	wortel = ouder;
//	cout<<"IK HEB EEN NIEUWE WORTEL MET INDEX: "<<ouderindex;
	wortelindex = ouderindex;
	blokindices.push(ouderindex);
}

/** splitst een tussenknoop, als tussen knoop een wortel was, wordt een nieuwe wortel aangemaakt
 * @param sleutel T (IN) sleutel waarmee gecontroleerd wordt in welke knoop verdergekeken moet worden
 *  voor de data
 * @param tussen_knoop Knoop (OUT) knoop dat gesplitst moet worden, nadien wordt hier de juiste knoop geplaatst
 * @param tussen_index blokindex (OUT) blokindex op schijf van tussenknoop
 * @param blokindices stack<blokindex> (OUT) wordt gebruikt om ouder te vinden.
 */
template<class T, class D, uint mtussen, uint mblad>
void Bplustree<T, D, mtussen, mblad>::splits_tussenknoop(const T & sleutel,	Knoop & tussen_knoop, blokindex & tussen_index,	stack<blokindex> & blokindices) {
//	std::cout << "splits tussenknoop met index: "<<tussen_index << endl;
//	cout<<"splitsen van tussenknooop !!!!!!"<<endl;
	// tussenknoop splitsen:
	// nieuwe tussenknoop aanmaken
	
	Knoop nieuw_tussen;
	nieuw_tussen.isblad = false;
	nieuw_tussen.tussen.k = 0;
	uint k = tussen_knoop.tussen.k;
	// helft kopieren
	uint midden = mtussen/2;
	T midden_sleutel = tussen_knoop.tussen.sleutel[midden];
	for (uint i = midden; i < k; i++) {
		// nieuwe knoop : startend vanaf links = i-(mtussen/2) -1
		// kopieren vanaf midden van oude knoop = i
		nieuw_tussen.tussen.sleutel[i - midden] = tussen_knoop.tussen.sleutel[i];
		nieuw_tussen.tussen.index[i - midden] =	tussen_knoop.tussen.index[i];
		nieuw_tussen.tussen.k++;
	}
	// hier werkt normale k bepaalen met -- niet want dan nog een tveel
	tussen_knoop.tussen.k = midden;
	
	// oude tussenknoop herschrijven
	schijf.herschrijf(tussen_knoop, tussen_index);
	// nieuwe knoop wegschrijven
	blokindex nieuw_index = schijf.schrijf(nieuw_tussen);
	// er gebeurt hier niets met de bladen dus moeten de pointers van de bladeren ook niet gewijzigd worden.
	if (tussen_index == wortelindex) {
//		cout<<"HIER MOET IK ZIJN";
		// tussenknoop was wortel
		// tussen knoop en nieuwe knoop moet aan een nieuwe ouder hangen dat een nieuwe wortel wordt
		if (VERBOSE) std::cout << "tussenknoop was wortel" << endl;
		maak_nieuwe_wortel(blokindices,tussen_index, nieuw_index, midden_sleutel);
	}else{
		// nieuw tussenknoop toevoegen aan ouder
		if (VERBOSE) std::cout << "nieuwe tussenknoop toevoegen aan ouder" << endl;
//		voegtoe_aan_ouder(nieuw_tussen.tussen.sleutel[0], nieuw_tussen, nieuw_index, blokindices);	
	}
	if (sleutel > nieuw_tussen.tussen.sleutel[0]) {
		// kijken in welke knoop het nieuwe kind geplaatst moet worden.
		// bepalen als nieuwe sleutel in buur moet gestoken worden of niet.
		tussen_knoop = nieuw_tussen;
		tussen_index = nieuw_index;
	}
}

/** voeg gegeven knoop toe als kindknoop van de ouder van de buur.
 * @param kind_sleutel T (IN) eerste sleutel van kindknoop
 * @param kindknoop Knoop (OUT) kindknoop dat toegevoegd moet worden aan de ouder
 * @param kindindex blokindex (OUT) blokindex op schijf van kindknoop
 * @param blokindices stack<blokindex> (OUT) afgelegde weg om ouder te vinden.
 */
template<class T, class D, uint mtussen, uint mblad>
void Bplustree<T, D, mtussen, mblad>::voegtoe_aan_ouder(const T & kind_sleutel,	Knoop & kindknoop, blokindex & kind_index,	stack<blokindex> & blokindices) {
	// er is enkel de eigen wortel. normaal niet nodig.
	blokindex ouder_index = wortelindex;
	if (!blokindices.empty()) {
		ouder_index = blokindices.top();
		//huidig index verwijderen van stack:
		blokindices.pop();
	}
	Knoop ouder_knoop;
	schijf.lees(ouder_knoop, ouder_index);
//	cout<<"ik lees hier ouder met grootte: "<<ouder_knoop.tussen.k<<endl;
	// kijken of er genoeg plaats is in ouder
	// indien niet genoeg plaats: splitsen.
	if (ouder_knoop.tussen.k + 1 > mtussen) {
		// geen vrije plaats, tussenknoop splitsen.
		splits_tussenknoop(kind_sleutel, ouder_knoop, ouder_index, blokindices);
	}
	// sleutel en wijzer toevoegen in juiste ouder_knoop
	int i = ouder_knoop.tussen.k;
	while (i > 0 && kind_sleutel < ouder_knoop.tussen.sleutel[i]) {
		ouder_knoop.tussen.sleutel[i] = ouder_knoop.tussen.sleutel[i-1];
		// indexwijzers mee verplaatsen
		ouder_knoop.tussen.index[i+1] = ouder_knoop.tussen.index[i];
		i--;
	}
	// sleutel en wijzer van kind opslaan
	ouder_knoop.tussen.sleutel[i] = kind_sleutel;
	ouder_knoop.tussen.index[i+1] = kind_index;
	ouder_knoop.tussen.k++;
	schijf.herschrijf(ouder_knoop, ouder_index);
}
/** voeg sleutel en data toe in blad
 * @param sleutel T (IN) sleutel dat toegevoegd moet worden
 * @param data D (IN) data dat hoort bij sleutel
 * @param blad_knoop Knoop (OUT) blad waarin sleutel toegevoegd moet worden
 * @param bladindex blokindex (OUT) blokindex op schijf waar blad zich bevindt
 */
template<class T, class D, uint mtussen, uint mblad>
void Bplustree<T, D, mtussen, mblad>::voeg_toe_in_blad(const T & sleutel, const D & data, Knoop & blad_knoop, blokindex blad_index) {
	// toevoegen via insertionsort (achteraan beginnen)
	// op plaats blad_knoop.blad.k-1 staat laatst toegevoegde sleutel.
	uint i = 0;
	while (i < blad_knoop.blad.k && blad_knoop.blad.sleutel[i] < sleutel) {
		i++;
	}
	if (i < blad_knoop.blad.k && sleutel == blad_knoop.blad.sleutel[i]) {
		if (VERYVERBOSE) {
			std::cout << "vervang " << blad_knoop.blad.sleutel[i] << " ("
					<< blad_knoop.blad.data[i] << ") with " << sleutel << " ("
					<< data << ")" << endl;
		}

	} else {
		// i wijst naar de plaats waar het geplaatst moet worden. 
		for(int j = i ; j<blad_knoop.blad.k; j++){
			blad_knoop.blad.sleutel[j + 1] = blad_knoop.blad.sleutel[j];
			blad_knoop.blad.data[j + 1] = blad_knoop.blad.data[j];
		}	
//		cout<<"ik ga een getal plaatsen op: "<<i;
//		while (i > 0 && sleutel < blad_knoop.blad.sleutel[i]) {
//			blad_knoop.blad.sleutel[i + 1] = blad_knoop.blad.sleutel[i];
//			// data mee verplaatsen
//			blad_knoop.blad.data[i + 1] = blad_knoop.blad.data[i];
//			i--;
//		}
		// grootte tabellen is nu 1 groter.
		blad_knoop.blad.k++;
	}
	// nieuwe sleutel en data opslaan
	blad_knoop.blad.sleutel[i] = sleutel;
	blad_knoop.blad.data[i] = data;
//	cout<<"dit is de nieuwe sleuteltabel "<<endl;
//	for(int i=0; i<blad_knoop.blad.k;i++){
//		cout<<blad_knoop.blad.data[i]<<", ";
//	}
	cout<<endl;
	
	schijf.herschrijf(blad_knoop, blad_index);
}

/** overloop gelinkte lijst op onderste niveau van btree
 *	(overloop sequence set)
 */
template<class T, class D, uint mtussen, uint mblad>
void Bplustree<T, D, mtussen, mblad>::overloop_gelinktelijst() const {
	Knoop gezochtblad;
	zoek_kleinste_blad(gezochtblad);
	int aantal = 1;
	bool end = false;
	while (gezochtblad.isblad && !end) {
		uint i = 0;
		while (i < gezochtblad.blad.k) {
//			std::cout << aantal++ << ". " << gezochtblad.blad.sleutel[i] << " ("
//					<< gezochtblad.blad.data[i] << ")" << endl;
			aantal++;
			i++;
		}
		if (gezochtblad.blad.volgendBlad != 0) {
			schijf.lees(gezochtblad, gezochtblad.blad.volgendBlad);
		} else {
//			cout<<"mijn volgend blad is geen blad"<<endl;
			end = true;
		}
	}

}

/** zoekt kleinste blad
 * @param gezochtblad Knoop (OUT) parameter waar blad met kleinste waarde aan toegevoegd zal worden.
 */
template<class T, class D, uint mtussen, uint mblad>
void Bplustree<T, D, mtussen, mblad>::zoek_kleinste_blad(Knoop & gezochtblad) const {
	gezochtblad = wortel;

	while (!gezochtblad.isblad) {
		schijf.lees(gezochtblad, gezochtblad.tussen.index[0]);
		cout<<"ik neem blad met index"<<gezochtblad.tussen.index[0]<<endl;
	}
}

#endif /* BPLUSTREE_H_ */
