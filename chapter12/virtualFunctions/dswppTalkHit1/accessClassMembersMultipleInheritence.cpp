#include <iostream>

using namespace std;

#include "accessClassMembersMultipleInheritence.h"
#include "D.h"
#include "E.h"
#include "F.h"

void accessClassMembersMultipleInheritence()
{
	string funcName = "accessClassMembersMultipleInheritence - ";
	D d1(2.4, -19, 5);
	D* pd = &d1;
	E* pe = &d1;
	F* pf = &d1;
	cout << funcName + "the FIRST class member of d1 is at address:" << pd << endl;
	cout << funcName + "the FIRST class member of d1 is ALSO being pointed by the first base class:" << pe << ", and has the value of:" << pe->m_i << endl;
	//cout << funcName + "the FIRST class member of d1 pointed by pf (F*):" << pf->m_i << endl;
}
