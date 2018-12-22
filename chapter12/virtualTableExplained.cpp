// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 
// Class members location upon multiple inheritance:
// -------------------------------------------------
// 1) When a derived class inherites from two (or more) "base" classes, the layout of all her members (hers + the inherited ones) are according to the order of the 
//    inheritence:
//    # Base1's members
//    # Base2's members
//    # Derived's members
// 2) The address of the "this" pointer of the Derived class is the same as the address of the first member of her -- which is the first member of the "first"
//    base class.
// 
// virtual table under the hood:
// -----------------------------
// Some notes about virtual functions and virtual tables:
// 1) A virtual table is created ONCE for each class. It is located (implementation specific) somewhere (probably) in the BSS segment (all the data
//    which is relevant for constructing the virtual table is known at compile time so it could be placed there).It is static. 
// 2) For a specific object - once it has AT LEAST one virtual function --> it will have (contain) also an additional "virtual pointer".
//    The objective of this pointer is to point to the virtual table.Its location will be (usually) at the first 4/8 bytes of the object (32/64 bit).
// 3) Virtual table is basically a structure that holds all the function pointers to all the VIRTUAL functions of an object. Note: It DOES NOT hold the 
//    pointers to non-virtual functions.
// 4) In the case of multiple inheritence, the derived class will inherite all it's base class(es) virtual pointer, thus increasing its size respectevly. 
//    Note that there will be no need for an additional virtual pointer "specifically" for the derived object (so in the example below - only two virtual pointers
//    will be added to the derived class). 
//    The layout will be as follows: (for the case below fo class Derived : public Base1, public Base2):
//    NOTES: 
//    - We assume "theoretically" there is no padding.
//    - Size of int and pointer is 4 bytes.
// 
//    bytes |           data
//    ---------------------------------  
//    0-3   |  vptr for Base1 v-table.
//    4-7   |  Base1 member (int)
//    8-11  |  vptr for Base2 v-table.
//    12-15 |  Base2 member (int)
//    16-19 |  Derived member (int)
//
//  5) The "extra" code that does the initialization of the v-table for each class in inserted by the compiler (for each ctor) right after the class's base class 
//     is done (in case there is one) and just before the body of the ctor is executed.
//     --> Due to this fact, calling a virtual function within a ctor, will invoke the current "most derived version" and NOT the absoulute most derived version 
//     ( as we wish...). 
//  
//  6) Some impacts of using v-table:
//     a) Calling a virtual function costs us in an extra read of the address of the actual function to be invoked during run-time (not so bad).
//        The exact arithmetic being done is pointer read + offset manipulation. 
//     b) Virtual functions CAN NOT be inline !!
//     
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================


#include <iostream>
using namespace std;

static void print_object(const char *name, void *this_, size_t size)
{
	void** tmp = reinterpret_cast<void**>(this_);
	size_t i;
	printf("created %s at address %p of size %zu\n", name, this_, size);
	for(i = 0 ; i < size / sizeof(void*) ; ++i)
	{
		printf("  pointer[%zu] == %p\n", i, tmp[i]);
	}
}

class Base1
{
public:
	Base1() : m_base1(17)
	{
		cout << "Base1::Base1 - setting m_base1 to:" << m_base1 << " this is at:" << this << " m_base1 is at:" << &m_base1 << endl;
		print_object(__FUNCTION__, this, sizeof(*this));
		
	}

	virtual ~Base1()
	{
		cout << "Base1::~Base1" << endl;
	}
	
	virtual void func1()
	{
		cout << "Base1::func1 - m_base1 is:" << m_base1 << endl;
	}
	
	int m_base1;
};

class Base2
{
public:
	Base2() : m_base2(15)
	{
		cout << "Base2::Base2 - setting m_base2 to:" << m_base2 << " this is at:" << this << " m_base2 is at:" << &m_base2 << endl;
		print_object(__FUNCTION__, this, sizeof(*this));
	}

	virtual ~Base2()
	{
		cout << "Base2::~Base2" << endl;
	}

	virtual void func2()
	{
		cout << "Base2::func2 - m_base2 is:" << m_base2 << endl;
	}
	
	int m_base2;
};

class Derived : public Base1 , public Base2
{
public:
	Derived() : m_derived(12)
	{
		cout << "Derived::Derived - setting m_derived to:" << m_derived << " this is at:" << this << " m_derived is at:" << &m_derived<< endl;
		print_object(__FUNCTION__, this, sizeof(*this));
	}

	virtual ~Derived()
	{
		cout << "Derived::~Derived" << endl;
	}

	virtual void func1()
	{
		cout << "Derived::func1 - m_derived is:" << m_derived << endl;
	}
	
	int m_derived;
};

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main program:
// ===================================================================================================================================================================
// ===================================================================================================================================================================

void example1()
{
	/*
	Base1* b1 = new Base1;
	Base2* b2 = new Base2;

	{
		void (Base1::*mfp)() = &Base1::func1;
		printf("virtualTableExplained - address of Base1::func1 is: %p \n", (void*)(b1->*mfp));
	}

	{
		void (Base2::*mfp)() = &Base2::func2;
		printf("virtualTableExplained - address of Base2::func2 is: %p \n", (void*)(b2->*mfp));
	}
	*/
	Derived* d = new Derived;
	{
		//void (Derived::*mfp)() = &Derived::func1;
		//printf("virtualTableExplained - address of Derived::func1 is: %p \n", (void*)(d->*mfp));
	}


	//delete b1;
	//delete b2;
	delete d;
}

int main(int argc, char** argv)
{
	cout << "virtualTableExplained - start " << endl;
	cout << "virtualTableExplained - sizeof(int) is:" << sizeof(int) << " bytes " << endl;
	cout << "virtualTableExplained - creating Derived object on the heap" << endl;
	Derived* d = new Derived;

	cout << "virtualTableExplained - calling d->func1()" << endl;
	d->func1();
	cout << "virtualTableExplained - deleting the Derived object" << endl;
	delete (d);
	cout << "virtualTableExplained - end" << endl;
	return 0;
}


