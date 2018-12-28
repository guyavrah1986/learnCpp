// ========================================================================================================================================================================
/*
* Item 9:
* ------
* One note worth mention in the first place is - Why should we use exceptions in the first place ? 
* The answer is simple: Exceptions can NOT be ignored !!
* 
* 1) One can create its own class and derive from the std::exception class. 
* 2) Once we derived from std::exception, we can override the what() method that returns a const char* string that describes the exception.NOTE: Do not use this string 
*   for comparsion - any compiler might implement it, thus return a different value. 
* 3) When we have several classes of excptions in an inheritence chain, we need to place the different excptions types from the most derived "downwards", otherwise 
*    the first match will be the one that will catch the excption.
* 4) In order to avoid resource leak (if A were defined as a "normal" plain pointer), we can use this technique - "wrap" the pointer to 
*    the object that is being created within a "wrapper" function, which:
* -  initialized it in the ctor.
* -  therefor, responsible, NO MATTER WHAT WILL HAPPEN DURING THE EXECUTION of the program, to destrcut it properly.
*    In this case, we achive this "requirment" via using the unique_ptr class from the STL.
*/
// ======================================================================================================================================================================

#include <iostream>
#include <exception>	// for std::exception
#include <cstring>	// for strcpy
#include <memory>	// for unique_ptr
#include <string>

using namespace std;

class MyException : public exception // 1)
{
	public:
	explicit MyException(const string& str) 
		: m_str(str)
	{
		cout << "MyException::MyException - setting m_str to:" << m_str << endl;
	}

	virtual ~MyException()
	{
		cout << "MyException::~MyException" << endl;
	}

	virtual const char* what() const throw ()  // 2) 
	{
		return m_str.c_str();
	}

	string m_str;	
};

class A
{
	public:	
	explicit A(int a) 	
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


void funcThatThrowsException()
{
	throw MyException("sample exception");
}

void item9Usage()
{
	cout << "item9Usage - start" << endl;

	// 4) allocate something on the heap
	unique_ptr<A> pa(new A(12));

	// call a function that will throw an exception WITHOUT handling it...
	funcThatThrowsException();
	cout << "\n \n item9Usage - " << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	try 
	{
		cout << "main - start of try block, about to call item9usage method" << endl;
		item9Usage();
	}
	catch (const MyException& e) // 3) 
	{
		cout << "main - within const MyExcpetion& e catch block, e.what is:" << e.what() << endl;
	}
	catch (const exception& e)
	{
		cout << "main - within const exception& e catch block, e.what is:" << e.what() << endl;
	}

	char c = 0;
	cout << "main - enter any key to terminate (and press enter)" << endl;
	cin >> c;
	cout << "\n \n main - end" << endl;
	return 0;
}
