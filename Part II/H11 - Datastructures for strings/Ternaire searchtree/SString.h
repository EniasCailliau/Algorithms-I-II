#include <string>
#include <vector>
using namespace std;
class SString{
	public:
		SString(string s){
			woord= s;
		}
		vector<string> genereerwildcards();
	private:
		string woord;
	
};

vector<string> SString::genereerwildcards(){
	vector<string> result;
	for(int i=0 ; i<woord.size(); i++){
		string resultaat = woord;
		resultaat[i]='?';
		result.push_back(resultaat);
	}
	return result;
}
