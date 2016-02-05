/*
 * C++ Program to Implement Pairing Heap
 */
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
/*
 * Node Class Declaration
 */
 

class PairNode
{
    public:
        int element;
        PairNode *leftChild;
        PairNode *nextSibling;
        PairNode *prev;
        PairNode(int element)
        {
            this->element = element;
            leftChild = NULL;
            nextSibling = NULL;
            prev = NULL;
        }
        void print()const{
        	cout <<element<<"; ";
        	if(nextSibling){
        		nextSibling->print();
			}else{
				cout<<endl;
			}
			if(leftChild) {
				cout<<"ouder("<<element<<")"; 
				leftChild->print();
			}
		}
};
 
/*
 * Class Declaration
 */
template <class T>
class PairingHeap
{
    private:
        PairNode *root;
        void reclaimMemory(PairNode *t);
        void compareAndLink(PairNode * &first, PairNode *second);
        PairNode *combineSiblings(PairNode *firstSibling);
        PairNode *clone(PairNode *t);
    public:
    	void Print()const{
			if(root) root->print();
		}
        PairingHeap();
        PairingHeap(PairingHeap &rhs);
        ~PairingHeap();
        bool isEmpty();
        bool isFull();
        int &findMin();
        PairNode *Insert(int &x);
        void deleteMin();
        void deleteMin(int &minItem);
        void makeEmpty();
        void decreaseKey(PairNode *p, int &newVal );
        PairingHeap &operator=(PairingHeap &rhs);
};

 template <class T>
PairingHeap<T>::PairingHeap()
{
    root = NULL;
}

 template <class T>
PairingHeap<T>::PairingHeap(PairingHeap<T> & rhs)
{
    root = NULL;
    *this = rhs;
}
 
/*
 * Destroy the leftist heap.
 */
 template <class T>
PairingHeap<T>::~PairingHeap<T>()
{
    makeEmpty();
}
 
/*
 * Insert item x into the priority queue, maintaining heap order.
 * Return a pointer to the node containing the new item.
 */
 template <class T>
PairNode *PairingHeap<T>::Insert(int &x)
{
    PairNode *newNode = new PairNode(x);
    if (root == NULL)
        root = newNode;
    else
        compareAndLink(root, newNode);
    return newNode;
}
 
/*
 * Find the smallest item in the priority queue.
 * Return the smallest item, or throw Underflow if empty.
 */
 template <class T>
int &PairingHeap<T>::findMin()
{
    return root->element;
}
 
/*
 * Remove the smallest item from the priority queue.
 * Throws Underflow if empty.
 */
 template <class T>
void PairingHeap<T>::deleteMin()
{
    PairNode *oldRoot = root;
    if (root->leftChild == NULL)
        root = NULL;
    else
        root = combineSiblings(root->leftChild);
    delete oldRoot;
}
 
/*
 * Remove the smallest item from the priority queue.
 * Pass back the smallest item, or throw Underflow if empty.
 */
 template <class T>
void PairingHeap<T>::deleteMin(int &minItem)
{
    if (isEmpty())
    {
        cout<<"The Heap is Empty"<<endl;
        return;
    }
    minItem = findMin();
    deleteMin();
    cout<<"Minimum Element: "<<minItem<<" deleted"<<endl;
}
 
/*
 * Test if the priority queue is logically empty.
 * Returns true if empty, false otherwise.
 */
 template <class T>
bool PairingHeap<T>::isEmpty()
{
    return root == NULL;
}
 
/*
 * Test if the priority queue is logically full.
 * Returns false in this implementation.
 */
 template <class T>
bool PairingHeap<T>::isFull()
{
    return false;
}
 
/*
 * Make the priority queue logically empty.
 */
 template <class T>
void PairingHeap<T>::makeEmpty()
{
    reclaimMemory(root);
    root = NULL;
}
 
/*
 * Deep copy.
*/ template <class T>
PairingHeap<T> &PairingHeap<T>::operator=(PairingHeap<T> & rhs)
{
    if (this != &rhs)
    {
        makeEmpty( );
        root = clone(rhs.root);
    }
    return *this;
}
 
