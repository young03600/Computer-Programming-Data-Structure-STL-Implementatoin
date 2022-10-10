// Identifier class member-function definitions.

#include "Identifier.h" // Identifier class definition
#include <iostream>
using std::ostream;
char keywords[61][20] = { "auto", "break", "case", "char", "const", "continue",
							  "default", "do", "double", "else", "enum", "extern",
							  "float", "for", "goto", "if", "int", "long",
							  "register", "return", "short", "signed", "sizeof",
							  "static", "struct", "switch", "typedef", "union",
							  "unsigned", "void", "volatile", "while", "bool",
							  "catch", "class", "const_cast", "delete",
							  "dynamic_cast", "explicit", "false", "friend",
							  "inline", "mutable", "namespace","new", "operator",
							  "private", "protected", "public", "reinterpret_cast",
							  "static_cast", "template", "this", "throw", "true",
							  "try", "typeid", "typename", "using", "virtual",
							  "include" };

// default/conversion constructor
Identifier::Identifier()
	: identifier()
{
}

// overloaded = operator; avoids self assignment
Identifier& Identifier::operator=(const string &right)
{
	identifier = right;
	return *this; // enables cascaded assignments
}

// check if the current identifier is a C++ keyword
bool Identifier::keyword()
{
	for (size_t i = 0; i < 61; i++) {
		string::size_type lens = strlen(keywords[i]);
		if (identifier == string(keywords[i], lens))
			return true;
	}

	return false;
}

bool operator==(const Identifier &lhs, const Identifier &rhs)
{
	return lhs.identifier == rhs.identifier;
}

bool operator!=(const Identifier &lhs, const Identifier &rhs)
{
	return !(lhs == rhs);
}

ostream& operator<<(ostream &output, Identifier &id)
{
	output << id.identifier;
	return output; // enables cout << x << y;
}