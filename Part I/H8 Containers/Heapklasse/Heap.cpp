#include "Heap.h"
template <typename T>
void Print (const vector<T>& v){
  for (int i=0; i<v.size();i++){
    cout << v[i]<<" ";
  }
  cout<<endl;
}


int main(){
	Heap h;
	h.VoegToe(10);
	h.VoegToe(5);
	h.VoegToe(11);
	h.VoegToe(13);
	h.VoegToe(2);
	h.VoegToe(20);
	cout << "heap basis: ";
	h.Print();
	cout<<"vervang top (3): ";
	h.VervangTop(3);
	h.Print();
	cout<<"vervan top:(1) ";
	h.VervangTop(1);
	h.Print();
	cout<<"vervan top:(30) ";
	h.VervangTop(30);
	h.Print();
	
	cout<<endl;
	vector<int> v;
	v.push_back(10);
	v.push_back(5);
	v.push_back(11);
	v.push_back(13);
	v.push_back(2);
	v.push_back(3);
	cout<<"vector die getransformeerd wordt: ";
	Print(v);
	cout<<"Heap op basis van de vector: ";
	Heap s(v);
	s.Print();
	//cout<<"Heap maken op minder performante basis: ";
	//s.MaakHeap(v);
	//Print(v);
	Heap t;
	cout<< endl;
	cout << "transform to heap :"<<endl;
	cout <<" originele vector: "; Print(v);
	t.TransformToHeap(v);
	cout << " Getransformeerd: ";
	Print(v);
//	int top = s.PopTop();
//	cout<< top <<endl;
//	s.Print();
//	top = s.PopTop();
//	cout<< top <<endl;
//	s.Print();
	s.Sort();
	s.Print();
	
	



return 0;

}
