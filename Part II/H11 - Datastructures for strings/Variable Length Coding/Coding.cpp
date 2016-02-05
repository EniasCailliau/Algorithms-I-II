// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include "printers.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>
#include <stack>


using std::stack;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::vector;

string trans_int_to_binary(int decimal);
int trans_binary_to_int(const string& binary);

string encode_eliasgamma(const int& A){
	string binary = trans_int_to_binary(A);
    binary.insert(0, binary.size() - 1, '0');  // prepend 0s.
    return binary;
}
string encode(const vector<int>& A) {
  string ret;
  for (const int& a : A) {
    string binary = trans_int_to_binary(a);
    binary.insert(0, binary.size() - 1, '0');  // prepend 0s.
    ret += encode_eliasgamma(a);
  }
  return ret;
}

string encode_delta(const int& a){
	string binary = trans_int_to_binary(a);
	string eliasgamma = encode_eliasgamma(binary.size());
	return eliasgamma + binary.substr(1);
}


string encode_delta(const vector<int>& v){
	string ret;
	for(const int& a : v){
		string binary = trans_int_to_binary(a);
		string eliasgamma = encode_eliasgamma(binary.size());
		ret += encode_delta(a);
	}
	return ret;
}

using namespace std;
 
string encode_fibbo(int& a){
	int getal = a;
   int n, c, first = 1, second = 1, next=1;
   stack<int> st;
	while(next <= a){
		st.push(next);
         next = first + second;
         first = second;
         second = next;
    }
   string codewoord;
   while(!st.empty()){
   		int fk = st.top();
   		st.pop();
   		if(getal-fk >= 0){
   			getal-=fk;
   			codewoord.push_back('1');
		}else{
			codewoord.push_back('0');
		}
   }
//   reverse(codewoord.begin(), codewoord.end());   	
   codewoord.push_back('1');

   return codewoord;
}

string trans_int_to_binary(int decimal) {
  string ret;
  while (decimal) {
    ret.push_back('0' + (decimal & 1));
    decimal >>= 1;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

vector<int> decode(const string& s) {
  vector<int> ret;
  int idx = 0;
  while (idx < s.size()) {
    // Count the number of consecutive 0s.
    int zero_idx = idx;
    while (zero_idx < s.size() && s[zero_idx] == '0') {
      ++zero_idx;
    }

    int len = zero_idx - idx + 1;
    ret.emplace_back(trans_binary_to_int(s.substr(zero_idx, len)));
    idx = zero_idx + len;
  }
  return ret;
}

int trans_binary_to_int(const string& binary) {
  int ret = 0;
  for (const char& c : binary) {
    ret = (ret << 1) + c - '0';
  }
  return ret;
}
// @exclude

int main(int argc, char* argv[]) {
  vector<int> v;
  v.push_back(9);

  string ret = encode(v);
  cout << ret << endl;


	printspecial("uittesten van elias delta");
	int getal = 9;
	vector<int> w;
	w.push_back(getal);
	ret = encode_delta(w);
	cout<< ret <<endl;
	printspecial("uittesten van fibonacci code");
	getal = 45
	;
	vector<int> y;
	y.push_back(getal);
	ret = encode_fibbo(getal);
	cout<<ret<<endl;
	printspecial("testen van pushback");
	string test = "test";
	cout<<test<<endl;
	test.push_back('f');
	cout<<test<<endl;
	test.insert(0,3,'a');
	cout<<test<<endl;
  
  
  
  return 0;
}
