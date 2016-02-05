#include "binary_tree_rep.h"

int main(){
	
	Node<int> node(5,new Node<int>(1,nullptr,new Node<int>(2,nullptr,new Node<int>(3,new Node<int>(5,nullptr, new Node<int>(6,nullptr,nullptr)),nullptr))),nullptr);
	node.schrijf_inorder(cout);
	
	return 0;
}
