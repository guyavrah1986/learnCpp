// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 1) default Ctor:
// ----------------
// a) As long as we have decalred and defined at least one Ctor of our own (does not matter which type of Ctor and how we implemented it) --> the defualt Ctor 
//    providied by the compiler is disabled (technically speaking - it is not public so it can NOT be used from outside of the class).
//
// b) Note that the values that the compiler's defualt constructor initializes the class members are garbage values - so we should NOT make any assumption on 
//    these values (it follows the "C++ mantra" of "you don't ask for it - you dont get it, and you dont pay for it"). 
//
// c) In this example we created the argument Ctor --> so we also defined the defualt Ctor (it is not always neccssary).
//
// d) In case our class holds class members which are classes as well, their defualt ctor will be called BEFORE the body of the ctor of our class will be 
//    executetd. 
//
// e) SEE NOTE IN THE CODE - This will invoke the defualt ctor we have implemented for our container object.
// Some additioanl notes here:
// # before the body of the container object is called - the Ctor of the object contained by value is called - it make sense, cause it might be the case that 
//   some logic in the container object will be based on its member -- so go ahead nad initialize them first !!
// # ONLY the defualt ctor of the object which is contained by value is invoked !! not the one of the object contained by pointer !!
// # for class members contained by reference we can not illustrate it here cause they enforces us to initialize them in all the given ctors initialization 
//   list - it will be discussed later...
//
// f) Note that if we switch between the order of declaration of the const stirng m_str and the m_innerObjWithString --> then, upon initialization of the 
//    m_innerObjWithString the const string is not yet defined and an undefined behaviour might take place (for example segmentation fault might occur 
//    when the uninitialized const stirng will be passed to the m_innerObjWithString object).
//    Note also, that because we invoked explictly the argument Ctor of the m_innerObjWithString object as part of the container class initializer 
//    list --> the defualt ctor of the m_innerObjWithString IS NOT CALLED. 
// 
// g) As the previous note state, the order of declration of our class members is important - they will be initialized according to the order which 
//    they were declared.
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>
#include <string>

using namespace std;

class InnerObjValue 
{

public:
	InnerObjValue() : m_a(17)
	{
		cout << "InnerObjValue::InnerObjValue - setting m_a to:" << m_a << endl;
	}

private:
	int m_a;
};


class InnerObjPointer 
{

public:
	InnerObjPointer() : m_c(15)
	{
		std::cout << "InnerObjPointer::InnerObjPointer - setting m_c to:" << m_c << endl;
	}

private:
	int m_c;
};


class InnerObjWithString
{

public:
	InnerObjWithString(const string& str) : m_str(str) 
	{
		cout << "InnerObjWithString::InnerObjWithString - m_str is set to:" << m_str << endl;
	}

private:
	string m_str;
};

class ContainerObj
{

public:
	ContainerObj() : m_innerObjWithString(m_str), m_d(22)
	{
		cout << "ContainerObj::ContainerObj - setting m_d to:" << m_d << endl;
	}

private:

	InnerObjValue m_innerObjByValue;
	const string m_str = "const string";
	InnerObjWithString m_innerObjWithString;// f)
	InnerObjPointer* m_innerObjByPointer;

	int m_d;
};

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================

int main(int argc, char** argv)
{

	cout << "main - start" << endl;
	cout << "about to create a ContainerObj on the stack of main" << endl;

	// e) 	
	ContainerObj obj;

	cout << "main - end" << endl;
	return 0;
}

