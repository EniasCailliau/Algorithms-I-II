#include "bucket.h"

//template<typename T>
//void Print(const vector<T>& tab){
//	for(int i=0; i<tab.size(); i++){
//		cout<<tab[i]<<" ";
//	}
//	cout<<endl;
//}

int main(){
	vector<int> v{5,4,1,6,11,22, 33, 44, 30, 40, 55, 59};
	Print(v);
//	Insertionsort(v);
//	Bucketsort(v);
//	Print(v);
	
	cout<<"\n \t Werken met Lijsten \n";
	Lijst<int> l;
	l.VoegToeVooraan(59);
	l.VoegToeVooraan(55);
	l.VoegToeVooraan(40);
	l.VoegToeVooraan(30);
	l.VoegToeVooraan(44);
	l.VoegToeVooraan(33);
	l.VoegToeVooraan(22);
	l.VoegToeVooraan(11);
	l.VoegToeVooraan(6);
	l.VoegToeVooraan(1);
	l.VoegToeVooraan(4);
	l.VoegToeVooraan(5);
	l.Print();
	Bucketsort(l,6);
	cout << "hier";
	l.Print();
	
	return 0;
}
