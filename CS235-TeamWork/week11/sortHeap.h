/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    Makram Ibrahim
 * Summary:
 *     Reference: discussion board and geeks for geeks website. 
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H
/*************************************************
  * HEAP 
  * Class
 ***********************************************/
template <class T>
class Heap
{
public:

   // Constructors
   Heap() : numItems(0), sortArray(NULL) {}

   // Non-default constructor
   Heap(T data[], int numItems);

   // Free Array from data
   ~Heap() { delete[] sortArray; }

   // Getters: Return the data we need 
   T & getMax() throw (const char *) { return sortArray[1]; }
   T * getData() { return sortArray; }
   int getnumItems() { return numItems; }

    // Delete the max value
    void deleteMax() 
    {
      sortArray[1] = sortArray[numItems];
      numItems--;
      percolateDown(sortArray, 1, numItems);
    }

   // Create a heap
   void heapify(T * data, int n)
   {
       for (int i = n /2; i >= 1; i--)
      percolateDown(data, i, n);
   }

   // Sort
   void sort(T * a, int n)
   {
      for (int i = n; i >= 2; i--) 
      {
        T tmp = a[i];
          a[i] = a[1];
          a[1] = tmp;
          percolateDown(a, 1, i - 1);
      }
   }

   void percolateDown(T* sortArray, int index, int n);

private:
   T * sortArray; // Hold the data here 
   int numItems; 

};

/*****************************************************
* Non-default constructor
****************************************************/
template<class T>
Heap<T>::Heap(T data[], int numItems)
{
   this->numItems = numItems;
   sortArray = new T[numItems + 1];

   // Copy heapify
   for (int i = 0; i <= numItems; i++)
   {
      sortArray[i] = data[i];
   }
   heapify(sortArray, numItems);
}

/*****************************************************
* SORT HEAP
****************************************************/
template <class T>
void sortHeap(T sortArray[], int numItems)
{
   // Add space 
   T sortsortArray[numItems + 1];

   for (int i = 0; i < numItems; i++)
      sortsortArray[i + 1] = sortArray[i];

   Heap<T>* heap = new Heap<T>(sortsortArray, numItems);
   heap->sort(heap->getData(), heap->getnumItems());

   for (int i = 1; i <= numItems; i++) {
      sortArray[i - 1] = heap->getData()[i];
   }
}

/*****************************************************
* PERCOLATE DOWN
****************************************************/
template<class T>
void Heap<T> :: percolateDown(T* sortArray, int index, int n)
{
   T tmp = sortArray[index];
   int i = 2 * index;

   // Put the heap in order 
   while (i <= n)
   {
      // Compare and fix the direction
      if (i < n && sortArray[i + 1] > sortArray[i])
         i = i + 1;

      if (sortArray[i] > tmp || sortArray[i] == tmp)
      {
         sortArray[i / 2] = sortArray[i];
         i = i * 2;
      }
      else if (tmp > sortArray[i])
      	break;
   }
   sortArray[i / 2] = tmp; 
}

#endif // SORT_HEAP_H