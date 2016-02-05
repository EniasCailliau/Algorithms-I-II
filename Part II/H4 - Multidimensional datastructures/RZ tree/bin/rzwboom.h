#include <cstdlib>
#include <iostream>
using std::ostream;
using std::max;
#include <queue>
#include <memory>

using namespace std;

// OUDE CODE:
//template<class T, class D>
//const int Rzwboom<T, D>::rood = 0;
//template<class T, class D>
//const int Rzwboom<T, D>::zwart = 1;
//template<class T, class D>
//const int Rzwboom<T, D>::dubbelzwart = 2;
enum Color {RED, BLACK, DOUBLEBLACK}; 


template<class T, class D>
class Rzwboom;

template<class T, class D>
class Rzwknoop;

template<class T, class D>
class Nullknoop;

template<class T, class D>
class Nullboom;




template<class T, class D>
using Rzwknoopptr=std::unique_ptr<Rzwknoop<T,D> >;

template<class T, class D>
class Rzwboom  : public Rzwknoopptr<T,D>{
	using Rzwknoopptr<T,D>::Rzwknoopptr;	
    friend class Rzwknoop<T, D> ;

public:
	Rzwboom(): Rzwboom<T,D>(NullknoopImp){
	}
	static Rzwknoop<T, D>* NullknoopImp;
    Color kleur;
    bool einde(){
    	return this->get()==NullknoopImp;
	}
    //bottom-up toevoegen, geen duplicaten toegestaan.
    //geeft false als de sleutel al in de boom zat.
    bool voegtoe(const T&, const D&);

    //volgende functie geeft false als de sleutel niet kan verwijderd
    //worden omdat hij niet in de boom zit.
    bool verwijder(const T&);

    D* zoekdata(const T&);
    int diepte();

    // << schrijft uit in level order.
    friend ostream& operator<<(ostream& os, Rzwboom<T, D>& b) {
        b.schrijf(os);
        return os;
    }

    //-1 is ongeldige boom; zwartediepte kan dus ook gebruikt worden
    // om boom te controleren.
    // Zwarte diepte: Het aantal ZWARTE knopen vanuit de knoop tot aan het blad, de originele knoop niet meegerekend.
    // Deze moet voor iedere knoop gelijk zijn.
    int zwartediepte();

    //geeft de voorganger als de linkerboom niet leeg is
    Rzwboom<T, D>* ondervoorganger(Rzwboom<T, D>*& boom);

    //
    bool ouderOK();

	private:
		void schrijf_inorder(ostream & os) const;
	    void schrijf(ostream&);
	    int geefkleur() {
	        if (this->get() != nullptr)
	            return this->get()->kleur;
	        else
	            return BLACK;
  	  }
    //Dit hoort op het eerste gezicht bij de klasse Rzwknoop.
    //Maar dit kan niet omdat kn een nulpointer mag zijn
    void schrijf(ostream& os, Rzwknoop<T, D>* kn);

    //alleen roteer oproepen als de operatie kan!
    void roteer(bool naarlinks);

    //maakzwart maakt de knoop in plaats->k zwart, en laat plaats wijzen naar
    //volgende boom die een probleem kan opleveren bij bottom-up toevoegen.
    void maakzwart(Rzwboom<T, D>*& plaats);

    //zoekknoop: postconditie: plaats wijst naar knoop met gezochte sleutel,
    //                           of naar lege boom die naar die knoop zou wijzen als hij bestond
    //                         ouder heeft waarde die in het ouderveld van de knoop staat/zou moeten staan
    void zoekknoop(const T&, Rzwboom<T, D>*& plaats,Rzwboom<T, D>*& ouder);

    // Geeft de voorganger van deze knoop (eronder.)
    Rzwboom<T, D>* ondervoorganger(Rzwknoop<T, D>* knoop);
};




//////////////
//	Knoop 	//
//////////////

template<class T, class D>
class Rzwknoop {	
    friend class Rzwboom<T, D>;
public:
	static Rzwboom<T, D>* NullboomImp;
    T sl;
    D data;
    Color kleur;
    Rzwboom<T, D>* ouder; //wijst naar de boom die naar de ouderknoop wijst
    Rzwboom<T, D>* links;
	Rzwboom<T, D>* rechts;
    Rzwknoop<T, D>() {
    }
    ;
    Rzwknoop<T, D>(const T& _sl, const D& _data)
            : ouder(0), sl(_sl), data(_data), kleur(RED) {
            	links = NullboomImp;
            	rechts = NullboomImp;
    }
};

