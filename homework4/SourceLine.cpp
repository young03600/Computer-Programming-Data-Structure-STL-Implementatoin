// SourceLine class member-function definitions.

#include <iostream>
using std::cout;

#include "SourceLine.h" // SourceLine class definition

// default constructor
SourceLine::SourceLine()
	: sourceLine()
{
}

SourceLine& SourceLine::operator=(const char * const ptr)
{
	sourceLine = ptr;
	return *this;
}

void SourceLine::delComments()
{
	if (sourceLine.size() > 1) {
		string::size_type loc;
		if ((loc = sourceLine.find('/')) != npos)
			sourceLine.erase(loc);
	}
}

void SourceLine::delStrConst()
{	
	if (sourceLine.size() > 1) {
		string::size_type valBegin;
		while ((valBegin = sourceLine.find('"')) != npos) {
			string::size_type valEnd = sourceLine.find('"', valBegin + 1); // searching the substr starts from valBegin
			if (valEnd < sourceLine.size())
				sourceLine.erase(valBegin, valEnd - valBegin + 1);
		}
	}
	
}

void SourceLine::delCharConst()
{
	if (sourceLine.size() > 1) {
		string::size_type valBegin;
		while ((valBegin = sourceLine.find('\'')) != npos) {
			string::size_type valEnd = sourceLine.find('\'', valBegin + 1);
			if (valEnd < sourceLine.size())
				sourceLine.erase(valBegin, valEnd - valBegin + 1);
		}
	}
}

string SourceLine::delFirstIdentifier()
{
	if (sourceLine.size() > 1) {
		string::iterator it = sourceLine.begin();
		
		//find the first char which is letters
		size_t letterBegin = 0;
		while (!isalpha(*it) || *it == '_') {
			if (*it == '\0')
				return string();
			
			letterBegin++;
			it++;
		}

		// find the first char which is a Symbol
		while( (isalpha(*it) || isdigit(*it)) || *it == '_')
			it++;

		// the char is not a symbol in here
		// find the position of char
		ptrdiff_t letterEnd = it - sourceLine.begin();
		string subString = sourceLine.substr(letterBegin, letterEnd - letterBegin);
		sourceLine.erase(0, letterEnd);

		return subString;
	}

	return string();
}