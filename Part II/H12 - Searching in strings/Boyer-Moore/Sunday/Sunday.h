//#include <string.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
/**
 
 */
vector<int> sundaySearch(const string & tekst,
                         const string & patroon)
{
    vector<int> result;        // Vector to hold return value
    int t = tekst.size();
    int p = patroon.size();

    // Handle trivial case: zero-length pattern always matches
    if (p == 0){
        result.push_back(0);
        cout<<"hier"<<endl;
        return result;
    }
    // Handle trivial case: pattern is bigger then text
    if(p > t){
    	cout<<"hier"<<endl;
    	return result;
	}

    // Make bad-symbol shift table
    vector<size_t> badsymbol(256, p);  // 256 possible char values
    for (int i = 0; i < p; ++i)
    {
        badsymbol[patroon[i]] = p - i;
    }

    // Do the search from the beginning of the text
    int j = 0;  // loc is current search location in text
    while (j <= (t - p)){
        // Check match against pattern right-to-left
        int i = p-1;
        while (tekst[j+i] == patroon[i] && i!= 0){ --i;}
           
           
        if (i == 0){  // Found! Return location
                result.push_back(j);
                return result;
        }
        char c = tekst[j+p];
        j += badsymbol[c];
    }

    // Return not-found result
    return result;
}
