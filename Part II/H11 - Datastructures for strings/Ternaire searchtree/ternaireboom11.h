//Ternaire boom zonder data
//afsluitsymbool: |, verondersteld groter te zijn dan alle letters
#ifndef __TERNAIREBOOM
#define __TERNAIREBOOM
#include <iostream>
#include <string>
#include <memory>
using std::ostream;
using std::istream;
using std::string;
using std::unique_ptr;
class Tboom;
class Tknoop;

using namespace std;

const char eind='|';



class Tboom: public unique_ptr<Tknoop>{
public:
    using unique_ptr<Tknoop>::unique_ptr;
    void voegtoe(const string&);
    void schrijf(ostream&);
    friend ostream& operator<<(ostream& os,Tboom& t){
        t.schrijf(os);
        return os;
    }
public:
//index wijst naar eerste letter die niet gevonden is
//geen const: anders castingproblemen
//s moet al aangevuld zijn met het afsluitteken.
//s
    void zoek(const string& s,int& index, Tboom*& tboom) ;
    void traverseTST();
    void traverseTSTUtil(char* buffer, int depth);
    void zoekgelijkenden(string buffer);
    void zoekgelijkenden(string buffer,string naald, int depth);


};
class Tknoop{
    friend class Tboom;
    char c;
//    string eind;
    Tboom kind[3];
    bool heeftzijkind(){
        return !kind[0] || !kind[2];
    }
    bool heeftkind(){
        return heeftzijkind() || kind[1];
    }
};

void Tboom::zoek(const string& s,int& index, Tboom*& boom){
    boom=this;
    index=0;
    //noot: als index==s.size() dan wordt automatisch *boom nul
    while (*boom){
        if ((*boom)->c == s[index]){
            index++;
            boom=&((*boom)->kind[1]);
        }
        else if ((*boom)->c > s[index])
            boom=&((*boom)->kind[0]);
        else
            boom=&((*boom)->kind[2]);
    }
    
}

void Tboom::voegtoe(const string& s){
    Tboom* plaats;
    int index;
    string z=s+eind;
    zoek(z,index,plaats);
    //noot: als z al in de boom zit is index==z.size() en gebeurt er niets
    int extra=z.size()-index;
    while (index<z.size()){
        *plaats=unique_ptr<Tknoop>(new Tknoop);
        (*plaats)->c=z[index++];
        plaats=&(*plaats)->kind[1];
    }
    std::cerr<<s<<" toegevoegd met "<<extra<<" nieuwe knopen\n";
}
void Tboom::schrijf(ostream& os){
    if (*this){
        Tknoop* wortel=this->get();
        os<<(*this)->c;
        if (wortel->heeftkind()){
            if (wortel->heeftzijkind())
                os<<"{ links : "<<wortel->kind[0]<<" midden["<<wortel->c <<"] &"<<wortel->kind[1]<<"rechts ["<<(*this)->c <<"]"<<wortel->kind[2]<<"}\n";
            else
                os<<"{\n"<<wortel->kind[1]<<"}\n";
        }
    }
}

void Tboom::traverseTSTUtil(char* buffer, int depth){
    if (*this)
    {
        this->get()->kind[0].traverseTSTUtil(buffer, depth);
 
        // Store the character of this node
        buffer[depth] = this->get()->c;
        if (this->get()->c == eind)
        {
            buffer[depth+1] = '\0';
            printf( "%s\n", buffer);
        }
        // Traverse the subtree using equal pointer (middle subtree)
        this->get()->kind[1].traverseTSTUtil(buffer, depth + 1);
 
        // Finally Traverse the right subtree
        this->get()->kind[2].traverseTSTUtil(buffer, depth);
    }
}

void Tboom::traverseTST()
{
    char buffer[50];
    traverseTSTUtil(buffer, 0);
}


void Tboom::zoekgelijkenden(string buffer,string naald, int depth){
    if (*this && (this->get()->c == naald[depth] || naald[depth] == '?') )
    {
    	
      	this->get()->kind[0].zoekgelijkenden(buffer, naald, depth);
 
        // Store the character of this node
        buffer[depth] = this->get()->c;
        if (this->get()->c == eind)
        {
            buffer[depth+1] = '\0';
            cout<< buffer<<endl;
        }
        // Traverse the subtree using equal pointer (middle subtree)
  		      this->get()->kind[1].zoekgelijkenden(buffer, naald, depth + 1);
 
        // Finally Traverse the right subtree
       		 this->get()->kind[2].zoekgelijkenden(buffer, naald, depth);
    }
}

void Tboom::zoekgelijkenden(string naald)
{
    string buffer;
    zoekgelijkenden(buffer,naald, 0);
}




#endif
    
