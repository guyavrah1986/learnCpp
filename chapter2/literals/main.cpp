// ================================================================================================================================================
// ================================================================================================================================================
// Chapter 2 - literals:
// ---------------------
// 1) C++ has two kinds of constants: literal, and symbolic. Here we’ll talk about literals.
// 2) Literal constants (usually just called “literals”) are values inserted directly into the code. They are constants because you can’t change
//    their values.
// 3) Just like variables have a type, all literals have a type too. The type of a literal is assumed from the value and format of the 
//    literal itself. By defualt it is as follows:
//    integral		5, 0, -3	int
//    boolean		true, false	bool
//    floating point	3.4, -2.2	double (not float)!
//    char		‘a’		char
//    C-style string	“Hello, world!”	const char[14] 
// 4) String literals are handled very strangely in C++. It’s fine to use string literals to print text with std::cout, but don’t try and assign
//    them to variables or pass them to functions -- it either won’t work, or won’t work like you’d expect.
// 5) In a way, literals are constants that are not explictly defined as consts (meaning, without the usage of the const keyword).
// =================================================================================================================================================
// =================================================================================================================================================

#include <iostream>

using namespace std;

void printLiteralString(const char* str)
{
	cout << "printLiteralString - got string:" << str << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	float f1 = 5.0f; // 5.0 has type float
	float f2 = 4.1;  // 4.1 has type double (!!)


	const char* cStyleString = "This is a C style (literal) string";
	printLiteralString(cStyleString);
	
	cout << "main - end" << endl;
	return 0;
}
