#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include <iostream>
#include <memory>

/*
Hier wordt const & gebruikt omdat we int willen kunnen gebruiken. Indien andere data is dat geen goed idee
beter moven dan indien de data nergens anders moet gebruikt worden.
*/

using namespace std;



struct Point{
	int  x;
	int  y;
	Point(int x = 0, int y = 0):x(x), y(y){};
	void schrijf(ostream& os){
		os<<"x= "<<x<<" y= "<<y<<endl;
	}
	bool operator<(const Point& p2){
		if(x == p2.x){
			return y < p2.y;
		}
		return x<p2.x;
	}
};

template<class T, class D>
class QuadtreePunt;

template<class T, class D>
class Quadtree: public std::unique_ptr<QuadtreePunt<T,D> >{
	using unique_ptr<QuadtreePunt<T,D> >::unique_ptr;
	public:
		bool aanwezig(T& p);
		Quadtree<T,D>* zoek(T& sleutel);
		bool voegToe(T& p,const D& data);
		void schrijf(ostream& os)const;
		int diepte()const;	
	private:
		const static int W = 0;
		const static int O = 1;
		const static int Z = 2;
		const static int N = 0;
};

template<class T, class D>
class QuadtreePunt{
	public:
		Quadtree<T,D> kinderen[4];
        T punt;
        D data;
    public:
    	QuadtreePunt(const T& p_,const D& data_):punt(p_),data(data_){
		};
		void schrijf(ostream& os)const;
		
};
template<class T, class D>
void Quadtree<T,D>::schrijf(ostream& os)const{
	if( this->get() != nullptr){
		this->get()->schrijf(os);
	}else{
		//todo: remove
		cout<<"Ik ben aan een einde gekomen"<<endl;
	}
}
template<class T, class D>
int Quadtree<T,D>::diepte()const{
	if(this->get() == nullptr){
		// hier -1 omdat de vw niet stopt bij de array maar bij de knoop waarnaar de array naar verwijst.
		return -1;
	}else{
		// normaal in knoop
		int max = -1;
		for(int i=0; i<4 ; i++){
			int res = this->get()->kinderen[i].diepte();
			if(res > max){
				max = res;
			}
		}
		return max+1;
	}
}
template<class T, class D>
bool Quadtree<T,D>::aanwezig(T& p){
	return true;
}
template<class T, class D>
Quadtree<T,D>* Quadtree<T,D>::zoek(T& p){
		Quadtree * loper = this;
		while(loper->get()){
			T ploper = loper->get()->punt;
			int plaats = 0;
			if(ploper.y == p.y && ploper.x == p.x){
				return loper;
			}
			if(ploper.y < p.y){
				plaats+=N;
			}else{
				plaats+=Z;
			}
			if(ploper.x < p.x){
				plaats+=O;
			}else{
				plaats+=W;
			}
			loper = &(loper->get()->kinderen[plaats]);
		}
		return loper;
	
}

template<class T, class D>
bool Quadtree<T,D>::voegToe(T& p,const D& data){
	if( this->get() == nullptr){
		(*this) = unique_ptr<QuadtreePunt<T,D> >(new QuadtreePunt<T,D>(p, data));
	}else{
		Quadtree<T,D>* gezochte= zoek(p);
		if(gezochte->get() == nullptr){
			// nieuwe quadtreepunt aanmaken en ernaar wijzen
			(*gezochte) = std::move(unique_ptr<QuadtreePunt<T,D> >(new QuadtreePunt<T,D>(p, data)));
			cout<<"Ik ga een nieuwe knoop aanmaken"<<endl;
			return true;
		}else{
			gezochte->get()->data = data;
			cout<<"Ik heb een duplicaat, ik geef hem de neiuwe data"<<endl;
			return false;
		}
		
		
	}
	
	return true;
}


/*
Implementatie van quadtreepunt
*/
template<class T, class D>
void QuadtreePunt<T,D>::schrijf(ostream& os)const{
	os<<"sl: "<<"("<<punt.x<<", "<<punt.y<<")"<<" data: "<<data<<endl;
	for(int i=0; i<4; i++){
		kinderen[i].schrijf(os);
	}
}



#endif
