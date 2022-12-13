#include<iostream>

using namespace std;


/*
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
*/

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



void example1()
{
	
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

	Derived* d = new Derived;
	{
		//void (Derived::*mfp)() = &Derived::func1;
		//printf("virtualTableExplained - address of Derived::func1 is: %p \n", (void*)(d->*mfp));
	}


	//delete b1;
	//delete b2;
	delete d;
}


