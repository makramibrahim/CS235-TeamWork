/***********************************************************************
 * Component:
 *    Week 13, Maze
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Draw and solve a maze
 ************************************************************************/

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include "set.h"
#include "vertex.h"
#include "graph.h"

using namespace std;

// solve the maze, the main program function
void solveMaze();

// read a maze in from a file
Graph readMaze(const char * fileName);

// display a maze on the screen
void drawMaze(const Graph & g, const vector <Vertex> & path);

void drawMazeRow(const Graph & g, int row, Set <CVertex> & s);
void drawMazeColumn(const Graph & g, int row, const Set <CVertex> & s);


#endif // MAZE_H
