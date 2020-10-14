//=============================================================================================================================================
/*
*  Item 2: Prefer C++ casts over C style cast
*  ------------------------------------------
*  1) Castting lets us "treat" an object a little "differently". But the way one treats an object differnetly in different types of casting is 
*     totally different - for example, casting "non constenss" Vs casting an object from Base class to a Derived class are two different things,
*     YET, thier "casting syntax" is the SAME. This is all true to C style casts. It would have been nice if there was more "information" on each
*     cast that is present in the code so one can better understand the motiviation and purpose behind that cast.
*     There are four different types of C++ casting
*  2) static_cast<type>(expresion)
*     Simply casts the expression to be of the type specified in <type>. Just as in good old C style cast.
*  3) const_cast<type>(expression)
*     is used to cast away the "constness" of an object. Note that it DOES NOT used to cast "in between" inheritence hireracy. 
*  4) dynamic_cast<type>(expression)
*     Is used to cast object pointer or reference across an inheritence hirecarcy. For example, cating Base class pointer to one of its
*     derived "sub types" (children) is possible using this cast. In case the casting is "legit inheritence wise" then the pointer is casted
*     to the derived type, otherwise it returns a NULL poiner or throws an excpetion in the case of reference.
*     IMPORTANT NOTE: dynamic_cast is applicable ONLY if the "base" object of the inheritence chain, is indeed "polymorphic", meaning, it has
*     at least one function that is virtual. If it does not, then trying to perform dynamic_cast will fail to compile.
*/
// =============================================================================================================================================
#include <iostream>
#include <string>

using namespace std;

class Base
{

};

class Derived : public Base
{
	public:
		void f2() const 
		{
			cout << "Derived::f2()" << endl;
		}
};


class Wideget
{
	public:
		Wideget() : m_a(12)
		{
			cout << "Wideget::Wideget" << endl;
		}

		virtual ~Wideget()
		{
			cout << "Wideget::~Wideget" << endl;
		}


		int m_a;
};

class SpecialWideget : public Wideget
{
	public:
		void f1() const
		{
			cout << "SpecialWideget::f1()" << endl;
		}
};

void updateWideget(Wideget* pWideget)
{
	pWideget->m_a = 17;
}

void item2Usage()
{
	string funcName = "item2Usage - ";
	cout << "item2Usage - start" << endl;

	// 2) static_cast
	int num1 = 12, num2 = 5;
	double res = static_cast<double>(num1) / num2;
	cout << "item2Usage - res is:" << res << endl;

	// 3) const_cast
	const Wideget wideget1;
	cout << funcName + " wideget1 m_a is:" << wideget1.m_a << endl;
	// updateWideget(&wideget1);  --> invalid conversion from const Wideget* to Wideget* [-fpermissive]
	updateWideget(const_cast<Wideget*>(&wideget1));
	cout << funcName + " after changing wideget1.m_a it is:" << wideget1.m_a << endl;

	// 4) dynamic_cast
	Wideget* pWideget = new SpecialWideget();
	cout << funcName + " when poiting with a normal Wideget* on a SpecialWideget, its value is:" << pWideget->m_a << endl;	
	// pWideget->f1(); base class pointer does NOT recoginze Dervied class "only" function.
	cout << funcName + " casting the Wideget pointer to be of type SpecialWideget pointer and then calling f1()" << endl;
	dynamic_cast<SpecialWideget*>(pWideget)->f1();

	Derived derived;
	Base* pBase = &derived;
	cout << funcName + "cating the Base pointer that points to a Dervied object using dynamci_cast and then trying to invoke Dervied class function" << endl;	
	
	// error: cannot dynamic_cast ‘pBase’ (of type ‘class Base*’) to type ‘class Derived*’ (source type is not polymorphic)
	//dynamic_cast<Derived*>(pBase)->f2();
	
	delete pWideget;
	cout << "item2Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item2Usage();
	cout << "\n \n main - end" << endl;
	return 0;
}


