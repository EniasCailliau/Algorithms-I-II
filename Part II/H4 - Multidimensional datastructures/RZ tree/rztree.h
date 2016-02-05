#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>

using std::ostream;
using namespace std;



template <class Sleutel,class Data>
class RZknoop;

template <class Sleutel,class Data>
class RZboom : public unique_ptr<RZknoop<Sleutel,Data>>{
public:
	 using unique_ptr<RZknoop<Sleutel,Data>>::unique_ptr; 
	 
     RZboom<Sleutel,Data>(){}  
     ~RZboom<Sleutel,Data>(){}
     
     RZboom<Sleutel,Data>(RZboom<Sleutel,Data>&& b):unique_ptr<RZknoop<Sleutel,Data>>(move(b)){
	 }
	 RZboom<Sleutel,Data>& operator=(RZboom<Sleutel,Data>&& b){
	 	 unique_ptr<RZknoop<Sleutel,Data>>::operator=(move(b));   
	 	 return *this;
	 }
	 
     int diepte() const{
        if (!*this)
            return 0;
        else
            return std::max((*this)->links.diepte(),(*this)->rechts.diepte())+1;
     };
     
     void schrijf(ostream&) const;
     void schrijf(ostream& os,RZknoop<Sleutel,Data>* kn) const{
        if (kn!=0){
        	        os<<"("<<kn->sl<<","<<kn->data<<")";
            os<<"["<< (kn->rood ? "R" : "Z") << "]";
		}
        else
            os<<"(,)";
     }
     void roteer(bool links);
     
     double gemDiepte() const;
     void bepaalDiepte(int diepte, double &nrKnopen, double& totDiepte) const;
};

template <class Sleutel,class Data>
double RZboom<Sleutel,Data>::gemDiepte() const{
	double nrKnopen=1;
	int diepte=0;
	double totDiepte=0;
	this->get()->links.bepaalDiepte(diepte++, nrKnopen, totDiepte);
	this->get()->rechts.bepaalDiepte(diepte++, nrKnopen, totDiepte);
	return totDiepte/nrKnopen;

}

template <class Sleutel,class Data>
void RZboom<Sleutel, Data >:: bepaalDiepte(int diepte, double &nrKnopen, double& totDiepte) const{
	if((*this)!=0){
		nrKnopen++;
		totDiepte+=diepte;
		this->get()->links.bepaalDiepte(diepte++, nrKnopen, totDiepte);
		this->get()->rechts.bepaalDiepte(diepte++, nrKnopen, totDiepte);
	}
}

template <class Sleutel,class Data>
class RZknoop{
    public:
        Sleutel sl;
        Data data;
        RZknoop<Sleutel,Data>* ouder;
        RZboom<Sleutel,Data> links,rechts;
        bool rood; // 1: zwart 0:rood
        RZknoop():ouder(0){}
        RZknoop(const Sleutel& _sl,const Data& _data):ouder(0),sl(_sl),data(_data),rood(true){}
};

template <class Sleutel,class Data>
class RoodZwarteBoom{
public:
     virtual void voegtoe(const Sleutel&,const Data&);
     	 	 
     RZboom<Sleutel,Data>* voegtoe(RZboom<Sleutel,Data>& knoop, const Sleutel& sl,const Data& data);
	 
//volgende functie doet niets als er geen knoop is met het gegeven Sleutel
     virtual void verwijder(const Sleutel&);
//geef pointer naar data horend bij een sleutel
     virtual Data* zoekdata(const Sleutel&);
     int diepte() const{return deRZboom.diepte();};
     double gemDiepte() const{return deRZboom.gemDiepte();};
     friend ostream& operator<<(ostream& os,RoodZwarteBoom<Sleutel,Data>& b){
        b.deRZboom.schrijf(os);
        return os;
    };
//protected:
//zoekplaats: geeft adres van boom waaraan knoop hangt, of zou moeten hangen
//en adres van de ouder.
     virtual void zoekplaats(const Sleutel&,RZboom<Sleutel,Data>*&,RZknoop<Sleutel,Data>*&);
//De binaire boom die de data bevat
     RZboom<Sleutel,Data> deRZboom;
//geeft de voorganger. Veronderstelt dat de linkerboom onder de knoop niet leeg is
     RZboom<Sleutel,Data>* ondervoorganger(RZknoop<Sleutel,Data>*);
     void maakzwart(RZboom<Sleutel,Data>*& waar);
	RZboom<Sleutel,Data>* geefBijhorendeBoom(RZknoop<Sleutel,Data>*& knoop);

     
};

