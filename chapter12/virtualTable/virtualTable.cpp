// ===================================================================================================================================================================
// ===================================================================================================================================================================
// This file comes to include some more information about the behaviour of the virtual table mechanism in C++. 
// In this example a "2-levels" inheritence chain will be used to illustrate the way it works.
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

	void Func4()
	{
		cout << "A::Func4" << endl;
	}

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

	void Func4()
	{
		cout << "B::Func4" << endl;
	}

protected:
	int m_b;
};

class C : public B
{

public:
		C(int a, int b, int c)
			: B(a, b)
			, m_c(c)
		{
			cout << "C::C - set m_c to:" << m_c << endl;
		}

		virtual ~C()
		{
			cout << "C::~C" << endl;
		}

		virtual void Func1()
		{
			cout << "C::Func1" << endl;
		}

		virtual void Func2()
		{
			cout << "C::Func2" << endl;
		}

		virtual void Func3()
		{
			cout << "C::Func3" << endl;
		}

		void Func4()
		{
			cout << "C::Func4" << endl;
		}

protected:
		int m_c;
};

void callVirtualFunctionsViaPointer()
{
	cout << "callVirtualFunctionsViaPointer - start" << endl;
	B b(8,9);
	A* pa = &b;
	cout << "callVirtualFunctionsViaPointer - calling pa->Func1()" << endl;
	pa->Func1();
	cout << "callVirtualFunctionsViaPointer - calling pa->Func2()" << endl;
	pa->Func2();
	cout << "callVirtualFunctionsViaPointer - calling pa->Func3()" << endl;
	pa->Func3();	
	cout << "callVirtualFunctionsViaPointer - end" << endl;
}

void callNonVirtualFunction()
{
	cout << "callNonVirtualFunction - start" << endl;
	C c(1,2,3);
	A* pa = &c;
	cout << "callNonVirtualFunction - calling pa->Func4()" << endl;
	pa->Func4();

	B* pb = &c;
	cout << "callNonVirtualFunction - calling pb->Func4()" << endl;
	pb->Func4();

	C* pc = &c;
	cout << "callNonVirtualFunction - calling pc->Func4()" << endl;
	pc->Func4();

	cout << "callNonVirtualFunction - end" << endl;
}


void createDerivedObjectOnTheStack()
{
	cout << "createDerivedObjectOnTheStack - start" << endl;
	C c(12, 15, 17);
	cout << "createDerivedObjectOnTheStack - end" << endl;
}

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main program:
// ===================================================================================================================================================================
// ===================================================================================================================================================================
int main(int argc, char** argv)
{
	cout << "virtualTable - start" << endl;

	//createDerivedObjectOnTheStack();
	callVirtualFunctionsViaPointer();
	callNonVirtualFunction();

	cout << "virtualTable - start" << endl;
	return 0;
}


