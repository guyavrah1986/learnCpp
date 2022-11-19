// ============================================================================================================================================================
// ============================================================================================================================================================
// Chapter 2 - const, constexpr and symbolic const:
// -----------------------------------------------
// 1) C++ has two kinds of constants: literal, and symbolic. Here we’ll talk about consts and symbolic consts.
// 2) Basically, const is a variable that is defined using the const keyword and MUST be initialized upon declration.
// 3) Constant variable can be initialized via other variables, which are NOT neccessarly constants.
// 4) Variables defined as constexpr are constant as well. YET one major difference between them and "normal const" variabels, is that they create
//    a "compile-time" constant always, while using "only" the const keyword, can produce a "run-time" constant - as described in 3:
//    Rule: Any variable that should not change values after initialization and whose initializer is known at compile-time should be declared as constexpr.
//    Rule: Any variable that should not change values after initialization and whose initializer is not known at compile-time should be declared as const.
// 5) Another approach to define contant variables is to use the #define directive. This is a BAD (!!) practice for two reasons:
//    a) #define directive ALWAYS have ONLY ENTIRE file scope,so if another directive with the same name but different value exists - conflicts can rise.
//    b) Any #define directive will NOT show up in the debbuger - which might cause the program to be harder to debug. 
// ============================================================================================================================================================
// ============================================================================================================================================================

#include <iostream>

using namespace std;

// 5b) - This situation will cause a compiler warning such as:"X" redefined (gcc)
void defineDircetive1()
{
	#define X 1
	cout << "defineDircetive1 - X is:" << X << endl;
}

void defineDircetive2()
{
	#define X 2
	cout << "defineDircetive2 - X is:" << X << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	int i = 9;
	const float f1 = 5.0; 
  	//const int i;	// won't compile - MUST be initialized upon definition.	// 2)
	const int j = i;	// 3)

	constexpr int k = 19;	// 4)

	cout << "main - end" << endl;
	return 0;
}
