// ===================================================================================================================================================================
// ===================================================================================================================================================================
// Virtual functions:
// -----------------
// This file comes to include some more information about the behaviour of the virtual functions mechanism in C++. 
// In this example a "3-levels" inheritence chain will be used to illustrate the way it works.
// 
// 1) Calling a pure virtual function from within a CTOR will most likely cause a compiler/linker error.
// 2) Calling a pure virtual function from some function is OK, cause eventually, the actuall object (at run-time after it was instancisated) that will call the
//    the "encapsulating function" will be called by an object that DOES implement the pure virtual funcntion (otherwise it could not have
//    been instanicated).   
// 3) Whether we call a virtual function via Base class pointer OR reference, automatically we "invoke" the virtual functions mechanism (i.e. - method reolution order).
//    Meaning, if the function that is called, again, via the pointer OR reference is virtual, then the MOST derived version of it will 
//    be (eventually) invoked (dynamic binding).
// 4) In this case it is even "simpler" than the previous case - the most derived flavor of the function will be invoked. 
//    NOTE: A distincation from the previous note is that in this case the reolution of the function to be called is known at compile time
//    which means that it will take less cycels to execute this function (early binding).
// 5) In this case, it is quite stragiht forward - there is no "precesne" of virtual functions what so ever, it is simply a call to a "noraml"
//    class member function.Note however, that the phenomen of "Name hiding" is taking place here, causing the B::Func4() to be invoked and not
//    the A::Func4().
// 6) When calling a non virtual function via a pointer OR reference of any type of class along the inheritence chain - "Name hiding" takes
//    place as well, so the function that will be invoked is the one of the B class.
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <iostream>

using namespace std;

class A
{
public:
	A(int a)
		: m_a(a)
	{
		cout << "A::A" << endl;
		//Func3();	// 1)
		Func2();
		cout << "A::A - set m_a to:" << m_a << ", this:" << this << endl;
	}

	virtual ~A()
	{
		cout << "A::~A" << endl;
		Func2();
		cout << "A::~A - this:" << this << endl;
	}

	virtual void Func1()
	{
		cout << "A::Func1 - this:" << this << endl;
		Func3();	// 2)
	}

	virtual void Func2()
	{
		cout << "A::Func2 - this:" << this << endl;
	}

	virtual void Func3() = 0;
	
	virtual void Func4()
	{
		cout << "A::Func4 - this:" << this << endl;
	}

protected:
	int m_a;
};

class B : public A
{
public:
	B(int a, int b)
		: A(a)
		, m_b(b)
	{
		cout << "B::B" << endl;
		cout << "B::B - set m_b to:" << m_b << ", this:" << this << endl;
	}

	virtual ~B()
	{
		cout << "B::~B" << endl;
		Func2();
		cout << "B::~B - this:" << this << endl;
	}

	virtual void Func1()
	{
		cout << "B::Func1 - this:" << this << endl;
	}

	/*
	virtual void Func2()
	{
		cout << "B::Func2 - this:" << this << endl;
	}
	*/

	virtual void Func3()
	{
		cout << "B::Func3 - this:" << this << endl;
	}
	
	void Func4()
	{
		cout << "B::Func4 - this:" << this << endl;
	}	

protected:
	int m_b;
};

class C : public B
{
public:
		C(int a, int b, int c)
			: B(a,b)
			, m_c(c)
		{
				cout << "C::C - set m_c to:" << m_c << ", this is at:" << this << endl;
		}
			
		virtual ~C()
		{
			cout << "C::~C" << endl;
		}
		
		virtual void Func1()
		{
			cout << "C::Func1 - this:" << this << endl;
		}

		virtual void Func2()
		{
			cout << "C::Func2 - this:" << this << endl;
		}
		
		virtual void Func3()
		{
			cout << "C::Func3 - this:" << this << endl;
		}
		
		/*
		void Func4()
		{
			cout << "C::Func4 - this:" << this << endl;
		}
		*/

		int m_c;
};


// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main program:
// ===================================================================================================================================================================
// ===================================================================================================================================================================

