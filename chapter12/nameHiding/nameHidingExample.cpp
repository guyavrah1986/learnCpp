// 
//  Name hiding:
// -------------
// In C++ every name (of an object/funciton/enumration) that is defined in some "inner" scope, hides (eliminate) a similar name that exsits in an "outer scope".
// So, here in this example, the fact that Derived class has a function called func1, which is NOT virtual, means that every function with the same name (not entire signature) 
// will be "hiden" --> not visible (we will get a compiler error when trying to call it).
//
//
//


#include <iostream>

using namespace std;


class Base
{
	public:
	Base() 
	{
		cout << "Base::Base" << endl;
	}

	virtual ~Base() 
	{
		cout << "Base::~Base" << endl;
	}

	void func1()
	{
		cout << "Base::func1()" << endl;
	}

	void func1(int i)
	{
		cout << "Base::func1(int) - got:" << i << endl;
	}
};


class Derived : public Base
{
	public:
	Derived()
	{
		cout << "Derived::Derived" << endl;
	}

	virtual ~Derived()
	{
		cout << "Derived::Derived" << endl;
	}

	void func1()
	{
		cout << "Derived::func1()" << endl;
	}
};

int main(int argc, char** argv)
{
	cout << "nameHidingExample - start" << endl;

	cout << "nameHidingExample - creating Derived object on the stack" << endl;
	Derived d;
	Base* bp = &d;

	cout << "nameHidingExample - calling func1 with a derived object" << endl;
	d.func1();

	cout << "nameHidingExample - calling func1 with a derived object pointed by a Base pointer" << endl;
	bp->func1();

	// Uncomment in order to see the compilation error.
	// trying to call the func1(int) version of the Base class won't work -- cause it is being hidden by the func1(void) of 
	// the Derived class. 
	//d.func1(16);

	cout << "\n \n nameHidingExample - end" << endl;
	return 0;
}

