#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <list>
#include <string>

struct Tree {
    char data;    ///< Data in the node
    Tree *left;   ///< Pointer to left child. May be null.
    Tree *right;  ///< Pointer to right child. May be null.

    /**
     * Number of nodes in the subtree rooted at this node. Filled by
     * computeSizes(this)
     */
    int size;

    /**
     * Create a new tree.
     *
     * @param d data for this node
     * @param l the left child/subtree for this new tree
     * @param r the right child/subtree for this new tree
     */
    Tree(char d, Tree *l, Tree *r)
            : data(d), left(l), right(r), size(-1) {
    }

    /**
     * Recover storage in the subtrees.
     */
    ~Tree() {
        delete left;
        delete right;
    }

    /**
     * Compute the size (# of nodes) of t and of all of t's descendants.
     * Store the computed sizes in the `size` data member of each node.
     *
     * @return the size of node t
     */
    static int computeSizes(Tree* t);

    /**
     * Compare two trees to see if they are equal (isomorphic).
     *
     * @param t1 a tree
     * @param t2 another tree
     * @return true if the two trees have the same shape and the same
     *              data in corresponding positions.
     */
    static bool equal(const Tree *t1, const Tree *t2);


    /**
     * Print an encoded representation of a pre-order traversal of the the
     * tree, using a # character to denote empty children.
     */
    static void print(std::ostream &out, const Tree *t);

    /**
     * Find the largest subtree occurring in two or more places within
     * a tree.
     *
     * @param t the tree in which to search
     * @return an instance of the largest duplicate subtree
     */
    static const Tree* findLargestDuplicateSubtree(const Tree *t);


};

inline
std::ostream& operator<<(std::ostream& out, const Tree& t) {
    Tree::print(out, &t);
    return out;
}



#endif
