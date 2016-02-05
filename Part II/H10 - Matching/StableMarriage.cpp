#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;
 
const char *men_data[][11] = {
    { "abe",  "abi","eve","cath","ivy","jan","dee","fay","bea","hope","gay" },
    { "bob",  "cath","hope","abi","dee","eve","fay","bea","jan","ivy","gay" },
    { "col",  "hope","eve","abi","dee","bea","fay","ivy","gay","cath","jan" },
    { "dan",  "ivy","fay","dee","gay","hope","eve","jan","bea","cath","abi" },
    { "ed",   "jan","dee","bea","cath","fay","eve","abi","ivy","hope","gay" },
    { "fred", "bea","abi","dee","gay","eve","ivy","cath","jan","hope","fay" },
    { "gav",  "gay","eve","ivy","bea","cath","abi","dee","hope","jan","fay" },
    { "hal",  "abi","eve","hope","fay","ivy","cath","jan","bea","gay","dee" },
    { "ian",  "hope","cath","dee","gay","bea","abi","fay","ivy","jan","eve" },
    { "jon",  "abi","fay","jan","gay","eve","bea","dee","cath","ivy","hope" }
};
 
const char *women_data[][11] = {
    { "abi",  "bob","fred","jon","gav","ian","abe","dan","ed","col","hal" },
    { "bea",  "bob","abe","col","fred","gav","dan","ian","ed","jon","hal" },
    { "cath", "fred","bob","ed","gav","hal","col","ian","abe","dan","jon" },
    { "dee",  "fred","jon","col","abe","ian","hal","gav","dan","bob","ed" },
    { "eve",  "jon","hal","fred","dan","abe","gav","col","ed","ian","bob" },
    { "fay",  "bob","abe","ed","ian","jon","dan","fred","gav","col","hal" },
    { "gay",  "jon","gav","hal","fred","bob","abe","col","ed","dan","ian" },
    { "hope", "gav","jon","bob","abe","ian","dan","hal","ed","col","fred" },
    { "ivy",  "ian","col","hal","gav","fred","bob","abe","ed","jon","dan" },
    { "jan",  "ed","hal","gav","abe","bob","jon","col","ian","fred","dan" }
};
 
typedef vector<string> PrefList;
typedef map<string, PrefList> PrefMap;
typedef map<string, map<string, int>> PrefMapSnel;
typedef map<string, string> Couples;
 
// Does 'first' appear before 'second' in preference list?
bool prefers(map<string, int> &prefer, const string &first, const string &second)
{
//    for (PrefList::const_iterator it = prefer.begin(); it != prefer.end(); ++it)
//    {
//        if (*it == first) return true;
//        if (*it == second) return false;
//    }
	if(prefer[first] < prefer[second]) return true;
    return false; // no preference
}
 
void check_stability(const Couples &engaged, const PrefMap &men_pref, const PrefMap &women_pref, map<string,map<string, int>> &women_pref_snel, map<string, map<string, int>> & men_pref_snel)
{
    cout << "Stablility:\n";
    bool stable = true;
    for (Couples::const_iterator it = engaged.begin(); it != engaged.end(); ++it)
    {
        const string &bride = it->first;
        const string &groom = it->second;
        // ophalen preflist man
        const PrefList &preflist = men_pref.at(groom);
 
        PrefList::const_iterator it_ = preflist.begin();
// When equal to bride, only worse marriages possible => Not relevant to check
// Controleren vanuit mannen.
        while(it_ != preflist.end() && *it_!= bride){
        	if (prefers(men_pref_snel[groom], *it_, bride) && // he prefers another woman
                prefers(women_pref_snel.at(*it_), groom, engaged.at(*it_))) // other woman prefers him
            {
                cout << "\t" << *it_ <<
                    " prefers " << groom <<
                    " over " << engaged.at(*it_) <<
                    " and " << groom <<
                    " prefers " << *it_ <<
                    " over " << bride << "\n";
                stable = false;
            } 
			it_++;	
		}   
    }
    
    if (stable) cout << "\t(all marriages stable)\n";
}
 
int main()
{
    PrefMap men_pref, women_pref;
    PrefMapSnel men_pref_snel, women_pref_snel;
    queue<string> bachelors;
 	map<string, PrefList::const_iterator> bachelor_proposals_pos;
    // init data structures
    for (int i = 0; i < 10; ++i){ //f.e. person
        for (int j = 1; j < 11; ++j){ // register preference
            men_pref[  men_data[i][0]].push_back(  men_data[i][j]);
            men_pref_snel[men_data[i][0]][men_data[i][j]] = j;
            women_pref[women_data[i][0]].push_back(women_data[i][j]);
            women_pref_snel[women_data[i][0]][women_data[i][j]] = j;

        }
        bachelors.push(men_data[i][0]); // een lijst met singles
        bachelor_proposals_pos[men_data[i][0]] = men_pref[  men_data[i][0]].begin();
    }
 
    Couples engaged; // <woman,man>
 
    cout << "Matchmaking:\n";
    while (!bachelors.empty()){
        const string &suitor = bachelors.front();
        const PrefList &preflist = men_pref[suitor];
		PrefList::const_iterator it = bachelor_proposals_pos[suitor];
		bool matched = false;
 		while(it != preflist.end() && !matched){
			const string &bride = *it;
// 			cout<<suitor<<" vraagt "<<bride<<endl;
 
            if (engaged.find(bride) == engaged.end()) {
//                cout << "\t" << bride << " and " << suitor << "\n";
                engaged[bride] = suitor; // hook up
				matched=true;
            }else{
              	const string &groom = engaged[bride];
	            if (prefers(women_pref_snel[bride], suitor, groom)){
//	                cout << "\t" << bride << " dumped " << groom << " for " << suitor << "\n";
	                bachelors.push(groom); // dump that zero
	                engaged[bride] = suitor; // get a hero
	                matched= true;
	            }	
			}
 
          	it++;
 			bachelor_proposals_pos[suitor] = it;
		 }

        bachelors.pop(); // pop at the end to not invalidate suitor reference
    }
    cout << "Engagements:\n";
    for (Couples::const_iterator it = engaged.begin(); it != engaged.end(); ++it)
    {
        cout << "\t" << it->first << " and " << it->second << "\n";
    }
 
    check_stability(engaged, men_pref, women_pref, women_pref_snel, men_pref_snel);
 
    cout << "Perturb:\n";
    std::swap(engaged["abi"], engaged["bea"]);
    cout << "\tengage abi with " << engaged["abi"] << " and bea with " << engaged["bea"] << "\n";
 
    check_stability(engaged, men_pref, women_pref, women_pref_snel, men_pref_snel);
}
