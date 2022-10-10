#include <iostream>
using std::cout;
using std::exit;

#include "string.h" // include definition of class String

string::string()
	: bx(),
	mySize(0),
	myRes(15)
{
}

// buffer
string::string(const char *const ptr, const size_type count)
	: bx(),
	mySize(0),
	myRes(15)
{
	// using bx.ptr
	if (count > myRes) {
		myRes += (count / 16) * 16;
		bx.ptr = new value_type[myRes+1];
	}

	memcpy(myPtr(), ptr, count);
	//for (size_type i = 0; i < count; i++)
		//myPtr()[i] = ptr[i];

	mySize += count;
	this->element(mySize) = '\0';
}

// fill
string::string(const size_type count, const char ch)
	: bx(),
	mySize(0),
	myRes(15)
{
	if (count > myRes) {
		myRes += (count / 16) * 16;
		bx.ptr = new value_type[myRes+1];
	}

	for (size_type i = 0; i < count; i++)
		myPtr()[i] = ch;

	mySize += count;
	myPtr()[mySize] = '\0';
}

// fill constructor regular //
// (count / 16)*16 + myRes
string::string(const string &right)
	: bx(),
	mySize(0),
	myRes(15)
{
	// using Dynamically array
	if (myRes < right.size()) {
		myRes = (right.size() / 16) * 16 + 15;
		bx.ptr = new value_type[myRes+1];
	}

	// copied either buf or Dynamically array
	//memcpy(myPtr(), right.myPtr(), right.size());
	for (size_type i = 0; i < right.size(); i++)
		myPtr()[i] = right.element(i);
	
	mySize += right.size();
	myPtr()[mySize] = '\0';
}

string::~string()
{
	if (myRes > 15)
		delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
	if (myRes < 16)
		return bx.buf;
	else
		return bx.ptr;
}

const string::value_type* string::myPtr() const
{
	if (myRes < 16)
		return bx.buf;
	else
		return bx.ptr;
}

string& string::assign(const string &right)
{

	if (right.size() > myRes) {
		if ((myRes + myRes / 2) > right.size()) {
			myRes = right.size()/16 *16 +15 > myRes + myRes / 2 ? right.size()/16 *16 +15 : myRes + myRes / 2;
		}
		else
			myRes = (right.size() / 16) * 16 + 15;

		bx.ptr = new value_type[myRes+1];
	}

	clear();
	for (size_type i = 0; i < right.size(); i++)
		myPtr()[i] = right.element(i);

	mySize += right.size();
	myPtr()[mySize] = '\0';

	return *this;
}

string::iterator string::insert(const_iterator where, const char ch)
{
	// myPtr() reuturns bx.buf or bx.ptr
	if (where >= myPtr() && where <= myPtr() + mySize)
	{	

		const_iterator oldBegin = begin();
		const_iterator oldEnd = end();
		
		if (size() == capacity()) {

			pointer tempPtr = new value_type[mySize];
			for (size_type i = 0; i < mySize; i++)
				tempPtr[i] = myPtr()[i];

			if (myPtr() != bx.buf && bx.ptr != nullptr)
				delete[] bx.ptr;

			if (myRes < 32)
				myRes += 16;
			else
				myRes += myRes / 2;
			
			bx.ptr = new value_type[myRes+1];
			for (size_type i = 0; i < mySize; i++)
				myPtr()[i] = tempPtr[i];
			
			myPtr()[mySize] = '\0';

			delete [] tempPtr;
			tempPtr = nullptr;
		}

		if (where == oldBegin) {
			// right shift
			for (size_type i = mySize; i > 0; i--)
				myPtr()[i] = myPtr()[i-1];

			front() = ch;
			mySize++;
			myPtr()[mySize] = '\0';

			return iterator(where);
		}
		else if (where == oldEnd) {

			*end() = ch;
			mySize++;
			myPtr()[mySize] = '\0';


			return iterator(where);
		}
		else {
			// Insert at n-th
			const size_type n = static_cast<size_type>(where - oldBegin);
			
			// right shift
			for (size_type i = mySize; i > n; i--)
				myPtr()[i] = myPtr()[i-1];

			myPtr()[n] = ch;
			mySize++;
			myPtr()[mySize] = '\0';

			return iterator(where);
		}
		
	}
	else
		return iterator(nullptr);
}

string::iterator string::erase(const_iterator where)
{
	if (where >= myPtr() && where < myPtr() + mySize)
	{
		if (where == end() - 1) {
			back() = '\0';
			mySize--;

			return iterator(where);
		}

		// begin or middle
		// left shift
		const size_type n = static_cast<size_type>(where - begin());
		for (size_type i = n; i < mySize; i++)
			myPtr()[i] = myPtr()[i+1];
		mySize--;
		myPtr()[mySize] = '\0';

		return iterator(where);
	}
	else
		return iterator(nullptr);
}

void string::clear()
{
	mySize = 0;
	myPtr()[0] = value_type();
}

string::iterator string::begin()
{
	return myPtr();
}

string::const_iterator string::begin() const
{
	return const_iterator(myPtr());
}

string::iterator string::end()
{
	return myPtr() + static_cast<difference_type>(mySize);
}

string::const_iterator string::end() const
{
	return const_iterator(myPtr() + static_cast<difference_type>(mySize));
}

string::reference string::element(const size_type off)
{
	if (off > mySize)
	{
		cout << "string subscript out of range\n";
		exit(1);
	}

	return myPtr()[off];
}

string::const_reference string::element(const size_type off) const
{
	if (off > mySize)
	{
		cout << "string subscript out of range\n";
		exit(1);
	}

	return myPtr()[off];
}

string::reference string::front()
{
	return myPtr()[0];
}

string::const_reference string::front() const
{
	return myPtr()[0];
}

string::reference string::back()
{
	return myPtr()[mySize - 1];
}

string::const_reference string::back() const
{
	return myPtr()[mySize - 1];
}

const char* string::c_str() const
{
	return myPtr();
}

string::size_type string::size() const
{
	return mySize;
}

string::size_type string::capacity() const
{
	return myRes;
}

bool string::empty() const
{
	return mySize == 0;
}