template <class Sleutel,class Data>
void RZboom<Sleutel,Data>::roteer(bool links){	
    RZboom<Sleutel,Data> op;
    RZknoop<Sleutel,Data>* ouder;
	if(links){ 
		cout<<"roteer links"<<endl;
    	op = move((*this)->rechts);
    	(*this)->rechts = move(op->links);
    	if((*this)->rechts != nullptr)
    		(*this)->rechts->ouder = (*this).get();    		
    	op->links = move(*this);
    	ouder = op->links->ouder;
	}
	else{
		cout<<"roteer rechts"<<endl;
		op = move((*this)->links);
    	(*this)->links = move(op->rechts);
    	if((*this)->links != nullptr)
    		(*this)->links->ouder = (*this).get();    		
    	op->rechts = move(*this);
    	ouder = op->rechts->ouder;
	}
	*this = move(op);
	(*this)->ouder = ouder;
	(*this)->links->ouder = (*this).get();
}


template <class Sleutel,class Data>
void RoodZwarteBoom<Sleutel,Data>::zoekplaats(const Sleutel& sl,RZboom<Sleutel,Data>*& plaats, RZknoop<Sleutel,Data>*& ouder){
    plaats=&deRZboom;
    ouder=0;
    while (*plaats!=0 && (*plaats)->sl!=sl){
        ouder=plaats->get();
        if (sl < (*plaats)->sl)
            plaats=&((*plaats)->links);
        else
            plaats=&((*plaats)->rechts);
    }
}
        
template <class Sleutel,class Data>
Data* RoodZwarteBoom<Sleutel,Data>::zoekdata(const Sleutel& sl){
    RZboom<Sleutel,Data>* plaats;
    RZknoop<Sleutel,Data>* ouder;
    zoekplaats(sl,plaats,ouder);
    if (plaats==0)
        return 0;
    else return &((*plaats)->data);
}

template <class Sleutel,class Data>
void RoodZwarteBoom<Sleutel,Data>::voegtoe(const Sleutel& sl,const Data& data){
	RZboom<Sleutel,Data> * waar;
    if(deRZboom==0){  
    	unique_ptr<RZknoop<Sleutel,Data>> nieuw = unique_ptr<RZknoop<Sleutel,Data>>(new RZknoop<Sleutel,Data>(sl,data));
        deRZboom = move(nieuw);  
        deRZboom->ouder=0;
        // nieuwe root toevoegen, geen probleem moet enkel nog zwart worden.
        deRZboom->rood = false;
        waar = &deRZboom;
    }
    else{
    	waar = voegtoe(deRZboom,sl,data);
    	cout<<"pas toegevoegd kind: ";
		waar->schrijf(cout);
	
		bool dubbelrood = (waar->get()->rood && waar->get()->ouder->rood);
		while(dubbelrood){
			cout<<"help ik heb dubbelrood"<<endl;
			maakzwart(waar);
			if(waar->get()->ouder == nullptr) break;
			dubbelrood = (waar->get()->rood &&  waar->get()->ouder->rood);
		}
	}

	// hier kan nog andere code staan om te verwerken
}

template <class Sleutel,class Data>
void RoodZwarteBoom<Sleutel,Data>::maakzwart(RZboom<Sleutel,Data>*& boom){
	RZknoop<Sleutel, Data>* kind = boom->get();
	RZknoop<Sleutel, Data>* ouder = boom->get()->ouder;
	RZknoop<Sleutel, Data>* grootouder = ouder->ouder;
	RZboom<Sleutel,Data>* grootouderboom = geefBijhorendeBoom(grootouder);
	grootouderboom->schrijf(cout);

	if(grootouder->rechts->rood && grootouder->links->rood){
		cout<<"eenvoudig geval!!"<<endl;
		grootouder->rood = true;
		grootouder->rechts->rood = false;
		grootouder->links->rood = false;
	}else{
//		broer is zwart.
// 		Eerst weten of p linker of rechterkind is van g
		bool ouderlinks = (ouder == grootouder->links.get());
//		if(ouderlinks) cout<<"ouder zit links"<<endl;
		bool kindlinks = (kind == ouder->links.get());
//		if(kindlinks) cout<<"kind zit links"<<endl;
		
		if(kindlinks != ouderlinks){
			cout<<"Situatie 2b;";
			if(ouderlinks){
				grootouder->links.roteer(true);
			}else{
				grootouder->rechts.roteer(false);
			}
		}
		cout<<"Situatie 2a"<<endl;
		grootouder->rood = true;
		ouder->rood = false;
		grootouderboom->roteer(!ouderlinks);
	}	
	boom = grootouderboom;
}

