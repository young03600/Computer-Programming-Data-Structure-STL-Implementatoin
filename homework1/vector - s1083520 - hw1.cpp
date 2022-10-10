#include "vector.h"  // include definition of class vector

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector() { myFirst = myLast = myEnd = nullptr; }

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector(const size_type count) {
	myFirst = new value_type[count];
	clear();
	for (size_type i = 0; i < count; i++) {
		myFirst[i] = 0;
		myLast++;
	}
	myEnd = myFirst + count;
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector(const vector &right) {
	const size_type rightCapacity =
		static_cast<size_type>(right.myEnd - right.myFirst);
	const size_type rightSize =
		static_cast<size_type>(right.myLast - right.myFirst);
	if (capacity() != rightCapacity) {
		if (myFirst != nullptr) delete[] myFirst;

		// The new size of vector is rightSize not rightCapacity
		myFirst = new value_type[rightSize];
		myEnd = myFirst + rightSize;
	}

	clear();
	for (size_type i = 0; i < rightSize; i++) {
		myFirst[i] = right.myFirst[i];
		myLast++;
	}
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector() {
	if (myFirst != nullptr) delete[] myFirst;
}

// The vector is extended by inserting a new element before the element
// at the specified position, effectively increasing the container size by one.
// This causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
// Relocates all the elements that were after "where" to their new positions.
// 28 28      s:35 c:42
vector::iterator vector::insert(const_iterator where, const value_type &val) {
	const size_type oldSize = size();
	const size_type oldCapacity = capacity();
	pointer oldBegin = myFirst;
	pointer oldEnd = myLast;

	if (size() == capacity()) {
		size_type newCapacity = oldCapacity + oldCapacity / 2;
		// node 0 or node 0 -> node 1
		if (empty() || capacity() == 1) {
			newCapacity = capacity() + 1;
		}

		pointer tempPtr = myFirst;
		myFirst = new value_type[newCapacity];
		clear();
		for (size_type i = 0; i < oldSize; i++) {
			myFirst[i] = tempPtr[i];
			myLast++;
		}
		myEnd = myFirst + newCapacity;

		delete[] tempPtr;
		tempPtr = nullptr;
	}

	if (where == oldBegin) {
		// right shift
		for (size_type i = size(); i > 0; i--) {
			myFirst[i] = myFirst[i - 1];
		}

		*myFirst = val;
		myLast++;

		return iterator(myFirst);
	}
	else if (where == oldEnd) {
		// Insert the element at the end of vector
		*myLast = val;
		myLast++;

		return iterator(end() - 1);
	}
	else {
		// Insert at the middle
		const size_type n = static_cast<size_type>(where - oldBegin);

		// right shift
		for (size_type i = size(); i > n; i--)
			myFirst[i] = myFirst[i - 1];

		myFirst[n] = val;
		myLast++;

		return iterator(where);
	}
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector &vector::assign(const vector &right) {
	const size_type rightCapacity =
		static_cast<size_type>(right.myEnd - right.myFirst);
	const size_type rightSize =
		static_cast<size_type>(right.myLast - right.myFirst);
	const size_type oldCap = capacity();

	if (capacity() < rightSize) {
		size_type newCapacity = oldCap + oldCap / 2 > rightSize ? (oldCap + oldCap / 2) : rightSize;

		myFirst = new value_type[newCapacity];
		myEnd = myFirst + newCapacity;
	}

	clear();
	for (size_type i = 0; i < rightSize; i++) {
		myFirst[i] = right.myFirst[i];
		myLast++;
	}

	return *this;
}

// Removes from the vector a single element (where).
// This effectively reduces the container size by one, which is destroyed.
// Relocates all the elements after the element erased to their new positions.
vector::iterator vector::erase(const_iterator where) {
	// Earse at the end of vector
	if (where == end()) {
		myLast--;
		return iterator(end() - 1);
	}

	// normal status
	const size_type n = static_cast<size_type>(where - begin());

	for (size_type i = n; i < size(); i++) myFirst[i] = myFirst[i + 1];
	myLast--;

	return iterator(myFirst + n);
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this
// function.
void vector::clear() { myLast = myFirst; }

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be
// dereferenced.
vector::iterator vector::begin() { return myFirst; }

// Returns an iterator referring to the past-the-end element in the vector
// container. The past-the-end element is the theoretical element that would
// follow the last element in the vector. It does not point to any element, and
// thus shall not be dereferenced. If the container is empty, this function
// returns the same as vector::begin.
vector::iterator vector::end() { return myLast; }

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty() { return myFirst == myLast; }

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size() {
	return static_cast<size_type>(myLast - myFirst);
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity() {
	return static_cast<size_type>(myEnd - myFirst);
}

// Returns a reference to the element at position "pos" in the vector container.
vector::value_type &vector::element(const size_type pos) {
	return myFirst[pos];
}