// =============================================================================================================================================================
/*
* item 4:
* ------
* C++ compilers automatically creates several functions to any user defined class. One of them is the default constructor. 
*
* 1) First, let us see some "issues" we might suffer in case we DON'T have a default constructor in our class. 
*    NOTE: We will end up WITHOUT a default ctor in our class if we implement by our own AT LEAST one ctor, and we DO NOT add the default ctor by our own.
* a) In this case, we can see that it is impossible to declare (create) a "stack-Base1d" array of objects with no default Ctor.
* b) The same goes when the araay is created on the heap.
* 
* 2) Second, it is worth mentionng that most (maybe all) of the STL containers DOES NOT require to have a default ctor --> so in these cases
*    there won't be any problem. Note, anyhow, that they do require that the objects that contained within them are copy-constructable
*    and assginmentable.
*
* 3) Third, a case worth mention is with base classes. In case a base class, say, in a long "inheritence chain" DOES NOT have a default ctor,
*    it implies that ALL derived classes will supply the base class values for its (the base's class) members (assuming there are). That is not such a 
*    "good constranit" to imply on the developers of a derived class (cause usually they do not care NOR wish to care about these members).
* a) In this case the base class DOES have a default ctor, so no "need" to know (send) arguemnts from the derived class ctor to the base class ctor.
* b) In this case the base class DOES NOT have a default ctor, then the derived class MUST provide ALL arguemnts to the NON default ctor in its ctor. 
*
* 4) Template issues: When an object does that lacks a default ctor is ineligible for use with many template-based container classes
*/
// ================================================================================================================================================================
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Base1
{
	public:
	Base1(int a) 
		: m_a(a)
	{
		cout << "Base1::Base1 - setting m_a to:" << m_a << " this address is:" << this << endl;
	}
	
	virtual ~Base1()
	{
		cout << "Base1::~Base1 - this address is:" << this << endl;
	}

	int m_a;
};

class Base2
{
	public:
	Base2(int b) 
		: m_b(b)
	{
		cout << "Base2::Base2 - setting m_b to:" << m_b << " this address is:" << this << endl;
	}
	
	Base2()
		: m_b(17)
	{
		cout << "Base2::Base2(default) - setting m_b to:" << m_b << endl;	
	}
	
	virtual ~Base2()
	{
		cout << "Base2::~Base2 - this address is:" << this << endl;
	}

	int m_b;
};

class Base3
{
	public:
	Base3(int a) 
		: m_a(a)
	{
		cout << "Base3::Base3 - setting m_a to:" << m_a << endl;
	}

	Base3()
		: m_a(12)
	{
		cout << "Base3::Base3(default) - setting m_a to:" << m_a << endl;
	}
	
	virtual ~Base3()
	{
		cout << "Base3::~Base3" << endl;
	}

	int m_a;
};

class Derived3 : public Base3
{
	public:
	Derived3(int b)
	{
		cout << "Derived3::Derived3 - setting m_b to:" << m_b << endl;
	}

	virtual ~Derived3()
	{
		cout << "Derived3::~Derived3" << endl;
	}
			
	int m_b;
};

class Base4
{
	public:
	Base4(int a) 
		: m_a(a)
	{
		cout << "Base4::Base4 - setting m_a to:" << m_a << endl;
	}

	virtual ~Base4()
	{
		cout << "Base4::~Base4" << endl;
	}

	int m_a;
};

class Derived4 : public Base4
{
	public:
	Derived4(int b) : Base4(4) // 3b) hard coded value for Base4 argument
		, m_b(b)
	{
		cout << "Derived4::Derived4 - setting m_b to:" << m_b << endl;
	}

	virtual ~Derived4()
	{
		cout << "Derived4::~Derived4" << endl;
	}
			
	int m_b;
};

void noDefaultCtorIssueWithArraysInitializationExample()
{
	cout << "noDefaultCtorIssueWithArraysInitializationExample - start" << endl;

	const size_t size = 3;
	// 1a) Won't compile cause we defined (at least) one ctor in our class
	// which causes the default ctor of the compiler NOT to be generated, so 
	// declaring "stack-based" array of this kind of object is not possible.
	// Base1 arr [size];

	// 1b) This also won't work
	// Base1* bp = new Base1 [size]; 
	
	// 2) No probelem - STL containers has the copy-constructable and 
	//    assginmenable --> so this code will work.
	map<Base1, int> m;
	vector<Base1> vec1;
	
	cout << "noDefaultCtorIssueWithArraysInitializationExample - end" << endl;
}

void noDefaultCtorInBaseClassExample()
{
	cout << "noDefaultCtorInBaseClassExample - start" << endl;
	
	// 3a)
	Derived3(12);
	
	// 3b) 
	Derived4(9);
	
	cout << "\n \n noDefaultCtorInBaseClassExample - end" << endl;
}

void item4Usage()
{
	cout << "item4Usage - start" << endl;

	noDefaultCtorIssueWithArraysInitializationExample();
	noDefaultCtorInBaseClassExample();
	
	cout << "\n \n item4Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item4Usage();
	
	
	cout << "main - please enter any key to terminate..." << endl;
	char c;
	cin >> c;
	cout << "\n \n main - end" << endl;
	return 0;
}
