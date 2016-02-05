#include "Splay.h"


int main(){
	Binboom<int,int> wortel(std::move(new Binknoop<int,int>(20,20)));
	wortel.schrijf(cout);
	wortel.voeg_toe(10,10);
	wortel.schrijf(cout);
}
