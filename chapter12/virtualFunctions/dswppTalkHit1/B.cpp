#include <iostream>

#include "B.h"

using namespace std;

B::B(const unsigned int& ui, const int& i, const char& c, const short s) : m_ui(ui), A(i, c, s)
{
	cout << "B::B - setting m_ui to:" << m_ui << endl;
}

B::~B()
{
	cout << "B::~B" << endl;
}
