// ========================================================================================================================================================================
/*
* Item 12:
* --------
* Preface:
* 1) Some key difference between passing an argument to a function than catching an exception in the catch clause:
* a) When we throw an exception (which might be any "std home-made" OR user defined class) to a catch cluases, if the catch 
*    clauses DOES NOT recive a pointer, meaning, it recives the exception "by reference" OR "by value" --> the object being thrown
*    is copied (!!) from the throw site ("caller") to the exception clauses ("calle").
* b) This is NOT the case with "simple" object passing to function's arguments.
* 2) As long as we do not throw a pointer object, a copy of the object we throw will be created, ALWAYS, regardless if we catch by
*    reference or by value. 
*    - In the specific case that we catch by value, an ADDITONAL copy is made to the "original" copy of the thrown object, whcih leaves
*    us with TWO copies that were made.
* a) The type of the object that will be created (copied) follows the static type copy, meaning, the copy will be according to the 
*    STATIC type of the object -- in this case b is "refered" via an A reference (Base class), so a copy of the A's part of the b 
*    object will be created (and not a copy of an "entire" B object).
* 3) Note that the order of the catch's blocks is VITAL. If we switch between the catch blocks, meaning, catch A& will be the first 
*   catch block followed by a B& catch block, than, upon throwing a B object - we will still enter catch A& block (and only into it).
* 4) In contrast to cases where an implict (legall) type conversion might occur - it is NOT the case when throwing primitive data types.
*    So, when an int is throw, ONLY an int catch clauses will cathc it, and NOT, for instance, a double catch clause.
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key note:
* - Each time an exception is thrown, a COPY of the object to be thrown is made, and it is the object which is throw.
* - When we catch an exception by value (due to the first note above), there is an additonal copy being performed.
* - Always prefer to "re-throw" an exception using throw (and not throw ex).
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*/
// ======================================================================================================================================================================

#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>
#include <string>

using namespace std;

class A
{
public:
	A(const string& str)
		: m_str(str)
	{
		cout << "A::A - set m_str to:" << m_str << endl;
	}

	~A()
	{
		cout << "A::~A" << endl;
	}

	A(const A& other)
		: A(other.m_str)
	{
		cout << "A::A(copy)" << endl;
	}

	A& operator=(const A& rhs)
	{
		if (this == &rhs)
		{
			cout << "A::operator= - returning *this" << endl;
			return *this;
		}

		this->m_str = rhs.m_str;
		return *this;
	}

	virtual const char* what()
	{
		m_str += " from A what";
		return m_str.c_str();
	}

	string m_str;
};

class B : public A
{
public:
	B(const string& str, int b)
		: A(str)
		, m_b(b)
	{
		cout << "B::B - set m_b to:" << m_b << endl;
	}

	~B()
	{
		cout << "B::~B" << endl;
	}

	B(const B& other)
		: B(other.m_str, other.m_b)
	{
		cout << "B::B(copy)" << endl;
	}

	virtual const char* what()
	{
		m_str += " from B what";
		return m_str.c_str();
	}

	int m_b;
};

void getAByRef(const A& a)
{
	cout << "getAByRef - got a object with address:" << &a << endl;
}

void diffBetweenCatchAndArgumentByValOrRef()
{
	cout << "diffBetweenCatchAndArgumentByValOrRef - start" << endl;
	try
	{
		A a("A on function stack");
		cout << "diffBetweenCatchAndArgumentByValOrRef - within try block, calling getAByRef, sending it a local object with address:" << &a << " as an argument" << endl;
		getAByRef(a); // 1b)
		cout << "diffBetweenCatchAndArgumentByValOrRef - within try block, throwing the same local A object as an exception" << endl;
		throw a; // 1a)
	}
	catch (const A& a) // 1a) 
	{
		cout << "diffBetweenCatchAndArgumentByValOrRef - within catch block, caught an A object with address:" << &a << endl;
	}
}

void illustrateThrowingDerivedExceptionObj()
{
	try
	{
		cout << "illustrateThrowingDerivedExceptionObj - within try block, creating B object on the stack" << endl;
		B b("B on function stack", 8);
		cout << "illustrateThrowingDerivedExceptionObj - within try block, setting an A reference to refer to the B object" << endl;

		A& aRef = b; // 2a)
		//throw aRef; 2a)

		throw b; // 2) 
	}
	catch (B& b) // 3) 
	{
		cout << "illustrateThrowingDerivedExceptionObj - within catch B& block, caught an B objet:" << b.what() << endl;
	}
	catch (A& a) // 3)
	{
		cout << "illustrateThrowingDerivedExceptionObj - within catch A& block, caught an A objet:" << a.what() << endl;
	}
}

void illustrateNoImplicitTypeConversionForPodAsThrownObject()
{
	cout << "illustrateNoImplicitTypeConversionForPodAsThrownObject - start" << endl;
	int i = 9;
	try
	{
		cout << "illustrateNoImplicitTypeConversionForPodAsThrownObject - within try block, throwing an int" << endl;
		throw i; // 4)
	}
	catch (double d)
	{
		cout << "illustrateNoImplicitTypeConversionForPodAsThrownObject - within catch double blcok, got d:" << d << endl;
	}
	catch (int i)
	{
		cout << "illustrateNoImplicitTypeConversionForPodAsThrownObject - within catch int blcok, got i:" << i << endl;
	}
}

void item12Usage()
{
	cout << "item12Usage - start" << endl;

	diffBetweenCatchAndArgumentByValOrRef();
	illustrateThrowingDerivedExceptionObj();
	illustrateNoImplicitTypeConversionForPodAsThrownObject();

	cout << "\n \n item12Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	item12Usage();

	char c = 0;
	cout << "main - enter any key to terminate (and press enter)" << endl;
	cin >> c;
	cout << "\n \n main - end" << endl;
	_CrtDumpMemoryLeaks();
	return 0;
}
