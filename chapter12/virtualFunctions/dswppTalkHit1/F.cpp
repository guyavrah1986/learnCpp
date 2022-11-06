#include <iostream>

#include "F.h"

using namespace std;

F::F(const short& s) : m_s(s)
{
	cout << "F::F - setting m_s to:" << m_s << endl;
}

F::~F()
{
	cout << "F::~F" << endl;
}
