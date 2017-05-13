/***********************************************************************
* Header:
*    Deque
* Summary:
*    This class contains the notion of a Deque: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the Deque, set, Deque, Deque, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Deque         : A class that holds stuff
*        DequeIterator : An interator through Deque
* Author
*    Makram Ibrahim
************************************************************************/

#ifndef Deque_H
#define Deque_H

#include <cassert>
#include <iostream>
#include <deque>

// forward declaration for DequeIterator
template <class T>
class DequeIterator;

// forward declaration for DequeConstIterator
template <class T>
class DequeConstIterator;

/************************************************
 * CONTAINER
 * A class that holds stuff
 ***********************************************/
template <class T>
class Deque
{
public:
   // default constructor : empty and kinda useless
   Deque() : numElements(0), numCapacity(0), data(NULL), iHead(0), iTail(0) 
   { allocateNewMemory(numCapacity);}

   // non-default constructor : pre-allocate
   Deque(int numCapacity) throw (const char *);

   // copy constructor : copy it
   Deque(const Deque & rhs) throw (const char *);
   
   // destructor : free everything
   ~Deque()        { if (numCapacity) delete [] data; }

   /**********************************************************
   * Operator=: Assignment operator. This method takes a Deque as 
   * a parameter and copies all the elements to this. If the current 
   * buffer size is sufficient, not allocation is made. If the current
   * buffer size is not sufficient, enough space is allocated to accomodate 
   * the new data. If there is insufficient memory to allocate a new buffer, 
   * then the following exception is thrown:ERROR: Unable to allocate a 
   * new buffer for Deque. It also returns *this by-reference as all 
   * assignment operators should
   ***************************************************************/
    Deque<T>& operator=(const Deque<T> &rhs) throw (const char *)
   {
      if(rhs.numElements == 0)
      {
         numCapacity = numElements = 0;
         data = NULL;
      }
    
        numCapacity = rhs.numCapacity;
        numElements = rhs.numElements;
        iHead = rhs.iHead;
        iTail = rhs.iTail;

      try 
        {
           data = new T[numCapacity];
        }
      catch (std::bad_alloc) 
        {
            throw "ERROR: Unable to allocate a new buffer for Deque.";
        }
     
       int index = iHead;
       for (int i = 0; i < numElements; i++) 
       {
         data[i] = rhs.data[index];
         index = (index + 1) % numCapacity;

       }

      return *this;
   }
 
   /***************************************************
   * empty(): Test whether the Deque is empty.This method 
   * takes no parameters and returns a Boolean value.
   **************************************************/
   bool empty() const  { return numElements == 0;       }


  /****************************************************
  * size(): Return the Deque size. This method takes no 
  * parameters and returns an integer value.
  *******************************************************/
   int size() const    { return numElements;              }



  /****************************************************
  * capacity(): Return the current capacity of the deque. 
  * That is, the number of elements the deque is able to 
  * store without reallocating.
  *******************************************************/
   int capacity() const { return numCapacity;            }



  /*****************************************************
  * clear():  Empties the deque of all items. 
  * There are no parameters and no return value.
  *******************************************************/
   void clear()        { numElements = 0;                 }

  /*******************************************************
  * push_front(): Adds an item to the front of the deque exactly 
  * the same as push_back().
  *********************************************************/
   void push_front(const T & t) throw (const char *);

