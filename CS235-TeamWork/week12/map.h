/*******************************************************************************
 * Component:
 *    Lesson 10, Binary Tree Balancing
 * Author:
 *    Andrew Larsen, Jefferson Santos, Makram Ibrahim
 *
 * Summary:
 *    Create a binary tree and balance it
 ******************************************************************************/

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "pair.h"
#include "bnode.h"
#include "bst.h"

template <class T1, class T2>
class MapIterator;
/*****************************************************************
* BINARY SEARCH TREE
* Create a Binary Search Tree
*****************************************************************/
template <class T1, class T2>
class Map
{  
   //Variables
   private:
   BST < Pair<T1, T2> > bst;
   int numItems;
   
  public:
   //constructors and deconstructor
   Map() : bst(), numItems(0) {}         
   Map(const Map  & rhs)
   {
      bst = rhs.bst;
      numItems = rhs.numItems;
   }

  ~Map() { bst.clear(); } 

   //Map & operator = (const Map & rhs) throw (const char *);
   Map & operator = (const Map  & rhs) throw (const char *)
   {
       bst = rhs.bst;
       numItems = rhs.numItems;
       return *this;
   }

	T2& operator [](const T1& key)
	{
		MapIterator<T1, T2> found(find(key));
		if (found == end())
		{
			bst.insert(Pair<T1, T2>(key, T2()));
			++numItems;
			found = find(key);
		}

		return *found;
	}

	T2& operator [](const T1& key) const
	{
		MapIterator<T1, T2> found(find(key));
		return *found;
	}
   
   bool empty() const { return bst.empty();        }
   int size() const   { return numItems;           }
   void clear()       { bst.clear(); numItems = 0; }
   MapIterator <T1, T2> find(const T1 & t) const { return bst.find(Pair<T1, T2>(t, T2())); }
   MapIterator <T1, T2> begin()  { return bst.begin();  }
   MapIterator <T1, T2> end()    { return bst.end();    }
   MapIterator <T1, T2> rbegin() { return bst.rbegin(); }
   MapIterator <T1, T2> rend()   { return bst.rend();   }
      
};

/**********************************************************
 * MAPITERATOR
 * Iterator Map
 *********************************************************/
template <class T1, class T2>
class MapIterator
{
private:
   BSTIterator<Pair<T1, T2> > nodes;
   
public:
   // constructors
   MapIterator(BinaryNode <Pair<T1, T2> > * p = NULL): nodes(p) {};
   MapIterator(const MapIterator & rhs) { nodes = rhs.nodes; }
   MapIterator(const BSTIterator <Pair <T1, T2> > & rhs)  { nodes = rhs; }

   // assignment operator
   MapIterator & operator = (const MapIterator & rhs)
   {
      nodes = rhs.nodes;
      return *this;
   }

   // compare operator
   bool operator == (const MapIterator & rhs) const
   {
      return nodes == rhs.nodes;
   }
   
   bool operator != (const MapIterator & rhs) const
   {
      return nodes != rhs.nodes;
   }

   T2 & operator * ()  
   {
      return (*nodes).second;
   }

   // iterators
   MapIterator & operator ++ ()
   {
      ++nodes;
      return *this;
   }

   MapIterator operator ++ (int postfix)
   {
      BSTIterator <Pair<T1, T2> > itReturn = nodes;
      ++nodes;
      return itReturn;
   }
   
   MapIterator & operator -- ()
   {
      --nodes;
      return *this;
   }
   
   MapIterator operator -- (int postfix)
   {
      BSTIterator <Pair<T1, T2> > itReturn = nodes;
      --nodes;
      return itReturn;
   }

};

#endif // MAP_H
