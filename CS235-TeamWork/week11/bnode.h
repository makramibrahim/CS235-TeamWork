/***********************************************************************
* Component:
*    Week 10, Binary Node w/ red lack info
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary:
*    Create a binary node for use in binary trees
************************************************************************/

#ifndef BNODE_H
#define BNODE_H

#include <iostream>  // for OFSTREAM
#include <cassert>

// debug stuff
#ifndef debug
#ifdef DEBUG
#define debug(x) x
#else
#define debug(x)
#endif // DEBUG
#endif // !debug
using namespace std;

/***********************************************************************
 * BNODE CLASS
 * Cantainer of a binary node tree
 ***********************************************************************/
template <class T>
class BinaryNode
{
  public:
   // Constructors
   BinaryNode() : pLeft(NULL), pRight(NULL), pParent(NULL) {}
   BinaryNode(T item, BinaryNode * pParent = NULL) : pParent(pParent), data(item), pLeft(NULL), pRight(NULL) {}
  
   ~BinaryNode() {}

   int findDepth() const;
   void verifyRedBlack(int depth) const;
   void verifyBTree() const;
   // Member Functions
   BinaryNode<T> * addLeft(T item) throw (const char *);
   BinaryNode<T> * addLeft(BinaryNode<T> * lhsChild) throw (const char *);
   BinaryNode<T> * addRight(T item) throw (const char *);
   BinaryNode<T> * addRight(BinaryNode<T> * rhsChild) throw (const char *);
  
   // Member Variables
   T data;
   BinaryNode * pLeft;
   BinaryNode * pRight;
   BinaryNode * pParent;
   bool isRed;
};

/***********************************************************************
 * BINARYNODE :: ADDLEFT
 * Adds a node to the left of the current node. 
 ***********************************************************************/
template <class T>
BinaryNode<T> * BinaryNode<T> :: addLeft(T item) throw (const char *)
{
   try
   {
      BinaryNode<T> *newNode = new(nothrow) BinaryNode(item);

       // paranoid: just to make sure
      assert(newNode);

      pLeft = newNode;
      newNode->pParent = this;
   }
   catch (...)
   {
      cout << "ERROR: Unbale to allocate a node";
   }

    // paranoid: just to make sure
   assert(this);
   
   return this;
}

/***********************************************************************
 * BINARYNODE :: ADDLEFT
 * Adds a node to the left of the current node. 
 ***********************************************************************/
template <class T>
BinaryNode<T> * BinaryNode<T>:: addLeft(BinaryNode<T> * lhsChild) throw (const char *)
{
   try
   {
      if(lhsChild != NULL)
      {
         lhsChild->pParent = this;
         pLeft = lhsChild;
      }
      else
      {
         pLeft = NULL;
      }
   }
   catch (...)
   {
      cout << "ERROR: Unbale to allocate a node";
   }

    // paranoid: just to make sure
   assert(this);
   
   return this;
}

/***********************************************************************
 * BINARYNODE :: ADDRIGHT
 *  Adds a node to the right of the current node.
 ***********************************************************************/
template <class T>
BinaryNode<T> * BinaryNode<T> :: addRight(T item) throw (const char *)
{
   try
   {
      BinaryNode<T> *newNode = new(nothrow) BinaryNode(item);

      // paranoid: just to make sure
      assert(newNode);

      pRight = newNode;
      
      newNode->pParent = this;
   }
   catch(...)
   {
      cout << "ERROR: Unable to allocate a node";
   }

    // paranoid: just to make sure
   assert(this);
   
   return this;
}

/***********************************************************************
 * BINARYNODE :: ADDRIGHT
 *  Adds a node to the right of the current node. 
 ***********************************************************************/
template <class T>
BinaryNode<T> * BinaryNode<T>:: addRight(BinaryNode<T> * rhsChild) throw (const char *)
{
   try
   {
      if(rhsChild != NULL)
      {
         pRight = rhsChild;
         rhsChild->pParent = this;
      }
      else
         pRight = NULL;
   }
   catch (...)
   {
      cout << "ERROR: Unbale to allocate a node";
   }

    // paranoid: just to make sure
   assert(this);
   
   return this;
}

/***********************************************************************
 * BINARYNODE :: DELETEBINARY
 * Takes a BinaryNode as a parameter and deletes all the children and
 * itself. This is a recursive function.
 ***********************************************************************/
template <class T>
void deleteBinaryTree(BinaryNode<T> * node)
{
   
   if (node == NULL)
      return;
   
   if(node->pRight != NULL)
      deleteBinaryTree(node->pRight);
   
   if(node->pLeft != NULL)
      deleteBinaryTree(node->pLeft);
   
   delete node;
   node = NULL;
}

/***********************************************************************
 * BINARYNODE :: INSERTION OPERATOR
 * Takes a constant BinaryNode * as a parameter and displays the tree
 * under the passed parameter.
 ***********************************************************************/
template <class T>
ostream & operator << (ostream & out, const BinaryNode<T> * rhs)
{
   if(rhs == NULL)
      return out;
   else
   {
      if(rhs != NULL)
      {
         out << rhs->pLeft;
         out << rhs->data << " ";
         out << rhs->pRight;
      }
      return out;
   }
}

/****************************************************
 * BINARY NODE :: FIND DEPTH
 * Find the depth of the black nodes. This is useful for
 * verifying that a given red-black tree is valid
 ****************************************************/
template <class T>
int BinaryNode <T> :: findDepth() const
{
   // if there are no children, the depth is ourselves
   if (pRight == NULL && pLeft == NULL)
      return (isRed ? 0 : 1);

   // if there is a right child, go that way
   if (pRight != NULL)
      return (isRed ? 0 : 1) + pRight->findDepth();
   else
      return (isRed ? 0 : 1) + pLeft->findDepth();
}

/****************************************************
 * BINARY NODE :: VERIFY RED BLACK
 * Do all four red-black rules work here?
 ***************************************************/
template <class T>
void BinaryNode <T> :: verifyRedBlack(int depth) const
{
   depth -= (isRed == false) ? 1 : 0;

   // Rule a) Every node is either red or black
   assert(isRed == true || isRed == false); // this feels silly

   // Rule b) The root is black
   if (pParent == NULL)
      assert(isRed == false);

   // Rule c) Red nodes have black children
   if (isRed == true)
   {
      if (pLeft != NULL)
         assert(pLeft->isRed == false);
      if (pRight != NULL)
         assert(pRight->isRed == false);
   }

   // Rule d) Every path from a leaf to the root has the same # of black nodes
   if (pLeft == NULL && pRight && NULL)
      assert(depth == 0);
   if (pLeft != NULL)
      pLeft->verifyRedBlack(depth);
   if (pRight != NULL)
      pRight->verifyRedBlack(depth);
}

/******************************************************
 * VERIFY B TREE
 * Verify that the tree is correctly formed
 ******************************************************/
template <class T>
void BinaryNode <T> :: verifyBTree() const
{
   // check parent
   if (pParent)
      assert(pParent->pLeft == this || pParent->pRight == this);

   // check left
   if (pLeft)
   {
      assert(pLeft->data <= data);
      assert(pLeft->pParent == this);
      pLeft->verifyBTree();
   }

   // check right
   if (pRight)
   {
      assert(pRight->data >= data);
      assert(pRight->pParent == this);
      pRight->verifyBTree();
   }
}

#endif //end BNODE_H