template<class T, class D>
class Nullknoop: public Rzwknoop<T, D> {
public:
    Nullknoop() {
        Rzwknoop<T, D>::kleur = BLACK;
        Rzwknoop<T, D>::ouder = 0;
    }
};

template<class T, class D>
class Nullboom: public Rzwboom<T, D> {
public:
    Nullboom<T,D>(Rzwknoopptr<T,D> && boom): Rzwboom<T,D>(std::move(boom)){
			Rzwboom<T, D>::kleur = BLACK;		
		}

        
    
};

template<class T, class D>
Rzwknoop<T, D>* Rzwboom<T, D>::NullknoopImp = new Nullknoop<T, D>();

template<class T,class D>
Rzwboom<T, D>* Rzwknoop<T, D>::NullboomImp = new Nullboom<T, D>(std::move(Rzwknoopptr<T,D>(Rzwboom<T,D>::NullknoopImp)));




//////////////////
//	BOOM IMPL.	//
//////////////////

template <class T,class D>
void Rzwboom<T,D>::roteer(bool links){	
    Rzwboom<T,D> op;
//    Rzwboom<T, D> neer = std::move(*this);

    if(links){ 
    	op = std::move(*(this->get()->rechts));
    	*(this->get()->rechts) = std::move(*(op->links));
    	if(*((*this)->rechts) != nullptr)
    		(*this)->rechts->get()->ouder = this;    		
    	*(op->links) = move(*this);
    	
    	*this = move(op);
    	(*this)->ouder = (*this)->links->get()->ouder;
    	(*this)->links->get()->ouder = this;
	}
	else{
		op = std::move(*(this->get()->links));
    	*(this->get()->links) = move(*(op->rechts));
    	if(*((*this)->links) != nullptr)
    		(*this)->links->get()->ouder = this;    		
    	*(op->rechts) = move(*this);
    	
    	*this = move(op);
    	(*this)->ouder = (*this)->rechts->get()->ouder;
    	(*this)->rechts->get()->ouder = this;
	}	
}




//template<class T, class D>
//void Rzwboom<T, D>::roteer(bool naarlinks) {
////    Rzwknoop<T, D>* op;
////    Rzwknoop<T, D>* neer = this->get();
//    if (naarlinks) {
//        op = k->rechts.k;
//        if (neer->links.k != NIL)
//            neer->links.k->ouder = &(op->links);
//        neer->rechts.k = op->links.k;
//        if (op->links.k != NIL) {
//            Rzwknoop<T, D>* kind = op->links.k;
//            kind->ouder = &(op->links);
//            if (kind->links.k != NIL)
//                kind->links.k->ouder = &(neer->rechts);
//            if (kind->rechts.k != NIL)
//                kind->rechts.k->ouder = &(neer->rechts);
//        }
//        if (op->rechts.k != NIL)
//            op->rechts.k->ouder = this;
//        op->links.k = neer;
//    }
//    else {
//        op = k->links.k;
//        if (neer->rechts.k != NIL)
//            neer->rechts.k->ouder = &(op->rechts);
//        neer->links.k = op->rechts.k;
//        if (op->links.k != NIL)
//            op->links.k->ouder = this;
//        if (op->rechts.k != NIL)
//            op->rechts.k->ouder = &(op->rechts);
//        if (op->rechts.k != NIL) {
//            Rzwknoop<T, D>* kind = op->rechts.k;
//            kind->ouder = &(op->rechts);
//            if (kind->links.k != NIL)
//                kind->links.k->ouder = &(neer->links);
//            if (kind->rechts.k != NIL)
//                kind->rechts.k->ouder = &(neer->links);
//        }
//        op->rechts.k = neer;
//    }
//    k = op;
//    op->ouder = neer->ouder;
//    neer->ouder = this;
//}

