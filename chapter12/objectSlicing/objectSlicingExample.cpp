// ===================================================================================================================================================================
// ===================================================================================================================================================================
// Object slicing:
// ---------------
// a) in function callByRef, due to the fact that we defined the argument to the function as const reference --> we must AS WELL define the foo function as const.
//    try it for yourself: remove the const from the argument to foo and you will be able to remove the const from the foo() function declration. 
// b) When we invoke a method that accepts an argument by value of type Base --> when we pass Base object,everything will occur as we excpect. 
//    Yet when we will pass a Derived object ,upon the function invocation, ONLY the Base's copy Ctor will be called leaving the sent argument as "sliced" -- only the
//    "Base part" of the object was copied --> therefor the passed object is of type Base.
//    NOTE: The thing here is to pay attention to situations where an invocation of this type might happen , cause with all that is related to compilation issues 
//    there wont be any, not even warnings that might warn us in advance. 
// c) The two approaches we can take in order to aviod the "object slicing" is to pass the argument by reference OR by address (pointer).
// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <iostream>


class Base 
{

public:
	Base(std::string str = "defualt_base") : m_str(str)
	{
		std::cout << "Base::Base - setting m_str to:" << m_str << " this is:" << this << std::endl;
	}

	Base(const Base& other) : m_str(other.m_str)	
	{
		std::cout << "Base::(copy) - setting m_str to:" << m_str << std::endl;
	}

	virtual ~Base()
	{
		std::cout << "Base::~Base" << std::endl;
	}

	virtual void foo() const   //a)
	{
		std::cout << "Base::foo - m_str is:" << m_str << std::endl;
	}

	std::string m_str;
};



class Derived : public Base 
{

public:
	Derived(std::string str1 = "defualt_derived", std::string str2 = "defualt_derived_base") : m_strDerived(str1) , Base(str2)
	{
		std::cout << "Derived::Derived - setting m_strDerived to:" << m_strDerived << " this is:" << this << std::endl;
	}

	Derived(const Derived& other) : m_strDerived(other.m_strDerived) , Base(other)
	{
		std::cout << "Derived:: (copy)" << std::endl;
	}

	~Derived()
	{
		std::cout << "Derived::~Derived" << std::endl;
	}

	virtual void foo() const //a)
	{
		std::cout << "Derived::foo - m_strDerived is:" << m_strDerived << std::endl;
	}

	std::string m_strDerived;
};


// ===================================================================================================================================================================
// ===================================================================================================================================================================


void callByValue(/* b) */Base b)
{
	std::cout << "callByValue" << std::endl;
	b.foo();
}

void callByRef(/* c) */ const Base& b) //a) 
{
	std::cout << "callByRef" << std::endl;
	b.foo();
}

void callByAddress(/* c) */ const Base* b) // a) 
{
	std::cout << "callByAddress" << std::endl;
	b->foo();
}


// ===================================================================================================================================================================
// ===================================================================================================================================================================


int main(int argc, char** argv)
{
	std::cout << "main - start" << std::endl;
	
	std::cout << "main - creating a Derived object on the main stack" << std::endl;
	Derived d("main_derived", "main_base");

	std::cout << "main - about to ibvoke callByValue" << std::endl;
	callByValue(/* b) */d);

	std::cout << "main - about to ibvoke callByRef" << std::endl;
	callByRef(d);

	std::cout << "main - about to ibvoke callByAddress" << std::endl;
	callByAddress(&d);

	std::cout << "main - end" << std::endl;
	return 0;
}

