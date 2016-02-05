#ifndef _PRQUADTREE_H_
#define _PRQUADTREE_H_

#include <iostream>
#include <vector>
	using std::vector;
#include <memory>

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



//template<class T, class D>
//class QuadtreePunt{
//	// todo: veranderen naar protected
//	public:
//        T punt;
//        D data;
//    public:
//    	QuadtreePunt(const T& p_,const D& data_):punt(p_),data(data_){
//		};
//		void schrijf(ostream& os)const;
//		
//};


template<class T, class D>
class prQuadNode;


template<class T, class D>
class Quadtree: public std::unique_ptr<prQuadNode<T,D> >{
	using unique_ptr<prQuadNode<T,D> >::unique_ptr;
	public:
		Quadtree(){
		}
		
		Quadtree(int xMin, int xMax, int yMin, int yMax) {
			this->xMin = xMin;
			this->xMax = xMax;
			this->yMin = yMin;
			this->yMax = yMax;
			cout<<"quadtree ["<<xMin<<";"<<xMax<<"]"<<";"<<"["<<yMin<<";"<<yMax<<"]"<<endl;
		}
		Quadtree& operator=(Quadtree<T,D>&& qtr){
			this->xMin = qtr.xMin;
			this->xMax = qtr.xMax;
			this->yMin = qtr.yMin;
			this->yMax = qtr.yMax;
			cout<<"quadtree ["<<xMin<<";"<<xMax<<"]"<<";"<<"["<<yMin<<";"<<yMax<<"]"<<endl;

			unique_ptr<prQuadNode<T,D>>::operator=(std::move(qtr));
		
			return *this;
		}
	
		bool aanwezig(T& p);
		Quadtree<T,D>* zoek(T& sleutel, Quadtree<T,D>* ouder);
		bool voegToe(T& p,const D& data);
		void schrijf(ostream& os)const;
		int diepte()const;	
		
		int xMin, xMax, yMin, yMax;

	private:
		const static int W = 0;
		const static int O = 1;
		const static int Z = 2;
		const static int N = 0;
};

template<class T, class D>
class prQuadNode{
	public:
//		virtual ~prQuadNode();
		virtual void schrijf(ostream& os)const = 0;
};

template<class T, class D>
class prQuadLeaf: public prQuadNode<T,D> {
	public:
		prQuadLeaf(T sl_,D elem){
			this->data = elem;
			this->sl = sl_;
		}
		void schrijf(ostream& os)const{
			cout<<data<<endl;
		}

	public:
		D data;
		T sl;
};


template<class T, class D>
class prQuadInternal: public prQuadNode<T,D> {
	public:
		prQuadInternal(int xMidden,int yMidden,int breedte,int hoogte){
			int halvebreedte = breedte/2;
			int halvehoogte = hoogte/2;
			kinderen[0]=std::move(Quadtree<T,D>(xMidden-halvebreedte, xMidden, yMidden, yMidden+halvehoogte));
			kinderen[1]=std::move(Quadtree<T,D>(xMidden, xMidden+halvebreedte, yMidden, yMidden+halvehoogte));
			kinderen[2]=std::move(Quadtree<T,D>(xMidden-halvebreedte, xMidden, yMidden-halvehoogte, yMidden));
			kinderen[3]=std::move(Quadtree<T,D>(xMidden, xMidden+halvebreedte, yMidden-halvehoogte, yMidden));
			cout<<"net een nieuwe interne knoop aangemaakt"<<endl;
			schrijf(cout);
			cout<<"------------------------"<<endl;
		};
		virtual void schrijf(ostream& os)const{
			for(int i=0; i<4; i++){
				kinderen[i].schrijf(os);
			}
		}

	public:
		Quadtree<T,D> kinderen[4];
};

/*
Implementatie
*/

