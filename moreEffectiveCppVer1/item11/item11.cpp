// ========================================================================================================================================================================
/*
* Item 11:
* --------
* Preface: When a C++ program is running, and there is an exception that is thrown and NOT YET caught - if an ADDITIONAL exception is thrown
* --> the program "crashes" (terminates) immidiatly, by calling the terminate method. This is a bad scenarion which we have to eliminate !!
* 1) Here we start the "facked stack-unwinding" flow.
* 2) New "feature" introduced - we can check to see if there is an "on-going" exception.
* 3) This is where things get tricky - if we enable this function WITHOUT catching the potential exception that it might throw, than, if there is 
*    already another exception on going, we will terminate immideatly, thus, potentially leaving the dtor WITHOUT executing all its "clean-up"
*    logic --> we will have a resource leak EVEN if the data members of this class are "stack" objects !!
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key note: In the precence of a possibilty that the code within a dtor might throw excpetions --> WE HAVE to use try and catch block
* within the dtor.
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*/
// ======================================================================================================================================================================

#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>
#include <memory>

using namespace std;

class B
{
public:
	explicit B(int b)
		: m_b(b)
	{
		cout << "B::B" << endl;
	}

	~B()
	{
		cout << "B::~B" << endl;
	}

	int m_b;
};

class A
{
public:
	A(int a)
		: m_a(a)
		, m_b(12)
	{
		cout << "A::A - set m_a to:" << m_a << endl;
	}

	A()
		: A(17)
	{
		cout << "A::A(default)" << endl;
	}

	void simpleFuncToThrowException()
	{
		cout << "A::simpleFuncToThrowException - throwing an exception" << endl;
		throw exception("sample exception to simulate situation where some function (code) of the dtor of class A threw an exception");
	}

	~A()
	{
		cout << "A::~A" << endl;
		if (uncaught_exception() == true) // 2)
		{
			cout << "A::~A - there is already an active exception" << endl;
		}
		else
		{
			cout << "A::~A - there is no active exception" << endl;
		}

		try
		{
			// 3) 
			simpleFuncToThrowException();
		}
		catch (const exception& e)
		{
			cout << "A::~A - caught an exceptino:" << e.what() << endl;
		}

	}

	B m_b;
	int m_a;
};

void item11Usage()
{
	cout << "item11Usage - start" << endl;
	
	// 1) simulate a situation where the dtor of class A will be invoked while 
	// there is "already" another exception "on-going"
	{
		try 
		{
			cout << "item11Usage - creating A object on the stack, and then immideatly throwing an exception" << endl;
			A a;
			throw exception("sample exception to start stack unwinding");
		}
		catch (const exception& e)
		{
			cout << "item11Usage - caught an exceptionn:" << e.what() << endl;
		}
	}

	cout << "\n \n item11Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	item11Usage();

	char c = 0;
	cout << "main - enter any key to terminate (and press enter)" << endl;
	cin >> c;
	cout << "\n \n main - end" << endl;
	_CrtDumpMemoryLeaks();
	return 0;
}
