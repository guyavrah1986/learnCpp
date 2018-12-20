// ===================================================================================================================================================================
// ===================================================================================================================================================================
// Composition:
// ------------
// 1) Basic composition means that every member class (which is a class on its own as well) of the "parent" class, "lives" exactly the same as it father - it gets 
//    destroyed while its father dtor is executed.
//    Also, every class member, also DOES NOT know about its parent existence.It just exists.It does not need to know anything from/about its father class in order
//    to do what it does.
// 2) In case the member class DOES NOT have a default ctor, it MUST be initialized in the INITIALIZATION LIST of all the ctors of its parent class.
// 3) In the "simple" case where both class members have default ctor AND they are NOT initialized in the parent ctor's initialization list, then they will created 
//    in the order they are declared within the parent class (top to bottom). 
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

	/* No default cotr	//2)
	InnerClass1() : m_a(15)
	{
		cout << "InnerClass1::InnerClass1() - set m_a:" << m_a << endl;
	}
	*/

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
public:				// 2)
	MyClass(int a, int b) : m_innerClass1(a), /* m_innerClass2(a),*/ m_b(b)
	{
		cout << "MyClass::MyClass(int b) - set m_b to:" << m_b << endl;
	}
			// 2)
	MyClass() : m_innerClass1(15), /*m_innerClass2(15),*/ m_b(17) 
	{
		cout << "MyClass::MyClass() - m_b:" << m_b << endl;
	}

	~MyClass()
	{
		cout << "MyClass::~MyClass" << endl;
	}

private:
	InnerClass1 m_innerClass1;
	InnerClass2 m_innerClass2;
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



