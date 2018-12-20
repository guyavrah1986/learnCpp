// ===================================================================================================================================================================
// ===================================================================================================================================================================
// Composition2:
// ------------
// 1) In this example we will illustrate another "technique" to implement composition, this time in a more "risky" way - the composed class members will be kept as
//    pointer.
// 2) Due to the fact mentioned in the previous note, we need to make sure that the parent class:
// 2a) Allocates the class members upon its creation (ALL ctors).
// 2b) De-allocates the class members upon its destruction (Dtor).
// --> Otherwise, we might (probably will) suffer from memory leaks.
// NOTE: Even if we do so, we can still suffer from memory leak in the case that, for some (faulty) reason the parent dtor was NOT invoked at all (due to a crash 
//       or some logic bug...).
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>

using namespace std;

class InnerClass1
{
public:
	InnerClass1(int a) : m_a(a)
	{
		cout << "InnerClass1::InnerClass1 - set m_a:" << m_a << endl;
	}

	InnerClass1() : m_a(15)
	{
		cout << "InnerClass1::InnerClass1() - set m_a:" << m_a << endl;
	}

	~InnerClass1()
	{
		cout << "InnerClass1::~InnerClass1" << endl;
	}

private:
	int m_a;
};

class InnerClass2
{
public:
	InnerClass2(int a) : m_a(a)
	{
		cout << "InnerClass2::InnerClass2 - set m_a:" << m_a << endl;
	}

	
	InnerClass2() : m_a(15)
	{
		cout << "InnerClass2::InnerClass2() - set m_a:" << m_a << endl;
	}
	

	~InnerClass2()
	{
		cout << "InnerClass2::~InnerClass2" << endl;
	}

private:
	int m_a;
};

class MyClass
{
public:				
	MyClass(int a, int b) 
		: m_innerClass1(new InnerClass1(a))	// 2a)
		, m_innerClass2(new InnerClass2(a))
		, m_b(b)
	{
		cout << "MyClass::MyClass(int b) - set m_b to:" << m_b << endl;
	}
			
	MyClass() 
		: m_innerClass1(new InnerClass1(15))	// 2a)
		, m_innerClass2(new InnerClass2(15))
		, m_b(17) 
	{
		cout << "MyClass::MyClass() - m_b:" << m_b << endl;
	}

	~MyClass()
	{
		// 2b) 
		delete m_innerClass1;
		delete m_innerClass2;
		cout << "MyClass::~MyClass" << endl;
	}

private:
	InnerClass1* m_innerClass1;
	InnerClass2* m_innerClass2;
	int m_b;
};


// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================

int main(int argc, char** argv)
{

	cout << "main - start" << endl;
	
	MyClass obj;

	cout << "main - end" << endl;
	return 0;
}



