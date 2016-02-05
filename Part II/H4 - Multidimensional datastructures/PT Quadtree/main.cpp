
#define _USE_MATH_DEFINES
#include <cmath> 

#include "quadtree.h"
#include "csv.h"
#include <iostream>


#include <algorithm>
#include <random>


using namespace std;

int main(){
	Quadtree<Point,int> quadtree;

	Point p(3,3);
	p.schrijf(cout);
	cout<<"-------------------Starten van de testen-------------------"<<endl;
	quadtree.voegToe(p,11);
	quadtree.schrijf(cout);
	Quadtree<Point,int>* res = quadtree.zoek(p);
	if(res == nullptr){
		cout<<"nullptr res"<<endl;
	}
	cout<<"Ik ga het resultaat uitschrijven van de zoekfunctie: ";
	res->get()->punt.schrijf(cout);
	cout<<"-------------------Vergelijken van punt testen-------------------"<<endl;
	Point p2(2,3);
	cout<<"kleiner dan? "<<(p<p2)<<endl;
	Quadtree<Point,int>* res2 = quadtree.zoek(p2);
	if(res2->get() == nullptr){
		cout<<"nullptr res"<<endl;
	}else{
		cout<<"Ik ga het resultaat uitschrijven van de zoekfunctie: ";
		res2->get()->punt.schrijf(cout);	
	}
	cout<<"-------------------Testen van toevoegen-------------------"<<endl;
	Point p3(4,4);
	bool res4  = quadtree.voegToe(p3, 12);
	cout<< (res4 ? "Toegevoegd" : "Niet toegevoegd")<<endl;
	quadtree.schrijf(cout);
	
	cout<<"-------------------Testen van diepte in een boom-------------------"<<endl;
	int resultaat  = quadtree.diepte();
	cout<<"diepte van de boom is: "<<resultaat<<endl;


	cout<<"-------------------Testen van diepte op spiraal-------------------"<<endl;
	CsvData grafiek("dieptedata1",'.');
    vector<double> dieptedata;

	Quadtree<Point,int> testquadtree;
	vector<Point> punten;
	int grens = 200;
	for(int i=0; i<grens; i++){
		int x = i;
		int y = ( (10000-5*i)* cos(i*0.25*M_PI), (10000-5*i)* sin(i*0.25*M_PI) );
		Point punt(x,y);
		punten.push_back(punt);
		bool gelukt = testquadtree.voegToe(punt, i*20);
		double diepte = testquadtree.diepte();
		cout<<diepte<<endl;
		dieptedata.push_back(diepte);
	}
	grafiek.voegDataToe(dieptedata);

	cout<<"-------------------Testen van diepte op spiraal(randomized)-------------------"<<endl;

	Quadtree<Point,int> testquadtree2;
    vector<double> dieptedata2;

	auto engine = std::default_random_engine{};
	std::shuffle(std::begin(punten), std::end(punten), engine);
	for(int i=0; i<grens; i++){
		bool gelukt = testquadtree2.voegToe(punten[i], i*20);
		double diepte = testquadtree2.diepte();
		cout<<diepte<<endl;
		dieptedata2.push_back(diepte);
	}
	grafiek.voegDataToe(dieptedata2);

	
	
	return 0;
}




