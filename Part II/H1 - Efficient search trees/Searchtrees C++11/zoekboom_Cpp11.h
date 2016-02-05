/**********************************************************************

   
   beschrijving: Deze code bevat fouten !!!!!!!!!!!!!!!!
   en C++11-features
   
***************************************************************************/
#ifndef __ZOEKBOOM_H
#define __ZOEKBOOM_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <algorithm>

using std::unique_ptr;
using std::ostream;



/**********************************************************************

   Klasse: Binboom met Binknoop: binaire boom
   
   beschrijving: Domme klasse om de gegevens van een boom te bevatten
                 Omdat ze enkel in een wrapper wordt gebruikt, heeft ze
                 alles publiek staan. Ze mag dan ook nooit buiten een
                 wrapper gebruikt worden!
   
***************************************************************************/

template <class Sleutel,class Data>
class Binknoop;

template <class Sleutel,class Data>
class Binboom : public unique_ptr<Binknoop<Sleutel,Data>>{
public:
	 using unique_ptr<Binknoop<Sleutel,Data>>::unique_ptr; 
	 double aantal_knopen(){
	 	int links = 0; 
		 int rechts =0;
	 	if((*this)->links)
	 	  	 links = (*this)->links.aantal_knopen() ;
	 	if((*this)->rechts)	
	 		 rechts=(*this)->rechts.aantal_knopen() ; 
	 	
	 	
	 	return rechts + links +1 ; 
	 }
	 void splay(int sleutel);
	 
	 double totale_diepte( int diepte){
	 	int links = 0; 
		 int rechts =0;
	 	if((*this)->links)
	 	  	 links = (*this)->links.totale_diepte(diepte+1);
	 	if((*this)->rechts)	
	 		 rechts=(*this)->rechts.totale_diepte(diepte+1) ; 
	 		
	 		return links + rechts +diepte;
	 }
	 
	 double gemiddelde_diepte(){
	 	return totale_diepte(0)/aantal_knopen() ;
	 }
	 
     Binboom<Sleutel,Data>(){}  
     ~Binboom<Sleutel,Data>(){}
     
     Binboom<Sleutel,Data>(Binboom<Sleutel,Data>&& b):unique_ptr<Binknoop<Sleutel,Data>>(move(b)){
	 }
	 Binboom<Sleutel,Data>& operator=(Binboom<Sleutel,Data>&& b){
	 	 unique_ptr<Binknoop<Sleutel,Data>>::operator=(move(b));   
	 	 return *this;
	 }
	 
     int diepte() const{
        if (!*this)
            return 0;
        else
            return std::max((*this)->links.diepte(),(*this)->rechts.diepte())+1;
     };
     void schrijf(ostream&) const;
     void schrijf(ostream& os,Binknoop<Sleutel,Data>* kn) const{
        if (kn!=0)
            os<<"("<<kn->sl<<","<<kn->data<<")";
        else
            os<<"(,)";
     }
     void roteer(bool links);
};

template <class Sleutel,class Data>
class Binknoop{
    public:
        Sleutel sl;
        Data data;
        Binknoop<Sleutel,Data>* ouder;
        Binboom<Sleutel,Data> links,rechts;
        Binknoop():ouder(0){}
        Binknoop(const Sleutel& _sl,const Data& _data):ouder(0),sl(_sl),data(_data){}
};

/**********************************************************************

   klasse: Zoekboom
   
   beschrijving: Dit is een wrapper voor een Binboom,
                 die ervoor zorgt dat de sleutels in de Binboom
                 op volgorde staan
   
***************************************************************************/

template <class Sleutel,class Data>
class Zoekboom{
public:
     virtual void voegtoe(const Sleutel&,const Data&);
     	 	 
     void voegtoe(Binboom<Sleutel,Data>& knoop, const Sleutel& sl,const Data& data);
	 
//volgende functie doet niets als er geen knoop is met het gegeven Sleutel
     virtual void verwijder(const Sleutel&);
//geef pointer naar data horend bij een sleutel
     virtual Data* zoekdata(const Sleutel&);
     int diepte() const{return deBinboom.diepte();};
     friend ostream& operator<<(ostream& os,Zoekboom<Sleutel,Data>& b){
        b.deBinboom.schrijf(os);
        return os;
    };
    Binboom<Sleutel,Data>* ondervoorganger(Binknoop<Sleutel,Data>*);
    virtual void zoekplaats(const Sleutel&,Binboom<Sleutel,Data>*&,Binknoop<Sleutel,Data>*&);
    Binboom<Sleutel,Data> deBinboom;
protected:
//zoekplaats: geeft adres van boom waaraan knoop hangt, of zou moeten hangen
//en adres van de ouder.

//De binaire boom die de data bevat
     
//geeft de voorganger. Veronderstelt dat de linkerboom onder de knoop niet leeg is
    
     
};

template <class Sleutel,class Data>
void Binboom<Sleutel,Data>::roteer(bool links){	
    Binboom<Sleutel,Data> op;
    if(links){ 
    	op = move((*this)->rechts);
    	(*this)->rechts = move(op->links);
    	if((*this)->rechts != nullptr)
    		(*this)->rechts->ouder = (*this).get();    		
    	op->links = move(*this);
    	
    	*this = move(op);
    	(*this)->ouder = (*this)->links->ouder;
    	(*this)->links->ouder = (*this).get();
	}
	else{
		op = move((*this)->links);
    	(*this)->links = move(op->rechts);
    	if((*this)->links != nullptr)
    		(*this)->links->ouder = (*this).get();    		
    	op->rechts = move(*this);
    	
    	*this = move(op);
    	(*this)->ouder = (*this)->rechts->ouder;
    	(*this)->rechts->ouder = (*this).get();
	}	
}


