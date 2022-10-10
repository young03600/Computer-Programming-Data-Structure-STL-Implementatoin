// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
	: integer(1)
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(unsigned int n)
	: integer((n > 0) ? n : 1)
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger(const HugeInteger &integerToCopy)
	: integer(integerToCopy.integer)
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger& HugeInteger::assign(const HugeInteger &right)
{
	if (&right != this) // avoid self-assignment
		integer.assign(right.integer);

	return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal(const HugeInteger &right) const
{
	if (integer.size() != right.integer.size())
		return false;

	vector::const_iterator it1 = integer.begin();
	vector::const_iterator it2 = right.integer.begin();
	for (; it1 != integer.end(); it1++, it2++)
		if (*it1 != *it2)
			return false;

	return true;
} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::less(const HugeInteger &right) const
{
	if (integer.size() > right.integer.size())
		return false;

	if (integer.size() < right.integer.size())
		return true;

	vector::const_iterator it1 = integer.end() - 1;
	vector::const_iterator it2 = right.integer.end() - 1;
	for (; it1 != integer.begin() - 1; it1--, it2--)
		if (*it1 > *it2)
			return false;
		else if (*it1 < *it2)
			return true;

	return false;
} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual(const HugeInteger &right) const
{
	return (less(right) || equal(right));
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add(HugeInteger &op2)
{
	unsigned int op1Size = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger sum(sumSize);
	cout << "in add function: cout this->n1    "; this->output(cout); cout << '\n';
	cout << "in add function: cout sum.addess  "; cout << sum.integer.begin() << '\n';
	vector::iterator it1 = integer.begin();
	vector::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	vector::iterator it2 = op2.integer.begin();
	for (it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	for (it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3)
		if (*it3 > 9)
		{
			(*it3) -= 10;
			(*(it3 + 1))++;
		}

	if (*it3 == 0)
		sum.integer.erase(sum.integer.end() - 1);

	return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::subtract(HugeInteger &op2)
{
	HugeInteger zero;

	if (equal(op2))
		return zero;

	HugeInteger difference(*this);
	if (op2.isZero())
		return difference;
	
	vector::iterator it2 = op2.integer.begin();
	vector::iterator it3 = difference.integer.begin();
	
	for (; it2 != op2.integer.end(); it2++, it3++)
		*it3 -= *it2;

	for(it3 = difference.integer.begin(); it3 != difference.integer.end(); it3++) 
		if (*it3 < 0) {
			*it3 += 10;
			(*(it3 + 1))--;
		}


	while ( *(difference.integer.end() - 1) == 0)
		difference.integer.erase(difference.integer.end() - 1);

	return difference;
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::multiply(HugeInteger &op2)
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
		return zero;

	unsigned int productSize = integer.size() + op2.integer.size();
	HugeInteger product(productSize);
	
	unsigned int size1 = integer.size();
	unsigned int size2 = op2.integer.size();
	for (unsigned int i = 0; i < size1; i++) 
		for (unsigned int j = 0; j < size2; j++) 
			product.integer.begin()[i+j] += integer.begin()[i] * op2.integer.begin()[j];
		
	for (vector::iterator it3 = product.integer.begin(); it3 != product.integer.end(); it3++)
		if (*it3 > 9) {
			(*(it3 + 1)) += *it3 / 10;
			*it3 %= 10;
		}

	while ( *(product.integer.end() - 1) == 0) 
		product.integer.erase(product.integer.end() - 1);

	return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::divide(HugeInteger &op2)
{
	HugeInteger zero;
	if (less(op2))
		return zero;

	if (isZero())
		return zero;

	HugeInteger remainder(*this);
	unsigned int n = integer.size() - op2.integer.size();
	HugeInteger buffer(integer.size());
	buffer.assign(buffer.add(op2));

	while (n--) {
		for (unsigned int i = buffer.integer.size(); i > 0; i--) {
			buffer.integer.begin()[i] = buffer.integer.begin()[i - 1];
			buffer.integer.begin()[i - 1] = 0;
		}
	}
	//buffer.output(cout);
	unsigned int quotientSize = integer.size() - op2.integer.size();
	if (remainder.less(buffer))
		buffer.divideByTen();
	else
		quotientSize++;

	HugeInteger quotient(quotientSize);
	for (int k = quotientSize - 1; k >= 0; k--) {
		//remainder >= buffer
		while (buffer.lessEqual(remainder)) {
			remainder.assign(remainder.subtract(buffer));
			quotient.integer.begin()[k]++;
		}
		//remainder < buffer
		buffer.divideByTen();
	}
	while ( *(quotient.integer.end() - 1) == 0)
		quotient.integer.erase(quotient.integer.end() - 1);

	return quotient;
} // end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus(HugeInteger &op2)
{
	HugeInteger quotient = divide(op2);
	HugeInteger product = quotient.multiply(op2);
	HugeInteger remainder = subtract(product);
	return remainder;
}

// assign a vector of decimal digits into a HugeInteger
void HugeInteger::assign(const vector &v)
{
	integer.assign(v);
} // end function assign

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
	for (vector::iterator it = integer.begin(); it != integer.end(); ++it)
		if (*it != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
	vector::iterator it = integer.begin();
	vector::iterator it2 = it;
	for (++it2; it2 != integer.end(); ++it, ++it2)
		*it = *it2;
	integer.erase(integer.end() - 1);
}

// overloaded output operator
void HugeInteger::output(ostream &outFile)
{
	vector::iterator it = integer.end() - 1;
	for (; it != integer.begin() - 1; --it)
		if (*it < 10)
			outFile << *it;
	outFile << endl;
} // end function output