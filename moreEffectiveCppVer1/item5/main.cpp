//=============================================================================================================================================
/*
*  Item 5: Be wary of user-defined conversion functions
*  -----------------------------------------------------
*  1) Implict conversion happens in C++ (as they originate from C) and in most (all) cases, the user does not have anything to do "against that"
*  (it is not always something negative). For example, you can pass a char to a function that recives int, or short to a function that recives
*  a double. You can't do anything about such conversions, because they're hard-coded into the language. When you add your own types, however,
*    you have more control, because you can choose whether to provide the functions compilers are allowed to use for implicit type conversions.
* 
*  2) There are two types of function that "allows" compilers to perfrom implict conversion.
*  a) Single argument ctor (or multiple arguments where the second argument and on are defualt).
*/
// =============================================================================================================================================
#include <iostream>
#include <string>

using namespace std;

class MyObj1
{
	public:
		MyObj1(int num) : m_num(num) // 2a)
		{
			cout << "MyObj1::MyObj1 - set m_num to:" << m_num << endl;
		}

	int m_num;
}


class MyObj2
{
	public:
		MyObj2(int num, int num2 = 17) : m_num(num), m_num2(num2)  // 2a) 
		{
			cout << "MyObj2::MyObj2 - set m_num to:" << m_num << " and m_num2 to:" << m_num2 << endl;
		}

	int m_num;
	int m_num2;
}

void funcThatGetsDouble(const double& d)
{
	string funcName = "funcThatGetsDouble - ";
	cout << funcName + "got:" << d << endl;
}

void item5Usage()
{
	string funcName = "item5Usage - ";
	cout << funcName + "start" << endl;
	short s = 12; // 1) 
	funcThatGetsDouble(s);
	cout << funcName + "end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item5Usage();
	cout << "\n \n main - end" << endl;
	return 0;
}


