// ===================================================================================================================================================================
// ===================================================================================================================================================================
// the "this" pointer:
// -------------------
// 1) For each object we create, there will be a "reference" to distinguish each instance from OTHER instances of the same class, this is the (main) motivation of 
//    the 'this pointer`.
// 2) For EVERY NON STATIC class member function, the compiler "adds" an additional argument, the `this pointer`.One can think about it as "argument No 0" to every
//    NON STATIC class function.
// 3) When we wish to use a class member function as a call back function that we will send its address - we CAN NOT use a NON STATIC class member function due to
//    the above fact - the signature of the function will not be correct no matter what type of signature we will use. 
// 4) One solution to this situation is to declare the call back function as a STATIC function - cause in these function no `this` pointer is added, so we can 
//    match the signature type correctly.   
//    NOTES:
//    a) As STATIC member function obligate - ONLY STATIC class members can be accessed in these function.
//    b) Note a might be crusial in cases where the call back function can be accessed via several threads concurrently AND if this function accesses any class member  
// 
// Some notes:
// -----------
// Good link in this topic: https://www.geeksforgeeks.org/this-pointer-in-c/ 
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>

typedef void (*callBackFuncPointer)(int);

using namespace std;

class A 
{

public:
	A() : m_a(17)
	{
		cout << "A::A - setting m_a to:" << m_a << ", this pointer is at address:" << this << ", m_a is at address:" << &m_a << endl;
	}

	~A()
	{
		cout << "A::~A" << endl;
	}	

	void someNonStaticFunc(int a)
	{
		cout << "A::someNonStaticFunc - got a:" << a  << ", this pointer is at address:" << this << endl;
	}

	static void someStaticFunc(int a)	// 4)
	{
		cout << "A::someStaticFunc - got a:" << a << endl;
	}

private:
	int m_a;
};

void funcToInvokeCallBackFunc(callBackFuncPointer cbFunc, int a)	// 3)
{
	cout << "funcToInvokeCallBackFunc - start" << endl;
	cbFunc(a);
	cout << "funcToInvokeCallBackFunc - end" << endl;
}


// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================


int main(int argc, char** argv)
{

	cout << "main - start" << endl;

	A a1;
	int a = 15;
	a1.someNonStaticFunc(17);
	//funcToInvokeCallBackFunc(A::someNonStaticFunc, a);	// 3)
	funcToInvokeCallBackFunc(A::someStaticFunc, a);


	cout << "main - end" << endl;
	return 0;
}



