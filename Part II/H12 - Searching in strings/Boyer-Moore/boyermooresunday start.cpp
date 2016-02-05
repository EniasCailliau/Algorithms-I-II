


void sundayInitocc()
{
    int j;
    char a;

    for (a=0; a<alphabetsize; a++)
        occ[a]=-1;

    for (j=0; j<m; j++)
    {
        a=p[j];
        occ[a]=j;
    }
void sundaySearch()
{
    int i=0;
    while (i<=n-m)
    {
        if (matchesAt(i)) report(i);
        i+=m;
        if (i<n) i-=occ[t[i]];
    }
}
