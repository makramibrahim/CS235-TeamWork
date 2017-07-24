/***********************************************************************
* Header:
*    Node.h
* Summary:
*    
*
*    This will contain the class definition of:
*        Bnode         : A class that holds stuff
*        DequeIterator : An interator through Deque
* Author
*    Andrew Larsen
************************************************************************/
#pragma once

#include <cassert>
#include <iostream>
using namespace std;
template<class T>
class BinaryNode {
public:
	//variables:
	BinaryNode* pLeft;
	BinaryNode* pRight;
	BinaryNode* pParent;
	T data;

	//constructors:
	BinaryNode() : pLeft(NULL), pRight(NULL), pParent(NULL) {}
	BinaryNode(T t) : pLeft(NULL), pRight(NULL), pParent(NULL), data(t) {}
	
	//functions:
	void addLeft(T t)
	{
		BinaryNode<T> * node = new BinaryNode(t);
		this->pLeft = node;
		node->pParent = this;
	}
	void addLeft(BinaryNode* node)
	{
		this->pLeft = node;
		if(node) node->pParent = this;
	}
	void addRight(T t)
	{
		BinaryNode<T> * node = new BinaryNode(t);
		this->pRight = node;
		node->pParent = this;
	}
	void addRight(BinaryNode* node)
	{
		this->pRight = node;
		if(node) node->pParent = this;
	}
	int size()
	{
		return 1 +
			(pLeft == NULL ? 0 : pLeft->size()) +
			(pRight == NULL ? 0 : pRight->size());
	}
};

template<class T>
void deleteBinaryTree(BinaryNode<T>* & node)
{
	if (node)
	{
		deleteBinaryTree(node->pLeft);
		deleteBinaryTree(node->pRight);
		delete node;
		node = NULL;
	}
}

template<class T>
ostream & operator << (ostream & out, const BinaryNode<T> * node)
{
	if (!node) return out;
	out << node->pLeft;
	out << node->data << ' ';
	out << node->pRight;
	return out;
}