#include <iostream>

#include "E.h"

using namespace std;

E::E(const int& i) : m_i(i)
{
	cout << "E::E - setting m_i to:" << m_i << endl;
}

E::~E()
{
	cout << "E::~E" << endl;
}
