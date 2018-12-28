// ===================================================================================================================================================================
// ===================================================================================================================================================================
// This file comes to include some more information about the behaviour of the virtual table mechanism in C++. 
// In this example a "4-levels" inheritence chain will be used to illustrate the way it works.
// 
// virtual table under the hood:
// -----
//     
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <iostream>

using namespace std;

class A
{
public:
	A(int a)
		: m_a(a)
	{
		cout << "A::A - calling Func1()" << endl;
		Func1();
		//Func3();
		cout << "A::A - set m_a to:" << m_a << ", this:" << this << endl;
	}

	virtual ~A()
	{
		cout << "A::~A - calling Func1()" << endl;
		Func1();
		cout << "A::~A - this:" << this << endl;
	}

	virtual void Func1()
	{
		cout << "A::Func1 - this:" << this << endl;
	}

	virtual void Func2()
	{
		cout << "A::Func2 - this:" << this << endl;
	}

	virtual void Func3() = 0;

protected:
	int m_a;
};

class B : public A
{
public:
	B(int a, int b)
		: A(a)
		, m_b(b)
	{
		cout << "B::B - calling Func1()" << endl;
		Func1();
		cout << "B::B - set m_b to:" << m_b << ", this:" << this << endl;
	}

	virtual ~B()
	{
		cout << "B::~B - calling Func1()" << endl;
		Func1();
		cout << "B::~B - this:" << this << endl;
	}

	virtual void Func1()
	{
		cout << "B::Func1 - this:" << this << endl;
	}

	/*
	virtual void Func2()
	{
		cout << "B::Func2 - this:" << this << endl;
	}
	*/

	virtual void Func3()
	{
		cout << "B::Func3 - this:" << this << endl;
	}

protected:
	int m_b;
};


// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main program:
// ===================================================================================================================================================================
// ===================================================================================================================================================================

void createDerivedObjectOnTheStack()
{
	cout << "createDerivedObjectOnTheStack - start" << endl;
	B b(15,17);
	cout << "createDerivedObjectOnTheStack - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "virtualTable - start" << endl;

	createDerivedObjectOnTheStack();

	cout << "virtualTable - start" << endl;
	return 0;
}


