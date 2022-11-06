#pragma once

#include "A.h"

struct B : A
{
	B(const unsigned int& ui, const int& i, const char& c, const short s);
	~B();

	unsigned int m_ui;
}__attribute__ ((__packed__));
