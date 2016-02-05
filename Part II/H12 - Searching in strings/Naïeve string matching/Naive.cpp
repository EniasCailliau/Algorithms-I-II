#include<stdio.h>
#include<string.h>
void search(char *pat, char *txt)
{
    int p = strlen(pat);
    int t = strlen(txt);
 
    /* A loop to slide pat[] one by one */
    for (int j = 0; j <= t - p; j++)
    {
 		int i;
        /* For current index i, check for pattern match */
        for (i = 0; i < p; i++)
        {
            if (txt[j + i] != pat[i])
                break;
        }
        if (i == p) // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        {
            printf("Pattern found at index %d (length=%d)\n", j, p);
        }
    }
}
 
/* Driver program to test above function */
int main()
{
    char *txt = "AABAACAADAABAAABAA";
    char *pat = "AABA";
    search(pat, txt);
    return 0;
}
