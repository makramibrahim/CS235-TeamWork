/***********************************************************************
* Header:
*    Node.h
* Summary:
*    This class contains the notion of a node : a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the Deque, Node, Deque, Deque, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Deque         : A class that holds stuff
*        DequeIterator : An interator through Deque
* Author
*    Makram Ibrahim
************************************************************************/
#ifndef NODE_H
#define NODE_H

#include <cassert>
#include <iostream>
using namespace std;

/**************************************************
* Node: CONTAINER CLASS
* A class that holds items
****************************************************/
template<class T>
class Node {

public:
  ////////////////Constructors//////////////////

  // create default constructor: empty 
  Node() : pNext(NULL), data(NULL) {}

  // creat a non-default constructor: per-allocate
  Node(const T & t) : pNext(NULL), data(t) {}

  /////////////////Member functions///////////////

  // find() search for the repeated item.
  Node<T> * find(Node<T> * pHead, const T & t);

  // insert(): add or insert the desired elements
  Node<T> * insert(const T & t, Node<T> * & pHead, bool next = false);

  // freeData(): Remove an element from the Node. 
  void freeData(Node<T> * & pHead) throw (const char *);

  //copy Node and its all elements
  Node<T> * copy(const Node<T> * newBox);

  // allocate and held the data in a new array
  void allocate(const Node<T> * newBox) throw(const char *);

  T data;            // store all data here 
  Node<T> * pNext;  // point on next location
   
};

/*******************************************
* Copy: 
* Takes a pointer to a Node as a parameter 
* and returns a newly created linked-list. 
*******************************************/
template <class T>
Node<T> * copy(const Node<T> * newBox)
{
	if (newBox == NULL)
	
		return NULL; 

		allocate(newBox);
}

/**********************************************
* ALLOCATES: NEW SPACE WHENEVER WE NEED!
* GET NEWINDEX
**********************************************/
template <class T>
Node <T> * allocate(const Node<T> * newBox) throw(const char *)
{
  // attempt to allocate
  try
  {
  	Node<T> * newLocation = new Node <T> (newBox->data);
  	Node<T> * pCurrent = newLocation;

  	while(newBox->pNext)
  	{
  		newBox = newBox->pNext;
  		pCurrent->pNext = new Node <T> (newBox->data);
  		pCurrent = pCurrent->pNext;
  	}

  	return newLocation;
  }
  // catch otherwise 
  catch (std::bad_alloc)
  {
    throw "ERROR: Unable to allocate a new buffer for Node";
  }
}


/**********************************************
* Operator <<(): 
* Display the contents of a given linked-list.
**********************************************/
template <class T>
ostream & operator << (ostream & out, Node<T> * pHead)
{
   
	for (const Node<T> * p = pHead; p; p = p->pNext)
	{
		out << pHead->data; 
		if (pHead->pNext)
			out << ", ";
		pHead = pHead->pNext;
	}
	return out;
}

/************************************************
* INSERT:
* ADD UNIQUE ELEMENTS TO THE CONTAINER
*************************************************/
template<class T>
Node<T> * insert(const T & t, Node<T> * & pHead, bool next = false) 
{
	
	// allcate new node 
	Node<T> * pNew = new Node<T>(t);

	//if pHead is empty
	if (pHead == NULL) 
	{
		pHead = pNew;
		return pNew;
	}

	// move to the head
	if (pHead != NULL && next)
	{
		pNew->pNext = pHead;
		pHead = pNew;
		return pHead;
	}

	else
	{
		pNew->pNext = pHead->pNext;
		pHead->pNext = pNew;
		return pNew;
	}

}

/************************************************
* FIND:
* LOOK FOR ELEMENTS WE NEED
*************************************************/
template <class T>
Node<T> * find(Node<T> * pHead, const T & t)
{ 
	for (Node<T> * p = pHead; p; p = p->pNext)
	{
		if (p->data == t)
		{
			return p;
		}
	}

}

/************************************************
* DELETE:
* freeData ELEMENTS FROM THE CONTAINER
*************************************************/
template<class T>
void freeData(Node<T> * & pHead)
{
	for (Node<T> * p = pHead; p; p = p->pNext)
		delete p;
	    pHead = NULL;
}

#endif // Node_H