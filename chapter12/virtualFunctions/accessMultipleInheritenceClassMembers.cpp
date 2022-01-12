#include <iostream>

using namespace std;

#include "accessMultipleInheritenceClassMembers.h"
#include "D.h"
#include "E.h"
#include "F.h"

void accessMultipleInheritenceClassMembers()
{
	string funcName = "accessMultipleInheritenceClassMembers - ";
	D d1(2.4, -19, 5);
	D* pd = &d1;
	E* pe = static_cast<E*>(&d1);
	F* pf = static_cast<F*>(&d1);
	cout << funcName + "the FIRST class member of d1 is at address:" << pd << endl;
	cout << funcName +  "the FIRST class member of d1 is ALSO being pointed by the first base class:" << pe << ", and has the value of:" << pe->m_i << endl;
}
