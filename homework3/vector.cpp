#include "vector.h" // include definition of class vector 

#include <iostream>
// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
	: myFirst(),
	myLast(),
	myEnd()
{
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector(const size_type count)
{
	myFirst = new value_type[count];
	clear();
	if (!empty())
		delete[] myFirst;

	for (size_type i = 0; i < count; i++) {
		myFirst[i] = 0;
		myLast++;
	}
	myEnd = myFirst + count;
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector(const vector &right)
{	
	if (capacity() != right.capacity()) {
		if (!empty())
			delete[] myFirst;

		myFirst = new value_type[right.size()];
		myEnd = myFirst + right.size();
	}

	clear();
	for (size_type i = 0; i < right.size(); i++) {
		myFirst[i] = right.myFirst[i];
		myLast++;
	}
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
}

// The vector is extended by inserting a new element before the element
// at the specified position, effectively increasing the container size by one.
// This causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
// Relocates all the elements that were after "where" to their new positions.
vector::iterator vector::insert(const_iterator where, const value_type &val)
{
	const_iterator oldBegin = begin();
	const_iterator oldEnd = end();
	const size_type oldSize = size();

	if (capacity() == size()) {
		size_type newCapacity = capacity() + capacity() / 2;

		if (empty() || capacity() == 1)
			newCapacity = capacity() + 1;

		pointer tempPtr = nullptr;
		if (!empty())
			tempPtr = myFirst;

		myFirst = new value_type[newCapacity];
		clear();
		for (size_type i = 0; i < oldSize; i++) {
			myFirst[i] = tempPtr[i];
			myLast++;
		}
		myEnd = myFirst + newCapacity;
		
		if (oldBegin == oldEnd) {
			delete[] tempPtr;
			tempPtr = nullptr;
		}
;	}


	if (where == oldEnd) {
		*end() = val;
	}
	else {
		//Insert at begin or the middle
		const size_type n = static_cast<size_type>(where - oldBegin);

		//right shift
		for (size_type i = size(); i > n; i--) {
			myFirst[i] = myFirst[i - 1];
		}

		myFirst[n] = val;
	}

	myLast++;

	return iterator(where);
}

// overloaded assignment operator
// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign(const vector &right)
{
	if (capacity()  < right.size()) {
		size_type newCapacity = capacity() + capacity() / 2 > right.size() ? capacity() + capacity() / 2 : right.size();
		if (!empty())
			delete[] myFirst;

		myFirst = new value_type[newCapacity];
		myEnd = myFirst + newCapacity;
	}

	clear();
	for (size_type i = 0; i < right.size(); i++) {
		myFirst[i] = right.myFirst[i];
		myLast++;
	}

	return *this; // enables x = y = z, for example
}

// Removes from the vector a single element (where).
// This effectively reduces the container size by one, which is destroyed.
// Relocates all the elements after the element erased to their new positions.
vector::iterator vector::erase(const_iterator where)
{
	if (where == end() - 1) {
		myLast--;
		return iterator(where);
	}


	//erase at the begin or middle
	const size_type n = static_cast<size_type>(where - begin());
	//left shift
	for (size_type i = n; i < size(); i++)
		myFirst[i] = myFirst[i+1];

	myLast--;

	return iterator(where);
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear() // erase all
{
	myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin()
{
	return myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::const_iterator vector::begin() const
{
	return const_iterator(myFirst);
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::iterator vector::end()
{
	return myLast;
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::const_iterator vector::end() const
{
	return const_iterator(myLast);
}

// Returns a const_iterator pointing to the first element in the container.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::const_iterator vector::cbegin() const
{
	return begin();
}

// Returns a const_iterator pointing to the past-the-end element in the container.
// If the container is empty, this function returns the same as vector::cbegin.
// The value returned shall not be dereferenced.
vector::const_iterator vector::cend() const
{
	return end();
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty() const
{
	return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size() const
{
	return static_cast<size_type>(myLast - myFirst);
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity() const
{
	return static_cast<size_type>(myEnd - myFirst);
}

// Returns a reference to the first element in the vector.
// Calling this function on an empty container causes undefined behavior.
vector::value_type& vector::front()
{
	return *myFirst;
}

// Returns a reference to the first element in the vector.
// Calling this function on an empty container causes undefined behavior.
const vector::value_type& vector::front() const
{
	return *myFirst;
}

// Returns a reference to the last element in the vector.
// Calling this function on an empty container causes undefined behavior.
vector::value_type& vector::back()
{
	return myLast[-1];
}

// Returns a reference to the last element in the vector.
// Calling this function on an empty container causes undefined behavior.
const vector::value_type& vector::back() const
{
	return myLast[-1];
}