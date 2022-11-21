// ================================================================================================================================================
// ================================================================================================================================================
// Chapter 8 - type conversions:
// ----------------------------
// 1) In C/C++ when some operation between two types is being conducted it is CRUCIAL to understand how the compiler treats this operation.
// 2) 
//    https://anteru.net/blog/2007/c-background-static-reinterpret-and-c-style-casts/
// 3) 
// =================================================================================================================================================
// =================================================================================================================================================

#include <iostream>

using namespace std;

class ParentWithoutVtable
{    
    char empty;
};

class ParentWithVTable
{
    public:
        virtual ~ParentWithVTable () { }
};

class Derived : public ParentWithoutVtable, public ParentWithVTable
{
};

void objectCastedViaDifferentTypesOfCasting()
{

}

void integersDivisionVsDoubleDivision()
{
	string funcName = "integersDivisionVsDoubleDivision - ";
	cout << funcName + "start" << endl;
	double d1 = 10 / 4; //1)
	cout << funcName + "the result of performing two literals division is:" << d1 << endl;
	d1 = static_cast<double>(10) / 4;
	cout << funcName + "the result of performing two literals division when one is casted to double is:" << d1 << endl;
	cout << funcName + "end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	integersDivisionVsDoubleDivision();
	cout << "main - end" << endl;
	return 0;
}
