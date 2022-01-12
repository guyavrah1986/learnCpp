#include <iostream>

#include "Base.h"

using namespace std;

Base::Base()
{
	cout << "Base::Base" << endl;
}

Base::~Base()
{
	cout << "Base::~Base" << endl;
}

void Base::f1()
{
	cout << "Base::f1" << endl;
}
