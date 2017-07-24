/***********************************************************************
 * Header:
 *    Set
 * Summary:
 *    An unordered collection of unique elements.
 * Author
 *    Michael Whatcott
 ************************************************************************/

#ifndef SET_H
#define SET_H

// forward declaration for SetIterator
template <class T>
class SetIterator;

// forward declaration for SetConstIterator
template <class T>
class SetConstIterator;

/************************************************
 * Set: A unique collection of items
 ***********************************************/
template <class T>
class Set
{
public:
   // Destructor: free everything
   ~Set() { if (_capacity) delete [] _data; }
   
   // Default constructor : empty and kinda useless
   Set() : _size(0), _capacity(0), _data(NULL) {}
   
   // Non-default constructor which pre-allocates.
   Set(int capacity) throw (const char *) : _size(0), _capacity(capacity)
   {
      if (_capacity == 0)
      {
         this->_data = NULL;
         return;
      }
      try
      {
         _data = new T[_capacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Set.";
      }
      for (int i = _size; i < _capacity; i++)
         _data[i] = T();
   }
   
   // Copy constructor.
   Set(const Set & rhs) throw (const char *) { *this = rhs; }
   
   // Override the assignment operator
   Set<T> & operator= (const Set<T> & rhs) throw (const char *)
   {
      if (rhs._capacity == 0)
      {
         _capacity = _size = 0;
         _data = NULL;
         return *this;
      }
      
      try
      {
         _data = new T[rhs._capacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Set.";
      }
      
      _capacity = rhs._capacity;
      _size = rhs._size;
      
      for (int i = 0; i < _size; i++)
      {
         if (i < _size)
            _data[i] = rhs._data[i];
         else
            _data[i] = T();
            }
      
      return *this;
   }
   
   // Getters:
   int size()     const { return _size; }
   int capacity() const { return _capacity; }
   bool empty()   const { return _size == 0; }
   
   // Remove all the items from the container.
   void clear() { _size = 0; }
   
   // Iterator access:
   SetIterator      <T> begin()  const { return SetIterator<T>(_data); }
   SetIterator      <T> end()    const { return SetIterator<T>(_data + _size); }
   SetConstIterator <T> cbegin() const { return SetConstIterator<T>(_data); }
   SetConstIterator <T> cend()   const { return SetConstIterator<T>(_data + _size); }
   
   // Find an item and return an iterator to it.
   SetIterator<T> find(T item) const
   {
      if (_size == 0)
         return end();
      
      int slot = findSlot(item);
      if (_data[slot] == item)
         return SetIterator<T>(_data+slot);
      
      return this->end();
   }
   
   // Find out where the item already lives, or should live if inserted.
   int findSlot(const T item, bool insert = false) const
   {
      int begin = 0;
      int end = _size - 1;
      
      while (begin <= end)
      {
         int middle = (begin + end) / 2;
         if (_data[middle] == item)
            return insert ? -1 : middle;
         else if (_data[middle] > item)
            end = middle - 1;
         else
            begin = middle + 1;
      }
      
      return begin;
   }
   
   // Insert an item, if it hasn't already been inserted.
   void insert(const T item) throw (const char *)
   {
      int f = findSlot(item, true);
      if (f < 0)
         return;
      
      grow();
      
      for (int x = _size-1; x >= f; x--)
         _data[x+1] = _data[x];
      
      _data[f] = item;
      _size++;
   }
   
   // Erase the item, if found.
   void erase(SetIterator<T> item)
   {
      if (item == end())
         return;
      
      T t = item.operator*();
      int f = findSlot(t);
      if (f < 0)
         return;
      
      for (int x = f; x < _size-1; x++)
         _data[x] = _data[x+1];
      
      _size--;
   }
   
   // Return the union of this and rhs (elements found in either).
   Set<T> operator || (const Set<T> & rhs) const
   {
      Set<T> _union;
      int i1 = 0;
      int i2 = 0;
      
      while (i1 < _size || i2 < rhs._size)
      {
         if (i1 == _size)
            _union.append(rhs._data[i2++]);
         else if (i2 == rhs._size)
            _union.append(_data[i1++]);
         else if (_data[i1] == rhs._data[i2])
         {
            _union.append(_data[i1]);
            i1++;
            i2++;
         }
         else if (_data[i1] < rhs._data[i2])
            _union.append(_data[i1++]);
         else
            _union.append(rhs._data[i2++]);
      }
      
      return _union;
   }
   
   // Return the intersection of this and rhs ((elements found in both).
   Set<T> operator && (const Set<T> & rhs) const
   {
      Set<T> intersection;
      int i1 = 0;
      int i2 = 0;
      
      while (i1 < _size || i2 < rhs._size)
      {
         if (i1 == _size)
            return intersection;
         else if (i2 == rhs._size)
            return intersection;
         else if (_data[i1] == rhs._data[i2])
         {
            intersection.append(_data[i1]);
            i1++;
            i2++;
         }
         else if (_data[i1] < rhs._data[i2])
            i1++;
         else
            i2++;
      }
      
      return intersection;
   }
   
   Set<T> operator - (const Set<T> & rhs)
   {
      Set<T> difference;
      int i1 = 0;
      int i2 = 0;
      
      while (i1 < _size)
      {
         if (i2 == rhs._size)
            difference.append(_data[i1++]);
         else if (_data[i1] == rhs._data[i2])
         {
            i1++;
            i2++;
         }
         else if (rhs._data[i2] > _data[i1])
            difference.append(_data[i1++]);
         else
            i2++;
      }
      
      return difference;
   }
   
private:
   T * _data;      // dynamically allocated array of T
   int _size;      // how many items are currently in the Set?
   int _capacity;  // how many items can I put on the Set before full?
   
   // Increase capacity of backing dynamic array.
   void grow()
   {
      if (_size < _capacity)
         return;
      
      if (_capacity == 0)
         _capacity++;
      else
         _capacity *= 2;
      
      T* temp;
      try
      {
         temp = new T[_capacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Set.";
      }
      
      for (int i = 0; i < _size; i++)
      {
         if (i < _size)
            temp[i] = _data[i];
         else
            temp[i] = T();
      }
      
      delete[] _data;
      _data = temp;
   }
   
   // Append item to _data. For building sets resulting from union,
   // intersection and other complex operations.
   void append(T item)
   {
      grow();
      _data[_size] = item;
      _size++;
   }
};

// An iterator through Set
template <class T>
class SetIterator
{
public:
   // constructors:
   SetIterator() : p(NULL) {}
   SetIterator(T * p) : p(p) {}
   SetIterator(const SetIterator & rhs) { *this = rhs; }
   
   // assignment operator
   SetIterator & operator = (const SetIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }
   
   // equality operators:
   bool operator == (const SetIterator & rhs) const { return rhs.p == this->p; }
   bool operator != (const SetIterator & rhs) const { return rhs.p != this->p; }
   
   // dereference operator
   T & operator * () { return *p; }
   
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

// An const iterator through Set
template <class T>
class SetConstIterator
{
public:
   // constructors:
   SetConstIterator() : p(NULL) {}
   SetConstIterator(T * p) : p(p) {}
   SetConstIterator(const SetConstIterator & rhs) { *this = rhs; }
   
   // assignment operator
   SetConstIterator & operator = (const SetConstIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }
   
   // equality operators:
   bool operator == (const SetConstIterator & rhs) const { return rhs.p == this->p; }
   bool operator != (const SetConstIterator & rhs) const { return rhs.p != this->p; }
   
   // dereference operator
   T & operator * () { return *p; }
   
   // prefix increment
   SetConstIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }
   
   // postfix increment
   SetConstIterator <T> operator++(int postfix)
   {
      SetConstIterator tmp(*this);
      p++;
      return tmp;
   }
   
private:
   
   T * p;
};

#endif // SET_H
