#include <iostream>
#include "MultiwayTrie.h"

using namespace std;

int main()
{
    Trie* trie = new Trie();
    trie->addWord("Hello");
    trie->addWord("Balloon");
    trie->addWord("Ball");

    if ( trie->searchWord("Hell") )
        cout << "Found Hell" << endl;

    if ( trie->searchWord("Hello") )
        cout << "Found Hello" << endl;

    if ( trie->searchWord("Helloo") )
        cout << "Found Helloo" << endl;

    if ( trie->searchWord("Ball") )
        cout << "Found Ball" << endl;

    if ( trie->searchWord("Balloon") )
        cout << "Found Balloon" << endl;

    delete trie;
}