// Zoek in de 'plaats'-boom naar de sleutel 'sl'.
// Als de sleutel gevonden is, zal:
//  - plaats-boom pointer naar de boom met wortel de gezochte sleutel
//  - ouder-boom pointen naar de ouder van plaats.
template<class T, class D>
void Rzwboom<T, D>::zoekknoop(const T& sl, Rzwboom<T, D>*& plaats, Rzwboom<T, D>*& ouder) {
    plaats = this;
    ouder = 0;
    while (!plaats->einde() && plaats->get()->sl != sl) {
        ouder = plaats;
        cout<<"hier"<<endl;
        if (sl < plaats->get()->sl)
            plaats = plaats->get()->links;
        else{
        plaats = plaats->get()->rechts;
		cout<<"hiero"<<endl;
        	
		}
    }
    cout<<"hiero"<<endl;

}

template<class T, class D>
D* Rzwboom<T, D>::zoekdata(const T& sl) {
    Rzwboom<T, D>* plaats;
    Rzwboom<T, D>* ouder; //dummy, eigenlijk overbodig bij zoekdata
    zoekknoop(sl, plaats, ouder);
    if (!plaats->einde())
        return 0;
    else
        return &(plaats->get()->data);
}

template<class T, class D>
int Rzwboom<T, D>::diepte() {
    if (einde())
        return 0;
    else
        return max(this->get()->links->diepte(), this->get()->rechts->diepte()) + 1;
}

template<class T, class D>
int Rzwboom<T, D>::zwartediepte() {
    if (einde())
        return 1;
    else if (geefkleur() == RED
            && (this->get()->links->geefkleur() == RED || this->get()->rechts->geefkleur() == RED))
        return -1;
    else {
        int linkszwartediepte = this->get()->links->zwartediepte();
        int rechtszwartediepte = this->get()->rechts->zwartediepte();
        if (linkszwartediepte != rechtszwartediepte || linkszwartediepte == -1)
            return -1;
        else
            return linkszwartediepte + geefkleur();
    }
}

template<class T, class D>
bool Rzwboom<T, D>::ouderOK() {
    if (einde())
        return true;
    else
        return (((this->get()->ouder == 0) || (this == this->get()->ouder->k->links)
                || (this == &(this->get()->ouder->get()->rechts))) && this->get()->links->ouderOK()
                && this->get()->rechts->ouderOK());
}

template<class T, class D>
void Rzwboom<T, D>::maakzwart(Rzwboom<T, D>*& plaats) {
    Rzwboom<T, D>* kind = plaats;
    Rzwboom<T, D>* ouder = kind->get()->ouder;
    Rzwboom<T, D>* grootouder = ouder->get()->ouder;

    // Simpele geval. De grootouder is zwart, de ouder en zijn broer rood.
    // Maak de grootouder rood, ouder en broer zwart. (zwart zakt 1 niveau).
    if (grootouder->get()->links->geefkleur() == RED
            && grootouder->get()->rechts->geefkleur() == RED) {
        grootouder->get()->kleur = RED;
        grootouder->get()->links->get()->kleur = BLACK;
        grootouder->get()->rechts->get()->kleur = BLACK;
    }
    else {
        // De broer is zwart.

        // 'ouderlinks' is true als de ouder van 'plaats' links hangt.
        bool ouderlinks = (ouder == grootouder->get()->links);
        // 'kindlinks' is true als het kind links hangt.
        bool kindlinks = (kind == ouder->get()->links);

        // Als het kind en de ouder niet op 1 lijn liggen,  (3e geval)
        // zorgen we ervoor dat deze op 1 lijn komen.
        if (kindlinks != ouderlinks) { //geval 1b
            if (ouderlinks)
                grootouder->get()->links->roteer(true);
            else
                grootouder->get()->rechts->roteer(false);
        };

        // Grootouder, ouder en kind liggen op 1 lijn. (2e geval)
        // Roteer de ouder en grootouder.
        grootouder->get()->kleur = RED;
        ouder->get()->kleur = BLACK;
        grootouder->roteer(!ouderlinks);
    }
    plaats = grootouder;
}

