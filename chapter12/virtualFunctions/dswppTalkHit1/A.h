#pragma once

struct A 
{
	A(const int& i, const char& c, const short& s);
	~A();

	int m_i;
	char m_c;
	short m_s;
	static int m_staticInt;
}__attribute__ ((__packed__));
