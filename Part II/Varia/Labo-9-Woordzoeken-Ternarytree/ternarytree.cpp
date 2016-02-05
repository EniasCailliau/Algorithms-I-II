/* 
 * C++ Program to Implement Ternary Seach Tree
 */
#include <iostream>
#include <cstdlib>
#include <vector>
#include "ternarytree.h"
#include <fstream>
#define MAX 50
using namespace std;
 

 
/* 
 * Main
 */  
int main()
{
	/*TernaryTree kap;
	
	ifstream file;
	file.open ("kapitaal.txt");
	string word;
	while(file >> word){
		kap.insert(word.c_str());
	}
	
	*/
	
	TernaryTree t;

	ifstream bib;
	bib.open ("bible.txt");
	string word;
	while(bib >> word){
		t.insert(word.c_str());
	}	
	
	vector<string> v;
	
	t.searchMetSterretje("het", v);
	
	cout << v.size() << endl;
	
	for(int i = 0; i < v.size();i++){
		cout << v[i] << " ";
	}
	cout << endl;
    return 0;
}
