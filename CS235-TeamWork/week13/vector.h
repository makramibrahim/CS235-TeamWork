/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of a container: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    containers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *        Vector         : A class that holds stuff
 *        VectorIterator : An interator through Vector
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#define INVALID_INDEX    "ERROR: Invalid index"

#define CAPACITY_EXPANSION_MULTIPLIER 2

#define INSUFFICIENT_SPACE "ERROR: Insufficient space"

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

// forward declaration for VectorConstIterator
template <class T>
class VectorConstIterator;

/************************************************
 * VECTOR: A clone of std:vector
 ***********************************************/
template <class T>
class Vector
{
public:
   // destructor : free everything
   ~Vector()
   {
      if (capacityCount)
         delete [] items;
   }
   
   // default constructor : empty and kinda useless
   Vector() : sizeCount(0), capacityCount(0), items(NULL) {}
   
   // non-default constructor : pre-allocate
   Vector(int capacity) throw (const char *) : sizeCount(0), capacityCount(capacity)
   {
      assert(capacityCount >= 0);
      
      if (capacityCount == 0)
      {
         this->items = NULL;
      }
      else
      {
         allocate(capacityCount);
         this->initializeRemainingItems();
      }
   }
   
   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *)
   {
      *this = rhs; // delegate to the assignment operator (overridden)
   }
   
   // override the assignment operator
   Vector<T> & operator= (const Vector<T> & rhs) throw (const char *)
   {
      assert(rhs.capacityCount >= 0);
      
      if (rhs.capacityCount == 0)
      {
         capacityCount = sizeCount = 0;
         items = NULL;
         return *this;
      }
      
      allocate(rhs.capacityCount);
      
      // copy over the cap and size
      assert(rhs.sizeCount >= 0 && rhs.sizeCount <= rhs.capacityCount);
      capacityCount = rhs.capacityCount;
      sizeCount = rhs.sizeCount;
      
      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < sizeCount; i++)
         items[i] = rhs.items[i];
      
      initializeRemainingItems();
      
      return *this;
   }
   
   // is the container currently empty
   bool empty() const
   {
      return sizeCount == 0;
   }
   
   // remove all the items from the container
   void clear()
   {
      sizeCount = 0;
   }
   
   // how many items are currently in the container?
   int size() const
   {
      return sizeCount;
   }
   
   // how many items can I put on the Vector before full?
   int capacity() const
   {
      return capacityCount;
   }
   
   // return an iterator to the beginning of the list
   VectorIterator <T> begin()
   {
      return VectorIterator<T>(items);
   }
   
   // return an iterator to the end of the list
   VectorIterator <T> end()
   {
      return VectorIterator<T>(items + sizeCount);
   }
   
   // return a const iterator to the beginning of the list
   VectorConstIterator <T> cbegin() const
   {
      return VectorConstIterator<T>(items);
   }
   
   // return a const iterator to the end of the list
   VectorConstIterator <T> cend() const
   {
      return VectorConstIterator<T>(items + sizeCount);
   }
   
   // override the subscript operator
   T & operator[] (const int index)
   {
      boundsCheck(index);
      return items[index];
   }
   
   // override the subscript operator (const version)
   T & operator[] (const int index) const
   {
      boundsCheck(index);
      return items[index];
   }
   
   // Insert an item at the end of the collection, if there's room.
   void insert(const T item) throw (const char *)
   {
      if (sizeCount == capacityCount)
         throw INSUFFICIENT_SPACE;
      
      items[sizeCount] = item;
      sizeCount++;
   }
   
   // Add an item to the end of the collection, expanding capacity as needed.
   void push_back(const T item) throw (const char *)
   {
      if (sizeCount == capacityCount)
         grow();
         
         items[sizeCount] = item;
      sizeCount++;
   }
   
private:
   T * items;          // dynamically allocated array of T
   int sizeCount;      // how many items are currently in the Vector?
   int capacityCount;  // how many items can I put on the Vector before full?
   
   void boundsCheck(const int index) const
   {
      if (index < 0 || index >= sizeCount)
         throw INVALID_INDEX;
   }
   
   // allocate memory for the items
   void allocate(int cap)
   {
      try
      {
         items = new T[cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Vector.";
      }
   }
   
   // fill unused slots with default value for T
   void initializeRemainingItems() const
   {
      for (int i = sizeCount; i < capacityCount; i++)
         items[i] = T();
   }
   
   // Increase capacity of backing dynamic array.
   void grow()
   {
      if (capacityCount == 0)
         capacityCount++;
      else
         capacityCount *= CAPACITY_EXPANSION_MULTIPLIER;
      
      T* tempArray;
      try
      {
         tempArray = new T[capacityCount];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Vector.";
      }
      
      for (int i = 0; i < sizeCount; i++)
         tempArray[i] = items[i];
      
      delete[] items;
      items = tempArray;
      
      initializeRemainingItems();
   }
};

/**************************************************
 * VECTOR ITERATOR: An iterator through Vector
 *************************************************/
template <class T>
class VectorIterator
{
public:
   // default constructor
   VectorIterator() : p(NULL) {}
   
   // initialize to direct p to some item
   VectorIterator(T * p) : p(p) {}
   
   // copy constructor
   VectorIterator(const VectorIterator & rhs)
   {
      *this = rhs;
   }
   
   // assignment operator
   VectorIterator & operator = (const VectorIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }
   
   // equals operator
   bool operator == (const VectorIterator & rhs) const
   {
      return rhs.p == this->p;
   }
   
   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   }
   
   // dereference operator
   T & operator * ()
   {
      return *p;
   }
   
   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }
   
   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
      VectorIterator tmp(*this);
      p++;
      return tmp;
   }
   
   // prefix decrement
   VectorIterator <T> & operator -- ()
   {
      p--;
      return *this;
   }
   
   // postfix decrement
   VectorIterator <T> operator--(int postfix)
   {
      VectorIterator tmp(*this);
      p--;
      return tmp;
   }
   
private:
   T * p;
};

/**************************************************
 * VECTOR ITERATOR: An iterator through Vector
 *************************************************/
template <class T>
class VectorConstIterator
{
public:
   // default constructor
   VectorConstIterator() : p(NULL) {}
   
   // initialize to direct p to some item
   VectorConstIterator(T * p) : p(p) {}
   
   // copy constructor
   VectorConstIterator(const VectorConstIterator & rhs)
   {
      *this = rhs;
   }
   
   // assignment operator
   VectorConstIterator & operator = (const VectorConstIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }
   
   // equals operator
   bool operator == (const VectorConstIterator & rhs) const
   {
      return rhs.p == this->p;
   }
   
   // not equals operator
   bool operator != (const VectorConstIterator & rhs) const
   {
      return rhs.p != this->p;
   }
   
   // dereference operator
   T & operator * ()
   {
      return *p;
   }
   
   // prefix increment
   VectorConstIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }
   
   // postfix increment
   VectorConstIterator <T> operator++(int postfix)
   {
      VectorConstIterator tmp(*this);
      p++;
      return tmp;
   }
   
   // prefix decrement
   VectorConstIterator <T> & operator -- ()
   {
      p--;
      return *this;
   }
   // postfix decrement
   VectorConstIterator <T> operator--(int postfix)
   {
      VectorConstIterator tmp(*this);
      p--;
      return tmp;
   }
   
private:
   T * p;
};

#endif // VECTOR_H
