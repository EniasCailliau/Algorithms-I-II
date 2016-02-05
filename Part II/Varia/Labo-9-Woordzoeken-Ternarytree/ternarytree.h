#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#define MAX 50

using namespace std;

struct Node
{
	int id = 0;
    char data;
    unsigned isEndOfString: 1;
    Node *left, *eq, *right;
    vector<string> gevonden;
};

class TernaryTree {
	
	public:		
		void insert(const char *);
		int searchTST(char *word);
		void traverseTST();
		void searchMetSterretje(Node *, char *, vector<string> &, int , char* ,vector<bool> &);
		void searchMetSterretje(char*, vector<string> &);
		
		int aantal_knopen = 0;
	
	
	private:	
		void insert(Node** root, const char *word);
		Node* newNode(char data);	
		int searchTST(Node *root, char *word);
		Node* root = NULL;
		void traverseTSTUtil(Node* root, char* buffer, int depth);

};

/* 
 * traverse Utility function
 */  
void TernaryTree::traverseTSTUtil(Node* root, char* buffer, int depth)
{
    if (root)
    {
        traverseTSTUtil(root->left, buffer, depth);
        buffer[depth] = root->data;
        if (root->isEndOfString)
        {
            buffer[depth + 1] = '\0';
            cout<<buffer<<endl;
        }
        traverseTSTUtil(root->eq, buffer, depth + 1);
        traverseTSTUtil(root->right, buffer, depth);
    }
}
/* 
 * traverse Ternary Search Tree
 */  
void TernaryTree::traverseTST()
{
    char buffer[MAX];
    traverseTSTUtil(root, buffer, 0);
}

void TernaryTree::insert(const char * word){
	
	insert(&root, word);
} 

void TernaryTree::insert(Node** root, const char *word)
{
    if (!(*root)){
    	
    	*root = newNode(*word);
    	
    }
        
    if ((*word) < (*root)->data)
        insert(&((*root)->left), word);
    else if ((*word) > (*root)->data)
        insert(&((*root)->right), word);
    else
    {
        if (*(word + 1))
            insert(&( (*root)->eq ), word + 1);
        else
            (*root)->isEndOfString = 1;
    }
}

Node* TernaryTree::newNode(char data) {
	Node* temp = new Node;
    temp->data = data;
    temp->id = aantal_knopen++;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}

int TernaryTree::searchTST(char *word){
	searchTST(root, word);
}

int TernaryTree::searchTST(Node *root, char *word)
{
    if (!root)
        return 0;
    if (*word < (root)->data)
        return searchTST(root->left, word);
    else if (*word > (root)->data)
        return searchTST(root->right, word);
    else
    {
        if (*(word + 1) == '\0')
            return root->isEndOfString;
        return searchTST(root->eq, word+1);
    }
}

void TernaryTree::searchMetSterretje(Node *node, char *word, vector<string> &result, int sterretjes, char* afdaalwoord, vector<bool> & gepasseerd)
{
	if (node){
		char afdaalwoordvolgende[strlen(afdaalwoord) + 1];
		strcpy(afdaalwoordvolgende, afdaalwoord);
		//cout << "Huidig afdaalwoord: "<< afdaalwoordvolgende <<endl;
		
		char afdaalwoordvolgendeextra[strlen(afdaalwoordvolgende) + 1];
		strcpy(afdaalwoordvolgendeextra, afdaalwoordvolgende);
		
		char extrachar[] = {(node)->data, '\0'};
		
		strcat(afdaalwoordvolgendeextra, extrachar);
    
    	if(sterretjes>0){
    		//cout << "Er zijn nog sterretjes"<<endl;
    		//cout << "Sterretje midden:"<<endl;
    		searchMetSterretje(node->eq, word+1, result, sterretjes -1, afdaalwoordvolgendeextra,gepasseerd);
    		//cout << "Sterretje links:"<<endl;
    		searchMetSterretje(node->left, word, result, sterretjes, afdaalwoordvolgende,gepasseerd);
    		//cout << "Sterretje rechts:"<<endl;
    		searchMetSterretje(node->right, word, result, sterretjes, afdaalwoordvolgende,gepasseerd);
    		
    		if(*(word + 1) == '\0' && node->isEndOfString && !gepasseerd[node->id]){
    			cout << "\t Toevoegen bij sterretjes: " <<afdaalwoordvolgendeextra << " \n";
    			gepasseerd[node->id] = true;
    			result.push_back(afdaalwoordvolgendeextra);
    		}
    		
    	}
    	
	    if (*word < (node)->data) {
	    	//cout << "Gaat links " << endl;
    		searchMetSterretje(node->left, word, result, sterretjes, afdaalwoordvolgende,gepasseerd);
	    }
	    else if (*word > (node)->data) {
	    	//cout << "Gaat rechts " << endl;
    		searchMetSterretje(node->right, word, result, sterretjes, afdaalwoordvolgende,gepasseerd);
	    }
	    else
	    {
	    	//cout << "Gaat Midden"  << endl;
			if(*(word + 1) == '\0'){
	        	if(node->isEndOfString && !gepasseerd[node->id]){	        		
	        		//cout << "\tEinde woord \n";
	        		gepasseerd[node->id] = true;
	        		result.push_back(afdaalwoordvolgendeextra);
	        		cout << "\t Toevoegen: " <<afdaalwoordvolgendeextra << " \n";

	        	}
	        } else {
	        	//cout << "\tNiet einde, zoek verder. " << endl;
    			searchMetSterretje(node->eq, word+1, result, sterretjes, afdaalwoordvolgendeextra,gepasseerd);
	        }
	    }
    }

}

void TernaryTree::searchMetSterretje(char* string, std::vector<std::string> &result) {
	vector<bool> gepasseerd(aantal_knopen);
	searchMetSterretje(root, string, result, 1, "",gepasseerd);
}

