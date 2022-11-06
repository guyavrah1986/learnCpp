#include <iostream>

#include "accessClassMembersChainedInheritence.h"
#include "A.h"
#include "B.h"
#include "C.h"

using namespace std;

void accessClassMembersChainedInheritence()
{
	string funcName = "accessClassMembersChainedInheritence - ";
	cout << funcName + "start" << endl;
	cout << funcName + "the sizeof(long) is:" << sizeof(long) << endl;
	C c1(17, 15, -1, 'a', 12);
	cout << funcName + "the sizeof(c1) is:" << sizeof(c1) << endl;
	cout << funcName + "the sizeof(void*) is:" << sizeof(void*) << endl;
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
