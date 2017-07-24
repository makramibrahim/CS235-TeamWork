/***********************************************************************
 * Header:
 *    QUEUE
 * Summary:
 *    This will contain the class definition for Queue:

 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#define ALLOCATION_ERROR "ERROR: Unable to allocate a new buffer for queue."

// A first-in, first-out (FIFO) queue.
template <class T>
class Queue
{
public:
   
   Queue() : _data(NULL), _capacity(0), _size(0), _front(0), _back(0) {}
   
   Queue(int capacity) throw (const char *);
   
   Queue(const Queue & rhs) throw (const char *);
   
   ~Queue();
   
   Queue<T> & operator = (const Queue<T> & rhs) throw (const char *);
   
   int size() const { return _size; }
   
   int capacity() const { return _capacity; };
   
   bool empty() const { return _size == 0; }
   
   void clear() { while (!empty()) pop(); }
   
   T & front() throw (const char *);
   
   T & back() throw (const char *);
   
   void push(T item) throw (const char *);
   
   void pop() throw (const char *);
   
public:
   
   T * _data;
   int _size;
   int _front;
   int _back;
   int _capacity;
   
   // Increase capacity of backing dynamic array.
   void grow() throw (const char *);
};

// Constructor that allocates according to capacity.
template <class T>
Queue<T>::Queue(int capacity) throw (const char *)
: _capacity(capacity), _size(0), _front(0), _back(0)
{
   if (_capacity == 0)
   {
      _data = NULL;
      return;
   }
   
   try
   {
      _data = new T[_capacity];
   }
   catch (std::bad_alloc)
   {
      throw ALLOCATION_ERROR;
   }
   
   for (int i = 0; i < _capacity; i++)
      _data[i] = T();
}

// Copy constructor.
template <class T>
Queue<T>::Queue(const Queue & rhs) throw (const char *)
{
   if (rhs._capacity == 0)
   {
      _capacity = 0;
      _size = 0;
      _front = 0;
      _back = 0;
      _data = NULL;
      return;
   }
   
   try
   {
      _data = new T[rhs._capacity];
   }
   catch (std::bad_alloc)
   {
      throw ALLOCATION_ERROR;
   }
   
   _capacity = rhs._capacity;
   _size = rhs._size;
   _front = rhs._front;
   _back = rhs._back;
   
   for (int i = 0; i < _capacity; i++)
      _data[i] = rhs._data[i];
      }

// Assignment operator.
template <class T>
Queue<T> & Queue<T>::operator=(const Queue<T> & rhs) throw (const char *)
{
   if (rhs._capacity == 0)
   {
      _capacity = 0;
      _size = 0;
      _front = 0;
      _back = 0;
      _data = NULL;
      return *this;
   }
   
   if (_capacity < rhs._capacity)
   {
      try
      {
         _data = new T[rhs._capacity];
      }
      catch (std::bad_alloc)
      {
         throw ALLOCATION_ERROR;
      }
   }
   
   _capacity = rhs._capacity;
   _size = rhs._size;
   _front = rhs._front;
   _back = rhs._back;
   
   for (int i = 0; i < _capacity; i++)
      _data[i] = rhs._data[i];
      
      return *this;
}

// Destructor.
template <class T>
Queue<T>::~Queue()
{
   if (_capacity > 0)
      delete [] _data;
}

// Return the item at the front of the queue (next to be popped).
template <class T>
T & Queue<T>::front() throw (const char *)
{
   if (empty())
      throw "ERROR: attempting to access an item in an empty queue";
   
   return _data[_front%_capacity];
}

// Return the item at the back of the queue (most recently pushed).
template <class T>
T & Queue<T>::back() throw (const char *)
{
   if (empty())
      throw "ERROR: attempting to access an item in an empty queue";
   
   return _data[(_back-1)%_capacity];
}

// Add an item onto the back of the queue.
template <class T>
void Queue<T>::push(T item) throw (const char *)
{
   if (_size == _capacity)
      grow();
      
      _data[_back % _capacity] = item;
      _back++;
   _size++;
}

// Remove the item at the front of the queue.
template <class T>
void Queue<T>::pop() throw (const char *)
{
   if (empty())
      throw "ERROR: attempting to pop from an empty queue";
   
   _front++;
   _size--;
}

// Increase capacity of backing dynamic array.
template <class T>
void Queue<T>::grow() throw (const char *)
{
   int oldCapacity = _capacity;
   if (_capacity == 0)
      _capacity++;
   else
      _capacity *= 2;
      
      T* tempArray;
   try
   {
      tempArray = new T[_capacity];
   }
   catch (std::bad_alloc)
   {
      throw ALLOCATION_ERROR;
   }
   
   for (int i = 0; i < oldCapacity; i++)
      tempArray[i] = _data[(i+_front) % oldCapacity];
      
      for (int i = oldCapacity; i < _capacity; i++)
         tempArray[i] = T();
         
         delete[] _data;
   _data = tempArray;
   _front = 0;
   _back = oldCapacity;
}

#endif //QUEUE_H


