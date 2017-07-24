
#include <iostream>
#include "graph.h"
#include "queue.h"


/**************************************
* GRAPH: main constructor
* Allocate a 2-d array of bools
**************************************/
Graph :: Graph(int items)
{
   assert(items > 0);
   try
   {
      this->table = new bool[items * items];
      this->items = items;
      clear();
   }
   catch (...)
   {
      this->table = NULL;
      this->items = 0;
      throw "ERROR: unable to allocate space for the graph";
   }
}

/*******************************************
* GRAPH :: CLEAR
* Remove all the edges from the graph
*******************************************/
void Graph :: clear()
{
   for (int i = 0; i < items * items; i++)
   table[i] = false;
}

/********************************************
* GRAPH :: FIND EDGES
* Return a set of all the edges
********************************************/
Set <Vertex> Graph :: findEdges(const Vertex & vFrom) const
{
   assert(vFrom.getMax() == items);
   Vertex vTo;
   Set <Vertex> s;

   for (int i = 0; i < items; i++)
   {
      vTo.set(i);
      if (isEdge(vFrom, vTo))
      s.insert(vTo);
   }
   return s;
}

/**********************************************
* GRAPH :: FIND PATH
* Find the set of verticies representing a path
* from vFrom to vTo in the graph
***********************************************/
vector <Vertex> Graph :: findPath(const Vertex & vFrom, const Vertex & vTo)
{
   // create an array representing the shortest path to each item.  Mark
   // the distance to vFrom as zero
   int distance = 0;
   int * distances = new int[items];
   Vertex * predecessor = new Vertex[items];
   for (int i = 0; i < items; i++)
      distances[i] = -1;
   distances[vFrom.index()] = distance;
   
   // create a queue of the ones to visit. Start with vFrom
   Queue <Vertex> toVisit;
   toVisit.push(vFrom);
   
   // while we have not found the destination and the list of places
   // we still have to go is not empty
   while (!toVisit.empty() && distances[vTo.index()] == -1)
   {
      // grab the next item off the head of the queue
      Vertex v = toVisit.front();
      toVisit.pop();
      
      // increment the distance as necessary
      if (distances[v.index()] > distance)
         distance++;
      
      // go through all the edges and add them as necessary
      Set <Vertex> s(findEdges(v));
      for (SetConstIterator <Vertex> it = s.cbegin(); it != s.cend(); ++it)
         if (distances[(*it).index()] == -1)
         {
            distances[(*it).index()] = distance + 1;
            predecessor[(*it).index()] = v;
            toVisit.push((*it));
         }
   }
   distance++;
   
   // now reconstruct the shortest path
   vector <Vertex> path(0);
   if (distances[vTo.index()] == -1)
   {
      cout << "No path found\n";
      return path;
   }
   
   path.push_back(vTo);
   for (int i = 1; i <= distance; i++)
      path.push_back(predecessor[path[i - 1].index()]);
   
   
   delete [] distances;
   delete [] predecessor;
   return path;
}

/**********************************************
 * isEdge() : returns matrix boolean slot
 **********************************************/
bool Graph::isEdge(const Vertex v1, const Vertex v2) const
{
   return table[index(v1, v2)];
}

/****************************************************
* GRAPH ASSIGNMENT
* Copy one graph onto another
***************************************************/
Graph & Graph :: operator = (const Graph & rhs) throw (const char *)
{
   // do nothing if the rhs is invalid
   if (rhs.items == 0)
      return *this;

   // realocate as necessary. Problem: Verticies can be only one size
   if (items != rhs.items)
   {
      if (table != NULL)
         delete [] table;
      try
      {
         this->table = new bool[rhs.items * rhs.items];
         this->items = rhs.items;

      }
      catch (...)
      {
         throw "ERROR: unable to allocate space for the graph";

      }

   }

   // copy it over
   for (int i = 0; i < items * items; i++)
   {
      table[i]= rhs.table[i];
    }
      return *this;

   }

/***************************************************
* GRAPH :: ADD
* Add an edge to the graph
**************************************************/
void Graph :: add(const Vertex & vFrom, const Vertex & vTo)
{
   assert(vFrom.index() < items);
   assert(vTo.index() < items);
   table[index(vFrom, vTo)] = true;

}

/***************************************************
* GRAPH :: ADD
* Add a bunch of edges to a graph
**************************************************/
void Graph :: add(const Vertex & vFrom, const Set <Vertex> & sTo)
{
   assert(vFrom.index() < items);
   for (SetConstIterator <Vertex> it = sTo.cbegin(); it != sTo.cend(); ++it)
   {
      assert((*it).index() < items);
      table[index(vFrom, *it)];
   }
}

int Graph::index(Vertex v1, Vertex v2) const
{
	return v1.index() * items + v2.index();
}