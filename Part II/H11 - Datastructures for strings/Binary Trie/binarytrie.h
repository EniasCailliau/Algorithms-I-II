#include "bitpatroon.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BTrie;

class Knoop{
	friend class BTrie;
	public:
	    Knoop(){
		}
	    virtual ~Knoop(){};
	    virtual bool isBlad(){
	    	return true;
		}
	    virtual void print(ostream & os)const{}
};

class Blad: public Knoop{
	friend class BTrie;
	public:
		virtual ~Blad(){};
		Blad(Bitpatroon& b):sl(b){
			
		}
		Blad(){
		}
	    virtual bool isBlad();
	    virtual void print(ostream& os)const{
				os<<sl<<endl;
		}
	public:
		Bitpatroon sl;
		
};

class InwendigeKnoop;

class BTrie{
	friend class InwendigeKnoop;
	public:
		BTrie(){
			root = nullptr;
		};
		BTrie(Knoop* kn):root(kn){
		};
//		void voegToe(char el);
//		Knoop** zoek(char el, uint& bitplaats);
		void voegToe(Bitpatroon bit);
		BTrie* zoek(Bitpatroon& bit, uint& bitplaats);
	private:
		Knoop* root;
};

class InwendigeKnoop: public Knoop{
	friend class BTrie;
	public:
		virtual ~InwendigeKnoop(){
			delete kinderen[0];
			delete kinderen[1];
		};
		InwendigeKnoop(){
			kinderen.resize(2);
			kinderen[0] = new BTrie();
			kinderen[1] = new BTrie();
		}
	    virtual bool isBlad();
	    virtual void print(ostream& os)const{
			for(int i=0; i<2; i++){
				kinderen[i]->root->print(os);
			}
		}
	private:
		vector<BTrie*> kinderen;
};



/*
Implementatie
*/

BTrie* BTrie::zoek(Bitpatroon& bit, uint& bitplaats){
//	cout<<"ik ga zoeken: "<<bit<<endl;
//	cout<<root->isBlad()<<endl;
//	cout<<"root is :"<<root->sl<<endl;

		BTrie* loper = this;
		bitplaats = 0;
//		cout<<"probleem bij en"<<endl;
		while(loper->root != nullptr && !loper->root->isBlad()){
//			cout<<"hier"<<endl;
//          	cout<<"ik ga naar :"<<bit.en(Bitpatroon::eenbit(bitplaats))<<endl;
			cout<<"ik ga nog dieper want root wees niet naar blad"<<endl;
          	InwendigeKnoop * ik = (InwendigeKnoop*) loper->root;
    		loper = ik->kinderen[bit.en(Bitpatroon::eenbit(bitplaats))];
    		bitplaats++;
		}
		cout<<"ik heb plaats van toevoegen gevonden";
		return loper;

	
}

//Knoop** BTrie::zoek(char el, uint& bitplaats){
//	uint kar = el;
//	Bitpatroon bit(kar);
////	cout<<"ik ga zoeken: "<<bit<<endl;
////	cout<<root->isBlad()<<endl;
////	cout<<"root is :"<<root->sl<<endl;
//	if(root == nullptr){
//		return nullptr;
//	}else{
//		BTrie* loper = this;
//		bitplaats = 0;
//		cout<<"probleem bij en"<<endl;
//		while(loper != nullptr && !(*loper)->isBlad()){
//			cout<<"hier"<<endl;
//          	cout<<"ik ga naar :"<<bit.en(Bitpatroon::eenbit(bitplaats))<<endl;
//          	InwendigeKnoop * ik = (InwendigeKnoop*) *loper;
//    		loper = &(ik->kinderen[bit.en(Bitpatroon::eenbit(bitplaats))]);
//    		bitplaats++;
//		}
//		cout<<"hier";
//		return loper;
//
//	}
//}

void BTrie::voegToe(Bitpatroon bit){
	cout<<"ik ga toevoegen: "<<bit<<endl;
	if(root == nullptr){
		root = (Knoop*) new Blad(bit);
		cout<<root->isBlad()<<":ik heb net een blad toegoevoegd"<<endl<<endl;
	}else{
//		root is niet nullptr, dus kan een blad zijn.
		cout<<"fml"<<endl;
		// eerst proberen zoeken, de enigste plaats waar de sleutel KAN aanwezig zijn
		uint bitplaats;
		BTrie* retu = zoek(bit, bitplaats);
		if(retu->root == nullptr){
			
		}else{
				Blad* bl  = (Blad*) retu->root;
				Bitpatroon data = bl->sl;
				if(bl->sl == bit){
					cout<<"ze zijn gelijk!, ik ga geen duplicaten toevoegen"<<endl;
				}else{
//					if(bl == root){
						cout<<"het gaat om de root"<<endl;
//						cout<<"ik een kind toevoegen :"<<bl->sl.en(Bitpatroon::eenbit(bitplaats))<<endl;
						bool gedefinieert = false;
							while(!gedefinieert){
								InwendigeKnoop* nieuweinwendige = new InwendigeKnoop();
								if(bit.en(Bitpatroon::eenbit(bitplaats)) != bl->sl.en(Bitpatroon::eenbit(bitplaats))){
									cout<<"yes ik kan toevoegen"<<endl;
									gedefinieert = true;
									nieuweinwendige->kinderen[bl->sl.en(Bitpatroon::eenbit(bitplaats))] = new BTrie(new Blad(data));
									nieuweinwendige->kinderen[bit.en(Bitpatroon::eenbit(bitplaats))] = new BTrie(new Blad(bit));
									retu->root = nieuweinwendige;
								}else{
									cout<<"ik zal extra vertakking maken"<<endl;
									nieuweinwendige->kinderen[bit.en(Bitpatroon::eenbit(bitplaats))] = new BTrie();
									retu->root = nieuweinwendige;
									bitplaats++;
									retu = nieuweinwendige->kinderen[bit.en(Bitpatroon::eenbit(bitplaats))];
								}
						}												
//					}else{
//						cout<<"nog meer miserie"<<endl;
//					}
				}
		}

}}

//void BTrie::voegToe(char el){
//	uint kar = el;
//	Bitpatroon bit(kar);
//	cout<<"ik ga toevoegen: "<<bit<<endl;
//	if(root == nullptr){
//		root = (Knoop*) new Blad(bit);
//		cout<<root->isBlad()<<"boe"<<endl;
//	}else{
////		root is niet nullptr, dus kan een blad zijn.
//		cout<<"fml"<<endl;
//		// eerst proberen zoeken, de enigste plaats waar de sleutel KAN aanwezig zijn
//		uint bitplaats;
//		Knoop** retu = zoek(el, bitplaats);
//		if(retu == nullptr){
//			
//		}else{
//				Blad* bl  = (Blad*) *retu;
//				cout<<bl->sl<<endl;
//				if(bl->sl == bit){
//					cout<<"ze zijn gelijk!, ik ga geen duplicaten toevoegen"<<endl;
//				}else{
//					if(bl == root){
//						cout<<"het gaat om de root"<<endl;
//						InwendigeKnoop* nieuweinwendige = new InwendigeKnoop();
//						cout<<"ik een kind toevoegen :"<<bl->sl.en(Bitpatroon::eenbit(bitplaats))<<endl;
//						retu = (Knoop**) &nieuweinwendige;
//					}
//				}
//		}
//	
//		
//	}
//	
//	
//}



bool Blad::isBlad(){return true;}
bool InwendigeKnoop::isBlad(){return false;}
