#include <memory>
#include <iostream>

using namespace std;

template <class T>
class Node;

template <class T>
class LinkedList : private unique_ptr<Node<T>>{
	using unique_ptr<Node<T>>::unique_ptr;
	public:
		void insert(int pos, LinkedList<T>&& lijst){
			LinkedList<T>* loper = this;
			for(int i=0; i<pos; i++){
				loper= &(loper->get()->volgende);
			}
		}
		void add(const T& data){
			LinkedList<T> back = std::move(*this);
			*this = std::move(unique_ptr<Node<T>>(new Node<T>(data)));
			(*this)->volgende = std::move(back);
		}
		void schrijf(ostream& os)const{
			const LinkedList<T>* loper = this;
			while(*loper){
				os<<loper->get()->data<<"; ";
				loper = &(loper->get()->volgende);
			}
			os<<endl;
		}
		bool empty()const{
			return *this == nullptr;
		}
	
};


template <class T>
class Node{
	friend class LinkedList<T>;
	public:
		Node(const T& data_){
			data = data_;
		}
		
	public:
		LinkedList<T> volgende;
		T data;
		
};
