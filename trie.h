#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <list>
#include <string>

#include "tree.h"

/**
 * A Trie over alphabetic characters, implemented using a binary tree.
 */
class Trie {

	Tree* root; ///> root of the tree used to store the trie

public:

    /**
     * Create a new trie.
     *
     * @param d data for this node
     * @param l the left child/subtree for this new tree
     * @param r the right child/subtree for this new tree
     */
    Trie()
	: root(nullptr)
	{
    }

    /**
     * Recover storage in the trie.
     */
    ~Trie() {
        delete root;
    }

    /**
     * Compute and save the size (# of nodes) of all tree nodes within the trie.
     *
     */
    void computeSizes();

    /**
     * Compare two tries to see if they are equal (isomorphic).
     *
     * @param right another trie
     * @return true if the two tries encode the same set of words
     */
    bool operator== (const Trie& right) const;

    /**
     * Add a word to the trie
     *
     * @param word the word being added to the trie
     */
    void add(const std::string &word);


    /**
     * Extract a list of words contained in the trie. (Mainly for testing and
     * debugging purposes).
     *
     * @return a list of words in the tire
     */
    std::list<std::string> allWords () const;


    /**
     * Find the largest (# of nodes) subtree that occurs two or more
     * places within the trie.
     *
     * Assumes that computeSizes() has been called since the last addition
     * to the subtree.
     *
     * @return one occurrence of the largest shared subtree
     */
    const Tree* getLargestSharedSubtree() const;


    /**
     * Get the underlying tree used to implement the trie.
     *
     * @return root of the implementing tree
     */
    Tree* getTree() {return root;}
    const Tree* getTree() const {return root;}

private:
    /**
     * Add a word to the trie implemented via this tree
     *
     * @param parent node of the tree representing the parent of the current
     *               position within the tree
     * @param t  current position within a tree, representing the string made
     *           up of characters 0..offSet-1 of word
     * @param word the word being added to the trie
     * @param offset the position within word of the next character to be added
     * @param extending true if we have already added at least one node to the
     *                  the trie in the course of processing the first offSet-1
     *                  characters of word.
     */
    static void addToTrie(Tree *parent, Tree *&t,
                   const std::string &word, unsigned offSet,
                   bool extending);

    /**
     * Extract a list of words contained in the trie. (Mainly for testing and
     * debugging purposes).
     *
     * @param words output, the list to be extracted
     * @param t current position within the trie
     * @param isLeft true iff t is a left child of its parent
     * @param s the string representing the trie path from its root to t.
     */
    static void listWords (std::list<std::string>& words, const Tree* t,
    					   bool isLeft, std::string s);


};

/**
 * Print a trie in an encoded form representing a pre-order traversal of its
 * implementing tree.
 */
std::ostream& operator<< (std::ostream& out, const Trie& trie);

#endif
