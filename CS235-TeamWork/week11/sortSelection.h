/***********************************************************************
 * Module:
 *    Week 11, Sort Select
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{
   // number of comparisons is initially zero
   int numCompare = 0;

   // did we switch two values on the last time through the outer loop?
   bool switched = true;
   
   int smallPos = 0;
   //int smallest = 0;
   // for each spot in the array, find the item that goes there with iCheck
   for (int iSpot = num-1; iSpot >= 1 && switched; iSpot--)
   {
      smallPos = iSpot;
      T smallest = array[smallPos];
      for (int iCheck = 0, switched = false; iCheck <= iSpot-1; iCheck++)
      {
         numCompare++;      // each time we are going to compare, add one
         if (array[iCheck] > smallest)
         {
            smallPos = iCheck;
            smallest = array[smallPos];
         }
         switched = true; // a swap happened, do outer loop again
      }
      array[smallPos] = array[iSpot];
      array[iSpot] = smallest;
   }
}

#endif // SORT_SELECTION_H