  /****************************************************
  * push_back(): Adds an item to the back of the deque. 
  * This method takes a single parameter (the item to be 
  * added to the end of the deque) and has no return value. 
  * Note that if the deque is full, then the capacity will 
  * be doubled. In the case of an allocation error, the following 
  * c-string exception will be thrown: ERROR: Unable to allocate
  *  a new buffer for deque
  *****************************************************/
   void push_back(const T & t) throw (const char *);

  
  /*******************************************************
  * pop(): Removes an item from the back of the Deque, serving 
  * to reduce the size by one. Note that if the Deque is already 
  * empty, the following c-string exception will be thrown:
  * ERROR: Unable to pop from an empty Deque
  *********************************************************/
   void  pop_back() throw (const char *)
   {
       if (!empty())
       {
          iTail = (iTail - 1 + numCapacity) % numCapacity;
          numElements--;
       }
       else 
         {
            throw "ERROR: unable to pop from the back of empty deque";
         }


    }
  /*******************************************************
  * pop_front(): Removes an item from the front of the deque 
  * exactly the same as pop_front().
  *********************************************************/
   void  pop_front() throw (const char *)
   {
       if (!empty())
       {
          iHead = (iHead + 1) % numCapacity;
          numElements--;
       }
       else 
         {
            throw "ERROR: unable to pop from the front of empty deque";
         }

    }

   /***************************************************
   * front(): Returns the item currently at the front of the Deque. 
   * This item is returned by-reference so the last item can be 
   * changed through the front() method. If the Deque is currently
   * empty, the following exception will be thrown:
   * ERROR: Unable to reference the element from an empty Deque 
   ************************************************************/
   T & front() throw (const char *)
   {
      if (!empty()) 
      {
         return array(iHead);
      }
      else
      {
         throw "ERROR: unable to access data from an empty deque";
      }
   }

   /***************************************************
   * back(): Returns the item currently at the back of the 
   * deque exactly the same as front().
   ************************************************************/
   T & back() throw (const char *)
   {
   	 
      if (iTail != 0) 
      {
         return array(iTail -1);
      }
      else
      {
        //throw "ERROR: unable to access data from an empty deque";
        return array(iTail);
      }
   }

   /***************************************************
   * array(): wrap deque when needed
   ****************************************************/
   T & array(int index) throw (const char *)
   {
   	 if (!empty()) 
   	 {
   	 	return data[index];
   	 }
   	 else
   	 {
   	 	throw "ERROR: unable to access data from an empty deque";
   	 }
   }

   /*****************************************
   * Now we will be pushing onto the front. This will require our index
   * to go negative. We will need some logic to turn a negative deque index
   * into a positive array index
   ******************************************/
   void allocateNewMemory(int memory) throw (const char *)
   {
   	try 
   	{
   		data = new T[memory];
   	}

   	catch(std::bad_alloc)
   	{
   		throw "ERROR: unable to allocate a new buffer from deque";
   	}
   
   }


private:
   T * data;             // dynamically allocated array of T
   int numElements;      // how many items are currently in the Deque?
   int numCapacity;      // how many items can I put on the Deque before full?
   int iTail;
   int iHead;
};

/**************************************************
 * Deque ITERATOR
 * An iterator through Deque
 *************************************************/
template <class T>
class DequeIterator
{
  public:
   // default constructor
  DequeIterator() : p(NULL) {}

   // initialize to direct p to some item
  DequeIterator(T * p) : p(p) {}

   // copy constructor
   DequeIterator(const DequeIterator & rhs) { *this = rhs; }

