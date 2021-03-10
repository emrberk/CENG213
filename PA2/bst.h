#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <functional>
#include <cstddef>
#include <ostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <utility>

#include <iostream>   


class DefaultBalanceCondition 
{
  public:
    bool operator() (int current_height, int ideal_height) const
    {
      return true;
    }
};


template <typename Key, typename Object,
          typename BalanceCondition=DefaultBalanceCondition,
	  typename Comparator=std::less<Key> >
class BinarySearchTree
{
  public:  /* DO NOT CHANGE */
    struct Node   // core structure of BinarySearchTree
    {
       Key key;         // unique key
       Object data;     // data to be stored, characterized by key
       Node * left;     // pointer to left subtree
       Node * right;    // pointer to right subtree
       size_t height;   // height of the node
       size_t subsize;  // size of the subtree node roots including itself

       Node(const Key &, const Object &, 
            Node *, Node *, size_t =0, size_t =1);   // Node constructor
    };

  public:  /* DO NOT CHANGE PROTOTYPES */
    BinarySearchTree();  // zero-parameter constructor
    BinarySearchTree(const std::list<std::pair<Key, Object> > &); // list is always sorted!
    ~BinarySearchTree();  // destructor

  public:  /* DO NOT CHANGE PROTOTYPES */
    void insert(const Key &, const Object &);  // insert new Key-Object
    void remove(const Key &);  // remove Node characterized by Key
    void toCompleteBST();  // convert into a complete BST

  public:  /* DO NOT CHANGE PROTOTYPES */
    Node * find(const Key &) const; // single item
    std::list<Node *> find(const Key &, const Key &) const; // range queries
    int height() const;  // return the height of the tree
    size_t size() const; // return the number of items in the tree
    bool empty() const;  //return whether the tree is empty or not
    Node * getRoot() const; // return a pointer to the root of the tree
    void print(std::ostream &) const;  // print tree structure into an output stream

  private:  /* DO NOT CHANGE DATA TYPES AND IDENTIFIERS */
    Node * root;                     // designated root
    size_t numNodes;                 // size
    Comparator isLessThan;           // operator upon which BST nodes are arranged
    BalanceCondition isBalanced;     // signals whether the signal is balanced
  
  private:  /* DO NOT CHANGE PROTOTYPES */
    Node * find(const Key &, Node *) const;
    int height(Node *) const;
    int subsize(Node *) const;
    void print(Node *, std::ostream &) const;

    // Define your const private utility functions below this line

  private:
    void makeEmpty(Node * &);       // utility for destructor
    
    // Define your private utility functions below this line
	Node* createBST(std::list<std::pair<Key,Object> > & datalist, int size, int level);

    Node* createBSTFromVector(std::vector<Node*>& v, int size, int level);

    void inOrderTraversal(Node* root, std::vector<Node*> &nodeptrs);

    void insertToTree(Node* &root, Node* &newNode);

    void balance(Node* &r);

    Node* removeHelper(const Key& k, Node* &r);

    Node* findInOrderSuccessor(Node*& r);

    Node* findSuccessor(Node*& r);

    void findHelper(const Key& lower, const Key& upper, std::list<Node*>& ranges, Node* r) const;


private: /* DO NOT CHANGE PROTOTYPES: compiler defaults are blocked */  
    BinarySearchTree(const BinarySearchTree &);
    const BinarySearchTree & operator=(const BinarySearchTree &);

  private:  // static utility functions
    template <typename T> //static utility function
    static const T & max(const T &, const T &);

    // Define more below this line if needed
	int leftLeaves(int size, int level) const;
	
	int toLevels(int listSize) const {
		int level = 1;
		if(listSize==0) {
			return 0;
		}

		while(true) {

			if(pow(2,level-1) -1 < listSize && pow(2,level) -1 >= listSize) {
				return level;
			}
			level++;
		}			
	}

};

#endif
template <typename K, typename O, typename B, typename C>
int BinarySearchTree<K,O,B,C>::leftLeaves(int size, int level) const{

	if(level==0 || level==1) {
		return 0;
	}
	
	else if(size-(pow(2,level-1)-1) <= pow(2,level-2) ) {
		return size-(pow(2,level-1)-1);
	}
	else if (size-(pow(2,level-1)-1) > pow(2,level-2) ) {
		return pow(2,level-2);
	}

}


template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K, O, B, C>::Node* BinarySearchTree<K, O, B, C>::createBST(std::list<std::pair<K, O> >& datalist, int size, int level) {

    typename std::list<std::pair<K, O> >::const_iterator it = datalist.begin();

    if (size == 0) {
        return nullptr;
    }

    int leftL = leftLeaves(size, level);
    int lefts;

    if (level >= 2) lefts = leftL + (pow(2, level - 2) - 1);
    else lefts = 0;

    int rightLevel;
    if (size - (pow(2, level - 1) - 1) - leftL > 0) {
        rightLevel = level - 1;
    }
    else {
        rightLevel = level - 2;
    }

	Node* left = createBST(datalist, lefts, level-1);

	Node* r = new Node(datalist.front().first , datalist.front().second, left, nullptr, level-1, size);
    r->height = level - 1;
    r->subsize = size;
    r->left = left;
    
    datalist.pop_front();

	r->right = createBST(datalist, size-lefts-1, rightLevel);

	return r; 
	
}

