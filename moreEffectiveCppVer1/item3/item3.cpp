#include <iostream>

using namespace std;

class Base
{
	public:
	Base(int a) 
		: m_a(a)
	{
		cout << "Base::Base - setting m_a to:" << m_a << " this address is:" << this << endl;
	}
	
	Base() 
		: m_a(12)
	{
		cout << "Base::Base(defualt)" << endl;
	}
	
	virtual ~Base()
	{
		cout << "Base::~Base - this address is:" << this << endl;
	}

	virtual void foo() const 
	{
		cout << "Base::foo" << endl;
	}
	
	int m_a;
};

class Derived : public Base
{
	public:	
	Derived(int a, int b) 
		: Base(a)
		, m_b(b)
	{
		cout << "Derived::Derived - setting m_b:" << m_b << endl;
	}

	Derived()
		: m_b(15)
	{
		cout << "Derived::Derived(defualt)" << endl;
	}

	virtual ~Derived()
	{
		cout << "Derived::~Derived" << endl;
	}
		
	virtual void foo() const 
	{
		cout << "Derived::foo - <m_a,m_b> is:<" << m_a << "," << m_b << ">" << endl;
	}

	// TODO: add an additional member in order that the sizeof(Derived) will be larger than 
	//       the sizeof(Base)
	int m_b;
		
};


void passArrAsBaseArray(const Base arr [], size_t size)
{
	cout << "passArrAsBaseArray - got an array of Base with size of:" << size << endl;
	for (size_t i = 0; i < size; ++i)
	{
		arr[i].foo();
	}
}

void item3Usage()
{
	cout << "item3Usage - start" << endl;
	const size_t size = 3;
	Derived arr[size];	

	// call the virtual function of the Derived objects with the "original" array
	cout << "item3Usage - invoking foo function for the original objects array" << endl;
	for (size_t i = 0; i < size; ++i)
	{
		arr[i].foo();
	}

	passArrAsBaseArray(arr, size);
	cout << "\n \n item3Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item3Usage();
	cout << "\n \n main - end" << endl;
	return 0;
}
