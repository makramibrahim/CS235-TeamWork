/***********************************************************************
* Header:
*    List
* Summary:
*    This class contains the notion of a Deque: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the Deque, List, Deque, Deque, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Deque         : A class that holds stuff
*        DequeIterator : An interator through Deque
* Author
*   <your name>
*    
************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <iostream>

/**************************************************
* Node: CONTAINER CLASS
* A class that holds uniqe items
****************************************************/
template<class T>
class Node {
public:
  T data;          // store all the data here      
  Node<T> *pNext; // point to next node
  Node<T> *pPrev; // point to previous node
  
  // create default constructor: empty 
  Node(): pNext(NULL), pPrev(NULL), data() {}

  // creat a non-default constructor: per-allocate
  Node(const T & data): pNext(NULL), pPrev(NULL), data(data) {}


};

//declare for ListIterator
template <class T>
class ListIterator;

// forward declaration for VectorConstIterator
template <class T>
class ListConstIterator;

/**************************************************
* List: CONTAINER CLASS
* A class that holds uniqe items
****************************************************/
template<class T>
class List {

public:
  ////////////////Constructors//////////////////

  // create default constructor: empty 
  List() : numItems (0), pHead(NULL), pTail(NULL) {}

  // copy constructor : copy all the stuff to right hand side!
  List(const List <T> & rhs) throw (const char *): 
   pHead(NULL), pTail(NULL), numItems(0) { *this = rhs; }

  // destructor: free everything
  ~List() { clear(); }


  ///////////////////Operators///////////////////

  // Operator=: Assignment operator
  List<T> & operator = (const List<T> & rhs) throw (const char*);

  //copy List and its all elements
  void copyList(const List<T> &rhs);

  // allocate and held the data in a new array
  void allocate(int newIndex) throw(const char *);

  /////////////////Member functions///////////////

  // size(): Return the Deque size. 
  int size()      const { return numItems ; }

  // empty(): Test whether the List is empty
  bool empty()    const { return pHead == NULL; }

  // clear(): Empties the List of all items.
  void clear();

  // resize(): add more size when it's needed
  void resize(int & newSize) throw (const char *);

  // push_back(): Adds an item to the back of the list. 
  void push_back (const T & data) throw (const char *);

  // push_front(): Adds an item to the front, the same as push_back().
  void push_front(const T & data) throw (const char *);

  // back(): Returns the item currently at the back the same as front().
  T & back()  throw (const char *);
 
  // front(): Returns the item currently at the front of the list.
  T & front() throw (const char *);
  
  //////////////ListIterators/////////////

  // insert(): add or insert the desired elements
  ListIterator <T> insert(ListIterator <T> & it, const T & data) throw (const char *);

  //remove(): Remove an element from the List. 
  ListIterator <T> remove(ListIterator <T> & it) throw (const char *);

  // begin(): return an iterator to the first element
  ListIterator<T> begin()  { return ListIterator<T>(pHead); }

  // end(): return an iterator refering to the past-the-end e
  ListIterator<T> end()   { return ListIterator<T>(NULL); }

  // rbegin(): Return an iterator to the last element in the list.
  ListIterator <T> rbegin()  { return ListIterator  <T> (pTail); }

  // rbegin(): Return an iterator to the last element in the list.
  ListIterator <T> rend()    { return ListIterator  <T> (NULL);  }


private:
  Node<T> * pHead; // beginning of the list
  Node<T> * pTail; // end of the list
  int numItems;   //    
  
};

/*************************************************
 * LIST ITERATOR
 * Iterate through a List, non-constant version
 ************************************************/
template <class T>
class ListIterator
{
public:
   // default constructor: not pointing to anything
   ListIterator() : p(NULL) {}

   // non-default constrictor taking a pointer as a parameter
   ListIterator(Node <T> * p) : p(p) {}

   // copy constructor
   ListIterator(const ListIterator <T> & rhs) : p(rhs.p) {}

