/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Makram Ibrahim
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype
#include "pair.h"
#include "bnode.h"
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
typedef Pair <string, float> Npair;
typedef Pair <string, string> Stpair;
typedef BinaryNode <Npair> BNode;
typedef vector <BNode*> VNode;
typedef vector <Stpair> Vstring;

/********************************************************************
 * Compare Node
 ********************************************************************/
bool compNode(BNode * leftNode, BNode * rightNode)
{
   if (leftNode->data.second == rightNode->data.second)
   {
      return (leftNode->data >= rightNode->data);
   }
   else
   {
   		return (leftNode->data.second >= rightNode->data.second);
   }
}

/**********************************************************************
 * Compare String 
 **********************************************************************/
bool compString(Stpair leftNode, Stpair rightNode)
{
   return (leftNode < rightNode);
}

/*********************************************************************
 * Add: get input from text file.
 ********************************************************************/
void add(VNode & data)
{
   while (data.size() > 1)
   {
      int size = data.size();
      // sum
      BNode * parent = new BNode
      (*(new Npair (data[size-1]->data.first + data[size-2]->data.first,
                 data[size-1]->data.second + data[size-2]->data.second)));
      
      // left and right node
      parent->addLeft(data[size-1]);
      parent->addRight(data[size-2]);
      data.pop_back();
      data.pop_back();
      data.push_back(parent);
      // sort the tree
      sort(data.begin(), data.end(), compNode);
   }
}

/*********************************************************************
 * recursive
 *********************************************************************/
void recursive(BNode * newNode, string newString, Vstring & code)
{
   if(newNode == NULL)
      return;
   
     recursive(newNode->pLeft, newString + "0", code);
     recursive(newNode->pRight, newString + "1", code);
    
    if(newNode->pLeft == NULL && newNode->pRight == NULL)
       code.push_back(Stpair(newNode->data.first, newString));
}

/*******************************************
 * HUFFMAN
 *******************************************/
void huffman(string filename)
{
   // Declare variables
   Npair temp;
   BNode * node;
   VNode data;
   Vstring code;
   string newString;

   ifstream fin(filename.c_str()); // open file
   if (fin.fail())
   {
      cout << "Error opening the file " << filename << endl;
   }
   
   while (fin >> temp)
   {
      node = new BNode(temp);
      data.push_back(node);
   }
   // sort tree
   sort(data.begin(), data.end(), compNode);
   // Create tree
   add(data);
   // path of the nodes on the add
   recursive(data[0], newString, code);
   // sort the tree
   sort(code.begin(), code.end(), compString);   
   // Print 
   for(int i = 0; i < code.size(); i++)
       cout << code[i].first << " = " << code[i].second << endl;
    fin.close(); // close file
}