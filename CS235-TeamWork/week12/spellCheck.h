/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#ifndef SPELL_CHECK_H
#define SPELL_CHECK_H
#include "hash.h"
using std::string;
class SpellChecker : public Hash <string>
{
public:
	SpellChecker()    throw (const char *) : Hash <string>() {}
	SpellChecker(const SpellChecker & rhs) throw (const char *) : Hash <string>(rhs) {}

	int hash(const string & value) const
	{
		int sum = 0;
		for(string::const_iterator it = value.begin(); it != value.end(); ++it)
		{
			sum += *it;
		}
		return sum % capacity();
	}
};
void spellCheck();

#endif // SPELL_CHECK_H
