#pragma once

#include "Base.h"

struct Derived : Base
{
	Derived();
	virtual ~Derived();
	virtual void f1();
};
