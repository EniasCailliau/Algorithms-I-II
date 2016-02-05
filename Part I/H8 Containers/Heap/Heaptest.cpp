#include "Heap.h"
#include "printers.h"


int main(){
	vector<int> v{4,7,3,11,9,22,14,20};
	Print(v);
//	Printspecial("Test van maakheap");
//	MaakHeap(v);
//	Print(v);	
	Printspecial("Test van Heapsort");
	Heapsort(v);
	Print(v);
	
	vector<int> w{40,7,3,11,9,22,14};
	Printspecial("Test van Minheap");
	MaakMinHeap(w,w.size());
	Print(w);
	//verwijdertopMinHeap(w,w.size());
	//Print(w);
	voegelementToeMinHeap(w,8);
	Print(w);
	
	return 0;
}
