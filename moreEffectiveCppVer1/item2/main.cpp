// =============================================================================================================================================
/*
*  Item 2: Prefer C++ casts over C style cast
*  ------------------------------------------
*  1) Castting lets us "treat" an object a little "differently". But the way one treats an object differnetly in different types of casting is 
*     totally different - for example, casting "non constenss" Vs casting an object from Base class to a Derived class are two different things,
*     YET, thier "casting syntax" is the SAME. This is all true to C style casts. It would have been nice if there was more "information" on each
*     cast that is present in the code. 
*
*/
// =============================================================================================================================================
#include <iostream>
#include <string>

using namespace std;

void item2Usage()
{
	cout << "item2Usage - start" << endl;
	cout << "item2Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item2Usage();
	cout << "\n \n main - end" << endl;
	return 0;
}
