/***********************************************************************
 * Component:
 *    Week 13, Maze
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Draw and solve a maze
 ************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include "list.h"
#include "queue.h"
#include "set.h"
#include "vertex.h"

using namespace std;

class Graph
{
   
public:
  //Constructos and Destructors
   Graph(int num);
   void clear();
   Set<Vertex> findEdges(const Vertex & vFrom) const;
   vector<Vertex> findPath(const Vertex & vFrom, const Vertex & vTo);
   bool isEdge(Vertex v1, Vertex v2) const;

   Graph & operator = (const Graph &rhs) throw (const char *);

   void add(const Vertex & vFrom, const Vertex & vTo);
   void add(const Vertex & vFrom, const Set<Vertex> & sTo);

   int index(Vertex v1, Vertex v2) const;
   int size() const { return items; }

   private:
   bool *table;
   int items;

};

#endif //GRAPH_H
