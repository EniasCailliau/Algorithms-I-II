#include <stdio.h>
#include <stdlib.h>
#include "printers.h"
#include "Sunday.h"

using namespace std;
 
int main(){
    int i;
    string src="test in text";
    string sub="text";
    vector<int> res = sundaySearch(src,sub);
    if(!res.empty()){
        cout<< res[0]<<endl;
	
	}
    
//    char* r=sunday_search(src,-1,sub,-1);
//    if(r) printf("%s\n",r);
//    else printf("not found\n");
//    src=(char*) malloc(8196000);
//    srand(1234567);
//    for(i=0;i<8196000;i++){
//        src[i]=rand()%256;
//    }
//    sub=(char*) malloc(1024000);
//    for(i=0;i<1024000;i++){
//        sub[i]=src[1234567+i];
//    }
//    r=sunday_search(src,8196000,sub,1024000);
//    if(r) printf("%d\n",r-src);
//    else printf("not found\n");
//    free(src);
//    free(sub);
}
