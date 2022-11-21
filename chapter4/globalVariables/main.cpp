// ================================================================================================================================================
// ================================================================================================================================================
// Chapter 4 - global linkage (variables):
// ---------------------------------------
// 1) C++ (and C) has the ability to "share" variables accros files of the same program (project). In order to do so, we need to declare a variable
//    in some "centralized" point "out side" of any function (see in the file globals.cpp).
//    In all other files within the project (i.e.- NOT where the global variable is defined, like in this file) we need to "decalre" it using 
//    the "extern" keyword - like telling to the compiler:"Someone else in another place defined it, its all good..."
// 2) A forward declration is required for functions as well when we DO NOT include the header file in which they are defined in (in this case
//    the function fooInGlobalFile is defined in another cpp file and NOT in a header file, so we MUST forward-decalre it).
///   NOTE:In the more "common case" where we DO include the header file in which the function is declared, then we DO NOT need to (also) forward-
//    declare the function cause, unless specified otherwise, every function automatically has the "extern" modifier in her defenition (one can 
//    think of it that in this manner the function is defined as "public" function, where if it was defined with the static modifer it was 
//    considered as a private method, that can be accessed ONLY within the file it was defined in).
// 3) In case a static modifer is applied to a global variable - it automatically limits the scope of the variable to the file where the variable
//    is declared in. In other files, forward declrations of this variable will COMPILE, yet when it will be accessed, a LINKER error will rise.
// 4) Functions are by default defined "with" the extern modifier. So in order to "enclose" them to a specific file, same goes here with the usage
//    of the static keyword.
// 5) In order to make global consts defined ONLY once, regardless of the number of times the header file in which they reside in is included,
//    we can define them as constants who are extern in a unique namespace and declare them within a single cpp file. This ensures that:
//    a) No matter how many files include's them, they will be defined only once.
//    b) Each time we modify one (or more) of these variables we need to compile ONLY the cpp file where they are defined, and NOT EVERY file that
//       includes their header file as well (which can slow down dramatically the compilation proccess).
// =================================================================================================================================================
// =================================================================================================================================================

#include <iostream>

#include "constants.h"

using namespace std;

// 1) forward declration for the global variable which was defined in another "place"
extern int g_x;

//2) forward declration for the "global" function which was defined in another "place"
void fooInGlobalFile();

// 3)
extern int g_y;

// 4)
void fooStatic();

void foo()
{
	cout << "foo - g_x is:" << g_x << endl;	
	//cout << "foo - g_y is:" << g_y << endl;	// 3) This line will cause a LINKER error
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	foo();
	int g_x = 8;
	cout << "main - g_x is:" << g_x << endl;

	fooInGlobalFile();

	// fooStatic();	// 4)

	cout << "main - rotem is:" << Constants::rotem << endl;
	cout << "main - end" << endl;
	return 0;
}
