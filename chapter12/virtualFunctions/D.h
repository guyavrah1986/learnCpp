#pragma once

#include "E.h"
#include "F.h"

struct  D : E, F
{
	D(const float& f, const int& i, const short& s);
	~D();

	float m_f;
}__attribute__ ((__packed__));
