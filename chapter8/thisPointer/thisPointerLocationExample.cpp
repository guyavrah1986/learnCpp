// 
// This pointer location within a class (with inheritence):
// --------------------------------------------------------
// 
// Answer: The this pointer in poiting to the "first" member of C which is the memeber of the base 
// class A. Regarindg the usage of this, you can access every 
// public/protected function of every "base class along the way" of your derived class...


#include <iostream>

class A 
{

public:
	A(int a) : m_a(a)
	{
		std::cout << "A::A - setting m_a to:" << m_a << " this is:" << this << " address of m_a is:" << &m_a << std::endl;
	}

	int m_a;
};


class B : public A 
{

public:
	B(int a, int b) :  A(a) ,m_b(b)
	{
		std::cout << "B::B - setting m_b to:" << m_b << " this is:" << this << " address of m_b is:" << &m_b << std::endl;
	}

	int m_b;
};


class C : public B 
{

public:
	C(int a, int b, int c) : B(a, b), m_c(c) 
	{
		std::cout << "C::C - setting m_c to:" << m_c << " this is:" << this << " address of m_c is:" << &m_c << std::endl;
	}

	int m_c;
};


int main(int argc, char** argv)
{

	std::cout << "thisPointerLocationExample - start" << std::endl;

	C c(1,2,3);
	std::cout << "thisPointerLocationExample - end" << std::endl;
	return 0;
}
