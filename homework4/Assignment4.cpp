#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include <vector>
using std::vector;

#include "Identifier.h" // Identifier class definition
#include "SourceLine.h" // SourceLine class definition

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(vector< Identifier > &identifiers, vector< Identifier >::iterator &pos);

int main()
{
	ifstream inFile("test.cpp", ios::in);

	// exit program if ifstream could not open file
	if (!inFile)
	{
		std::cout << "File could not be opened" << std::endl;
		system("pause");
		exit(1);
	}

	char source[200];
	SourceLine sourceLine;
	Identifier identifier;
	vector< Identifier > identifiers;
	int numIdentifiers = 0;

	while (inFile.getline(source, sizeof(source), '\n'))
	{
		sourceLine = source;
		sourceLine.delComments(); // deletes the comment beginning with "//" in sourceLine
		sourceLine.delStrConst(); // deletes all string constants in sourceLine
		sourceLine.delCharConst(); // deletes all character constants in sourceLine

		// extracts all identifiers from sourceLine
		while ((identifier = sourceLine.delFirstIdentifier()) != Identifier())
			identifiers.insert(identifiers.end(), identifier);
	}

	vector< Identifier >::iterator it;
	for (it = identifiers.begin(); it != identifiers.end(); ++it)
		if (!it->keyword() && !duplicate(identifiers, it))
			cout << *it << endl;

	system("pause");
}

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(vector< Identifier > &identifiers, vector< Identifier >::iterator &pos)
{
	vector< Identifier >::iterator it;
	for (it = identifiers.begin(); it < pos; ++it)
		if (*it == *pos)
			return true;

	return false;
}