template <class Sleutel,class Data>
RZboom<Sleutel,Data>* RoodZwarteBoom<Sleutel,Data>::geefBijhorendeBoom(RZknoop<Sleutel,Data>*& knoop){
	if(knoop->ouder != 0){
		bool links = knoop->ouder->links.get();
		if(links){
			return &(knoop->ouder->links) ;
		}else{
			return &(knoop->ouder->rechts);
		}
	}else{
		// indien het geen ouder heeft dan is het de boom zelf.
		return &(this->deRZboom);
	}
	
}



template <class Sleutel,class Data>
RZboom<Sleutel,Data>* RoodZwarteBoom<Sleutel,Data>::voegtoe(RZboom<Sleutel,Data>& knoop, const Sleutel& sl,const Data& data){
    RZboom<Sleutel,Data> *kind;
    if (sl < knoop->sl)
        kind=&(knoop->links);
    else
        kind=&(knoop->rechts);
    if (*kind == 0){
        (*kind) = move((unique_ptr<RZknoop<Sleutel,Data>>) new RZknoop<Sleutel,Data>(sl,data));
        (*kind)->ouder = knoop.get();
        return kind;
    }
    else
        voegtoe(*kind, sl,data);
}


template <class Sleutel,class Data>
RZboom<Sleutel,Data>* RoodZwarteBoom<Sleutel,Data>::ondervoorganger(RZknoop<Sleutel,Data>* kn){
    RZboom<Sleutel,Data>* onder=&(kn->links);
    while ((*onder) && (*onder)->rechts!=0)
        onder=&((*onder)->rechts);
    return onder;
}


template <class Sleutel,class Data>
void RZboom<Sleutel,Data>::schrijf(ostream& os) const{
    if (*this!=0){
       RZknoop<Sleutel,Data>* loper = this->get();    	
       std::queue<RZknoop<Sleutel,Data>*, std::deque<RZknoop<Sleutel,Data>*> > q;
       q.push(loper);
       while(!q.empty()){
           RZknoop<Sleutel,Data>* nu=q.front();
           schrijf(os,nu);
           os<<" links: ";
           schrijf(os,nu->links.get());
           os<<" rechts: ";
           schrijf(os,nu->rechts.get());
           os<<" ouder: ";
           schrijf(os,nu->ouder);
           os<<std::endl;
           if (nu->links!=0)
               q.push(nu->links.get());
           if (nu->rechts!=0)
               q.push(nu->rechts.get());
           q.pop();
       }
    }
    else{
        os<<" XX ";
    }
}

//template <class Sleutel, class Data>
//class SplayTree: public RoodZwarteBoom<Sleutel, Data>{
//	using RoodZwarteBoom<Sleutel,Data>::RoodZwarteBoom;
//	public :
//		Data* zoekdata (const Sleutel & s);
//		
//};
//
//template <class Sleutel, class Data>
//Data * SplayTree<Sleutel, Data>::zoekdata(const Sleutel & s){
//	/*
//	 1.Vertrek bij de binboom met een een pointer naar de wortel.
//	 2.Als je in een lege boom zit, of in de boom waarvan de wortel de gezochte sleutel heeft, stop.
//	 3.Als de gezochte sleutel kleiner is dan de sleutel in de wortel, roteer naar rechts.
//	 4.Als de gezochte sleutel daarmee naar rechts geroteerd is ga naar de rechter deelboom.
//	 5.Als de gezochte sleutel groter is dan de sleutel in de wortel, roteer naar links.
//	 6.Als de gezochte sleutel daarmee naar links geroteerd is ga naar de linker deelboom.
//	 7.Ga terug naar stap 2.
//	*/
//	//RZboom<Sleutel, Data>* temp = &deRZboom; 
//	RZboom<Sleutel, Data> * huidig = &(RoodZwarteBoom<Sleutel,Data>::deRZboom);
//	cout<<"zoek "<<s<<endl;
//	while(huidig != nullptr && (*huidig).get()->sl != s ){
//		if((*huidig).get()->sl > s){
//			if((*huidig).get()->rechts != nullptr){
//				(*huidig).roteer(false);
//			}
//			if((*huidig).get()->sl < s){
//				huidig = &((*huidig)->rechts);
//			}
//		}
//		
//		if((*huidig).get()->sl < s){
//			if((*huidig).get()->links != nullptr){
//				(*huidig).roteer(true);
//			}
//			if((*huidig).get()->sl > s){
//				huidig = &((*huidig)->links);
//			}
//		}
//		cout<<*this;
//	}
//	if(huidig != nullptr){
//		return nullptr;
//	} else {
//		return &((*huidig)->data);
//	}
//}


