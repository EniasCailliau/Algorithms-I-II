#include <vector>
#include <iostream>
using namespace std;

template <class T>
class Gesorteerdetabel{
	public:
		Gesorteerdetabel();
		~Gesorteerdetabel();
		// ik voeg geen duplicaten toe
		bool voegtoe(T sl);
		T zoek(T sl);
	
	friend ostream& operator<<(ostream& os, const Gesorteerdetabel<T>& g){
		for(int i=0; i<g.v.size(); i++){
			os<<g.v[i]<<"\t";
		}
		os<<endl;
		return os;
	}	
	
	private:
		vector<T> v;
};


template <class T>
Gesorteerdetabel<T>::Gesorteerdetabel(){
	
}
template <class T>
Gesorteerdetabel<T>::~Gesorteerdetabel(){
	
}
template <class T>
bool Gesorteerdetabel<T>::voegtoe(const T& sl){
	// eerst de plaats zoeken
	v.push_back(sl);
	int i=v.size()-2;
	while(i >= 0 && v[i]>sl){
		v[i+1]=v[i];
		i--;
	}
	v[i+1]=sl;
}
template <class T>
T Gesorteerdetabel<T>::zoek(T sl){
	int l=0; int r=v.size()-1;
	while(l < r){
		int m= l+(r-l)/2;
		if(sl <= v[m]){
			r=m;
		}else{
			l=m+1;
		}
	}
	return v[l]==sl ? l : -1;
}


