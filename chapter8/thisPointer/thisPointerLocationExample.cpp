// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 
// This pointer location within a class (with inheritence):
// --------------------------------------------------------
// 
// Answer: The this pointer in poiting to the "first" member of C which is the memeber of the base 
// class A. Regarindg the usage of this, you can access every 
// public/protected function of every "base class along the way" of your derived class...
//
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>

using namespace std;

class A 
{

public:
	A(int a) : m_a(a)
	{
		cout << "A::A - setting m_a to:" << m_a << " this is:" << this << " address of m_a is:" << &m_a << endl;
	}

	int m_a;
};


class B : public A 
{

public:
	B(int a, int b) :  A(a) ,m_b(b)
	{
		cout << "B::B - setting m_b to:" << m_b << " this is:" << this << " address of m_b is:" << &m_b << endl;
	}

	int m_b;
};


class C : public B 
{

public:
	C(int a, int b, int c) : B(a, b), m_c(c) 
	{
		cout << "C::C - setting m_c to:" << m_c << " this is:" << this << " address of m_c is:" << &m_c << endl;
	}

	int m_c;
};


int main(int argc, char** argv)
{

	cout << "thisPointerLocationExample - start" << endl;

	C c(1,2,3);
	cout << "thisPointerLocationExample - end" << endl;
	return 0;
}
