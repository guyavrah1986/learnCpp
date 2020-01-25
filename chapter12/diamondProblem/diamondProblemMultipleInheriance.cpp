// ##############################################################################################################################################################################################
// ##############################################################################################################################################################################################
// The diamond probelm:
// ====================
// 1) It arises, for example, when a "Derived" class inherites from two (or more) Base classes where two of them in turn inherits from the same grandparent
//    class --> causing each:
//    a) class member defined in the grandparent class to appear twice.
//    b) class method to be dfeind twice as well thus causing compilation error as follows (compiling with g++ and the command:g++ diamondProblemMultipleInheriance.cpp -o myExe)
//    diamondProblemMultipleInheriance.cpp: In function ‘void diamondProblemIllustration()’:
//    diamondProblemMultipleInheriance.cpp:77:4: error: request for member ‘func1’ is ambiguous
//    d.func1();
//    ^~~~~
//    diamondProblemMultipleInheriance.cpp:23:7: note: candidates are: void Base1::func1()
//    void func1()
//    ^~~~~
//    diamondProblemMultipleInheriance.cpp:23:7: note:                 void Base1::func1()
//
// 2) In order to solve this "issue" one should do the following:
// the virtual keyword was added in the Base2 & Base3 inheritance notation:
// a) In class Base2
// b) In class Base3
// c) The default CTOR of Base1 should be implemented (explicitly)
//
// ##############################################################################################################################################################################################
// ##############################################################################################################################################################################################
#include <iostream>

using namespace std;

class Base1
{
public:
	Base1(int b1) : m_b1(b1)
	{
		cout << "Base1::Base1(int) - setting m_b1 to:" << this->m_b1 << endl;
	}

	Base1() : m_b1(0) // 2c)
	{
		cout << "Base1::Base1() - setting m_b1 to:" << this->m_b1 << endl;
	}

	void func1()
	{
		string funcName = "Base1::func1 - ";
		cout << funcName << endl;
	}

protected:
	int m_b1;
};

class Base2 : virtual public Base1 // 2a) delete the virtual keyword and see the compilation error
{
public:
	Base2(int b1, int b2) : Base1(b1), m_b2(b2)
	{
		cout << "Base2::Base2(int, int) - setting m_b2 to:" << b2 << endl;
	}

protected:
	int m_b2;
};

class Base3 : virtual public Base1 // 2b) delete the virtual keyword and see the compilation error
{
public:
	Base3(int b1, int b3) : Base1(b1), m_b3(b3)
	{
		cout << "Base3::Base3(int, int) - setting m_b3 to:" << this->m_b3 << endl;
	}

protected:
	int m_b3;
};

class Derived : public Base3, Base2
{
public:
	Derived(int b1, int b2, int b3, int d) : Base3(b1, b3), Base2(b1, b2), m_d(d)
	{
		cout << "Derived::Derived(int, int, int, int) - setting m_d to:" << this->m_d << endl;
	}

protected:
	int m_d;
};


void diamondProblemIllustration()
{
	string funcName = "diamondProblemIllustration - ";
	cout << funcName + "start" << endl;
	cout << funcName + "creating a Dervied object on the stack" << endl;
	Derived d(1,2, 3, 4);
	cout << funcName + "calling d.func1()" << endl;
	d.func1();
	cout << funcName + "end" << endl;
}

int main(int argc, char** argv)
{
	string funcName = "main - ";
	cout << funcName + "start" << endl;
	diamondProblemIllustration();
	cout << funcName + "end" << endl;
	return 0;
}