   // assignment operator
   ListIterator <T> & operator = (const ListIterator <T> & rhs)
   {
      p = rhs.p;
      return *this;
   }
   
   // dereference operator, fetch a node
   T & operator * () throw (const char *)
   {
      if (p)
         return p->data;
      else
         throw "ERROR: Trying to dereference a NULL pointer";
   }

   // equals operator: are the iterators the same?
   bool operator == (const ListIterator <T> & rhs) const
   {
      return rhs.p == this->p;
   }

   // not-equals operator: are the iterators different?
   bool operator != (const ListIterator <T> & rhs) const
   {
      return rhs.p != this->p;
   }

   // postfix increment
   ListIterator <T> operator ++ (int postfix)
   {
      ListIterator <T> old(*this);
      assert(p);
      p = p->pNext;
      return old;
   }

   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      assert(p);
      p = p->pNext;
      return *this;
   }
   
   // postfix decrement
   ListIterator <T> operator -- (int postfix)
   {
      ListIterator <T> old(*this);
      assert(p);
      p = p->pPrev;
      return old;
   }

   // prefix decrement
   ListIterator <T> & operator -- ()
   {
      assert(p);
      p = p->pPrev;
      return *this;
   }

   // two friends who need to access p directly
   friend ListIterator <T> List <T> :: insert(ListIterator <T> & it,
                                              const T & data)
                                    throw (const char *);
   friend ListIterator <T> List <T> :: remove(ListIterator <T> & it)
                                    throw (const char *);
private:
   Node <T> * p;
};

/*************************************************
 * LIST CONST ITERATOR
 * Iterate through a List, the constant version
 ************************************************/
template <class T>
class ListConstIterator
{
public:
   // default constructor: not pointing to anything
   ListConstIterator() : p(NULL) {}

   // non-default constrictor taking a pointer as a parameter
   ListConstIterator(const Node <T> * p) : p(p) {}

   // copy constructor
   ListConstIterator(const ListConstIterator <T> & rhs) : p(rhs.p) {}

   // assignment operator
   ListConstIterator <T> & operator = (const ListConstIterator <T> & rhs)
   {
      p = rhs.p;
      return *this;
   }
   
   // dereference operator, fetch a node
   // this is the only real difference between ListConstIterator and the other
   T operator * () const { return p->data; }

   // equals operator: are the iterators the same?
   bool operator == (const ListConstIterator <T> & rhs) const
   {
      return rhs.p == this->p;
   }

   // not-equals operator: are the iterators different?
   bool operator != (const ListConstIterator <T> & rhs) const
   {
      return rhs.p != this->p;
   }

   // postfix increment
   ListConstIterator <T> operator ++ (int postfix)
   {
      ListConstIterator <T> old(*this);
      assert(p);
      p = p->pNext;
      return old;
   }

   // prefix increment
   ListConstIterator <T> & operator ++ ()
   {
      assert(p);
      p = p->pNext;
      return *this;
   }
   
   // postfix decrement
   ListConstIterator <T> operator -- (int postfix)
   {
      ListConstIterator <T> old(*this);
      assert(p);
      p = p->pPrev;
      return old;
   }

   // prefix decrement
   ListConstIterator <T> & operator -- ()
   {
      assert(p);
      p = p->pPrev;
      return *this;
   } 
   
private:
   const Node <T> * p;
};

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *********************************************/
template <class T>
List <T> & List <T> :: operator = (const List <T> & rhs) throw (const char *)
{
   // erase all the existing elements
   clear();

   // now allocate the new nodes
   for (Node <T> * p = rhs.pHead; p; p = p->pNext)
      push_back(p->data); // this could throw

   // return the new buffer
   return *this;
}

/**********************************************
 * LIST :: CLEAR
 * Remove all the items currently in the linked list
 *********************************************/
template <class T>
void List <T> :: clear()
{
   // loop through the entire list, removing everything
   Node <T> * pNext;
   for (Node <T> * p = pHead; p; p = pNext)
   {
      pNext = p->pNext;
      delete p;
   }
   pHead = pTail = NULL;
   numItems = 0;
}

