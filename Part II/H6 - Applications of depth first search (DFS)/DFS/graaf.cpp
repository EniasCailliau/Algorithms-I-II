#include "graaf.h"
#include "printers.h"
#include <fstream>
using namespace std;


int main(){
//	Graaf<GERICHT> gr;
//	ifstream is("graaf.txt");
//	gr.lees(is);
//	gr.schrijf(cout);
//	Printspecial("Andere graaf voor componenten");
//	ifstream iss("graaf1.txt");
//	gr.lees(iss);
//	gr.schrijf(cout);
//	Printspecial("Bepaal nu de componenten");
//	vector<int> v = gr.bepaalcomp();
//	Print(v);
	
//	cout<<"is samenhangend?"<<gr.isSamenhangend()<<endl;
	
//gr.overloop_breedte_eerst();
	


/*
Deel II: Sterk samenhangende componenten van een gerichte graaf
*/
//	Graaf<GERICHT> gr;
//	Printspecial("Sterk samenhangend testen");
//	ifstream iss("graaf2.txt");
//	gr.lees(iss);
//	gr.schrijf(cout);
//	Graaf<GERICHT> gr_inv;
//	gr.draaiOm(gr_inv);
////	gr_inv.schrijf(cout);
//	vector<int> postordernummering = gr_inv.bepaal_postorder_nummering();
//	Print(postordernummering);
//	vector<int> sterke_comp = gr.bepaal_sterk_samenhangende_componenten(postordernummering
//	);
//	Print(sterke_comp);

/*
Deel III: Dubbel samenhangende componenten van een graaf.
*/

//	Printspecial("Detectie van een scharnierpunt");
//	Graaf<ONGERICHT> graafMetScharnierpunten;
//	ifstream iss("graaf4.txt");
//	graafMetScharnierpunten.lees(iss);
//	graafMetScharnierpunten.schrijf(cout);
//	cout<<"Uitschrijven van de scharnierpunten"<<endl;
//	graafMetScharnierpunten.zoek_scharnierpunten();


	std::priority_queue<pair<int,int>,vector<pair<int,int>>> pq;
	pq.push(pair<int,int>(1,2));
	pq.push(pair<int,int>(2,5));
	pair<int,int> top = pq.top();
	cout<<top.second<<endl;

	return 0;
}
