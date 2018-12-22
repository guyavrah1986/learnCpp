// =====================================================================================================================
// =====================================================================================================================
// mutable keyowrd in C++:
// -----------------------
// 1) In its very basic usage, the `mutabble` keyowrd in C++ can be assgined to a class member which is NOT static OR
//    const. 
// 
// 2) The most common use of it is when we create a CONST class instance, and at some point of time we wish to modify
//    one of its members. The ONLY member we will be able to modify is the one which its "storage" specifier is 
//    mutable.
//
// =====================================================================================================================
// =====================================================================================================================
#include <iostream>

using namespace std;

class A
{
public:
	A(int x, int y)
		: m_x(x)
		, m_y(y)
	{
		cout << "A::A - set m_x to:" << m_x << ", m_y to:" << m_y << endl;
	}

	~A()
	{
		cout << "A::~A" << endl;
	}

	mutable int m_x;	// 1)
	int m_y;
};

void basicMutableExample()
{
	cout << "basicMutableExample - start" << endl;

	const A a(15,17);
	a.m_x = 9;
	//a.m_y = 10;
	cout << "basicMutableExample - end" << endl;
}


// ----------------------
// main
// ----------------------

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	
	basicMutableExample();

	cout << "main - start" << endl;
	return 0;
}
