/***********************************************************************
* Header:
*    Set
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
#ifndef SET_H
#define SET_H

#include <cassert>
#include <iostream>

//declare for SetIterator
template <class T>
class SetIterator;

// forward declaration for VectorConstIterator
template <class T>
class SetConstIterator;

/**************************************************
* SET: CONTAINER CLASS
* A class that holds uniqe items 
****************************************************/
template<class T>
class Set {

public:
     ////////////////Constructors//////////////////

	// create default constructor: empty 
	Set() : numElements(0), numCapacity(0), data(NULL) {}

	// creat a non-default constructor: per-allocate
	Set(int numCapacity) throw (const char *);

	// copy constructor : copy all the stuff to right hand side!
	Set(const Set & rhs) throw (const char *);

	// destructor: free everything
	~Set() { if (numCapacity) delete[] data; }


	///////////////////Operators///////////////////

   //copy Set and its all elements
   void copySet(const Set<T> &rhs);

   // allocate and held the data in a new array
   void allocate(int newIndex) throw(const char *);

	// Operator=: Assignment operator
	Set<T>  operator = (const Set<T> & rhs);

	// union(): || the union operator.
	Set<T>  operator || (const Set<T> & rhs); 

	// inertsection(): && the intersection operator.
	Set<T>  operator && (const Set<T> & rhs);

    // get the unique numbers that not in others sets 
    Set <T>  operator - (const Set <T> & rhs); 


	/////////////////Member functions///////////////

	// size(): Return the Deque size. 
	int size()      const { return numElements;    }

	// capacity(): Return the current capacity of the Set.
	int capacity()  const { return numCapacity;     }

	// empty(): Test whether the Set is empty
	bool empty()    const { return numElements == 0; }

	// clear(): Empties the deque of all items.
	int clear()    const { return numElements == 0;   }

    // iFind() search for the repeated item.
    int iFind(const T & t);

   // resize(): add more size when it's needed
   int resize(int & newSize) throw (const char *);


	//////////////Class member function/////////////

    // find(): look for elements we need
	SetIterator<T> find(const T & t );

	// begin(): return an iterator to the first element
	SetIterator<T> begin() const { return SetIterator<T>(data);              }

	// end(): return an iterator refering to the past-the-end e
	SetIterator<T> end() const   { return SetIterator<T>(data + numElements);}

	// insert(): add or insert the desired elements
	void insert(T & t) throw (const char *);

	// erase(): Remove an element from the set. 
	void erase(SetIterator<T> & it) throw (const char *);    

private:
	T * data; // store all the data here 
	int numElements; // 
	int numCapacity;
};

/**************************************************
 * Set ITERATOR
 * An iterator through Set
 *************************************************/
template <class T>
class SetIterator
{
  public:
   // default constructor
  SetIterator() : p(NULL) {}

   // initialize to direct p to some item
  SetIterator(T * p) : p(p) {}

   // copy constructor
   SetIterator(const SetIterator & rhs) { *this = rhs; }

  // SetIterator <T>::iterator it;
    //  for (it = rhs.begin(); it != rhs.end(); ++it)
      //   *it; 

