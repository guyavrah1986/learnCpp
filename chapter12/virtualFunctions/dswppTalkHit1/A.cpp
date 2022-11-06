#include <iostream>

#include "A.h"

using namespace std;

int A::m_staticInt = 17; 

A::A(const int& i, const char& c, const short& s) : m_i(i), m_c(c), m_s(s)
{
	cout << "A::A - setting m_i:" << this->m_i << ", m_c:" << m_c << ", m_s:" << m_s << endl;
}

A::~A()
{
	cout << "A::~A" << endl;
}
