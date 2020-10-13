// =============================================================================================================================================
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
*/
// =============================================================================================================================================
#include <iostream>
#include <string>

using namespace std;

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
	// updateWideget(&wideget1);  --> invalid conversion from ‘const Wideget*’ to ‘Wideget*’ [-fpermissive]
	updateWideget(const_cast<Wideget*>(&wideget1));
	cout << funcName + " after changing wideget1.m_a it is:" << wideget1.m_a << endl;
	cout << "item2Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item2Usage();
	cout << "\n \n main - end" << endl;
	return 0;
}
