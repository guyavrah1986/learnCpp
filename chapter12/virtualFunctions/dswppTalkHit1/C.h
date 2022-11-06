#pragma once

#include "A.h"
#include "B.h"

struct C : public B
{
	C(const long& l, const unsigned int& ui, const int& i, const char& c, const short s);
	~C();

	long m_l;
}__attribute__ ((__packed__));
