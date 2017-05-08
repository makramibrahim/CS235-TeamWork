/***********************************************************************
* Header:
*    Stack
* Summary:
*    This class contains the notion of a Stack: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the Stack, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Stack         : A class that holds stuff
*        StackIterator : An interator through Stack
* Author
*    Makram Ibrahim
************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert>
#include <iostream>

// forward declaration for StackIterator
template <class T>
class StackIterator;

// forward declaration for StackConstIterator
template <class T>
class StackConstIterator;

/************************************************
 * CONTAINER
 * A class that holds stuff
 ***********************************************/
template <class T>
class Stack
{
public:
   // default constructor : empty and kinda useless
   Stack() : numElements(0), numCapacity(0), data(NULL) {}

   // non-default constructor : pre-allocate
   Stack(int numCapacity) throw (const char *);

   // copy constructor : copy it
   Stack(const Stack & rhs) throw (const char *);
   
   // destructor : free everything
   ~Stack()        { if (numCapacity) delete [] data; }

   /**********************************************************
   * Operator=: Assignment operator. This method takes a Stack as 
   * a parameter and copies all the elements to this. If the current 
   * buffer size is sufficient, not allocation is made. If the current
   * buffer size is not sufficient, enough space is allocated to accomodate 
   * the new data. If there is insufficient memory to allocate a new buffer, 
   * then the following exception is thrown:ERROR: Unable to allocate a 
   * new buffer for Stack. It also returns *this by-reference as all 
   * assignment operators should
   ***************************************************************/
    Stack<T>& operator=(const Stack<T> &rhs) throw (const char *)
   {
      if(rhs.numElements == 0)
      {
         numCapacity = numElements = 0;
         data = NULL;
      }

      numCapacity = rhs.numCapacity;
      numElements = rhs.numElements;

      try 
      {
         data = new T[numCapacity];
      }
      catch (std::bad_alloc) {
         throw "ERROR: Unable to allocate a new buffer for Stack.";
      }

      for (int i = 0; i < numElements; i++) {
         data[i] = rhs.data[i];
      }

      return *this;
   }
 
   /***************************************************
   * empty(): Test whether the stack is empty.This method 
   * takes no parameters and returns a Boolean value.
   **************************************************/
   bool empty() const  { return numElements == 0;         }


  /****************************************************
  * size(): Return the stack size. This method takes no 
  * parameters and returns an integer value.
  *******************************************************/
   int size() const    { return numElements;              }



  /****************************************************
  * capacity(): Return the number of elements that can be 
  * held in the currently allocated storage. This method
  *  takes no parameters and returns an integer value.
  *******************************************************/
   int capacity() const { return numCapacity;            }



  /*****************************************************
  * clear(): Clear the contents. This method takes no 
  * parameters and returns nothing. Note that you do not
  *  need to free the allocated memory; just set the size 
  * member variable to zero.
  *******************************************************/
   void clear()        { numElements = 0;                 }

 
  /******************************************************
  * push(): Adds an item to the container. This method takes 
  * a single parameter (the item to be added to the end of the 
  * stack) and has no return value. Note that if the stack is 
  * full, then the capacity will be doubled. In the case of an 
  * allocation error, the following c-string exception will be throw:
  * ERROR: Unable to allocate a new buffer for Stack
  *****************************************************************/
   void push(const T & t) throw (const char *);

  
  /*******************************************************
  * pop(): Removes an item from the end of the stack, serving 
  * to reduce the size by one. Note that if the stack is already 
  * empty, the following c-string exception will be thrown:
  * ERROR: Unable to pop from an empty Stack
  *********************************************************/
   void pop() throw (const char *)
   {
     if (empty())
     {
         throw "ERROR: Unable to pop from an empty Stack";
     }
     else 
     {
         numElements--;
     }

   }

   /***************************************************
   * top(): Returns the item currently at the end of the stack. 
   * This item is returned by-reference so the last item can be 
   * changed through the top() method. If the stack is currently
   * empty, the following exception will be thrown:
   * ERROR: Unable to reference the element from an empty Stack 
   ************************************************************/
   T top() throw (const char *)
   {
      if (!empty()) 
      {
         return data[size() -1];
      }
      else
      {
         throw "ERROR: Unable to reference the element from an empty Stack";
      }
   }

   // return an iterator to the beginning of the list
   StackIterator <T> begin() { return StackIterator<T>(data); }

   // return an iterator to the end of the list
   StackIterator <T> end() { return StackIterator<T>(data + numElements);}

   // return an iterator to the beginning of the list
   StackConstIterator <T> cbegin() const
         { return StackConstIterator<T>(data); }

   // return an iterator to the end of the list
   StackConstIterator <T> cend() const
         { return StackConstIterator<T>(data + numElements);}

private:
   T * data;          // dynamically allocated array of T
   int numElements;      // how many items are currently in the Stack?
   int numCapacity;      // how many items can I put on the Stack before full?
};

/**************************************************
 * Stack ITERATOR
 * An iterator through Stack
 *************************************************/
template <class T>
class StackIterator
{
  public:
   // default constructor
  StackIterator() : p(NULL) {}

   // initialize to direct p to some item
  StackIterator(T * p) : p(p) {}

   // copy constructor
   StackIterator(const StackIterator & rhs) { *this = rhs; }

   // assignment operator
   StackIterator & operator = (const StackIterator & lhs)
   {
      this->p = lhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const StackIterator & lhs) const
   {
      return lhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   StackIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   StackIterator <T> operator++(int postfix)
   {
      StackIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/*******************************************
 * Stack :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
   assert(rhs.numCapacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numCapacity == 0)
   {
      numCapacity = numElements = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.numCapacity];
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the numCapacity and size
   assert(rhs.numElements >= 0 && rhs.numElements <= rhs.numCapacity);
   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numElements; i < numCapacity; i++)
      data[i] = T();
}

/**********************************************
 * Stack : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Stack to "numCapacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int numCapacity) throw (const char *)
{
   assert(numCapacity >= 0);
   
   // do nothing if there is nothing to do
   if (numCapacity == 0)
   {
      this->numCapacity = this->numElements = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->numCapacity = numCapacity;
   this->numElements = 0;

   // initialize the Stack by calling the default constructor
   for (int i = 0; i < numCapacity; i++)
      data[i] = T();
}

/***************************************************
 * Stack :: Push_Back
 * Insert an item on the end of the Stack
 **************************************************/
template <class T>
void Stack <T> :: push(const T & t) throw (const char *)
{

   if (numCapacity == 0)
   {
      this->numCapacity = 1;
   }

   	if (numCapacity == numElements)
	{
		numCapacity *= 2;	
    }

   // attempt to allocate
   try
   {
      T * text = new T[numCapacity];
      for (int i = 0; i < numElements; i++)
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
  // this->numCapacity = numCapacity;
   //this->numElements = numElements;        
   data[numElements++] = t;


     // std::cerr << "YOUR_TEXT";

}

#endif // Stack_H

