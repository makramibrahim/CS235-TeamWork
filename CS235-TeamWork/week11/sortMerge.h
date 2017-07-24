/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Jonesl, CS 235
 * Author:
 *    Andrew Larsen, borrowing code from Brother Jones
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

template <class T>
void merge(T a[], int p, int q, int r)
{
	T * b = new T[r];     //same size of a[]
	int i, j, k;
	k = 0;
	i = p;
	j = q + 1;
	while (i <= q && j <= r)
	{
		if (a[j] > a[i])
		{
			b[k++] = a[i++];       // same as b[k]=a[i]; k++; i++;
		}
		else
		{
			b[k++] = a[j++];
		}
	}

	while (i <= q)
	{
		b[k++] = a[i++];
	}

	while (j <= r)
	{
		b[k++] = a[j++];
	}

	for (i = r; i >= p; i--)
	{
		a[i] = b[--k];        // copying back the sorted list to a[]
	}

}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
template <class T>
void mergeSort(T arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}
template <class T>
void sortMerge(T array[], int num)
{
	mergeSort(array, 0, num - 1);  //call to function with begin and end for recursive
}
#endif

