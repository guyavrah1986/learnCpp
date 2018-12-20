// ===================================================================================================================================================================
// ===================================================================================================================================================================
// Aggregation1:
// ------------
// 1) In this example we will illustrate the most basic aggregation using C++98 (i.e.- anything BEFORE C++11). Therfor, in its most "naive" implementation, a simple
//    and straight forward aggregation is basically the parent object holds a pointer to the aggreagted object (class member).
// 2) One important difference in this form, in contrast to composition, is that the parent object (class) is not responsible to the CREATION nor the DESTRUCTION
//    of the aggreagted object. 
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>

using namespace std;

class AggregatedClass
{
public:
	AggregatedClass(int a) : m_a(a)
	{
		cout << "AggregatedClass::AggregatedClass - set m_a:" << m_a << endl;
	}

	void func1()
	{
		cout << "AggregatedClass::func1" << endl;
	}

	~AggregatedClass()
	{
		cout << "AggregatedClass::~AggregatedClass" << endl;
	}

private:
	int m_a;
};


class MyClass
{
public:			
	MyClass(AggregatedClass* obj) 
		: m_aggregatedClass(obj)
	{
		cout << "MyClass::MyClass(AggregatedClass* obj)" << endl;
	}
			
	MyClass() 
		: m_aggregatedClass(NULL) 
	{
		cout << "MyClass::MyClass()" << endl;
	}

	void func1()
	{
		cout << "MyClass::func1" << endl;
		m_aggregatedClass->func1();
	}

	~MyClass()
	{
		cout << "MyClass::~MyClass" << endl;
	}

private:
	AggregatedClass* m_aggregatedClass;
};


// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================

int main(int argc, char** argv)
{

	cout << "main - start" << endl;
	
	// first we need to create the aggregated object
	AggregatedClass* aggregatedObj = new AggregatedClass(15);
	MyClass obj(aggregatedObj);
	obj.func1();

	// now we (main program) must take care of the destruction
	// of the aggregated object "manually"
	delete aggregatedObj;

	cout << "main - end" << endl;
	return 0;
}

