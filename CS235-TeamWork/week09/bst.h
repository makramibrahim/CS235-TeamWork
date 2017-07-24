/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Helfrich, CS 235
 * Author:
 *    Makram Ibrahim
 * Summary:
 *    
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h" // for BinaryNode
#include "stack.h" // for Stack

template <class T>
class BSTIterator;

/*****************************************************************
* BINARY SEARCH TREE
* Create a Binary Search Tree
*****************************************************************/
template <class T>
class BST
{
public:

   //Constructor: Default constructor setting root to
   //   NULL, and the copy constructor. In the case of
   //   an allocation error, the following c-string
   //   exception will be thrown: ERROR: Unable to allocate a node
   BST() : root(NULL) { }

   BST(const BST & rhs);

   //Destructor: Delete all the elements in the binary tree,
   //   probably calling the function deleteBinaryTree()
   //   from the previous lesson.
   ~BST() { clear(); }

   //operator=: Assignment operator. Copy one binary
   //   search tree onto another.
   BST & operator = (const BST & rhs) throw (const char *);
   // copy tree
   void copy(BinaryNode<T> * pThis, BinaryNode<T> * pRhs) throw (const char *);

   // standard container interfaces
   //empty(): Determines whether the current binary
   //   search tree is empty. This can be accomplished
   //   by testing if the root node is NULL.
   bool empty() const { return root == NULL; }
   
   //size(): Return the number of nodes in the binary
   //   search tree. This method takes no parameters
   //   and returns an integer value.
   int size() const { return empty() ? 0 : root->size(); }
   
   //clear(): Delete all the elements in the binary search tree.
   void clear()
   {
      if (root)
         deleteBinaryTree(root);
         assert(empty());
   }

   // BST specific interfaces
   //insert(): The parameter is the data t to be inserted into
   //   the binary search tree. This will involve finding the
   //   appropriate location in the tree for the data t and
   //   creating a node to encapsulate it. There is no return
   //   value. In the case of an allocation error, the following
   //   c-string exception will be thrown: ERROR: Unable to allocate a node
   void insert(const T & t) throw (const char * );
   
   //remove(): The parameter is an iterator referring to the
   //   t to be removed from the binary search tree. The node
   //   will then be removed following the algorithm presented in
   //   the textbook (titled "Removing a Node from a BST" in chapter 12.4).
   //   There is no return value.
   void remove(BSTIterator <T> & it);
   
   //find(): The parameter is the data t to be found and the return
   //   value is an iterator referring to the element in the tree
   //   corresponding to the parameter. If no element is found, the end()
   //   iterator will be returned.
   BSTIterator <T> find(const T & t);

   // iterators
   //begin(): There is no parameter, and the return value is an iterator
   //   referring to the leftmost element in the BST.
   BSTIterator <T> begin();
   
   //end(): There is no parameter, and the return value is an iterator
   //   referring to no element in the BST. By convention, this is the
   //   NULL iterator.
   BSTIterator <T> end() { return BSTIterator <T> (NULL); }
   
   //rbegin(): There is no parameter, and the return value is an iterator
   //   referring to the rightmost element in the BST.
   BSTIterator <T> rbegin();
   
   //rend(): There is no parameter, and the return value is an
   //   iterator referring to no element in the BST. By convention,
   //   this is the NULL iterator.
   BSTIterator <T> rend() { return BSTIterator <T> (NULL); }

private:
   // delete a single node from the tree
   void deleteNode (BinaryNode <T> * & pDelete, bool toRight);
   BinaryNode <T> * root;
};

/*********************************************************
* Copy::constructor
**********************************************************/
template <class T>
BST<T>::BST(const BST &rhs)
{
   this->root = NULL;
   *this = rhs;
}

/**********************************************************
 * BSTIterator
 * Forward and reverse iterator through binary search tree
 *********************************************************/
template <class T>
class BSTIterator
{
public:
   // constructors
   BSTIterator(BinaryNode <T> * p = NULL)    { nodes.push(p);  }
   BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s;         }
   BSTIterator(const BSTIterator <T> & rhs)  { nodes = rhs.nodes; }

   // assignment
   BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
   {
      // need an assignment operator for the Stack class.
      nodes = rhs.nodes;
      return *this;
   }

   // compare
   bool operator == (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() == nodes.const_top();
   }
   bool operator != (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() != nodes.const_top();
   }

   // de-reference. Cannot change because it will invalidate the BST
   T & operator * ()  
   {
      return nodes.top()->data;
   }

   // iterators
   BSTIterator <T> & operator ++ ();
   BSTIterator <T>   operator ++ (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      ++(*this);
      return itReturn;
   }
   BSTIterator <T> & operator -- ();
   BSTIterator <T>   operator -- (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      --(*this);
      return itReturn;
   }

   // must give friend status to remove so it can call getNode() from it
   friend void BST <T> :: remove(BSTIterator <T> & it);

private:
   BinaryNode<T> * p;
 
   // get the node pointer
   BinaryNode <T> * getNode() { return nodes.top(); }
   
   // the stack of nodes
   Stack < BinaryNode <T> * > nodes;
};


/**********************************************************
* operator=: Assignment operator. 
* Copy one binary search tree onto another.
************************************************************/
template<class T>
BST<T> & BST <T> :: operator = (const BST & rhs) throw (const char *)
{
   clear();
   // return this if the rhs is empty 
   if (rhs.empty())
      return *this;
   else
   {
      // copy root
      this->root = new BinaryNode<T>(rhs.root->data);
      copy(rhs.root, this->root);
   }
   return *this;
}