template <class Sleutel,class Data>
void Binboom<Sleutel,Data>::splay(int sleutel){	
if((*this) !=0 && sleutel != (*this)->sl){
		if(sleutel< (*this)->sl ){
			(*this).roteer(false);
			if((*this)->sl <sleutel){
				(*this)->rechts.splay(sleutel)	;		
			}else{
				(*this).splay(sleutel);
			}
				
		}else{
		//sowieso groter dan de gezochte sleutel
			(*this).roteer(true);
			if((*this)->sl > sleutel){
				(*this)->links.splay(sleutel);
			
			}else{
				(*this).splay(sleutel);
			}
		}				
	}
}


template <class Sleutel,class Data>
void Zoekboom<Sleutel,Data>::zoekplaats(const Sleutel& sl,Binboom<Sleutel,Data>*& plaats, Binknoop<Sleutel,Data>*& ouder){
    plaats=&deBinboom;
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
Data* Zoekboom<Sleutel,Data>::zoekdata(const Sleutel& sl){
    Binboom<Sleutel,Data>* plaats;
    Binknoop<Sleutel,Data>* ouder;
    zoekplaats(sl,plaats,ouder);
    if (plaats==0)
        return 0;
    else return &((*plaats)->data);
}

template <class Sleutel,class Data>
void Zoekboom<Sleutel,Data>::voegtoe(const Sleutel& sl,const Data& data){
    if(deBinboom==0){  
    	unique_ptr<Binknoop<Sleutel,Data>> nieuw = unique_ptr<Binknoop<Sleutel,Data>>(new Binknoop<Sleutel,Data>(sl,data));
        deBinboom = move(nieuw);  
        deBinboom->ouder=0;
    }
    else
        voegtoe(deBinboom,sl,data);
}
template <class Sleutel,class Data>
void Zoekboom<Sleutel,Data>::voegtoe(Binboom<Sleutel,Data>& knoop, const Sleutel& sl,const Data& data){
    Binboom<Sleutel,Data> *kind;
    if (sl < knoop->sl)
        kind=&(knoop->links);
    else
        kind=&(knoop->rechts);
    if (*kind == 0){
    	(*kind) = move(unique_ptr<Binknoop<Sleutel,Data>>(new Binknoop<Sleutel,Data>(sl,data)));
        //(*kind) = move((unique_ptr<Binknoop<Sleutel,Data>>) new Binknoop<Sleutel,Data>(sl,data));
        (*kind)->ouder = knoop.get();
    }
    else
        voegtoe(*kind, sl,data);
}

template <class Sleutel,class Data>
void Zoekboom<Sleutel,Data>::verwijder(const Sleutel& sl){
	Binboom<Sleutel,Data> * plaats;
	Binknoop<Sleutel,Data> * ouder;
	zoekplaats(sl,plaats,ouder);
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
            Binboom<Sleutel,Data>* voorloper=ondervoorganger(plaats->get());
//            Binknoop<Sleutel,Data>* voorganger= voorlink->get();
            if (voorloper!=&((*plaats)->links)){				
//            	Binboom<Sleutel,Data> voorganger2 = std::move(*voorlink);
//				Binboom<Sleutel, Data> linkerboom_voorloper = std::move((*voorloper)->links);
				Binboom<Sleutel, Data> backup_voorloper = std::move(*voorloper);
            	//stap 1: voorganger 'losmaken' maar wel nog bijhouden via voorganger 2, anders verdwijnt de knoop in volgende stap (maak tekening!)
            	(*voorloper) = std::move(backup_voorloper->links);
            	(*voorloper)->ouder= backup_voorloper->ouder;
        		std::cout<<"hier"<<std::endl;

//				(*voorlink) = std::move(voorganger2->links);
//            	if((*voorlink)!=0){
//            		(*voorlink)->ouder = voorganger->ouder;
//				}
            	//stap 2: kinderen van voorganger laten wijzen naar kinderen van te verwijderen knoop
            	// geen nul controles nodig gezien er zeker kinderen zijn in deze stap
            	backup_voorloper->links = std::move((*plaats)->links);
            	backup_voorloper->links->ouder = backup_voorloper.get();
            	backup_voorloper->rechts = std::move((*plaats)->rechts);
            	backup_voorloper->rechts->ouder = backup_voorloper.get();
            	//stap 3: plaat plaats naar voorganger2 wijzen
            	(*plaats) = std::move(backup_voorloper);
                (*plaats)->ouder=ouder;
            }
            else{
            	voorloper->get()->rechts = std::move((*plaats)->rechts);
            	voorloper->get()->rechts->ouder = voorloper->get();
            	voorloper->get()->ouder = ouder;
            	(*plaats) = std::move(*voorloper);
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

template <class Sleutel,class Data>
Binboom<Sleutel,Data>* Zoekboom<Sleutel,Data>::ondervoorganger(Binknoop<Sleutel,Data>* kn){
//    Binboom<Sleutel,Data>* onder=&(kn->links);
//    while (onder->k->rechts.k!=0)
//        onder=&(onder->k->rechts);
//    return onder;
	Binboom<Sleutel,Data>* onder=&(kn->links);
	while((*onder)->rechts!=0){
		onder = &((*onder)->rechts);
	}
	return onder;
}


template <class Sleutel,class Data>
void Binboom<Sleutel,Data>::schrijf(ostream& os) const{
    if (*this!=0){
       Binknoop<Sleutel,Data>* loper = this->get();    	
       std::queue<Binknoop<Sleutel,Data>*, std::deque<Binknoop<Sleutel,Data>*> > q;
       q.push(loper);
       while(!q.empty()){
           Binknoop<Sleutel,Data>* nu=q.front();
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


#endif

