/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "map.h"       
#include "wordCount.h"   
#include "pair.h"
#include <iostream>
#include <fstream>       
using namespace std;

/******************************************************************
 * GETFILE
 ******************************************************************/
void getFile(string & fileName)
{
   cout << "What is the filename to be counted? ";
   cin.ignore();
   getline(cin, fileName);
}

/**************************************************************
 * READ FILE
 ******************************************************************/
void readFile(Map <string, int> & map, const string & fileName, string text)
{
   ifstream fin(fileName.c_str());
   
   if (fin.fail())
   {
      cout << "Error, reading the file\n";
   }
   
   while(fin >> text)
   {
      map[text]++;
   }
   
   fin.close();
   
}

/*****************************************************
 * WORD COUNT
 *****************************************************/
void wordCount()
{
   string fileName, text;
   getFile(fileName);
   Map <string, int> map;
   readFile(map, fileName, text);
   
   cout << "What word whose frequency is to be found. "
        << "Type ! when done\n";

   do
   {
      cout << "> ";
      cin >> text;
      cin.clear();
      cin.ignore();

      if (text != "!")
      {
          cout << "\t" << text << " : " << map[text] << endl;
      }
      else if (text != "!")
      cout << "\t" << text << " : 0\n"; 

   }  while (text != "!");
   
}


