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
#include <cassert>     // for ASSERT
#include <iostream>    // for NULL

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <class T>
class Node
{
public:
   // default constructor: set pointers to NULL.  This is the only reason
   // why Node is not a structure
   Node() : pNext(NULL), pPrev(NULL), data() {}

   // non-default.  Initialize data as we create the node
   Node(const T & data) : pNext(NULL), pPrev(NULL), data(data) {}

   T data;                 // user data
   Node <T> * pNext;       // pointer to next node
   Node <T> * pPrev;       // pointer to previous node
};

// forward declaration for ListIterator.  This will work for
// both the forward iterator and the reverse iterator
template <class T>
class ListIterator;

// we need a constant iterator also even though it is so redundant
template <class T>
class ListConstIterator;

/**************************************************
 * LIST
 * Generic linked list class. Supports the following:
 *    =          : copy one list onto another
 *    ERASE      : empty the list
 *    EMPTY      : is the list currently empty?
 *    PUSH_BACK  : add an item to the tail
 *    PUSH_FRONT : add an item to the head of the list
 *    BACK       : returns the last element in the list
 *    FRONT      : returns the first element in the list
 *    INSERT     : add an item to a location somewhere in the middle
 *    iterators  : forward and backward iterators, const and non-const
 **************************************************/
template <class T>
class List
{
public:
   // default constructor: the empty List
   List() : numItems(0), pHead(NULL), pTail(NULL) {}

   // copy constructor
   List(const List <T> & rhs) throw (const char *) :
          pHead(NULL), pTail(NULL), numItems(0) { *this = rhs; }

   // destructor: remove all elements
  ~List() { clear(); }

   // assignment operator
   List <T> & operator = (const List <T> & rhs) throw (const char *);
  
   // remove all the items in the list
   void clear();

   // is the list currently empty?
   bool empty() const { return (pHead == NULL); }

   // how many items are currently in the list
   int size() const { return numItems; }
   
   // add an item to the end of the list
   void push_back(const T & data) throw (const char *);

   // add an item to the head of the list
   void push_front(const T & data) throw (const char *);

   // returns the last element in the list
   T & back() throw (const char *);

   // returns the first element in the list
   T & front() throw (const char *);
   
   // add an item to the middle of the list
   ListIterator <T> insert(ListIterator <T> & it, const T & data)
      throw (const char *);

   // remove an item from the list
   ListIterator <T> remove(ListIterator <T> & it) throw (const char *);
   
   // iterator stuff
   ListIterator <T> begin()   { return ListIterator  <T> (pHead); }
   ListIterator <T> end()     { return ListIterator  <T> (NULL);  }
   ListIterator <T> rbegin()  { return ListIterator  <T> (pTail); }
   ListIterator <T> rend()    { return ListIterator  <T> (NULL);  }

   // constant iterator stuff
   ListConstIterator<T>cbegin()  const { return ListConstIterator<T>(pHead); }
   ListConstIterator<T>cend()    const { return ListConstIterator<T>(NULL);  }
   ListConstIterator<T>crbegin() const { return ListConstIterator<T>(pTail); }
   ListConstIterator<T>crend()   const { return ListConstIterator<T>(NULL);  }

private:
   int numItems;
   Node <T> * pHead;    // pointer to the beginning of the list
   Node <T> * pTail;    // pointer to the ending of the list
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
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
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
 *     INPUT  :
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
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
 *    INPUT  : data to be added to the list
 *    OUTPUT :
 *    COST   : O(1)
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
         pHead = pNew;   // there is no tail so there is no head!
      
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
 * LIST :: PUSH FRONT
 * add an item to the head of the list
 *     INPUT  : data to be added to the list
 *     OUTPUT :
 *     COST   : O(1)
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
 * LIST :: FRONT
 * retrieves the first element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
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
 * LIST :: BACK
 * retrieves the last element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
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
 *     INPUT  : an iterator to the item being removed
 *     OUTPUT : iterator to the new location 
 *     COST   : O(1)
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
   if (it.p->pNext)   // not the last element
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
 *     INPUT  : data to be added to the list
 *              an iterator to the location where it is to be inserted
 *     OUTPUT : iterator to the new item
 *     COST   : O(1)
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

   // make sure pHead and pTail are correctly set
   assert(pTail && pHead);
   assert(pHead->pPrev == NULL);
   assert(pTail->pNext == NULL);

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

#endif // LIST_H