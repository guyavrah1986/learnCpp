// ===================================================================================================================================================================
// ===================================================================================================================================================================
// Aggregation2:
// ------------
// 1) In this example we will illustrate the most basic aggregation using C++98 (i.e.- anything BEFORE C++11) using references to hold the aggregated class members.
// 2) Here, as well as in the case where the aggregated class members are held by pointers, a main difference with respect to composition, is that the parent object
//    (class) is not responsible to the CREATION nor the DESTRUCTION of the aggreagted object. 
// 3) IMPORTANT NOTE: Due to the fact that the class member is held by reference, we can NOT have a default ctor for the parent class - cause the aggregated class 
//    member MUST be initialized with some other reference, which, offcourse, can NOT be provided by the default ctor.
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
	MyClass(AggregatedClass& obj) 
		: m_aggregatedClass(obj)
	{
		cout << "MyClass::MyClass(AggregatedClass& obj)" << endl;
	}
	
	/*		// 3)		
	MyClass() 
		: m_aggregatedClass() 
	{
		cout << "MyClass::MyClass()" << endl;
	}
	*/

	void func1()
	{
		cout << "MyClass::func1" << endl;
		m_aggregatedClass.func1();
	}

	~MyClass()
	{
		cout << "MyClass::~MyClass" << endl;
	}

private:
	AggregatedClass& m_aggregatedClass;
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
	AggregatedClass aggregatedObj(15);
	MyClass obj(aggregatedObj);
	obj.func1();

	cout << "main - end" << endl;
	return 0;
}

