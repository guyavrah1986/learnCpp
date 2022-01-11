// ===================================================================================================================================================================
// ===================================================================================================================================================================
// C++ class layout:
// -----------------
// 1) Each class in C++ can contain class members and class methods.
// 2) The class members are "stored" within the class instance in the EXACT order of their declration within the class.
// 2.1) Memory layout is mostly left to the implementation. The key exception is that member variables for a given access specifier will be in order of their declaration.
//
// References:
// a) https://stackoverflow.com/questions/25377877/first-member-of-class
// b) https://stackoverflow.com/questions/1632600/memory-layout-c-objects
// c) https://stackoverflow.com/questions/32509820/address-of-static-member-in-a-class
// d) https://stackoverflow.com/questions/50763943/using-attribute-packed-for-classes-in-gcc
// e) https://stackoverflow.com/questions/4842056/do-static-members-of-a-class-occupy-memory-if-no-object-of-that-class-is-created
// f) https://stackoverflow.com/questions/648647/in-c-where-in-memory-are-class-functions-put
// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <iostream>

#include "A.h"
#include "B.h"
#include "C.h"

using namespace std;

void accessClassMembers()
{
	string funcName = "accessClassMembers - ";
	cout << funcName + "start" << endl;
	cout << funcName + "the sizeof(int) is:" << sizeof(int) << endl;
	cout << funcName + "the sizeof(char) is:" << sizeof(char) << endl;
	cout << funcName + "the sizeof(short) is:" << sizeof(short) << endl;
	A a1(1, 'a', 12);
	cout << funcName + "the sizeof(a1) is:" << sizeof(a1) << endl;
	A* pa1 = &a1;
	cout << funcName + "the address that pa1 points to is:" << pa1 << endl;
	int* pi = static_cast<int*>(&(pa1->m_i));
	cout << funcName + "the FIRST class member of a1 is at address:" << pa1 << ", which is also pointed by pi:" << pi << ", and has the value:" << (*pi) << endl;
	++pi;
	char* pc = (char*)(pi);
	cout << funcName + "the SECOND class member of a1 is at address:" << (void*)pc << ", and has the value:" << (*pc) << endl;
	++pc;
	short* ps = (short*)(pc);
	cout << funcName + "the THIRD class member of a1 is at address:" << ps << ", and has the value:" << (*ps) << endl;
	cout << funcName + "end" << endl;
}


void accessSingleInheritenceClassMembers()
{
	string funcName = "accessSingleInheritenceClassMembers - ";
	cout << funcName + "start" << endl;
	cout << funcName + "the sizeof(unsigned int) is:" << sizeof(unsigned int) << endl;
	B b1(15, -1, 'a', 12);
	cout << funcName + "the sizeof(b1) is:" << sizeof(b1) << endl;
	A* pa1 = &b1;
	B* pb1 = &b1;
	cout << funcName + "the address that pa1 points to is:" << pa1 << endl;
	cout << funcName + "the address that pb1 points to is:" << pb1 << endl;
	int* pi = static_cast<int*>(&(pa1->m_i));
	cout << funcName + "the FIRST class member of b1 (actually of A's part) is at address:" << pa1 << ", which is also pointed by pi:" << pi << ", and has the value:" << (*pi) << endl;
	++pi;
	char* pc = (char*)(pi);
	cout << funcName + "the SECOND class member of b1 (actually of A's part) is at address:" << (void*)pc << ", and has the value:" << (*pc) << endl;
	++pc;
	short* ps = (short*)(pc);
	cout << funcName + "the THIRD class member of b1 (actually of A's part) is at address:" << ps << ", and has the value:" << (*ps) << endl;
	++ps;
	unsigned int* pui = (unsigned int*)(ps);
	cout << funcName + "the FOURTH class member of b1 is at address:" << pui << ", and has the value:" << (*pui) << endl;
	cout << funcName + "end" << endl;
}

void accessChainedInheritenceClassMembers()
{
	string funcName = "accessChainedInheritenceClassMembers - ";
	cout << funcName + "start" << endl;
	cout << funcName + "the sizeof(long) is:" << sizeof(long) << endl;
	C c1(17, 15, -1, 'a', 12);
	cout << funcName + "the sizeof(c1) is:" << sizeof(c1) << endl;
	A* pa1 = &c1;
	B* pb1 = &c1;
	C* pc1 = &c1;
	cout << funcName + "the address that pa1 points to is:" << pa1 << endl;
	cout << funcName + "the address that pb1 points to is:" << pb1 << endl;
	cout << funcName + "the address that pc1 points to is:" << pc1 << endl;
	int* pi = static_cast<int*>(&(pa1->m_i));
	cout << funcName + "the FIRST class member of C1 (actually of A's part) is at address:" << pa1 << ", which is also pointed by pi:" << pi << ", and has the value:" << (*pi) << endl;
	++pi;
	char* pc = (char*)(pi);
	cout << funcName + "the SECOND class member of c1 (actually of A's part) is at address:" << (void*)pc << ", and has the value:" << (*pc) << endl;
	++pc;
	short* ps = (short*)(pc);
	cout << funcName + "the THIRD class member of c1 (actually of A's part) is at address:" << ps << ", and has the value:" << (*ps) << endl;
	++ps;
	unsigned int* pui = (unsigned int*)(ps);
	cout << funcName + "the FOURTH class member of c1 (actually of B's part) is at address:" << pui << ", and has the value:" << (*pui) << endl;
	++pui;
	long* pl = (long*)(pui);
	cout << funcName + "the FIFTH class member of c1 is at address:" << pl << ", and has the value:" << (*pl) << endl;
	cout << funcName + "end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	//accessClassMembers();
	//accessSingleInheritenceClassMembers();
	accessChainedInheritenceClassMembers();
	cout << "main - end" << endl;
	return 0;
}
