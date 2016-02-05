#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define ALPHABET_LEN 256
#define NOT_FOUND patlen
#define max(a, b) ((a < b) ? b : a)

int is_prefix(string word, int pos) {
    int i;
    int suffixlen = word.length() - pos;
    // could also use the strncmp() library function here
    for (i = 0; i < word.length(); i++) {
        if (word[i] != word[pos+i]) {
            return 0;
        }
    }
    return 1;
}

int suffix_length(string word, int pos) {
	int wordlen = word.length();
    int i;
    // increment suffix length i to the first mismatch or beginning
    // of the word
    for (i = 0; (word[pos-i] == word[wordlen-1-i]) && (i < pos); i++);
    return i;
}

vector<int> make_delta2(string pat) {
	vector<int> res(pat.length());
    int p;
    int patlen = pat.length();
    int last_prefix_index = patlen-1;
    // first loop
    for (p=patlen-1; p>=0; p--) {
        if (is_prefix(pat, p+1)) {
            last_prefix_index = p+1;
        }
        res[p] = last_prefix_index + (patlen-1 - p);
    }

    // second loop
    for (p=0; p < patlen-1; p++) {
        int slen = suffix_length(pat, p);
        if (pat[p - slen] != pat[patlen-1 - slen]) {
            res[patlen-1 - slen] = patlen-1 - p + slen;
        }
    }
    return res;
}
 int[] makeOffsetTable(char[] needle) {
        int[] table = new int[needle.length];
        int lastPrefixPosition = needle.length;
        for (int i = needle.length - 1; i >= 0; --i) {
            if (isPrefix(needle, i + 1)) {
                lastPrefixPosition = i + 1;
            }
            table[needle.length - 1 - i] = lastPrefixPosition - i + needle.length - 1;
        }
        for (int i = 0; i < needle.length - 1; ++i) {
            int slen = suffixLength(needle, i);
            table[slen] = needle.length - 1 - i + slen;
        }
        return table;
    }
    
    /**
     * Is needle[p:end] a prefix of needle?
     */
    private static boolean isPrefix(char[] needle, int p) {
        for (int i = p, j = 0; i < needle.length; ++i, ++j) {
            if (needle[i] != needle[j]) {
                return false;
            }
        }
        return true;
    }
    
    /**
     * Returns the maximum length of the substring ends at p and is a suffix.
     */
    private static int suffixLength(char[] needle, int p) {
        int len = 0;
        for (int i = p, j = needle.length - 1;
                 i >= 0 && needle[i] == needle[j]; --i, --j) {
            len += 1;
        }
        return len;
    }
int main(){
	string pat = "ATAATGATGAT";
    vector<int> res = make_delta2(pat);
    for(int i=0; i<pat.length(); i++){
    	cout<<res[i]<<" ";
	}
	cout<<endl;
	
	return 0;
}
