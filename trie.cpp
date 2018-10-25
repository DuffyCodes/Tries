
#include <iostream>
#include <list>
#include <string>

#include "trie.h"


using namespace std;


/**
 * Compute and save the size (# of nodes) of all tree nodes within the trie.
 *
 */
void Trie::computeSizes()
{
	Tree::computeSizes(root);
}

/**
 * Compare two tries to see if they are equal (isomorphic).
 *
 * @param right another trie
 * @return true if the two tries encode the same set of words
 */
bool Trie::operator== (const Trie& right) const
{
	return Tree::equal(root, right.root);
}

/**
 * Add a word to the trie
 *
 * @param word the word being added to the trie
 */
void Trie::add(const std::string &word)
{
	Trie::addToTrie(nullptr, root, word, 0, false);
}


/**
 * Extract a list of words contained in the trie. (Mainly for testing and
 * debugging purposes).
 *
 * @return a list of words in the tire
 */
std::list<std::string> Trie::allWords () const
{
	list<string> words;
    Trie::listWords (words, root, true, "");
    return words;
}


/**
 * Find the largest (# of nodes) subtree that occurs two or more
 * places within the trie.
 *
 * Assumes that computeSizes() has been called since the last addition
 * to the subtree.
 *
 * @return one occurrence of the largest shared subtree
 */
const Tree* Trie::getLargestSharedSubtree() const
{
	return Tree::findLargestDuplicateSubtree(root);
}



/**
 * Print a trie in an encoded form representing a pre-order traversal of its
 * implementing tree.
 */
std::ostream& operator<< (std::ostream& out, const Trie& trie)
{
	if (trie.getTree() == nullptr)
		out << "#";
	else
		out << *(trie.getTree());
	return out;
}


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
void Trie::addToTrie(
		Tree *parent, Tree *&t,
		const std::string &word, unsigned offSet,
		bool extending)
{
	if (offSet >= word.size()) {
		// At the end of a word.
		if (t != nullptr && t->data != '@') {
			t = new Tree('@', nullptr, parent->left);
		}
	} else {
		char ch = word[offSet];
		if (t == nullptr && parent != nullptr && !extending) {
			Tree *t1 = new Tree(ch, nullptr, nullptr);
			t = new Tree('@', nullptr, t1);
			addToTrie(t->right, t1->left, word, offSet + 1, true);
		} else if (t == nullptr) {
			t = new Tree(ch, nullptr, nullptr);
			addToTrie(t, t->left, word, offSet + 1, true);
		} else {
			Tree *p = parent;
			Tree *c = t;
			while (c != nullptr && c->data < ch) {
				p = c;
				c = c->right;
			}
			if (c == nullptr) {
				p->right = new Tree(ch, nullptr, nullptr);
				addToTrie(p->right, p->right->left, word,
						offSet + 1, true);
			} else if (c->data == ch) {
				addToTrie(c, c->left, word,
						offSet + 1, extending);
			} else {
				Tree *t1 = new Tree(ch, nullptr, c);
				if (p == nullptr) {
					*t1 = *c;
					c->data = ch;
					c->left = nullptr;
					c->right = t1;
					addToTrie(c, c->left, word,
							offSet + 1, false);
				}
				else if (c == p->left) {
					p->left = t1;
					addToTrie(p->left, t1->left, word,
							offSet + 1, true);
				} else {
					p->right = t1;
					addToTrie(p->right, t1->left, word,
							offSet + 1, true);
				}
			}
		}
	}
}

/**
 * Extract a list of words contained in the trie. (Mainly for testing and
 * debugging purposes).
 *
 * @param words output, the list to be extracted
 * @param t current position within the trie
 * @param isLeft true iff t is a left child of its parent
 * @param s the string representing the trie path from its root to t.
 */
void Trie::listWords (std::list<std::string>& words, const Tree* t,
					   bool isLeft, std::string s)
{
    if (t == nullptr) {
        if (isLeft && s.size() > 0) {
        	if (s[s.size()-1] == '@')
        		s = s.substr(0, s.size()-1);
            words.push_back(s);
        }
        return;
    }

    string s0 = s;
    if (isLeft)
        s0 += t->data;
    else
        s0[s0.size()-1] = t->data;
    Trie::listWords(words, t->left, true, s0);
    Trie::listWords(words, t->right, false, s0);
}