template <class Sleutel,class Data>
void RoodZwarteBoom<Sleutel,Data>::verwijder(const Sleutel& sl){
	
	RZboom<Sleutel,Data> * plaats;
	RZknoop<Sleutel,Data> * ouder;
	zoekplaats(sl,plaats,ouder);
	//Binknoop<Sleutel,Data>* weg = plaats->k;
	// onze RZboom wisjt naar iets dat betekent dat de knoop naar wie hij verwijst zeker naar iemand gaat wijzen,
	// anders zou deze knoop niet bestaan
	if((*plaats) != 0 ){ //anders komt de te verwijderen knoop niet voor
		if((*plaats)->links == 0){
			(*plaats) = std::move((*plaats)->rechts);
			if((*plaats)!=0){
				(*plaats)->ouder = ouder;
			}
		}
		else if((*plaats)->rechts == 0){
			(*plaats) = std::move((*plaats)->links);
			if((*plaats)!=0){
				(*plaats)->ouder = ouder;
			}
		}
		else{
			 //vervangen door voorganger
            RZboom<Sleutel,Data>* voorlink=ondervoorganger(plaats->get());
            RZknoop<Sleutel,Data>* voorganger= voorlink->get();
            if (voorlink!=&((*plaats)->links)){
            	RZboom<Sleutel,Data> voorganger2 = std::move(*voorlink);
            	//stap 1: voorganger 'losmaken' maar wel nog bijhouden via voorganger 2, anders verdwijnt de knoop in volgende stap (maak tekening!)
            	(*voorlink) = std::move(voorganger2->links);
            	if((*voorlink)!=0){
            		(*voorlink)->ouder = voorganger->ouder;
				}
            	//stap 2: kinderen van voorganger laten wijzen naar kinderen van te verwijderen knoop
            	voorganger->links = std::move((*plaats)->links);
            	voorganger->links->ouder = voorganger;
            	voorganger->rechts = std::move((*plaats)->rechts);
            	voorganger->rechts->ouder = voorganger;
            	//stap 3: plaat plaats naar voorganger2 wijzen
            	(*plaats) = std::move(voorganger2);
                voorganger->ouder=ouder;
            }
            else{
            	voorganger->rechts = std::move((*plaats)->rechts);
            	voorganger->rechts->ouder = voorganger;
            	voorganger->ouder = ouder;
            	(*plaats) = std::move((*plaats)->links);
			}
            
		}
	}
	// Oorspronkelijke interface:
	// Binboom bevat (gewone) pointer met naam k naar knoop
	/*	
	Binboom<Sleutel,Data>* plaats;
    Binknoop<Sleutel,Data>* ouder;
    zoekplaats(sl,plaats,ouder);
    Binknoop<Sleutel,Data>* weg=plaats->k;
    if (plaats->k != 0){
        if (weg->links.k==0){
            plaats->k=weg->rechts.k;
            if (plaats->k != 0)
                plaats->k->ouder=ouder;
            weg->rechts.k=0;
            delete weg;
        }
        else if (weg->rechts.k==0){
            plaats->k=weg->links.k;
            if (plaats->k != 0)
                plaats->k->ouder=ouder;
            weg->links.k=0;
            delete weg;
        }
        else{
            //vervangen door voorganger
            Binboom<Sleutel,Data>* voorlink=ondervoorganger(weg);
            Binknoop<Sleutel,Data>* voorganger=voorlink->k;
            if (voorlink!=&(weg->links)){
                voorlink->k=voorganger->links.k;
                if (voorganger->links.k !=0)
                    voorganger->links.k->ouder=voorganger->ouder;
                //geen test voor volgende twee: deze bestaan!
                plaats->k=voorganger;
                voorganger->ouder=ouder;
                voorganger->links.k=weg->links.k;
                voorganger->links.k->ouder=voorganger;
                voorganger->rechts.k=weg->rechts.k;
                voorganger->rechts.k->ouder=voorganger;
            }
            else{
                voorganger->rechts.k=weg->rechts.k;
                weg->rechts.k->ouder=voorganger;
                voorganger->ouder=weg->ouder;
                plaats->k=voorganger;
            }
            weg->links.k=0;
            weg->rechts.k=0;
            delete weg;
        }
    }
    */
}





