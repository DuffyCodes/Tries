

#include <iostream>
#include <string>

#include "trie.h"
#include "tree.h"

using namespace std;


int main() {
	Trie trie;
    string line;
    getline(cin, line);
    while ((cin) && (line != "***")) {
        trie.add(line);
        cerr << trie << endl;
        getline(cin, line);
    }

    const Tree *t = trie.getLargestSharedSubtree();
    if (t == nullptr)
        cout << 0 << endl;
    else
        cout << t->size << ' ' << *t << endl;

    return 0;
}
