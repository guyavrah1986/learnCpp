// ========================================================================================================================================================================
/*
* Temporaries:
* ------------
* The "formal" definition of when temporary objects are created is when:A non heap object is created AND it is not named.
* Practiaclly it happens in two main cases:
* a) An implict conversion is made in a function call to make the passed argument being valid argument.
* # By passing an object by value.
* # When passing an object by non const reference - a good example will be the conversion of char arr[] into a string object (see example in the book).
* 
* b) When a function returns an object by value.
* This is relevant almost in all cases, there are some exceptions though (the Return Value Optimization aka RVO is one of them).
*
*/
// ======================================================================================================================================================================

#include <iostream>
#include <string>

using namespace std;

class B
{
	public:
	B(const string& str) : m_str(str)
	{
		cout << "B::B - setting m_str to:" << m_str << endl;
	}

	~B()
	{
		cout << "B::~B" << endl;
	}

	B(const B& other) : B(other.m_str)
	{
		cout << "B::B(copy)" << endl;
	}

	string m_str;
};

class A
{
	public:
	A(int a, const string& str) : m_a(a), b(str)
	{
		cout << "A::A - setting m_a to:" << m_a << " and b.m_str to:" << b.m_str << endl;
	}

	virtual ~A()
	{
		cout << "A::~A" << endl;
	}

	A(const A& other) : A(other.m_a, other.b.m_str) 
	{
		cout << "A::A(copy)" << endl;
	}

	B GetInnerObjByValue() const 
	{
		cout << "A::GetInnerObjByValue()" << endl;
		return b;
	}

	const B& GetInnerObjByConstRef() const
	{
		cout << "A::GetInnerObjByConstRef" << endl;
		return b;	
	}  

	int m_a;
	B b;
};


void passArgByConstRef(const A& arg)
{
	cout << "passArgByConstRef - address of recived argument is:" << &arg << endl;
}

void passArgByNonConstRef(A& arg)
{
	cout << "passArgByNonConstRef - address of recived argument is:" << &arg << endl;
}

void passArgByValue(A arg)
{
	cout << "passArgByNonConstRef - address of recived argument is:" << &arg << endl;
}

void item19Usage()
{
	cout << "item19Usage - start" << endl;

	const string str("calbas");
	A obj(17, str);
	cout << "item19Usage - creating an object on the stack with address of:" << &obj << endl;

	cout << "item19Usage - calling passArgByConstRef" << endl;
	passArgByConstRef(obj);	// no temp is created !!

	cout << "item19Usage - calling passArgByNonConstRef" << endl;
	passArgByNonConstRef(obj);

	cout << "item19Usage - calling passArgByValue" << endl;
	passArgByValue(obj);	// a temp object is created and destroyed once the function returns !!

	const B& refb1 = obj.GetInnerObjByValue();

	const B& refb2 = obj.GetInnerObjByConstRef();
	cout << "\n \n item19Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item19Usage();
	
	cout << "\n \n main - end" << endl;
	return 0;
}