/*********************************************
 * LIST :: PUSH BACK
 * add an item to the end of the list
 *********************************************/
template <class T>
void List <T> :: push_back(const T & data) throw (const char *)
{
   try
   {
      // create the node
      Node <T> * pNew = new Node <T> (data);

      // point it to the old tail
      pNew->pPrev = pTail;

      // now point tail to the new guy
      if (pTail != NULL)
         pTail->pNext = pNew;
      else
         pHead = pNew;   
      
      // finally, this is the new tail
      pTail = pNew;
      numItems++;
   }
   catch (...)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/*********************************************
 * LIST :: FRONT
 * retrieves the first element in the list
 *********************************************/
template <class T>
T & List <T> :: front() throw (const char *)
{
   if (pHead != NULL)
      return pHead->data;
   else
      throw "ERROR: unable to access data from an empty list";
}

/*********************************************
 * LIST :: PUSH FRONT
 * add an item to the head of the list
 *********************************************/
template <class T>
void List <T> :: push_front(const T & data) throw (const char *)
{
   try
   {
      // create the node
      Node <T> * pNew = new Node <T> (data);

      // point it to the old head
      pNew->pNext = pHead;

      // now point head to the new guy
      if (pHead != NULL)
         pHead->pPrev = pNew;
      else
         pTail = pNew;       // there is no head so there is no tail!

      // finally, this is the new head
      pHead = pNew;
      numItems++;
   }
   catch (...)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/*********************************************
 * LIST :: BACK
 * retrieves the last element in the list
 *********************************************/
template <class T>
T & List <T> :: back() throw (const char *)
{
   if (pHead != NULL)
      return pTail->data;
   else
      throw "ERROR: unable to access data from an empty list";
}

/******************************************
 * LIST :: REMOVE
 * remove an item from the middle of the list
 ******************************************/
template <class T>
ListIterator <T> List <T> :: remove(ListIterator <T> & it) throw (const char *)
{
   ListIterator <T> itNext = end();
   
   // invalid iterator case
   if (it == end())
      throw "ERROR: unable to remove from an invalid location in a list";
   assert(pHead && pTail);
   
   // fixup everything after the current location
   if (it.p->pNext)   
   {
      it.p->pNext->pPrev = it.p->pPrev;
      itNext = it.p->pNext;
   }
   else  // are the last element
      pTail = pTail->pPrev;

   // fixup everything before the current location
   if (it.p->pPrev) // not the first element
      it.p->pPrev->pNext = it.p->pNext;
   else
      pHead = pHead->pNext;

   // delete self and return
   delete it.p;
   numItems--;
   return itNext;
}

/******************************************
 * LIST :: INSERT
 * add an item to the middle of the list
 ******************************************/
template <class T>
ListIterator <T> List <T> :: insert(ListIterator <T> & it, const T & data)
               throw (const char *)
{
   // empty list case
   if (pHead == NULL)
   {
      assert(pTail == NULL);
      pHead = pTail = new Node <T> (data);
      return begin();
   }

   try
   { 
      Node <T> * pNew = new Node <T> (data);

      // end of list case
      if (it == end())
      {
         // update pTail as appropriate
         pTail->pNext = pNew;
         pNew->pPrev = pTail;
         pTail = pNew;

         // update the iterator
         it = pNew;
      }
         // otherwise we have a valid iterator
      else
      {
         // set pNext and pPrev
         pNew->pPrev = it.p->pPrev;
         pNew->pNext = it.p;

         // update who pNext and pPrev point to
         if (pNew->pPrev)
            pNew->pPrev->pNext = pNew;
         else
            pHead = pNew;
         if (pNew->pNext)
            pNew->pNext->pPrev = pNew;
         else
            pTail = pNew;

         it = pNew;
      }
      numItems++;
   }
   catch (...)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }

   return it;
}

#endif // List_H