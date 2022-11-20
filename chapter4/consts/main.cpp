// ================================================================================================================================================
// ================================================================================================================================================
// Chapter 4 - const:
// ------------------
// 1) C++ introduces the concept (and keyword) of const. This enables us to define variables that will NOT change thier values.
//    Const variable MUST be assgined in its declaration.
//    and use them both.
// 2) 
// 3) 
// =================================================================================================================================================
// =================================================================================================================================================

#include <iostream>

using namespace std;

void constInitialization()
{
	string funcName = "constInitialization - ";
	cout << funcName + "start" << endl;
	const int x {5};

	/*
	const short s;
	s = 4;	// won't compile
	*/
	int input;

	cout << funcName + "please enter a number:" << endl;
	cin >> input;
	const int y = input;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	constInitialization();
	cout << "main - end" << endl;
	return 0;
}
