#include <memory>
#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::ostream;

template <class Sleutel,class Data>
class Binknoop;

template <class Sleutel,class Data>
class Binboom : public unique_ptr<Binknoop<Sleutel,Data>>{
public:
	using unique_ptr<Binknoop<Sleutel,Data>>::unique_ptr; 
    Binboom<Sleutel,Data>(){}  
    ~Binboom<Sleutel,Data>(){}
    
    Binboom<Sleutel,Data>(Binboom<Sleutel,Data>&& b):unique_ptr<Binknoop<Sleutel,Data>>(move(b)){
	}
	Binboom<Sleutel,Data>& operator=(Binboom<Sleutel,Data>&& b){
		unique_ptr<Binknoop<Sleutel,Data>>::operator=(move(b));   
		return *this;
	}
	 
    int diepte() const{
       if (!*this)
           return 0;
       else
           return max(*this->links.diepte(),*this->rechts.diepte())+1;
    };
    void schrijf(ostream& os){
		Binboom<Sleutel, Data>* tree = this;
		if(*tree!=nullptr){
			if((*tree)->links!=nullptr){
				if((*tree)->rechts!=nullptr){
					cout<<(*tree)->sl<<" ouder  met kinderen "<<(*tree)->links->sl<<", "<<(*tree)->rechts->sl<<endl;
					(*tree)->links.schrijf(os);
					(*tree)->rechts.schrijf(os);
				}
				else{
					cout<<(*tree)->sl<<" ouder  met linkerkind "<<(*tree)->links->sl<<endl;
					(*tree)->links.schrijf(os);
				}
			}
			else{
				if((*tree)->rechts!=nullptr){
					cout<<(*tree)->sl<<" ouder  met rechterkind "<<(*tree)->rechts->sl<<endl;
					(*tree)->rechts.schrijf(os);
				}
				else{
					cout<<(*tree)->sl<<" ouder  zonde kind "<<endl;
				}	
			}
			
		}
	}
    void schrijf(ostream& os,Binknoop<Sleutel,Data>* kn) const{
        if (kn!=0)
            os<<"("<<kn->sl<<","<<kn->data<<")";
        else
            os<<"(,)";
    }
    void roteer(bool links);
    
    void voeg_toe(Sleutel sl, Data data);
    void verwijder(Sleutel sl);
    void zoek(Sleutel sl,Binboom<Sleutel,Data>*& plaats, Binknoop<Sleutel,Data>*& ouder);
    void splay();
};

template <class Sleutel,class Data>
class Binknoop{
    public:
        Sleutel sl;
        Data data;
        Binknoop<Sleutel,Data>* ouder;
        Binboom<Sleutel,Data> links,rechts;
        Binknoop():ouder(0){}
        Binknoop(const Sleutel& _sl,const Data& _data):ouder(0),sl(_sl),data(_data){}
};

template <class Sleutel,class Data>
void Binboom<Sleutel,Data>::roteer(bool links){
	Binboom<Sleutel,Data> op;
    Binknoop<Sleutel,Data>* ouder;
	if(links){ 
		cout<<"roteer links"<<endl;
    	op = move((*this)->rechts);
    	(*this)->rechts = move(op->links);
    	if((*this)->rechts != nullptr)
    		(*this)->rechts->ouder = (*this).get();    		
    	op->links = move(*this);
    	op->links->ouder = op.get();
    	ouder = op->links->ouder;
	}
	else{
		cout<<"roteer rechts"<<endl;
		op = move((*this)->links);
    	(*this)->links = move(op->rechts);
    	if((*this)->links != nullptr)
    		(*this)->links->ouder = (*this).get();    		
    	op->rechts = move(*this);
    	op->rechts->ouder = op.get();
    	ouder = op->rechts->ouder;
	}
	*this = move(op);
	(*this)->ouder = ouder;
	cout<<"roteer klaar"<<endl;
}

template <class Sleutel,class Data>
void Binboom<Sleutel,Data>::zoek(Sleutel sl,Binboom<Sleutel,Data>*& plaats, Binknoop<Sleutel,Data>*& ouder){
	cout<<"zoek"<<endl;
	plaats=this;
    ouder=0;
    while (*plaats!=0 && (*plaats)->sl!=sl){
        ouder=plaats->get();
        if (sl < (*plaats)->sl)
            plaats=&((*plaats)->links);
        else
            plaats=&((*plaats)->rechts);
    }
    cout<<"gevonden"<<endl;
}

template <class Sleutel,class Data>
void Binboom<Sleutel,Data>::splay(){
	//fout in code:: moet normaal roteer oproepen op de ouder en niet op this
	//maar is methode van binboom en daar kan ik nie aan.
	while((*this)->ouder!=nullptr){
		if((*this)->ouder->ouder != nullptr && (*this)->ouder->ouder->links->sl == (*this)->ouder->sl){
			if((*this)->ouder->ouder == nullptr){
				roteer(false);
			}
			else{
				if((*this)->ouder->links->sl == (*this)->sl){
					(*this)->ouder->ouder->links.roteer(false);
					roteer(false);
				}
				else{
					roteer(true);
					(*this)->ouder->ouder->links.roteer(false);
				}
			}
		}
		else{
			if((*this)->ouder->ouder == nullptr){
				cout<<"grootouder is nullptr"<<endl;
				if((*this)->ouder->links!=nullptr && (*this)->ouder->links->sl == (*this)->sl){
					roteer(false);
				}
				else{
					roteer(true);
				}
			}
			else{
				if((*this)->ouder->rechts->sl == (*this)->sl){
					(*this)->ouder->ouder->rechts.roteer(true);
					roteer(true);
				}
				else{
					roteer(false);
					(*this)->ouder->ouder->rechts.roteer(true);
				}
			}
		}
	}
}

template <class Sleutel,class Data>
void Binboom<Sleutel,Data>::voeg_toe(Sleutel sl, Data data){
	Binboom<Sleutel, Data>* tree;
	Binknoop<Sleutel, Data>* knoop;
	zoek(sl, tree, knoop);
	Binboom<Sleutel, Data> nieuw(std::move(new Binknoop<Sleutel, Data>(sl,data)));
	nieuw->ouder=knoop;
	*tree = std::move(nieuw);
	cout<<"beginnen met splay"<<endl;
	tree->splay();
}
	
