#include "binboom.h"

int main(){
	
	
	BinaireBoom<string> bb;
	bb.lees("binboom_input.txt");
	//bb.schrijf(cout,"in");
	bb.schijfinlevel();
	//b->left = std::move(c);
	//	cout<<b->inhoud;
	//BinaireBoom<int> a(std::move(b));
	//b=std::move(a);
	
	//b.schrijf(cout, "in");
	
	return 0;
}
