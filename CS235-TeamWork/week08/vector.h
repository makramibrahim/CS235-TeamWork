/***********************************************************************
* Header:
*    Vector
* Summary:
*    This class contains the notion of a Vector: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Vector
* Author
*    Makram Ibrahim
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>
#include <iostream>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

// forward declaration for VectorConstIterator
template <class T>
class VectorConstIterator;

/************************************************
 * CONTAINER
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), vCapacity(0), data(NULL) {}

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int vCapacity) throw (const char *);
   
   // destructor : free everything
   ~Vector()        { if (vCapacity) delete [] data; }


   /*************************************************
   * SET all required functions for vector class 
   **************************************************/

     // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
   void clear()        { numItems = 0;                 }

   // how many items are currently in the container?
   int size() const    { return numItems;              }

   // add an item to the container
  // void insert(const T & t) throw (const char *);
   void push_back(const T & t) throw (const char *);
  
   // return the capacity
   int capacity() const { return vCapacity; }

    // assignment operator
   Vector<T>& operator=(const Vector<T> &rhs) throw (const char *)
  {
    if(rhs.numItems == 0)
    {
      vCapacity = numItems = 0;
      data = NULL;
    }

    vCapacity = rhs.vCapacity;
    numItems = rhs.numItems;

    try 
    {
      data = new T[vCapacity];
    }
    catch (std::bad_alloc) {
      throw "ERROR: Unable to allocate buffer";
    }

    for (int i = 0; i < numItems; i++) {
      data[i] = rhs.data[i];
    }

    return *this;
  }
  
   // square bracket operator
   T& operator [](int index) throw (const char *)  
   {
      if (index < 0 || index >= numItems) 
      {
        throw "ERROR";
      }

      return data[index];

   }


   const T& operator [](int index) const throw (const char *)
   {
      if (index < 0 || index >= numItems) 
      {
        throw "ERROR";
      }

      return data[index];

   }

   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}

   // return an iterator to the beginning of the list
   VectorConstIterator <T> cbegin() const
         { return VectorConstIterator<T>(data); }

   // return an iterator to the end of the list
   VectorConstIterator <T> cend() const
         { return VectorConstIterator<T>(data + numItems);}

private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Vector?
   int vCapacity;      // how many items can I put on the Vector before full?
};

/**************************************************
 * Vector ITERATOR
 * An iterator through Vector
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
   VectorIterator(const VectorIterator & rhs) { *this = rhs; }

   /* VectorIterator <T>::iterator it;
      for (it = rhs.begin(); it != rhs.end(); ++it)
         *it; */

   // assignment operator
   VectorIterator & operator = (const VectorIterator & lhs)
   {
      this->p = lhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const VectorIterator & lhs) const
   {
      return lhs.p != this->p;
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
   
  private:
   T * p;
};

/*******************************************
 * Vector :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
   assert(rhs.vCapacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.vCapacity == 0)
   {
      vCapacity = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.vCapacity];
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the vCapacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.vCapacity);
   vCapacity = rhs.vCapacity;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < vCapacity; i++)
      data[i] = T();
}

/**********************************************
 * Vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Vector to "vCapacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int vCapacity) throw (const char *)
{
   assert(vCapacity >= 0);
   
   // do nothing if there is nothing to do
   if (vCapacity == 0)
   {
      this->vCapacity = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[vCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->vCapacity = vCapacity;
   this->numItems = 0;

   // initialize the Vector by calling the default constructor
   for (int i = 0; i < vCapacity; i++)
      data[i] = T();
}

/***************************************************
 * Vector :: Push_Back
 * Insert an item on the end of the Vector
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T & t) throw (const char *)
{

   if (vCapacity == 0)
   {
      this->vCapacity = 1;
   }

    if (vCapacity == numItems)
  {
    vCapacity *= 2; 
    }

   // attempt to allocate
   try
   {
      T * text = new T[vCapacity];
      for (int i = 0; i < numItems; i++)
           text[i] = data[i];
      delete[] data;
       data = text;
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
     

    // copy over the stuff
   //data = data;
  // this->vCapacity = vCapacity;
   //this->numItems = numItems;        
   data[numItems++] = t;


     // std::cerr << "YOUR_TEXT";

}

#endif // VECTOR_H

