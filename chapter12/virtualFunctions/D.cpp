#include <iostream>

#include "D.h"

using namespace std;

D::D(const float& f, const int& i, const short& s) : m_f(f), E(i), F(s)
{
	cout << "D::D - setting m_f to:" << m_f << endl;
}

D::~D()
{
	cout << "D::~D" << endl;
}
