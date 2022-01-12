#include <iostream>

#include "Derived.h"

using namespace std;

Derived::Derived()
{
	cout << "Derived::Derived" << endl;
}


Derived::~Derived()
{
	cout << "Derived::~Derived" << endl;
}

void Derived::f1()
{
	cout << "Derived::f1" << endl;
}
