#include "bplustree.h"
#include "schijf.h"
#include "printers.h"

#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <ctype.h>
#include <functional>
#include <cctype>
#include <algorithm>

int main(){
	const uint mtussen = 2;
	const uint mblad = 2;
	Schijf<Bplusknoop<int, uint, mtussen, mblad> > schijf;
	Bplustree<int, uint, mtussen, mblad> bplustree(schijf);
	bplustree.overloop_gelinktelijst();
	printspecial("uitschrijven van sequence list");
	bplustree.voegtoe(1,1);
	bplustree.voegtoe(2,2);
	bplustree.voegtoe(3,3);
//	bplustree.overloop_gelinktelijst();
	printspecial("forceren van een split van interne knopen");
	Bplusknoop<int, uint, mtussen, mblad> buffer;
	schijf.lees(buffer, 12);
	cout<<"ik had vroeger een rechtse: "<<buffer.blad.sleutel[1]<<endl;
	bplustree.voegtoe(4,4);
	schijf.lees(buffer, 13);
//	// Hiermee kan controle uitgevoerd worden of de root effectief klopt. (zie tekening)
	cout<<buffer.tussen.index[2];
	bplustree.overloop_gelinktelijst();
	// todo fixen van splits interne knoop
	bplustree.voegtoe(5,5);
	schijf.lees(buffer, 17);
	cout<<"buffer lezen"<<endl;
	cout<<buffer.tussen.sleutel[0];

//	bplustree.overloop_gelinktelijst();
	
	
	printspecial("forceren van een split van interne knopen");
	cout<<bplustree.zoek(4);

	


	return 0;
}