void callVirtualFunctionWithPointerOrReferenceOfBaseClasses()	// 3)
{
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - start" << endl;
	C c(1,2,3);
	A* pa = &c;
	A& ra = c;
	B* pb = &c;
	B& rb = c;
	C* pc = &c;
	C& rc = c;
	
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling all virtual functions via pointer and ref of type A" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pa->Func1()" << endl;
	pa->Func1();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling ra.Func1()" << endl;
	ra.Func1();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pa->Func2()" << endl;
	pa->Func2();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling ra.Func2()" << endl;
	ra.Func2();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pa->Func3()" << endl;
	pa->Func3();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling ra.Func3()" << endl;
	ra.Func3();
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling all virtual functions via pointer and ref of type B" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pb->Func1()" << endl;
	pb->Func1();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rb.Func1()" << endl;
	rb.Func1();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pb->Func2()" << endl;
	pb->Func2();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rb.Func2()" << endl;
	rb.Func2();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pb->Func3()" << endl;
	pb->Func3();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rb.Func3()" << endl;
	rb.Func3();
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling all virtual functions via pointer and ref of type C" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pc->Func1()" << endl;
	pc->Func1();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rc.Func1()" << endl;
	rc.Func1();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pc->Func2()" << endl;
	pc->Func2();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rc.Func2()" << endl;
	rc.Func2();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pc->Func3()" << endl;
	pc->Func3();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rc.Func3()" << endl;
	rc.Func3();
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - end" << endl;
}

void callVirtualFunctionDirectlyViaDerivedObject()	// 4)
{
	cout << "callVirtualFunctionDirectlyViaDerivedObject - start" << endl;
	
	C c(4,5,6);
	cout << "callVirtualFunctionDirectlyViaDerivedObject - calling c.Func1()" << endl;
	c.Func1();
	
	cout << "callVirtualFunctionDirectlyViaDerivedObject - calling c.Func2()" << endl;
	c.Func2();
	
	cout << "callVirtualFunctionDirectlyViaDerivedObject - calling c.Func3()" << endl;
	c.Func3();
	
	cout << "callVirtualFunctionDirectlyViaDerivedObject - end" << endl;
}

void callNonVirtualFunctionDirectlyViaDerivedObject()	// 5)
{
	cout << "callNonVirtualFunctionDirectlyViaDerivedObject - start" << endl;
	C c(7,8,9);
	
	cout << "callNonVirtualFunctionDirectlyViaDerivedObject - calling c.Func4()" << endl;
	c.Func4();
	cout << "callNonVirtualFunctionDirectlyViaDerivedObject - end" << endl;
}

void callNonVirtualFunctionViaPointerOrReference()	// 6)
{
	cout << "callNonVirtualFunctionViaPointerOrReference - start" << endl;
	C c(11,12,13);
	A* pa = &c;
	B* pb = &c;
	C* pc = &c;
	
	cout << "callNonVirtualFunctionViaPointerOrReference - calling pa->Func4()" << endl;
	pa->Func4();
	
	cout << "callNonVirtualFunctionViaPointerOrReference - calling pb->Func4()" << endl;
	pb->Func4();
	
	cout << "callNonVirtualFunctionViaPointerOrReference - calling pc->Func4()" << endl;
	pc->Func4();
	
	cout << "callNonVirtualFunctionViaPointerOrReference - end" << endl;
}


void testFuntion()
{
	C c(1,2,3);
	A* pa = &c;
	A& ra = c;
	B* pb = &c;
	B& rb = c;
	C* pc = &c;
	C& rc = c;

	cout << "testFuntion - calling pa.Func1()" << endl;
	pa->Func1();
	cout << "testFuntion - calling ra.Func1()" << endl;
	ra.Func1();

	cout << "testFuntion - calling pb.Func1()" << endl;
	pb->Func1();
	cout << "testFuntion - calling rb.Func1()" << endl;
	rb.Func1();

	cout << "testFuntion - calling cb.Func1()" << endl;
	pc->Func1();
	cout << "testFuntion - calling rc.Func1()" << endl;
	rc.Func1();

	cout << "testFuntion - calling c.Func1()" << endl;
	c.Func1();
	
	cout << "testFuntion - calling c.Func2()" << endl;
	c.Func2();
	
	cout << "testFuntion - calling c.Func3()" << endl;
	c.Func3();


		
	cout << "testFuntion - calling pa->Func4()" << endl;
	pa->Func4();
	
	cout << "testFuntion - calling pb->Func4()" << endl;
	pb->Func4();
	
	cout << "testFuntion - calling pc->Func4()" << endl;
	pc->Func4();

	cout << "testFuntion - calling c.Func4()" << endl;
	c.Func4();


	
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	/*
	callVirtualFunctionWithPointerOrReferenceOfBaseClasses();
	callVirtualFunctionDirectlyViaDerivedObject();
	callNonVirtualFunctionDirectlyViaDerivedObject();
	callNonVirtualFunctionViaPointerOrReference();
	*/
	testFuntion();
	cout << "main - end" << endl;
	return 0;
}


