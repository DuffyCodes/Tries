#include <iostream>
#include <string>

#include "tree.h"
#include "trie.h"


using namespace std;



/**
 * Compare two trees to see if they are equal (isomorphic).
 *
 * @param t1 a tree
 * @param t2 another tree
 * @return true if the two trees have the same shape and the same
 *              data in corresponding positions.
 */
bool Tree::equal(const Tree *t1, const Tree *t2) {
  /***   Insert your code here ***/
    if (t1 == NULL && t2 == NULL)
        return true;

    if (t1 == NULL || t2 == NULL)
        return false;

    if (t1->data != t2->data)
        return false;

    return
    (equal(t1->left,t2->left) && equal(t1->right,t2->right))||
    (equal(t1->left,t2->right) && equal(t1->right,t2->left));
}

/**
 * Print an encoded representation of a pre-order traversal of the the
 * tree, using a # character to denote empty children.
 */
void Tree::print(std::ostream &out, const Tree *t) {
    if (t == 0)
        out << "#";
    else {
        out << t->data;
        print(out, t->left);
        print(out, t->right);
    }
}
/**
 * Compute the size (# of nodes) of t and of all of t's descendants.
 * Store the computed sizes in the `size` data member of each node.
 *
 * @return the size of node t
 */
int Tree::computeSizes(Tree *t) {
   if(t == NULL)
        return 0;
    else
    {
        t->size = computeSizes(t->left) + computeSizes(t->right) +1;
        return t->size;
    }
}
int computeSizes(const Tree *t) {
   if(t == NULL)
        return 0;
    else
    {
        int size = computeSizes(t->left) + computeSizes(t->right) +1;
        return size;
    }
}

static Tree* pleaseWork = nullptr;
static int best;
Tree* searchForRepeats(const Tree* t, const Tree* f, const int maxSize)
{
    if(computeSizes(t) != 1)
    {
        //cerr<<"Comparing "<<*t<<" to "<<*f<<endl;

        if(f != nullptr){
            searchForRepeats(t, f->left, maxSize);
            searchForRepeats(t, f->right, maxSize);
        }
        //cerr<<"equal: "<<Tree::equal(f,t)<<" size of t: "<<computeSizes(t)<<" size of f: "<<computeSizes(f)<<endl;
        if(computeSizes(t) > best &&Tree::equal(f, t)&&f!=t)
        {
            //cerr<<"statement 122"<<endl;
            pleaseWork = const_cast <Tree* const>(t);
            //cerr<<*pleaseWork<<endl;
            best = computeSizes(pleaseWork);

        }

    }
    //cerr<<"line 136: "<<*pleaseWork<<endl;
    return pleaseWork;
}
const Tree* exists(const Tree *full, const Tree *temp)
{
    //cerr<<"in exists\n";
    int maxSize = computeSizes(full);
    int bestSize = 0;
    int num = 0;

    Tree *bestSoFar= nullptr;
    if (temp != nullptr){
        exists(full, temp->left);
        exists(full, temp->right);
        bestSoFar = searchForRepeats(temp, full, maxSize);
        bestSize = computeSizes(bestSoFar);
    }
    return bestSoFar;


}

/**
 * Find the largest subtree occurring in two or more places within
 * a tree.
 *
 * @param root the tree in which to search
 * @return an instance of the largest duplicate subtree
 */
const Tree* Tree::findLargestDuplicateSubtree(const Tree *root)
{
    computeSizes((Tree*) root);
     Tree* bestSoFar = nullptr;
    int bestSize = 0;
    bestSoFar =const_cast <Tree* const>(exists(root, root));
    computeSizes((Tree*)bestSoFar);
    return bestSoFar;
}





