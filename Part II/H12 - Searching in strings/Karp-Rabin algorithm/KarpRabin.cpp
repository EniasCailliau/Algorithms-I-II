/*
 * C++ Program to Implement Rabin-Karp Algorithm
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;
#define d 256
/*

INFO:
h= hergebruik van d^(p-1) mod r 
d= aantal verschillende karakters is alfabet
t0 en p0 worden niet O(1) berekent
tj wordt berekent in O(1)
 */
void search(string pat, string txt, int r)
{
    int p = pat.length();
    int t = txt.length();
    int i, j;
    int p0 = 0;
    int t0 = 0;

    int h = 1;
    // start berekening van h
    for (i = 0; i < p - 1; i++){
    	h = (h * d) % r;
	}
	// start berekening van p0 en t0
    for (i = 0; i < p; i++){
        p0 = (d * p0 + pat[i]) % r;
        t0 = (d * t0 + txt[i]) % r;
    }
    int tj = t0;
	// alle getallen met radix r vergelijken
    for (i = 0; i <= t - p; i++){
        if (p0 == tj){
        	// controle indien beide strings ook effectief gelijk zijn
        	int j=0;
        	while(j<p && txt[i+j] == pat[j]){
        		j++;
			}
            if (j == p){
                cout<<"Pattern found at index: "<<i<<endl;
            }
        }
        if (i < t - p){
            tj = ((tj - txt[i] * h)*d + txt[i + p]) % r;
            // rekening houden dat programmatorisch gezien een module negatief resultaat kan hebben
            if (tj < 0){
            	tj = (tj + r);
			}
        }
    }
}
 
/* Main */
int main()
{
    string txt = "Sanfoundry Linux Training";
    string pat = "nux";
    int q = 101;
    search(pat, txt, q);
    return 0;
}