/*
 * Internal method to make the tree empty.
 */
 template <class T>
void PairingHeap<T>::reclaimMemory(PairNode * t)
{
    if (t != NULL)
    {
        reclaimMemory(t->leftChild);
        reclaimMemory(t->nextSibling);
        delete t;
    }
}
 
/*
 * Change the value of the item stored in the pairing heap.
 * Does nothing if newVal is larger than currently stored value.
 * p points to a node returned by insert.
 * newVal is the new value, which must be smaller
 *    than the currently stored value.
 */
 template <class T>
void PairingHeap<T>::decreaseKey(PairNode *p, int &newVal)
{
    if (p->element < newVal)
        return;
    p->element = newVal;
    if (p != root)
    {
        if (p->nextSibling != NULL)
            p->nextSibling->prev = p->prev;
        if (p->prev->leftChild == p)
            p->prev->leftChild = p->nextSibling;
        else
            p->prev->nextSibling = p->nextSibling;
            p->nextSibling = NULL;
            compareAndLink(root, p);
    }
}
 
/*
 * Internal method that is the basic operation to maintain order.
 * Links first and second together to satisfy heap order.
 * first is root of tree 1, which may not be NULL.
 *    first->nextSibling MUST be NULL on entry.
 * second is root of tree 2, which may be NULL.
 * first becomes the result of the tree merge.
 */
 template <class T>
void PairingHeap<T>::compareAndLink(PairNode * &first, PairNode *second)
{
    if (second == NULL){
    	return;
	}
//      second->element < first->element  
    T t; 
    if (t(second,first))
    {
        second->prev = first->prev;
        first->prev = second;
        first->nextSibling = second->leftChild;
        if (first->nextSibling != NULL)
            first->nextSibling->prev = first;
        second->leftChild = first;
        first = second;
    }
    else
    {
        second->prev = first;
        first->nextSibling = second->nextSibling;
        if (first->nextSibling != NULL)
            first->nextSibling->prev = first;
        second->nextSibling = first->leftChild;
        if (second->nextSibling != NULL)
            second->nextSibling->prev = second;
        first->leftChild = second;
    }
}
 
/*
 * Internal method that implements two-pass merging.
 * firstSibling the root of the conglomerate;
 *     assumed not NULL.
 */
  template <class T>

PairNode *PairingHeap<T>::combineSiblings(PairNode *firstSibling)
{
    if (firstSibling->nextSibling == NULL)
        return firstSibling;
    static vector<PairNode *> treeArray(5);
    int numSiblings = 0;
    for (; firstSibling != NULL; numSiblings++)
    {
        if (numSiblings == treeArray.size())
            treeArray.resize(numSiblings * 2);
        treeArray[numSiblings] = firstSibling;
        firstSibling->prev->nextSibling = NULL;
        firstSibling = firstSibling->nextSibling;
    }
    if (numSiblings == treeArray.size())
        treeArray.resize(numSiblings + 1);
    treeArray[numSiblings] = NULL;
    int i = 0;
    for (; i + 1 < numSiblings; i += 2)
        compareAndLink(treeArray[i], treeArray[i + 1]);
    int j = i - 2;
    if (j == numSiblings - 3)
        compareAndLink (treeArray[j], treeArray[j + 2]);
    for (; j >= 2; j -= 2)
        compareAndLink(treeArray[j - 2], treeArray[j] );
    return treeArray[0];
}
 
/*
 * Internal method to clone subtree.
 */
  template <class T>
PairNode *PairingHeap<T>::clone(PairNode * t)
{
    if (t == NULL)
        return NULL;
    else
    {
        PairNode *p = new PairNode(t->element);
        if ((p->leftChild = clone( t->leftChild)) != NULL)
            p->leftChild->prev = p;
        if ((p->nextSibling = clone( t->nextSibling)) != NULL)
            p->nextSibling->prev = p;
        return p;
    }
}
 
/*
 * Main Contains Menu
 */

