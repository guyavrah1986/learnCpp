#include <iostream>

#include "A.h"
#include "B.h"

using namespace std;

void accessClassMembersSingleInheritence()
{
	string funcName = "accessClassMembersSingleInheritence - ";
	cout << funcName + "start" << endl;
	cout << funcName + "the sizeof(int) is:" << sizeof(int) << endl;
	cout << funcName + "the sizeof(char) is:" << sizeof(char) << endl;
	cout << funcName + "the sizeof(short) is:" << sizeof(short) << endl;
	A a1(1, 'a', 12);
	cout << funcName + "the sizeof(a1) is:" << sizeof(a1) << endl;
	A* pa1 = &a1;
	B* pb1 = static_cast<B*>(&a1);
	cout << funcName + "the address that pa1 points to is:" << pa1 << endl;
	int* pi = static_cast<int*>(&(pa1->m_i));
	cout << funcName + "the FIRST class member of a1 is at address:" << pa1 << ", which is also pointed by pi:" << pi << ", and has the value:" << (*pi) << endl;
	pi = static_cast<int*>(&(pb1->m_i));
	cout << funcName + "the FIRST class member of a1 accessed via B pointer is at address:" << pi << ", and has the value:" << (*pi) << endl;
	++pi;
	char* pc = (char*)(pi);
	cout << funcName + "the SECOND class member of a1 is at address:" << (void*)pc << ", and has the value:" << (*pc) << endl;
	++pc;
	short* ps = (short*)(pc);
	cout << funcName + "the THIRD class member of a1 is at address:" << ps << ", and has the value:" << (*ps) << endl;
	cout << funcName + "end" << endl;
}
