// ===================================================================================================================================================================
// ===================================================================================================================================================================
// Object slicing:
// ---------------
// a) in function callByRef, due to the fact that we defined the argument to the function as const reference --> we must AS WELL define the foo function as const.
//    try it for yourself: remove the const from the argument to foo and you will be able to remove the const from the foo() function declration. 
// b) When we invoke a method that accepts an argument by value of type Base --> when we pass Base object,everything will occur as we excpect. 
//    Yet when we will pass a Derived object ,upon the function invocation, ONLY the Base's copy Ctor will be called leaving the sent argument as "sliced" -- only the
//    "Base part" of the object was copied --> therefor the passed object is of type Base (it does NOT have the Derived part).
//    NOTE: The thing here is to pay attention to situations where an invocation of this type might happen , cause with all that is related to compilation issues 
//    there wont be any, not even warnings that might warn us in advance. 
// c) The two approaches we can take in order to aviod the "object slicing" is to pass the argument by reference OR by address (pointer).
// ===================================================================================================================================================================
// =================================================================================================================================================================== 
#include <iostream>
#include <vector>

using namespace std;

class Base 
{

public:
	Base(string str = "defualt_base") : m_str(str)
	{
		cout << "Base::Base - setting m_str to:" << m_str << " this is:" << this << endl;
	}

	Base(const Base& other) : m_str(other.m_str)	
	{
		cout << "Base::(copy) - setting m_str to:" << m_str << endl;
	}

	virtual ~Base()
	{
		cout << "Base::~Base" << endl;
	}

	virtual void foo() const   //a)
	{
		cout << "Base::foo - m_str is:" << m_str << endl;
	}

	string m_str;
};



class Derived : public Base 
{

public:
	Derived(string str1 = "defualt_derived", string str2 = "defualt_derived_base") 
		: Base(str2)
		, m_strDerived(str1)
	{
		cout << "Derived::Derived - setting m_strDerived to:" << m_strDerived << " this is:" << this << endl;
	}

	Derived(const Derived& other) 
		: Base(other)
		, m_strDerived(other.m_strDerived)
	{
		cout << "Derived:: (copy)" << endl;
	}

	~Derived()
	{
		cout << "Derived::~Derived" << endl;
	}

	virtual void foo() const //a)
	{
		cout << "Derived::foo - m_strDerived is:" << m_strDerived << endl;
	}

	string m_strDerived;
};


// ===================================================================================================================================================================
// ===================================================================================================================================================================


void callByValue(Base b)	// b)
{
	cout << "callByValue" << endl;
	b.foo();
}

void callByRef(/* c) */ const Base& b) //a) 
{
	cout << "callByRef" << endl;
	b.foo();
}

void callByAddress(/* c) */ const Base* b) // a) 
{
	cout << "callByAddress" << endl;
	b->foo();
}


// ===================================================================================================================================================================
// ===================================================================================================================================================================


int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	
	cout << "main - creating a Derived object on the main stack" << endl;
	Derived d("main_derived", "main_base");

	cout << "main - about to invoke callByValue" << endl;
	callByValue(d);	// b)

	cout << "main - about to invoke callByRef" << endl;
	callByRef(d);

	cout << "main - about to invoke callByAddress" << endl;
	callByAddress(&d);

	vector<Base> baseVec;
	cout << "main - about to insert d into the vector" << endl;
	baseVec.push_back(d);
	cout << "main - done inserting d into the vector, lets call its derived function" << endl;
	baseVec[0].foo();

	cout << "main - end" << endl;
	return 0;
}

