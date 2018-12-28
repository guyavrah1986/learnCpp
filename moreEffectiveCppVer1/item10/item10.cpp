// ========================================================================================================================================================================
/*
* Item 10:
* --------
* Long story short - if a class's ctor does not "run to completion" (for instance by throwing an exception during its run) its dtor WILL
* NOT be invoked, no matter how we "called" the ctor (i.e.- for a stack object/heap object).
* --> this situation might casue resource leaks or the like (that were prevented if the dtor WAS invoked normally).
* So far we have understood the PROBLEM and it causes.
*
* 1) In this case - all good, no "worries".
* 2) In this case, when intentioally we "simulate" an exception throw form the C class's ctor. 
* a) It is important no note here, that, even
*    if we manually (explictly) call the dtor of class C AFTER the exception was thrown and caught - it won't help, cause a dtor of
*    a class is relevant ONLY if the ctor of that class was run completly --> so we will have a memory leak (in the size of class A, cause
*    it's ctor did run completly, YET its dtor did not...).
* b) Any data member of class C (i.e.- not a pointer) is not effected from the fact that the dtor of class C is NOT invoked -- it is 
*    being deleted ANYWAY !!
* 3) On the other hand, if we do wish to be able to delete the pointer of the object that was not initizlied completly, we can throw
*    the exception form the Init method -- and than the call to the dtor indeed will work.
* 4) Here, no matter what will happen, the pointer data members of E, will be delete properly.
* a) Defining both of them as a unique_ptr will do the trick.
*
* Notes:
* ) No need to check for NULL pointer before deleting the pointers of class C in the dtor (C++ permits to delete NULL pointers).
*/
// ======================================================================================================================================================================

#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>
#include <memory>

using namespace std;

class A
{
public:
	A(int a)
		: m_a(a)
	{
		cout << "A::A - setting m_a to:" << m_a << endl;
	}

	~A()
	{
		cout << "A::~A" << endl;
	}

	int m_a;
};

class B
{
public:
	B(int b)
		: m_b(b)
	{
		cout << "B::B - setting m_b to:" << m_b << endl;
	}

	~B()
	{
		cout << "B::~B" << endl;
	}

	int m_b;
};

class C
{
public:
	C(int a, int b, const string& str)
		: m_a(nullptr)
		, m_b(nullptr)
		, m_str(str)
	{
		m_a = new A(a);
		cout << "C::C - setting m_a to a newly A object created on the heap (address):" << m_a << endl;
		if (b == 0)
		{
			throw exception("sample exception to simulate situation where m_b was not fully initialized in class C ctor");
		}

		m_b = new B(b);
		cout << "C::C - setting m_b to a newly B object created on the heap (address):" << m_b << endl;
	}

	~C()
	{
		delete m_a;
		delete m_b;
		cout << "C::~C" << endl;
	}

	A* m_a;
	B* m_b;
	string m_str; // 2b)
};

class D
{
public:
	D()
		: m_a(nullptr)
		, m_b(nullptr)
	{
		cout << "D::D" << endl;
	}

	void InitD(int a, int b)
	{
		cout << "D::InitD" << endl;
		m_a = new A(a);
		if (b == 0)
		{
			throw exception("sample exception to simulate situation where m_b was not fully initialized in class D Init() method");
		}

		m_b = new B(b);
	}

	~D()
	{
		delete m_a;
		delete m_b;
		cout << "D::~D" << endl;
	}

	A* m_a; 
	B* m_b;
};

class E
{
public:
	E(int a, int b)
		: m_a(nullptr)
		, m_b(nullptr)
	{
		cout << "E::E" << endl;
		m_a.reset(new A(a));
		if (b == 0)
		{
			throw exception("sample exception to simulate situation where m_b was not fully initialized in class E ctor");
		}

		m_b.reset(new B(b));
	}

	~E()
	{
		cout << "E::~E" << endl;
	}

	unique_ptr<A> m_a; // 4a)
	unique_ptr<B> m_b; // 4a)
};

void item10Usage()
{
	cout << "item10Usage - start" << endl;
	
	// 1) invoke a normal creation of a C object - on the stack
	// Due to the fact that C's ctor throws an exception - its dtor
	// won't be invoked when we leave this scope
	{
		try
		{
			C c(1, 0, "str1");
		}
		catch (const exception& e)
		{
			cout << "item10Usage - caught an excpetiopn when trying to create a C object on the stack:" << e.what() << endl;
		}
	}
	
	// 2) same as io 1) for a heap based C object - the explict call to 
	//    C's dtor (delete pc) won't have any effect
	C* pc = 0;
	try
	{
		pc = new C(1, 0, "str2");
	}
	catch (const exception& e)
	{
		cout << "item10Usage - caught an exception while trying to create a new C object on the heap:" << e.what() << endl;
		delete pc; // 2a)
	}
	
	// 3) Here, on the other hand, the call to delete pd will indeed 
	//    invoke D's dtor
	D* pd = new D();
	try
	{
		pd->InitD(1,0);
	}
	catch (const exception& e)
	{
		cout << "item10Usage - caught an excpetion while trying to init a D object:" << e.what() << endl;
		delete pd; // 3a) 
	}

	// 4) This is "most" proper way to do it !!
	E* pe = nullptr;
	try
	{
		pe = new E(1, 0);
	}
	catch (const exception& e)
	{
		cout << "item10Usage - caught an excpetion while trying to init an E object:" << e.what() << endl;
	}

	cout << "\n \n item10Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	item10Usage();

	char c = 0;
	cout << "main - enter any key to terminate (and press enter)" << endl;
	cin >> c;
	cout << "\n \n main - end" << endl;
	_CrtDumpMemoryLeaks();
	return 0;
}
