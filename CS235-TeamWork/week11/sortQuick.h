/***********************************************************************
 * Module:
 *    Week 11, Sort Quick
 *    Brother Helfrich, CS 235
 * Author:
 *    Andrew 
 * Summary:
 *    This program will implement the Quick Sort
 ************************************************************************/

#ifndef SORT_QUICK_H
#define SORT_QUICK_H

/*****************************************************
 * SORT QUICK
 * Perform the quick sort
 ****************************************************/
template <class T>

void sortQuick(T array[], int num)

{

// do nothing if there is nothing to do

if (num <= 1)

return;

int iEnd = num - 1;

// find the pivot, in the middle in this case

T pivot = array[iEnd / 2] ;

int iUp = 0; // going up...

int iDown = iEnd; // heading down...

while (iUp <= iDown)

{

// advance up as long as it is not greater than the pivot

while (iUp <= iEnd && pivot > array[iUp])

iUp++;

// advance down as long as it is not less than the pivot

while (iDown >= 0 && array[iDown] > pivot)

iDown--;

// swap them

if (iUp <= iDown)

{

T temp = array[iUp];

array[iUp++] = array[iDown];

array[iDown--] = temp;

}

}

// recursively sort the two halves as specified by the pivot

sortQuick(array, iUp); // lower half

sortQuick(array + iUp, iEnd - iUp + 1); // upper half

}

#endif // SORT_QUICK_H