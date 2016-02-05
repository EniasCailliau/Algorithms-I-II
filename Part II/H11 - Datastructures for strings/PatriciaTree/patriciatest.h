#include "sleutel2.h"

using namespace std;
class Knoop{
	public:
		Knoop( const Sleutel & _sleutel, const & _index):index(_index), sleutel(_sleutel){
		}

	Sleutel sleutel;
	Knoop * links;
	Knoop * rechts;
	int index;
	
	friend ostream& operator<<(ostream& os, const Knoop& b){
     	os<<"("<< b.sleutel<<" index "<<b.index<<")";
        return os;
    }
	
};





class Patriciatrie{
	friend class Knoop;
	public:
	Patriciatrie(){
		const Sleutel sleutel(0);
		wortel = new Knoop(sleutel,-1);
		wortel->links = wortel;
	}
	int zoek(const  & sleutel);

    void voegtoe(const Sleutel & sleutel );
	

		Knoop * wortel;
	Knoop* zoek(Knoop* k, const Sleutel & sleutel , int index);
    Knoop* voegtoe(Knoop* k, Knoop* parent, const Sleutel & sleutel , int index);
    
    void schrijf(ostream& os ,Knoop* k )const{
			os<<"ouder "<<*k;			
			if(  k->links && k->links->index > k->index){
				cout<< "links kind "<<*(k->links);
			}else if(k->links){
				if(k->links->index == k->index){
					cout<<"links kind naar zichzelf ";
				}else{
					cout<<" links kin terug verbinding ";
				}	
			}

			if( k->rechts && k->rechts->index > k->index){
				cout<<"rechts kind "<<*(k->rechts);
			}else if(k->rechts){
				if(k->rechts->index == k->index){
					cout<<"rechts kind naar zichzelf ";
				}else{
					cout<<" rechts kin terug verbinding ";
				}
		//					cout<<"index rechts knoop"<<k->rechts->index <<" index ouder knoop"<< k->index <<endl;
			}

			cout<<endl;
			if(  k->links && k->links->index > k->index)
				schrijf(os,k->links);
			
			if( k->rechts && k->rechts->index > k->index)
				schrijf(os,k->rechts);

		}
		

	friend ostream& operator<<(ostream& os, const Patriciatrie& b){
     	b.schrijf(os ,b.wortel );
        return os;
    }
	
};

Knoop* Patriciatrie::zoek(Knoop* k, const Sleutel & sleutel , int index){
	if(k->index <= index){
		//huidige index kleiner dan k dat een kind is
		//terug verbinding of knoop naar jezelf, stoppen met zoeken
		return k;
	}
	
	if(sleutel.bit(k->index)){ //met eigen index vergelijken
		return zoek(k->rechts,sleutel,k->index);
	}else{
		return zoek(k->links,sleutel,k->index);
	}
	
	
}


void Patriciatrie::voegtoe(const Sleutel & sleutel ){
	//
	Knoop * knoop = zoek(wortel->links , sleutel, -1);
	
	if(knoop->sleutel == sleutel){
		cout<<"is al gevonden"<<endl;
		return;
	}
	
	int verschilindex = knoop->sleutel.verschilbit(sleutel);
	//	cout<<"verschil index "<<verschilindex<< " tussen "<<knoop->sleutel <<"  ->  "<<sleutel<<endl;
	//toevoegen aan kind van parent
	wortel->links = voegtoe(wortel->links, wortel, sleutel , verschilindex) ;

}


Knoop* Patriciatrie::voegtoe(Knoop* k, Knoop* parent, const Sleutel & sleutel , int index){ //index is verschilindex
	if(k->index >= index || k->index <= parent->index){
	//1. grotere index gevonden dan verschil index
    //nieuwe knoop tussen voegen
    //sleutel in knoop opslaan
    //gepaste wijzer naar knoop wijzen
    
   
 	//2. geen knoop met hogere index, je zit eigenlijk nog steeds parent zijn links of rechts aan te passen
 	//eidigen in blad
 	Knoop * nieuwe = new Knoop(sleutel,index);
 	nieuwe->links = sleutel.bit(index) ? k : nieuwe;
 	nieuwe->rechts = sleutel.bit(index) ? nieuwe : k;
 	return nieuwe;
 }
 
 
 	if(sleutel.bit(k->index)){ //met eigen index vergelijken
		k->rechts =  voegtoe(k->rechts,k,sleutel,index);
	}else{
		k->links =  voegtoe(k->links,k,sleutel,index);
	}
 
 return k;
	
}


