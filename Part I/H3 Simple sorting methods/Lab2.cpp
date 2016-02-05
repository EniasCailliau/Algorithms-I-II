#include "sorteermethode.h"
#include "sortvector.h"

int main(){
	Sortvector<int> v(200);
	v.vul_range();
	v.vul_random();
	v.shuffle();
	cout << v << endl;
	MQuicksort<int> sm;
	v.Sorteer(sm);
	cout << v;
	return 0;
}