   // assignment operator
   DequeIterator & operator = (const DequeIterator & lhs)
   {
      this->p = lhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const DequeIterator & lhs) const
   {
      return lhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   DequeIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   DequeIterator <T> operator++(int postfix)
   {
      DequeIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/*******************************************
 * Deque :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *)
{
   assert(rhs.numCapacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numCapacity == 0)
   {
      numCapacity = numElements = 0;
      iHead = iHead = 0;
      data = NULL;
      return;
   }

   // copy over the numCapacity and size
   assert(rhs.numElements >= 0 && rhs.numElements <= rhs.numCapacity);
   this->numCapacity = rhs.numCapacity;
   this->numElements = rhs.numElements;
   this->iHead = rhs.iHead;
   this->iTail = rhs.iTail;
   
      // attempt to allocate
  
      try
      {
         data = new T[numCapacity]; 
        for (int i = 0; i < numCapacity; i++)
        data[i] = rhs.data[i];         
      }

      catch (std::bad_alloc)
      {
          throw "ERROR: Unable to allocate buffer";
      }

     int front = iHead;

      for (int i = 0; i < numElements; i++)
      {
         data[front] = rhs.data[front];
         front = (front + 1) % numCapacity;
      } 
  
   // the rest needs to be filled with the default value for T
    //for (int i = numElements; i < numCapacity; i++)
     //data[i] = T();
}

/**********************************************
 * Deque : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Deque to "numCapacity"
 **********************************************/
template <class T>
Deque <T> :: Deque(int numCapacity) throw (const char *)
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
   this->iTail = 0;
   this->iHead = 0;

   // initialize the Deque by calling the default constructor
   for (int i = 0; i < numCapacity; i++)
      data[i] = T();
}


/***************************************************
 * Deque :: Push_front
 * Insert an item on the front of the Deque
 **************************************************/
template <class T>
void Deque <T> :: push_front(const T & t) throw (const char *)
{
    int newCapacity;
    int front = iHead;

    if (numCapacity > 0) 
    {
        front = (iHead + 1) % numCapacity;
    }
    // check the capacity if is empty 
    if (numCapacity == empty() || (numCapacity - size()) == 0)
    {
        if (numCapacity == 0) 
        {
            newCapacity = 4; // set 4 even though size is 0
        }

        else 
        {
            newCapacity = (numCapacity * 2);
        }

        // attempt to allocate
        try 
        {
           // create new allocation if the size is full 
             T * newData = new T[numCapacity];
            for (int i = 0; i < size(); i++) 
            {
              int index = (i + iHead) % size();
              newData[i] = data[index];
            }

            delete[] data;
            data = new T[newCapacity];
            numCapacity = newCapacity;

            // correct new allocation for iHead and iHead
            iHead = numElements;
            front = (iHead - 1 + numCapacity) % numCapacity;
            iHead = 0;

            // get a copy of the new allocated data
            for (int i= 0; i < numElements; i++) {
                data[i] = newData[i];
            }

            // free allocated memory 
            delete[] newData;     
            newData = newData;       
        }

        catch(std::bad_alloc) 
        {
            throw "ERROR: Unable to allocate a new buffer for Deque";
        }
    }

    // increase the tail vale
    data[iHead] = t;
    iHead = front;
    numElements++;
}

/***************************************************
 * Deque :: Push_Back
 * Insert an item on the end of the Deque
 **************************************************/
template <class T>
void Deque <T> :: push_back(const T & t) throw (const char *)
{
    int newCapacity;
    int back = iTail;

    if (numCapacity > 0) 
    {
        back = (iTail + 1) % numCapacity;
    }
    // check the capacity if is empty 
    if (numCapacity == empty() || (numCapacity - size()) == 0)
    {
        if (numCapacity == 0) 
        {
            newCapacity = 4; // set 4 even though size is 0
        }

        else 
        {
            newCapacity = (numCapacity * 2);
        }

        // attempt to allocate
        try 
        {
           // create new allocation if the size is full 
             T * newData = new T[numCapacity];
            for (int i = 0; i < size(); i++) 
            {
              int index = (i + iHead) % size();
              newData[i] = data[index];
            }

            delete[] data;
            data = new T[newCapacity];
            numCapacity = newCapacity;

            // correct new allocation for iTail and iHead
            iTail = numElements;
            back = (iTail + 1) % numCapacity;
            iHead = 0;

            // get a copy of the new allocated data
            for (int i= 0; i < numElements; i++) {
                data[i] = newData[i];
            }

            // free allocated memory 
            delete[] newData;     
            newData = newData;       
        }

        catch(std::bad_alloc) 
        {
            throw "ERROR: Unable to allocate a new buffer for Deque";
        }
    }

    // increase the tail vale
    data[iTail] = t;
    iTail = back;
    numElements++;
}

#endif // Deque_H

