// =============================================================================================================================================================
/*
* item 8:
* ------
* The differences between new operator and operator new.
* 
* 1) When we create a new object (on the heap) using the mentioned statment (new operator), what actually happens "under the hood" is two actions:
* a) The new operator allocates "raw memory" in a size that is suffiecnt to hold the allocated object.
* b) The new operator calls the (respective) ctor of the object, WITH the allocated memory from the previous step.
* --> This operator is a BUILT-IN operator of the langudge -- it CAN NOT be modified !!
* 
* 2) The second "function" in this context is the operator new, which is inherintly part of every user defined object (class function).
*    The ONLY task of this function (operator) is to allocate (enough) memory to hold the object in memory. This function CAN be override/overload. 
* a) In case we would have want to add a different "allocation logic" than the "simple" malloc, this function is the place to put it into.
* 
* 3) There are cases (not common) that we DO wish to call the ctor on our own, provided the memory in which the object we are about to create will 
*    reside in - it is very common in cases of shared memory situations.
* a) For this purpose we have a specific "flavour" of the operator new --> placement new. In this flavour, we are ALREADY GIVEN the memory location
*    that will hold the object that is about to be created, THUS, the only thing we have left to do is to invoke "on" this location the (desired) ctor 
*    of the object.
*    NOTE: Other than the buffer in which the object will be created, this fucntion ALSO MUST get all the neccessary arguments for the object.
*
* 4) Each call to operator new MUST have its corresponding call to delete operator. Similarly to the way operator new works, delete operator does the 
*    opposite actions in the following order:
* a) The delete operator calls the object's destructor.
* b) The delete operator de-allocates the memory that was used by this object and was allocated by new operator!!
*
* 5) Similarly to the case where we used operator new instead of the new operator, we need to call operator delete on the pointer that holds the 
*    data (object) that was allocated via the operator new.
* a) Note that it DOES NOT matter whether we invoke the operator delete on the pointer that holds the object OR on the pointer points to the "buffer"
*    that was passed to the operator new.
*
* 6) When "combining" the usage of operator new with operator delete, we are basically performing memory managment like malloc & free works.
* a) Note that, the same as malloc works, the memory that was allocated via operator new, IS NOT initialized to a certain value --> it might contain garbage 
*    values.
*
*/
// ================================================================================================================================================================

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// NOTE: the order of the includes that FOLLOWS this define is important
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include <stdlib.h>  
#ifdef _WIN32
	#define _CRTDBG_MAP_ALLOC  
	#include <crtdbg.h> 
#endif

#include <iostream>

using namespace std;

class B
{
	public:
	B(int a) 
		: m_a(a)
	{
		cout << "B::B - setting m_a to:" << m_a << " this address is:" << this << endl;
	}
	
	virtual ~B()
	{
		cout << "B::~B - this address is:" << this << endl;
	}
	
	void* operator new(size_t size) // 2)
	{
		cout << "B::operator new - got size of:" << size << endl;
		void* ret = malloc(sizeof(char) * size);
		if (ret != NULL)
		{
			cout << "B::operator new - allocated address:" << ret << endl;
			return ret;
		}
		else
		{
			cerr << "B::operator new - malloc was NOT able to allocate memory, returning NULL pointer" << endl;
			return NULL;
		}
	}

	int m_a;
};

B* CreateObjectInBuffer(void* buff, int a)
{
	cout << "CreateObjectInBuffer - got buff in address:" << buff << endl;
	return ::new (buff) B(a); // 3) placement new usage
}

void operatorNewAndOperatorDeleteCombined()
{
	cout << "operatorNewAndOperatorDeleteCombined - start" << endl;
	const size_t size = 10;
	
	// 6a)  
	char* buff = static_cast<char*>(operator new (sizeof(char) * size));
	cout << "operatorNewAndOperatorDeleteCombined - after allocating " << size << " bytes using operator new, their initial value is:" << endl;
	for (size_t i = 0; i < size; ++i)
	{
		cout << buff[i] << " ";
	}

	// 6b) 
	operator delete (static_cast<void*>(buff));
}

void item8Usage()
{
	cout << "item8Usage - start" << endl;

	// 1)
	B* pb1 = new B(17);
	
	cout << "item8Usage - about to create obejct using placement new, first lets allocate memory for a B object using malloc" << endl;
	void* p = malloc(sizeof(B));
	cout << "item8Usage - allocated memory in address:" << p << endl;
	B* pb2 = CreateObjectInBuffer(p, 8);

	// 4) delete the B object pb1 points to (was created "normally" using the new operator)
	delete pb1;

	// 5) INTENTIOALLY DO NOT delete the other B object that pb2 points to (was allocated using placement new).
	// This will generate a memory leak 
	delete p; // OR delete pb2;

	operatorNewAndOperatorDeleteCombined();
	
	cout << "\n \n item8Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item8Usage();
	
	
	cout << "main - please enter any key to terminate..." << endl;
	char c;
	cin >> c;
	cout << "\n \n main - end" << endl;
	#ifdef _WIN32
		_CrtDumpMemoryLeaks();
	#endif
	return 0;
}
