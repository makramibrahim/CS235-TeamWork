/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Andrew Larsen
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
#include "list.h"
using namespace std;

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/

void spellCheck()
{
	int result = 0;
	string input;
	string word;
	char response;
	ifstream file;
	SpellChecker table;
	List<string> misspelled;

	file.open("/home/cs235/week12/dictionary.txt");
	if (file.fail())
	{
		cout << "could not read dictionary file.\n";
	}
	while (file >> word)
	{
		table.insert(word);
	}
	file.close();

	cout << "What file do you want to check? ";
	cin >> input;
	file.open(input.c_str());
	if (file.fail())
	{
		cout << "could not read file.";
	}
	while (file >> word)
	{
		string temp = word;
		for (unsigned x = 0; x < word.length(); ++x)
		{
			temp[x] = tolower(temp[x]);
		}
		if (!table.find(temp))
		{
			misspelled.push_back(word);
		}
	}
	int i = 0;
	if (misspelled.size() == 0)
		cout << "File contains no spelling errors\n";
	else {
		cout << "Misspelled: ";

		for (ListIterator<string> it = misspelled.begin(); it != misspelled.end(); ++it, ++i)
		{
			cout << *it;
			if (i != misspelled.size()-1)
			{
				cout << ", ";
			}
		}
		cout << endl;
	}
}
