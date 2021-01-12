// ===================================================================================================================================================================
// ===================================================================================================================================================================
// copy elision:
// -------------
// 1) In both cases (a and b), the "phenonmana" that takes place is that the compiler taking advatage of the fact that the local object is goiong to be returned by 
//    value any way, so it "skips" the actual copying of the object and simply "directly" initializes the object into the "recving" object in the main program 
//    (calling function). This optimization is also known as the Return Value Optimization (RVO).
// 
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>

using namespace std;

class A
{
public:
	A() : m_a(12)
	{
		cout << "A::A()" << endl;
	}

	A(int a) : m_a(a)
	{
		cout << "A::A(int a)" << endl;
	}

	A(const A& other) 
	{
		cout << "A::A(copy)" << endl;
		this->m_a = other.m_a;
	}

	A& operator=(const A& rhs) 
	{
		cout << "A::A(operator=)" << endl;
		if (&rhs == this)
		{
			cout << "A::A(operator=) - &rhs == this" << endl;
			return *this;
		}

		this->m_a = rhs.m_a;
		return *this;
	}

	~A()
	{
		cout << "A::~A" << endl;
	}

	int m_a;
};

A returnObjectByValue1()
{
	cout << "returnObjectByValue1" << endl; 
	A a(12);
	return a; //1a)
}

A returnObjectByValue2()
{
	cout << "returnObjectByValue2" << endl;
	return A(15); //1b)
}

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================


int main(int argc, char** argv)
{

	cout << "main - start" << endl;


	A a1 = returnObjectByValue1();
	cout << "main - a1.m_a is:" << a1.m_a << endl;
	cout << "main - returnObjectByValue1 directly into cout, m_a is:" << returnObjectByValue1().m_a << endl;


	A a2 = returnObjectByValue2();
	cout << "main - a2.m_a is:" << a2.m_a << endl;
	cout << "main - returnObjectByValue2 directly into cout, m_a is:" << returnObjectByValue2().m_a << endl;


	cout << "main - end" << endl;
	return 0;
}




