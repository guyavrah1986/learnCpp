// ================================================================================================================================================
// ================================================================================================================================================
// Chapter 4 - namespaces:
// ----------------------
// 1) C++ introduces the concept (and keyword) of namespace. This enables us to "gather" several variables and functions into a unique enviroment
//    in which they are defined. This way we can define, for instance, two functions with the exact (!!) same signature in TWO DIFFERENT namespaces
//    and use them both.
// 2) Note that namespace can be EXPANDED throughout several files.
// 3) In this case the compiler won't know to which "version" of the function doSomething it should call, so a compiler error will rise.
// =================================================================================================================================================
// =================================================================================================================================================

#include <iostream>

#include "add.h"
#include "sub.h"
#include "subCont.h"	// 2) 

using namespace std;

void callFuncWithoutNamespacePrefix()
{
	cout << "callFuncWithoutNamespacePrefix - start" << endl;
	//int res = doSomething(12,15);
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	cout << "main - using Add::doSomething(4,2):" << Add::doSomething(4,2) << endl;
	cout << "main - using Sub::doSomething(4,2):" << Sub::doSomething(4,2) << endl;
	cout << "main - using Sub::doSomething2(4,2):" << Sub::doSomething2(4,2) << endl;

	cout << "main - end" << endl;
	return 0;
}
