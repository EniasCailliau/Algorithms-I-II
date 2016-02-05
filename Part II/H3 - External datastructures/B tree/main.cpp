#include "btree.h"
#include "schijf.h"
#include "printers.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// gebruikte sleutel, kan een klasse zijn maar struct werkt ook.
struct Woord {
    string w;
    // vergelijkingsoperator (kleiner dan)
    bool operator<(const Woord &t) const {
        int o = w.compare(t.w);
        return (o < 0) ? true : false;
    }

    bool operator==(const Woord &t) const {
        int o = w.compare(t.w);
        return (o == 0);
    }
};

int main() {

    Schijf<Bknoop<Woord, int, 666> > schijf;
    Btree<Woord, int, 666> tree(schijf);

    ifstream ifile;
    ifile.open("bible.txt");
    if (!ifile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    string woord;
    ifile >> woord;
    while (!ifile.fail()) {
    	cout<<"hier"<<endl;
        Woord my_woord;
        my_woord.w = woord;
        int aantal = tree.get(my_woord);
        tree.put(my_woord, aantal + 1);
        ifile >> woord;
    }

    ifile.close();

    cout << "Done";

    return 0;
}