template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K, O, B, C>::Node* BinarySearchTree<K, O, B, C>::createBSTFromVector(std::vector<typename BinarySearchTree<K, O, B, C>::Node*>& v, int size, int level) {

    if (size == 0) {
        return nullptr;
    }
    int leftleafs = leftLeaves(size, level);
    int lefts = leftleafs + (pow(2, level - 2) - 1);
    int rightLevel;
    if (size - (pow(2, level - 1) - 1) - leftleafs > 0) {
        rightLevel = level - 1;
    }
    else {
        rightLevel = level - 2;
    }

    Node* left = createBSTFromVector(v, lefts, level - 1);
    
    Node* r = v[0];
    r->height = level-1;
    r->subsize = size;
    r->left = left;

    v.erase(v.begin());

    r->right = createBSTFromVector(v, size - lefts - 1, rightLevel);

    return r;

}
template <typename K, typename O, typename B, typename C>
void BinarySearchTree<K, O, B, C>::balance(typename BinarySearchTree<K, O, B, C>::Node* &r) {
    
    if (r == nullptr) return;
    BinarySearchTree<K, O, B, C>* subtree = new BinarySearchTree<K, O, B, C>();
    subtree->root = r;
    subtree->numNodes = r->subsize;
    if (!subtree->isBalanced(r->height, log2(r->subsize))) {
        subtree->toCompleteBST();
        r = subtree->root;
    }
    subtree->root = nullptr;
    delete subtree;

}


template <typename K, typename O, typename B, typename C>
void BinarySearchTree<K, O, B, C>::inOrderTraversal(typename BinarySearchTree<K, O, B, C>::Node* root, std::vector<typename BinarySearchTree<K, O, B, C>::Node*> & nodeptrs) {

    if (root == nullptr) {
        return;
    }

    inOrderTraversal(root->left, nodeptrs);
    nodeptrs.push_back(root);
    inOrderTraversal(root->right, nodeptrs);

}
template <typename K, typename O, typename B, typename C>
void BinarySearchTree<K, O, B, C>::insertToTree(typename BinarySearchTree<K, O, B, C>::Node* &r, typename BinarySearchTree<K, O, B, C>::Node* &newNode) {

    if (r == NULL)
    {
        r = newNode;
        return;

    }

    else if (isLessThan(newNode->key, r->key))
    {
        insertToTree(r->left, newNode);
        
    }
    else if (isLessThan(r->key, newNode->key))
    {
        insertToTree(r->right, newNode);
        
    }
    r->subsize++;
    r->height = 1 + max(height(r->left), height(r->right));
    
    balance(r);

}

// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::Node::
Node(const K & _k, const O & _d, Node * _l, Node * _r, size_t _h, size_t _s)
  : key(_k), data(_d), left(_l), right(_r), height(_h), subsize(_s)
{
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::BinarySearchTree()
  : root(NULL), numNodes(0)  //comparator(C() ??)
{
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::BinarySearchTree(const std::list<std::pair<K,O> > & datalist)
   : root(NULL), numNodes(0)  // change it as you'd like
{
    numNodes = datalist.size();

	std::list<std::pair<K,O> > listcopy = datalist;
	this->root = createBST(listcopy, datalist.size(), toLevels(datalist.size()));
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::toCompleteBST()
{
    std::vector<Node*> nodeptrs;

    inOrderTraversal(this->root, nodeptrs);
    
    this->root = createBSTFromVector(nodeptrs, nodeptrs.size(), toLevels(nodeptrs.size()));


}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::insert(const K & k, const O & x)
{
    Node* found = find(k);
    if (found) {
        found->data = x;
    }
    else {
        Node* newNode = new Node(k, x, nullptr, nullptr, 0, 1);
        insertToTree(this->root, newNode);
       
    }

}

template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K, O, B, C>::Node* BinarySearchTree<K, O, B, C>::findSuccessor(typename BinarySearchTree<K, O, B, C>::Node*& r) {
    
    Node* successor;
    
    if (r->left == nullptr) {
        successor = r;
        r = r->right;
        if (r != nullptr) {
            r->height = 1 + max(height(r->left), height(r->right));
            r->subsize = 1 + subsize(r->left) + subsize(r->right);
        }
        return successor;   
    }
    else {
        Node* successor = findSuccessor(r->left);
        r->height = 1 + max(height(r->left), height(r->right));
        r->subsize = 1 + subsize(r->left) + subsize(r->right);
        balance(r);
        return successor;

    }

}


template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K, O, B, C>::Node* BinarySearchTree<K, O, B, C>::removeHelper(const K& k, typename BinarySearchTree<K, O, B, C>::Node*& r) {

    if (r == nullptr) {
        return nullptr;
    }
    else if (isLessThan(k, r->key)) {
        r->left = removeHelper(k, r->left);
        balance(r);
        r->height = 1 + max(height(r->left), height(r->right));
        r->subsize = 1 + subsize(r->left) + subsize(r->right);
    }
    else if (isLessThan(r->key, k)) {
        r->right = removeHelper(k, r->right);
        balance(r);
        r->height = 1 + max(height(r->left), height(r->right));
        r->subsize = 1 + subsize(r->left) + subsize(r->right);
        
    }

    else {
        if (r->left == nullptr && r->right == nullptr) {
            delete r;
            r = nullptr;
            return r;
        }
        else if (r->left == nullptr && r->right != nullptr) {
            Node* ret = r->right;
            delete r;
            r = nullptr;
            return ret;
        }
        else if (r->left != nullptr && r->right == nullptr) {
            Node* ret = r->left;
            delete r;
            r = nullptr;
            return ret;
        }
        else {
            Node* successor = findSuccessor(r->right);

            successor->right = r->right;
            successor->left = r->left;
            successor->height = 1 + max(height(successor->left), height(successor->right));
            successor->subsize = 1 + subsize(successor->left) + subsize(successor->right);
            
            delete r;
            r = nullptr;
            balance(successor);




            return successor;
        }


    }

    return r;


}

// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::remove(const K & k)
{
    if (this->root == nullptr) return;
    root = removeHelper(k, root);
    balance(root);

}



// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::find(const K & key) const
{
  return find(key, root);
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::find(const K & key, Node * t) const
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (isLessThan(key, t->key))
  {
    return find(key, t->left);
  }
  else if (isLessThan(t->key, key))
  {
    return find(key, t->right);
  }
  else //found
  {
    return t;
  }
}

template <typename K, typename O, typename B, typename C>
void BinarySearchTree<K, O, B, C>::findHelper(const K& lower, const K& upper, std::list<typename BinarySearchTree<K, O, B, C>::Node*>& ranges, typename BinarySearchTree<K, O, B, C>::Node* r ) const {
    
    if (r == nullptr) {
        return;
    }
    else if (isLessThan(upper,r->key)) {
        findHelper(lower, upper, ranges, r->left);
    }
    else if  (isLessThan(r->key, upper)  && isLessThan(lower, r->key) ) {
        findHelper(lower, upper, ranges, r->left);
        ranges.push_back(r);
        findHelper(lower, upper, ranges, r->right);
    }
    else if (isLessThan(r->key ,lower)) {
        findHelper(lower, upper, ranges, r->right);
    }
    else {
        findHelper(lower, upper, ranges, r->left);
        ranges.push_back(r);
        findHelper(lower, upper, ranges, r->right);
 
    }
    

}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
std::list<typename BinarySearchTree<K,O,B,C>::Node *>
BinarySearchTree<K,O,B,C>::find(const K & lower, const K & upper) const
{
    std::list<Node *> ranges;
    
    // implement
    findHelper(lower, upper, ranges, this->root);


    return ranges;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::getRoot() const
{
  return root;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::height() const
{
  return height(root);
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::height(Node * t) const
{
  return (t == NULL) ? -1 : t->height;
}


// private utility
template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::subsize(Node * t) const
{
  return (t == NULL) ? 0 : t->subsize;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
size_t
BinarySearchTree<K,O,B,C>::size() const
{
  return numNodes;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
bool
BinarySearchTree<K,O,B,C>::empty() const
{
  return numNodes == 0;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::makeEmpty(Node * & t)
{
  if (t != NULL)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;

    --numNodes;
  }
  
  t = NULL;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::~BinarySearchTree()
{
  makeEmpty(root);
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::print(std::ostream & out) const
{
  print(root, out);
  out << '\n';
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::print(Node * t, std::ostream & out) const
{
  if (t != NULL && t->left != NULL) 
  {
    out << '[';
    print( t->left, out );
  }
  else if (t != NULL && t->left == NULL && t->right != NULL)
  {
    out << "[";
  }

  if (t != NULL)
  {
    if (t->left == NULL && t->right == NULL)
    {
      out << '(' << (t->key) << ')';
    }
    else if (t->left != NULL || t->right != NULL)
    {
      out << '{' << (t->key) << ",H" << t->height << ",S" << t->subsize << '}';
    }
  }
  
  if (t != NULL && t->right != NULL)
  {
    print( t->right, out );
    out << ']';
  }
  else if (t != NULL && t->left != NULL && t->right == NULL)
  {
    out << "]";
  }
}


// do not change
template <typename K, typename O, typename B, typename C>
template <typename T>
const T &
BinarySearchTree<K,O,B,C>::max(const T & el1, const T & el2)
{
  return el1 > el2 ? el1 : el2;
}