//bottom up
template<class T, class D>
bool Rzwboom<T, D>::voegtoe(const T& sl, const D& data) {
    Rzwboom<T, D>* plaats;
    Rzwboom<T, D>* ouder;

    // Kijk of er een knoop bestaat met deze sleutel.
    // We voegen namelijk geen dubbels toe.

    zoekknoop(sl, plaats, ouder);
    bool nietgevonden = plaats->einde();
    if (nietgevonden) {
        // Knoop toevoegen. (standaard is deze rood)
        cout<<"nieuwe knoop toevoegen"<<endl;
        *plaats = std::move(Rzwboom<T,D>(new Rzwknoop<T, D>(sl, data)));
        plaats->get()->ouder = ouder;

        // De knoop is toegevoegd met standaard kleur rood.
        // Nu gaan we omhoog in de boom en kijken of alles klopt (dus niet 2x rood achter mekaar)
        // noot: ouder wijst nooit naar een ledige boom.
        bool dubbelrood = (ouder != 0 && ouder->get()->kleur == RED);
        while (dubbelrood) {
            // Deze (en de ouder) is rood.
            // Corrigeer deze situatie.
            maakzwart(plaats);

            // Haal volgende ouder op.
            assert(!plaats->einde());
            ouder = plaats->get()->ouder;
            dubbelrood = (plaats->get()->kleur == RED && ouder != 0 && ouder->get()->kleur == RED);
        }
        cout<<"hier geraakt"<<endl;
        this->get()->kleur = BLACK; //eventueel wortel zwart maken.
    }
    return nietgevonden;
}

template<class T, class D>
void Rzwboom<T, D>::schrijf(ostream& os) {
    if (einde()) {
        std::queue<Rzwknoop<T, D>*, std::deque<Rzwknoop<T, D>*> > q;
        q.push(this->get());
        while (!q.empty()) {
            Rzwknoop<T, D>* nu = q.front();
            schrijf(os, nu);
            os << " links: ";
            schrijf(os, nu->links->get());
            os << " rechts: ";
            schrijf(os, nu->rechts->get());
            os << " ouder: ";
            if (nu->ouder == 0)
                schrijf(os, NullknoopImp);
            else
                schrijf(os, nu->ouder->get());
            os << std::endl;
            if (!nu->links->einde())
                q.push(nu->links->get());
            if (!nu->rechts->einde()){
            	cout<<"ik ga rechts ook uitschrijven"<<endl;
            	 q.push(nu->rechts->get());

			}
            q.pop();
        }
    }
    else {
        schrijf(os, this->get());
    }
}

template<class T, class D>
void Rzwboom<T, D>::schrijf(ostream& os, Rzwknoop<T, D>* kn) {
    if (kn != NullknoopImp)
        os << (kn->kleur == RED ? "rood " : "zwart") << "(" << kn->sl << "," << kn->data
                << ")";
    else
        os << "---";
}

template<class T, class D>
Rzwboom<T, D>* Rzwboom<T, D>::ondervoorganger(Rzwknoop<T, D>* knoop) {
    // Zolang mogelijk naar links gaan.
    Rzwboom<T, D>* onder = knoop->links;
    while (!onder.einde() && !onder->get()->rechts.einde())
        onder = onder->get()->rechts;
    return onder;
}

