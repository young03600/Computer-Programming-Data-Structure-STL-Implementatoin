// string class member-function definitions.

#include <iostream>
using std::cerr;

#include "string.h" // string class definition

string::string()
	: myData()
{
}

string::string(const char *const ptr, const size_type count)
	: myData()
{
	// using bx.ptr
	if (count > myData.myRes) {
		myData.myRes += (count / 16) * 16;
		myData.bx.ptr = new value_type[myData.myRes + 1];
	}

	memcpy(myData.myPtr(), ptr, count);
	myData.mySize = count;
	myData.myPtr()[myData.mySize] = '\0';
}

string::string(const size_type count, const char ch)
	: myData()
{
	if (count > myData.myRes) {
		myData.myRes += (count / 16) * 16;
		myData.bx.ptr = new value_type[myData.myRes + 1];
	}

	for (size_type i = 0; i < count; i++)
		myData.myPtr()[i] = ch;

	myData.mySize = count;
	myData.myPtr()[myData.mySize] = '\0';
}

string::string(const string &right)
	: myData()
{
	// using Dynamically array
	if (myData.myRes < right.size()) {
		myData.myRes = (right.size() / 16) * 16 + 15;
		myData.bx.ptr = new value_type[myData.myRes + 1];
	}

	// copied either buf or Dynamically array
	//memcpy(myPtr(), right.myPtr(), right.size());
	for (size_type i = 0; i < right.size(); i++)
		myData.myPtr()[i] = right.myData.myPtr()[i];

	myData.mySize = right.size();
	myData.myPtr()[myData.mySize] = '\0';
}

string::~string()
{
	if (myData.myRes > 15)
		delete[] myData.bx.ptr;
}

string& string::operator=(const string &right)
{
	if (this != &right)
	{
		// using Dynamically array
		if (myData.myRes < right.size()) {
			myData.myRes = (right.size() / 16) * 16 + 15;
			myData.bx.ptr = new value_type[myData.myRes + 1];
		}

		// copied either buf or Dynamically array
		//memcpy(myPtr(), right.myPtr(), right.size());
		for (size_type i = 0; i < right.size(); i++)
			myData.myPtr()[i] = right.myData.myPtr()[i];

		myData.mySize = right.size();
		myData.myPtr()[myData.mySize] = '\0';
	}

	return *this;
}

string& string::operator=(const char * const ptr)
{
	size_t count = strlen(ptr);
	if (count > 0)
	{
		// using Dynamically array
		if (myData.myRes < count) {
			myData.myRes = (count / 16) * 16 + 15;
			myData.bx.ptr = new value_type[myData.myRes + 1];
		}

		// copied either buf or Dynamically array
		//memcpy(myPtr(), right.myPtr(), right.size());
		for (size_type i = 0; i < count; i++)
			myData.myPtr()[i] = ptr[i];

		myData.myPtr()[count] = '\0';
	}

	myData.mySize = count;

	return *this;
}

string& string::erase(size_t off, size_t count)
{
	if (count == npos || off + count > size()) {
		myData.mySize = off;
		myData.myPtr()[myData.mySize] = '\0';
		return *this;
	}

	if (off < myData.mySize)
	{	
		//shift left
		for (size_type i = off, j = off + count; j < size(); i++, j++)
			myData.myPtr()[i] = myData.myPtr()[j];

		myData.mySize -= count;
		myData.myPtr()[myData.mySize] = '\0';
	}

	return *this;
}

void string::clear()
{
	myData.mySize = 0;
	myData.myPtr()[0] = value_type();
}

string::iterator string::begin()
{
	return iterator(myData.myPtr());
}

string::const_iterator string::begin() const
{
	return const_iterator(myData.myPtr());
}

string::iterator string::end()
{
	return iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
}

string::const_iterator string::end() const
{
	return const_iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
}

string::reference string::operator[](size_type off)
{
	// check for off out-of-range error
	if (off > myData.mySize)
	{
		cerr << "\nstring subscript out of range\n";
		system("pause");
		exit(1); // terminate program; off out of range
	}

	return myData.myPtr()[off]; // returns copy of this element
}

string::const_reference string::operator[](size_type off) const
{
	// check for off out-of-range error
	if (off > myData.mySize)
	{
		cerr << "\nstring subscript out of range\n";
		system("pause");
		exit(1); // terminate program; off out of range
	}

	return myData.myPtr()[off]; // returns copy of this element
}

string::const_pointer string::data() const
{
	return myData.myPtr();
}

string::size_type string::size() const
{
	return myData.mySize;
}

string::size_type string::find(char ch, size_type off) const
{
	for (size_type i = off; i < size(); i++)
		if (data()[i] == ch)
			return i;

	return static_cast<size_t>(-1);
}

string string::substr(size_type off, size_type count) const
{
	if (off < myData.mySize)
	{
		pointer newString = new value_type[count + 1];
		for (size_type i = 0, j = off; i < count && j < size(); i++, j++)
			newString[i] = data()[j];

		return string(newString, count);
	}

	return string();
}

// compare [ 0, size() ) with right for equality
bool string::equal(const string &right) const
{	
	if (size() != right.size())
		return false;

	for (size_type i = 0; i < size(); i++)
		if (data()[i] != right.data()[i])
			return false;

	return true;
}

bool operator==(const string &left, const string &right)
{
	return left.equal(right);
}

bool operator!=(const string &left, const string &right)
{
	return !left.equal(right);
}

ostream& operator<<(ostream &ostr, string &str)
{
	for (size_t i = 0; i < str.size(); i++)
		ostr << str.data()[i];

	return ostr; // enables cout << x << y;
}