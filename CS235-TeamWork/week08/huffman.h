/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Makram Ibrahim
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include "pair.h"
#include "bnode.h"
#include <vector>
#include <string>

/**********************************************
* Huffman
* Class
***********************************************/
class Huffman
{
public:
   Huffman(): tree(NULL) {}
   BinaryNode < Pair <string, float> > * tree;
};

void huffman(string filename);
#endif // HUFFMAN_H
