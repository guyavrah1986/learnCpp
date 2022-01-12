#include <iostream>

#include "accessVirtualFunction.h"
#include "Derived.h"

using namespace std;

void accessVirtualFunction()
{
	cout << "accessVirtualFunction - start" << endl;
	Derived d;
	d.f1();
	Base* bp = &d;
	bp->f1();
}
