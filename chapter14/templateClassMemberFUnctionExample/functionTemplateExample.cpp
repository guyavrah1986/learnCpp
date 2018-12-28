// ======================================================================================================================================================================================
/*
*  Function templates:
*  -------------------
*  1) In this line of code we "enforce" the compiler to generate an "instance" from our template "blue print" --> this time praticularly with int type.
*  2) In this line of code we also "enforce" the compiler to generate an "instance" from our teamplate "blue print" --> this time for double type.
*  NOTES: 
*  - In both of the cases above, a different function is generated (with the respective type) and then it is being compiled. 
*  - If the main program, praticulary this CPP file, did not contain ANY call to the templated function, then NO "instace" of the function would have been generated + compiled. 
*
*
*/
// ======================================================================================================================================================================================

#include "functionTemplateExample.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	
	int a = 7;
	int b = 19;
	cout << "main - BEFORE calling foo, a and b are:<" << a << ", " << b << ">" << endl; 
	// 1) 
	mySwap(a, b);
	cout << "main - AFTER calling foo, a and b are:<" << a << ", " << b << ">" << endl; 

	double c = 7.6;
	double d = 88.7;
	cout << "main - BEFORE calling foo, c and d are:<" << c << ", " << d << ">" << endl; 
	// 2) 
	mySwap(c, d);
	cout << "main - AFTER calling foo, c and d are:<" << c << ", " << d << ">" << endl; 

	// 3) 
	A a1(3);
	A a2(4);
	cout << "main -	myComapre(a2(4), a1(3)) returned:" << std::boolalpha << myComapre(a2, a1) << endl;
 
	cout << "\n \n main - end" << endl;
	return 0;
}