template<class T, class D>
void Quadtree<T,D>::schrijf(ostream& os)const{
	cout<<"quadtree ["<<xMin<<";"<<xMax<<"]"<<";"<<"["<<yMin<<";"<<yMax<<"]"<<endl;
	if(this->get() != nullptr){
		this->get()->schrijf(os);
	}
}

template<class T, class D>
int Quadtree<T,D>::diepte()const{
	if(this->get() == nullptr){
		return -1;
	}else{
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


// geeft een pointer terug naar een quadtree die naar niets wijst indien er nog geen blad aangemaakt is.
// OF geeft een pointer terug naar een quadtree die naar een blad wijst ==> er zal moeten gesplitst worden.

template<class T, class D>
Quadtree<T,D>* Quadtree<T,D>::zoek(T& p, Quadtree<T,D>* ouder){
		Quadtree * loper = this;		
		while(loper->get()){
			int plaats = 0;
			if(typeid(*(loper->get())) == typeid(prQuadLeaf<T,D>)){
				return loper;
			}
			int breedte = ouder->xMax - ouder->xMin;
			int hoogte = ouder->yMax - ouder->yMin;
			int xMidden = ouder->xMin + breedte/2;
			int yMidden = ouder->yMin + hoogte/2;
			cout<<"ik zoek eentje dieper ["<<xMidden<<";"<<yMidden<<"]"<<endl;
			if(yMidden < p.y){
				plaats+=N;
			}else{
				plaats+=Z;
			}
			if(xMidden < p.x){
				plaats+=O;
			}else{
				plaats+=W;
			}
			prQuadInternal<T,D>* lopertje = static_cast<prQuadInternal<T,D>*>(loper->get());
			
			loper = &(lopertje->kinderen[plaats]);
		}
		cout<<"dikke seks"<<endl;
		return loper;	
}

template<class T, class D>
bool Quadtree<T,D>::voegToe(T& p,const D& data){
//	if( this->get() == nullptr){
//		(*this) = unique_ptr<QuadtreePunt<T,D> >(new QuadtreePunt<T,D>(p, data));
//	}else{
		Quadtree<T,D>* ouder;
		Quadtree<T,D>* gezochte= zoek(p,ouder );
		cout<<"dikke seks"<<endl;
		if(gezochte->get() == nullptr){
			// nieuwe quadtreepunt aanmaken en ernaar wijzen
			cout<<"ik heb een minimum"<<gezochte->xMin;
			int xMin = gezochte->xMin;
			int xMax= gezochte->xMax; 
			int yMin = gezochte->yMin;
			 int yMax = gezochte->yMax;
			(*gezochte) = std::move(Quadtree<T,D>(new prQuadLeaf<T,D>(p, data)));
			gezochte->xMin = xMin;
			gezochte->xMax = xMax;
			gezochte->yMin = yMin;
			gezochte->yMax = yMax;
			cout<<"Ik ga een nieuwe knoop aanmaken"<<endl;
			return true;
		}else{
			cout<<"ik moet het blad splitsen"<<endl;
			// blad bestaat en moet dus gesplitst worden recursief.
			prQuadLeaf<T,D>* lopertje = static_cast<prQuadLeaf<T,D>*>(gezochte->get());
			int breedte = gezochte->xMax - gezochte->xMin;
			int hoogte = gezochte->yMax - gezochte->yMin;
			int xMidden = gezochte->xMin + breedte/2;
			int yMidden = gezochte->yMin + hoogte/2;
			D data_ = lopertje->data;
			T sleutel = lopertje->sl;
			(*gezochte) = std::move(unique_ptr<prQuadInternal<T,D> >(new prQuadInternal<T,D>(xMidden, yMidden, breedte, hoogte)));
			gezochte->voegToe(sleutel, data_);
			gezochte->voegToe(p, data);
//			gezochte->get()->data = data;
//			cout<<"Ik heb een duplicaat, ik geef hem de neiuwe data"<<endl;
//			return false;
		}
		
		
//	}
	
	return true;
}



#endif
