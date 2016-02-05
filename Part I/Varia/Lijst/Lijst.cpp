#include "Lijst.h"

int main(){
	Lijst<int> l;
	Lijstknoop<int> lp;
	l.VoegToeVooraan(4);
	l.VoegToeVooraan(10);
	l.VoegToeAchteraan(7);
	l.VoegToeAchteraan(2);
	l.VoegToeAchteraan(40);
	l.VoegToeAchteraan(4);
	l.Print();
	cout << "size="<<l.size() <<endl;
	//l.PrintRecursief(cout);
	cout << endl;
	// Lijst<int> * result = l.zoek_gerangschikt(6);
	// result->Print();
	// cout<< endl;
	// Lijst<int> l2(l);
	// l2.Print();
	//cout<<endl;
//	l2.insertion_sort();
	l.Print();
	cout<<endl;
	// cout<<endl;
	//l2.Append(&l);
	// l2.Print();
	// cout<< "\n Nu werken met vectoren" <<endl;
	
	
	//Nu met vectoren
	// vector<int> v{4,10, 7,2,40,4};
	// Print(v);
	// Instertionsort(v);
	// Print(v);
	
	//In dit labo gaan we dus duidelijk vergelijken het verschil tussen "verschuiven" enerzijds
	// en "pointers verplaatsen" anderzijds; --> weinig performantie verschil voor kleine datastructuren
	// cout<< "\n \t InsertionSort\n";
	//l2.insertion_sort();
	//l2.Print();
	
	
	// Start verwerken van selectionsort
	// cout<< "\n \t SelectionSort\n";
	//Lijst<int> * max = l2.ZoekMax();
	//max->Print();
	//cout<<endl;
	//l2.selection_sort();
	//l2.Print();
	//Lijst<int>* min = l2.ZoekMin();
	//min->Print();
	//cout << endl;
	l.insertion_sort();
	l.Print();
	
	
	
	return 0;
	
}
