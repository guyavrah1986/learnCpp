// ======================================================================================================================================================================================
/*
*  Function templates:
*  -------------------
* 1) When we define a function template we define a "blue print" for a potential function instantiation. Nothing is being "created" (compiled) yet.
* 2) It is important to note that when we use template for user defined classes, than we should make sure that all functions and/or operators that are used within the template function
*    are "well defined" (whether by us or by the compiler) as we wish it to be implemented.
*    In case it is not defined we will recive a compilation error when the complier will generate the respective function that uses the user defined class.
*
*
*/
// ======================================================================================================================================================================================

#pragma once

#include <iostream>

class A
{
	public:
	A(int a) : m_a(a)
	{
		std::cout << "A::A - setting m_a to:" << m_a << std::endl;
	}

	friend bool operator>(const A& lhs, const A& rhs)
	{
		return lhs.m_a > rhs.m_a;
	}
	
	private:
	int m_a;
};

// 1)
template <typename T> void mySwap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

//2)
template <typename T> bool myComapre(const T& lhs, const T& rhs)
{
	return lhs > rhs;
}



