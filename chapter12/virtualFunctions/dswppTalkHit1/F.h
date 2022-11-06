#pragma once

struct F
{
	F(const short& s);
	~F();

	short m_s;
}__attribute__ ((__packed__));
