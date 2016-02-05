#include <iostream>
#include <vector>
#include "printers.h"
using namespace std;

//----------------------------
//Returns a vector containing the zero based index of 
//  the start of each match of the string K in S.
//  Matches may overlap
// TODO: bekijken van algo andere
//----------------------------
vector<int> KMP(string S, string K)
{
    vector<int> T(K.size() + 1, -1);
	vector<int> matches;

        if(K.size() == 0)
        {
            matches.push_back(0);
            return matches;
        }
        T[1]=0;
	for(int i = 2; i <= K.size(); i++)
	{
		int j = T[i - 1];
		while(j != -1 && K[j] != K[i - 1]) j = T[j];
		T[i] = j + 1;
	}
	print(T);

	int j = 0;
	int i = 0;
	while(j < S.size())
	{
		while(i != -1 && (i == K.size() || K[i] != S[j])) i = T[i];
		i++;
		j++;
		if(i == K.size()) matches.push_back(j - K.size());
	}
	
	return matches;
}


int main(){
	
	vector<int> res = KMP("eeeabc","abc");
	printspecial("resultaat");
	print(res);
	return 1;
}
