//=============================================================================================================================================
/*
*  Item 3: Never treat arrays polymorphically
*  ------------------------------------------
*  TL;DR: Polymorphism and pointer's arithmetic don't go along together. 
*  1) When you declare a function that recevices an array of Bsae class, YET you send it an array of Derived class of this Base class, most 
*     likely things WON'T work. This is due to the fact that when an object (treated via pointer or reference) is used from "within" an array,
*     what actually happens there is "simply put" pointer's arithmetic. Meaning, in order to get to arr[i], the compiler needs to generate code
*     that "moves forwards" i*sizeof(object) bytes in the memory. Now, due to the fact that MOST likely the derived class is "bigger" than its
*     Base class, then if the actuall array that was passed was passed with Derived objects, the calculation made by the compiler is "in correct"
*     cause it assumed that the type of the objects in the array is Base, which has a different size than Derived object.
*  2) Same goes when one tries to delete an array of Dervied objects pointed to by Base class object. Behind the sence, the compiler will 
*     generate a loop similar to the one in the first example, this time calling the object's DTOR. The same goes here for the pointer's 
*     arithmetic that will be incorrect.
*/
// =============================================================================================================================================
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

	int m_b;	
};


void passArrAsBaseArray(const Base arr [], size_t size)
{
	cout << "passArrAsBaseArray - got an array of Base with size of:" << size << endl;
	for (size_t i = 0; i < size; ++i)
	{
		// 1) the pointer arithmetic here is: arr[i] = arr + (i * sizeof(Base))
		arr[i].foo();
	}
}

void deleteArrayOfObjectViaBaseClassPointer(Base arr[])
{
	string funcName = "deleteArrayOfObjectViaBaseClassPointer - ";
	cout << funcName + "about to delete an entire array pointed by a Base class pointer" << endl;

	// 2) 
	// delete [] arr; 
	
	// instead, a "dirty overcome"
	if (dynamic_cast<Derived*>(arr) != NULL)
	{
		cout << funcName + "casting succeeded, deleting the array" << endl;
		delete [] static_cast<Derived*>(arr);
	}
}

void item3Usage()
{
	cout << "item3Usage - start" << endl;
	const size_t size = 3;
	Derived* arr = new Derived[size];	

	// call the virtual function of the Derived objects with the "original" array
	cout << "item3Usage - invoking foo function for the original objects array" << endl;
	for (size_t i = 0; i < size; ++i)
	{
		arr[i].foo();
	}

	passArrAsBaseArray(arr, size);

	deleteArrayOfObjectViaBaseClassPointer(arr);
	cout << "\n \n item3Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item3Usage();
	cout << "\n \n main - end" << endl;
	return 0;
}