   // assignment operator
   SetIterator & operator = (const SetIterator & lhs)
   {
      this->p = lhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const SetIterator & lhs) const
   {
      return lhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   SetIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   SetIterator <T> operator++(int postfix)
   {
      SetIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};


/*******************************************
 * Set :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Set <T> :: Set(const Set <T> & rhs) throw (const char *)
{
   assert(rhs.numCapacity >= 0);

   // do nothing if there is no capacity to do anything
   if (rhs.numCapacity == 0)
   {
      numCapacity = numElements = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
  allocate(rhs.numCapacity);

   // copy over the capacity and size
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
 * Set : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Set to "capacity"
 **********************************************/
template <class T>
Set <T> ::Set(int capacity) throw (const char *)
{
   assert(capacity >= 0);

   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->numCapacity = this->numElements = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   allocate(capacity);

   // copy over the stuff
   this->numCapacity = capacity;
   this->numElements = 0;

   // initialize the Set by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}



/*******************************************
* COPYSET::COPY ALL ELEMENTS TO RIGHT HAND SIDE
*******************************************/
template <class T>
void Set<T> :: copySet(const Set<T> &rhs)
{

    this->numElements = rhs.numElements;
    this->numCapacity = rhs.numCapacity;
    this->numElements = 0;

  // copy the all the stuff over
  for (int i = 0; i < numElements; i++)
  {
    data[i] = rhs.data[i];
  }

  // default vale for T
  for (int i = numElements; i < numCapacity; i++)
  {
    data[i] = T();
  }
}

/**********************************************
* ALLOCATES: NEW SPACE WHENEVER WE NEED!
* GET NEWINDEX 
**********************************************/
template <class T>
void Set <T>::allocate(int newIndex) throw(const char *) 
{
    // attempt to allocate
    try
    {
        data = new T[newIndex];
    }
    // catch otherwise 
    catch(std::bad_alloc) 
    {
        throw "ERROR: Unable to allocate a new buffer for set";
    }
 }

/**********************************************
* RESIZE: NEW SIZE WHENEVER WE NEED!
* GET NEWSIZE:
**********************************************/
template <class T>
int Set<T> :: resize(int & newSize) throw (const char *)
{	
	int iSize = newSize;
	//Resize to capacity of two
	newSize *= 2;
	T* set_newSet = new T[newSize];

	// copy over
	for (int i = 0; i < iSize; i++)
	{
		set_newSet[i] = data[i];
	}

	delete[] data;
	data = set_newSet;
}

/**********************************************
* ALLOCATES: NEW SPACE WHENEVER WE NEED!
* GET NEWINDEX 
**********************************************/
template <class T>
Set<T> Set <T> :: operator = (const Set<T> &rhs)
{
    if (rhs.numCapacity == 0)
    {
      numCapacity = numElements = 0;
      data = NULL;
      return *this;
    }

    allocate(rhs.numCapacity);
    copySet(rhs);
    numElements = rhs.numElements;
    numCapacity = rhs.numCapacity;

    for (int i = 0; i < numElements; i++)
    {
      data[i] = rhs.data[i];
    }

    for (int i = numElements; i < numCapacity; i++)
      data[i] = T();
    return *this;
}

/************************************************
 * Set :: operartor ||
 * Used for UNION of two sets
 ***********************************************/
template <class T>
Set<T> Set <T> :: operator || (const Set <T> &rhs) 
{
   Set <T> set_newSet;
   // Copies what is needed
   for (int i = 0; i < numElements; i++)
   {
      set_newSet.insert(data[i]);
   }

   for (int i = 0; i < rhs.numElements; i++)
   {
      set_newSet.insert(rhs.data[i]);
   }

   return set_newSet;
}

/************************************************
 * Set :: operator &&
 * Used for Intersection of two sets
 ***********************************************/
template <class T>
Set<T> Set <T> :: operator && (const Set <T> &rhs) 
{
   Set <T> set_newSet;

   int set1 = 0;
   int set2 = 0;

   while (set1 < numElements || set2 < rhs.numElements)
   {
      if (set1 == numElements)
      {
         return set_newSet;
      }
      else if (set2 == rhs.numElements)
      {
        return set_newSet;
      }
      else if (data[set1] == rhs.data[set2])
      {
         set_newSet.insert(data[set1]);
         set1++;
         set2++;
      }
      else if (data[set1] < data[set2])
         set1++;
      else
         set2++;
   }

   return set_newSet;
}

/************************************************
 * Set :: operator -
 * Used for difference of two sets
 ***********************************************/
template <class T>
Set<T> Set <T> :: operator - (const Set <T> & rhs) 
{
   Set<T> set_newSet;

   int set1 = 0;
   int set2 = 0;

   // check difference between sets
   while (set1 < numElements || set2 < rhs.numElements)
   {
      if (set1 == numElements)
      {
         return set_newSet;
      }
      else if (set2 == rhs.numElements)
      {
         set_newSet.insert(data[set1++]);
      }
      else if (data[set1] == rhs.data[set2])
      {
         set1++;
         set2++;
      }
      else if (data[set1] < rhs.data[set2])
      {
         set_newSet.insert(data[set1++]);
      }
      else if (data[set1] > rhs.data[set2])
         set2++;
   }
   return set_newSet;
}

/************************************************
* INSERT: 
* ADD UNIQUE ELEMENTS TO THE CONTAINER
*************************************************/
template<class T>
void Set<T> :: insert(T & t) throw (const char *)
{	
	
   int i = 0;
   SetIterator <T> it;

   // check and increase capacity
   if (numCapacity == 0)
   {
      numCapacity = 2;
      allocate(numCapacity);
   }

   // reallocate if it's full
   if (numCapacity >= size())
      resize(numCapacity);

   //check if item already exists
   it = find(t);
   if (it != end())  
    return;

   //find the item we're looking for
   for (i = 0; i < numElements; i++)
      if (data[i] > t)    
      break; // stop here when done      

   // if the samll item was last make sure to follow the big items 
   for (int smallNum = numElements; smallNum > i; smallNum--)
       data[smallNum] = data[smallNum - 1];

   //Add new item
   data[i] = t;
   numElements++;

}

/************************************************
* FIND: 
* LOOK FOR ELEMENTS WE NEED
*************************************************/
template <class T>
SetIterator<T> Set<T> :: find(const T & t ) 
{
	int i = iFind(t);

	if (i >= 0)
	{
	  return data + i;
	}
	else 
		return end();
}

/************************************************
 * Set :: IFind
 * 
 ***********************************************/
template <class T>
int Set<T> :: iFind(const T & t)
{

   int iBegin = 0;
   int iEnd = numElements - 1;

   while (iBegin <= iEnd)
   {
   	    int iMiddle = (iBegin + iEnd) / 2;
   		if (t == data[iMiddle])
   		{
          return iMiddle;
   		}

        if (t < data[iMiddle])
        {
          iEnd = iMiddle - 1;
        }
        else
        {
          iBegin = iMiddle + 1;
        }
   }

   return -1;             

}

/************************************************
* DELETE: 
* ERASE ELEMENTS FROM THE CONTAINER
*************************************************/
template<class T>
void Set<T> :: erase(SetIterator<T> & it) throw (const char *)
{
  int findI =iFind(*it);
  if (findI == -1) 
  {
    return;
  }

  if (findI == (numElements -1))
  {
    numElements--;
    return;
  }

  for (int i = 0; i < numElements -1; i++)
  {
    data[i] = data[i + 1];
  }
  numElements++;
}

#endif // SET_H