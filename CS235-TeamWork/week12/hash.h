/***********************************************************************
* Header:
*    Hash
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
*   Jefferson Santos & Andrew Larsen
*
************************************************************************/


#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <iomanip>
#include "list.h"
#include "bst.h"
#include "map.h"

/************************************************
* HASH
* An abstract Hash base class
************************************************/
template <class T>
class Hash
{
public:

   // constructors and destructor
   Hash() : numItems(0), numList(1) {}

   // non defalut constructor
   Hash(int numBuckets) throw (const char *); 
   Hash(const Hash <T> & rhs) : numItems(0), numList(1) { *this = rhs; } 
  ~Hash() {} 
   
   // find the item
    bool find(const T & t) const
    {
	    for (ListConstIterator <T> it = table[hash(t)].cbegin(); it != table[hash(t)].cend(); ++it)
       {
		
			if (t == *it)
				return true;
       }  
		return false;
    }

   // assignment operator
   Hash<T> & operator = (const Hash<T> & rhs) throw (const char *);
  
   // pure virtual function: hash
   virtual int hash(const T & t) const = 0;

   // we need to have access to the size
    int size() const     { return numItems;        } 

    // are we empty?
    bool empty() const   { return (numItems == 0); } 

    // we need to have access to the number of numBuckets
    int capacity() const { return numList;      }

    // insert into the hash
    void insert(const T & t)
   {
      assert(hash(t) >= 0 && hash(t) < capacity());
	  table[hash(t)].push_back(t);
      numItems++;
	  //numList++;
   }

   // display the bucket sizes
   void display ()
   {
      for (int i = 0; i < numList; i++)
      std::cout << std::setw(10) << i
      << " : " << table[i].size()
      << std::endl;
   } 
   
private:
   Map <int, List<T> > table; // the hash table
   int numItems; // number of items in the Hash
   int numList; // number of lists in the hash table
};

/***********************************************************************
 * NON-DEFAULT CONTRUCTOR
 ***********************************************************************/
template <class T>
Hash <T> :: Hash(int numBuckets) throw (const char *)
{
   numItems = 0;
   numList = numBuckets;
}

/**************************************************
* ASSIGNMENT OPERATOR
*************************************************/
template <class T>
Hash <T> & Hash <T> :: operator = (const Hash <T> & rhs) throw (const char *)
{
         numList = rhs.numList;
		 numItems = rhs.numItems;
		 table = rhs.table;
	return *this;
}

#endif // HASH_H