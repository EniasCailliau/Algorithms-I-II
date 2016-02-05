#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
#include <vector>
using std::vector;

/*
	Deze implementatie gebruikt een aangepaste formule, per direct verschuiving afleesbaar 
	Normaal: p-1-j met j = occ[T[k+p-1]]
*/

// hStrMatch
// String matching - Horspool's Algorithm
// [Remainder of documentation identical to function bfStrMatch]
vector<int> hStrMatch(const string & tekst,
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
    for (int i = 0; i < p-1; ++i)
    {
        badsymbol[patroon[i]] = p - 1 - i;
    }

    // Do the search from the beginning of the text
    int j = 0;  // loc is current search location in text
    while (j <= (t - p)){
        // Check match against pattern right-to-left
        int i = p-1;
        while (tekst[j+i] == patroon[i] && i!= 0){ --i;}
           
           
        if (i == 0){  // Found! Return location
                result.push_back(j);
//                return result;
        }
        char c = tekst[j+p-1];
        j += badsymbol[c];
    }

    // Return not-found result
    return result;
}

// testMatch
// Test String matching functions bfStrMatch, hStrMatch on given text,
//  pattern. Print pattern & then output for each function, followed by
//  a blank line.
void testMatch(const string & text, const string & pattern)
{
    // Print pattern
    cout << "Pattern: [" << pattern << "]" << endl;

    // Print Horspool's Algorithm results
    vector<int> hresult =
        hStrMatch(text, pattern);
    cout << "Horspool's:  ";
    if (hresult.empty())
        cout << "NO match" << endl;
    else
        cout << "MATCH - " <<endl;
	for(int i=0; i<hresult.size(); i++){
		cout<<hresult[i] << endl;
	}	

    // End with a blank line
    cout << endl;
}


// Main program
// Test string matching functions using function testMatch
int main()
{
    // Text to search in
    string text = "dit is een cococo  string";
    cout << "Text: [" << text << "]" << endl;
    cout << endl;

    // Test 1
    testMatch(text, "coco");
    
    cout << "Press ENTER to quit ";
    while (cin.get() != '\n') ;

    return 0;
}
