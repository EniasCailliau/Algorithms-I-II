#include "Lijst.h"



void merge(Lijst<int>* l1, Lijst<int>* l2){
	Lijst<int> tijd; //tijd dient om tijdelijk de 
	
//	Lijst<int>* loper1 = &l1;
//	Lijst<int>* loper2 = &l2;
	while(l1->k && l2->k){
		if(l1->k->sl <= l2->k->sl){
			cout<<"hier";
			tijd.steelvanlijst(l1);
		//	loper1 = &(loper1->k->volgend);
		}else{
			cout<<"daar";
			tijd.steelvanlijst(l2);
		//	loper2 = &(loper2->k->volgend);
		}
	}	
	//l1->Print();
	//l2->Print();
	
	while(l1->k){
		tijd.steelvanlijst(l1);

	}
	while(l2->k) tijd.steelvanlijst(l2);

	tijd.Print();
}