template<class T, class D>
bool Rzwboom<T, D>::verwijder(const T& sl) {
//    // We zoeken de knoop die bij deze sleutel hoort
//    Rzwboom<T, D>* plaats;
//    Rzwboom<T, D>* ouder;
//    zoekknoop(sl, plaats, ouder);
//
//    bool gevonden = plaats->k != NIL;
//    if (gevonden) {
//        // We zoeken de ondervoorganger van deze knoop.
//        // Als er 1 is dan 'wisselen' we deze en deleten we de knoop van de ONDERVOORGANGER.
//        // We zitten dan onderaan.
//        // Is er geen ondervoorganger, dan zitten we al helemaal onderaan en kunnen we deze dus verwijderen.
//        Rzwboom<T, D>* fys_boom = plaats;
//        Rzwboom<T, D>* ondervoorganger = ouder->ondervoorganger(plaats->k);
//        if (ondervoorganger->k != NIL) {
//            // Plaats de ondervoorganger op de huidige.
//            plaats->k->sl = ondervoorganger->k->sl;
//            plaats->k->data = ondervoorganger->k->data;
//            fys_boom = ondervoorganger;
//        }
//
//        // fys_boom->k is de fysisch te verwijderen boom.
//        // Als die rood is, kunnen we die zonder meer verwijderen (kan geen kinderen meer hebben)
//        if (fys_boom->k->rzw == rood) {
//            // TODO Delete poi
//            delete fys_boom;
//        }
//        else {
//            // De knoop is zwart.
//            // 2 deelgevallen
//            //	- 1 (links) rood kind
//            //	- geen kinderen
//
//            // Deelgeval 1: een links rood kind.
//            if (fys_boom->k->links.k != NIL && fys_boom->k->links.k->rzw == rood) {
//                // Schuif het kind omhoog.
//                fys_boom->k->sl = fys_boom->k->links.k->sl;
//                fys_boom->k->data = fys_boom->k->links.k->data;
//
//                // Verwijder het kind.
//                delete fys_boom->k->links.k;
//            }
//            // Deelgeval 2: de fysieke knoop is zwart zonder kinderen.
//            else {
//                // Eerst maken we de fys_boom->k een nulknoop die dubbelzwart is.
//                fys_boom->k = NIL;
//                fys_boom->k->rzw = dubbelzwart;
//
//                // Zolang de knoop dubbelzwart is, en een ouder heeft,
//                // proberen we de situatie te herstellen.
//                Rzwknoop<T, D>* c = fys_boom->k;
//                while (c->rzw == dubbelzwart && c->ouder != 0) {
//
//                    // Selecteer de correcte broer knoop, aangezien daar veel van afhangt.
//                    Rzwboom<T, D> broer_boom = c->ouder->k->links;
//                    bool is_links = (c == c->ouder->k->links.k);
//                    if (is_links) {
//                        Rzwboom<T, D> broer_boom = c->ouder->k->rechts;
//                    }
//                    Rzwknoop<T, D>* broer_knoop = broer_boom.k;
//
//
//                    // Als de broer zwart is, onderscheiden we 3 gevallen.
//                    if (broer_knoop->rzw == zwart) {
//
//                        // Geval 1a: De broer zijn beide kinderen zijn zwart.
//                        if (broer_knoop->links.k != NIL && broer_knoop->rechts.k != NIL) {
//                            c->rzw = zwart;
//                            broer_knoop->rzw = rood;
//                            // De ouder wordt dubbelzwart als hij al zwart was.
//                            // In dat geval hebben we het probleem hogerop geschoven en lossen we het straks op.
//                            if (c->ouder->k->rzw == zwart) {
//                                c->ouder->k->rzw = dubbelzwart;
//                                c = c->ouder->k;
//                            }
//                            else {
//                                c->ouder->k->rzw = zwart;
//                            }
//                        }
//
//
//                        // Geval 1b: De broer heeft 1 rood rechter kind. (als c links hangt)
//                        else if (broer_knoop->rechts.k != NIL
//                                && broer_knoop->rechts.k->rzw == rood) {
//                            // Roteer de ouder naar links
//                            c->ouder->roteer(true);
//                            c->rzw = zwart; // Dubbelzwart wordt enkel zwart.
//                            broer_knoop->rzw = c->ouder->k->rzw; // Broer krijgt willekeurige kleur v/d ouder
//                            broer_knoop->rechts.k->rzw = zwart; // Rode rechterkind wordt zwart
//                            c->ouder->k->rzw = zwart; // De ouder wordt zwart.
//                        }
//
//                        else if (broer_knoop->rechts.k->rzw == zwart
//                                && broer_knoop->links.k->rzw == rood) {
//                            // Roteer de broer naar rechts.
//                            broer_boom.roteer(false);
//                            broer_knoop->links.k->rzw = zwart;
//                            broer_knoop->rzw = rood;
//                            // De dubbele zwarte knoop is hiermee nog niet opgelost,
//                            // Maar dit zal in de volgende iteratie zich herleiden tot geval 2a
//                        }
//                    }
//                    else {
//                        // De broer is rood.
//                        // Roteer de ouder naar links.
//                        c->ouder->roteer(true);
//                        c->ouder->k->rzw = rood;
//                        broer_knoop->rzw = zwart;
//                    }
//                }
//            }
//
//            // Ofwel is het opgelost ofwel is c de wortel en dubbelzwart.
//            // Als het de wortel is, kunnen we deze 1 zwarte kleur laten vallen
//            if (c->rzw == dubbelzwart) {
//                c->rzw = zwart;
//            }
//        }
//    }
//
//}
//
return false;
}

template<class T, class D>
void Rzwboom<T,D>::schrijf_inorder(ostream & os) const{
	if(*this){
		this->get()->left.schrijf_inorder(os);
		cout<< this->get()->inhoud<<endl;
		this->get()->right.schrijf_inorder(os);
	}
}