/**********************************************************
* operator=: Assignment operator. 
* Copy one binary search tree onto another.
************************************************************/
template <class T>
void BST<T> :: copy(BinaryNode<T> * pRhs, BinaryNode<T> * pThis) throw (const char *)
{
   // if pLeft and pRight are empty then
   if (pRhs->pLeft == NULL && pRhs->pRight == NULL)
      return;
   
   // copy children
   else
   {
      if (pRhs->pLeft)
      {
         // create node in the new tree
         pThis->addLeft(pRhs->pLeft->data);
        
         // recurse down 
         copy(pRhs->pLeft, pThis->pLeft);
      }
      
      if (pRhs->pRight)
      {
         // do the same for right
         pThis->addRight(pRhs->pRight->data);
         
         copy(pRhs->pRight, pThis->pRight);
      }
   }
}

/*****************************************************
 * Begin():
 * The first left node in a binary search tree
 ****************************************************/
template <class T>
BSTIterator<T> BST<T>::begin() {
  Stack<BinaryNode<T>*> nodes;

  nodes.push(NULL);
  nodes.push(root);
  while (nodes.top() != NULL && nodes.top()->pLeft)
    nodes.push(nodes.top()->pLeft);

  return nodes;
}

/*****************************************************
 * BST :: rebegin()
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin()
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);

   return nodes;
}  

/************************************************
* BST :: INSERT
* Insert a given node as specified by the iterator
************************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{
   try
   {
      BinaryNode<T> * position = root;
      BinaryNode<T> * parent = NULL;
      
      while (position != NULL  ) {
         parent = position;
         if (t < position->data)
            position = position->pLeft;
            else
               position = position->pRight;
               }
      
      position = new BinaryNode<T>(t);
      if(parent == NULL)
         root = position;
         else if (t < parent->data)
         {
            parent->pLeft = position;
            position->pParent = parent;
         }
         else
         {
            parent->pRight = position;
            position->pParent = parent;
         }
         
   }
   catch (bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for this tree.";
   }
}

/************************************************
 * Find function
 * Used to find a node from the tree
 ***********************************************/
template <class T>
BSTIterator <T> BST <T> :: find(const T & t)
{
   BinaryNode<T> * pNode = root;
   bool bFound = false;
   
   while(!bFound && pNode != NULL)
   {
      if(t < pNode->data)
         pNode = pNode->pLeft;
      else if (pNode->data < t)
         pNode = pNode->pRight;
      else
         bFound=true;
   }
   if(bFound)
      return pNode;
   else
      return end();
}

/*************************************************
* BST :: REMOVE
* Remove a given node as specified by the iterator
************************************************/
template <class T>
void BST <T> :: remove(BSTIterator <T> & it)
{
   // find the node
   BinaryNode <T> * pNode = it.getNode();

   // do nothing if there is nothing to do
   if (pNode == NULL)
      return;

   // if there is only one child (right) or no children (how sad!)
   if (pNode->pLeft == NULL)
      deleteNode(pNode, true /* goRight */);

   // if there is only one child (left)
   else if (pNode->pRight == NULL)
      deleteNode(pNode, false /* goRight */);

   // otherwise, swap places with the in-order successor
   else
   {
   // find the in-order successor
   BinaryNode <T> * pNodeIOS = pNode->pRight;
      while (pNodeIOS->pLeft != NULL)
         pNodeIOS = pNodeIOS->pLeft;
         // copy its data
         pNode->data = pNodeIOS->data;
         // if there are any children under the in-order successor, fix them
         assert(pNodeIOS->pLeft == NULL); // there cannot be a left child or
         // I would not be the IOS
         deleteNode(pNodeIOS, true /*goRight*/);
         // prepare for deletion
         pNode = pNodeIOS;
   }
   delete pNode;
}

/****************************************************
* DELETE NODE
* Delete a single node (pDelete) from the tree indicated
* by a node (pDelete).
* pDelete the node to be deleted
* toRight should the right branch inherit our place?
****************************************************/
template <class T>
void BST <T> :: deleteNode(BinaryNode <T> * & pDelete, bool toRight)
{
   // shift everything up
   BinaryNode <T> * pNext = (toRight ? pDelete->pRight : pDelete->pLeft);

   // if we are not the parent, hook ourselves into the existing tree
   if (pDelete != root)
   {
      if (pDelete->pParent->pLeft == pDelete)
      {
         pDelete->pParent->pLeft = NULL;
         pDelete->pParent->addLeft(pNext);
      }
      else
      {
         pDelete->pParent->pRight = NULL;
         pDelete->pParent->addRight(pNext);
       }
   }
   // otherwise, the pNext is the new root
   else
   {
      root = pNext;
      pNext->pParent = NULL;
   }
}


/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. Note that this implementation uses
 *     a stack of nodes to remember where we are. This stack
 *     is called "nodes".
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template<class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

/**************************************************
 * ITERATOR :: BSTIterator
 * Advance by one
 *************************************************/
template <class T>
BSTIterator<T>& BSTIterator<T>::operator++() {
  // do nothing if we have nothing
  if (nodes.top() == NULL)
    return *this;

  // if there is a right node, take it
  if (nodes.top()->pRight != NULL) {
    nodes.push(nodes.top()->pRight);

    // there might be more left-most children
    while (nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);
    return *this;
  }

  // there are no right children, the left are done
  assert(nodes.top()->pRight == NULL);
  BinaryNode<T>* pSave = nodes.top();
  nodes.pop();

  // if the parent is the NULL, we are done!
  if (NULL == nodes.top())
    return *this;

  // if we are the left-child, got to the parent.
  if (pSave == nodes.top()->pLeft)
    return *this;

  // we are the right-child, go up as long as we are the right child!
  while (nodes.top() != NULL && pSave == nodes.top()->pRight) {
    pSave = nodes.top();
    nodes.pop();
  }

  return *this;
}


#endif // BST_H