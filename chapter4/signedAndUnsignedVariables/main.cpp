// ============================================================================================================================================
/* This example follows the Learn Cpp chapter 4:
*  ---------------------------------------------
*  1. When unsigned variables are assgined with values greater than thier maximum capacity, the actual value that is assgined to them is 
*     the VAL % MAX_VAL.
*  2. When performing arithmetics operations on two integers, it is mostly prefered that these two variables will be signed and NOT unsigned
*     variables.  
*
*/
// ============================================================================================================================================

#include <iostream>

using namespace std;

void arithmeticOperationsOnSignedAndUnsigned()
{
	const string funcName = "arithmeticOperationsOnSignedAndUnsigned - ";
	char a {3};
	char b {5};
	
	cout << funcName + "when performing substruction of two SIGNED variables in which the first is SMALLER" << endl;
	cout << funcName + "substructing a=" << +a << " from b=" << +b << " in which they are both SIGNED results in:" << +(a - b) << endl;
	unsigned int c {3};
	unsigned int d {5};
	cout << funcName + "when performing substruction of two UNSIGNED variables in which the first is SMALLER" << endl;
	cout << funcName + "substructing c=" << c << " from d=" << d << " in which they are both UNSIGNED results in:" << (c - d) << endl; //2)
}

void assginMoreThanMaxVal()
{
	const string funcName = "assginMoreThanMaxVal - ";
	unsigned char uc {17};
	cout << funcName + "uc is:" << +uc << endl;
	uc = 255; // max value that can be stored in 8 bits
	cout <<  funcName + "uc is now:" << +uc << endl;
	unsigned char addToUc = 3;
	uc += addToUc;
	cout << funcName + "after adding " << + addToUc << " to uc it is now:" << +uc << endl; //1)
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	assginMoreThanMaxVal();
	arithmeticOperationsOnSignedAndUnsigned();
	cout << "main - end" << endl;
}

