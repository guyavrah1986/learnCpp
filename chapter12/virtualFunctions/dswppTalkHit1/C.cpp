#include <iostream>

#include "C.h"

using namespace std;

C::C(const long& l, const unsigned int& ui, const int& i, const char& c, const short s) : m_l(l), B(ui, i, c, s)
{
	cout << "C::C - setting m_l to:" << m_l << endl;
}

C::~C()
{
	cout << "C::~C" << endl;
}
