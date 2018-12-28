// ===================================================================================================================================================================
// ===================================================================================================================================================================
// Throwing exception from ctor:
// ----------------------------
// This examp[le shows what exactly happens when a ctor of a certain object throws an excpetion while it is constructed:
// In general, if an object is NOT fully constructed - than "there is nothing to destroy" --> SO NO DTOR will be invoked.
// 1) In this case the integer that will be allocated will not be free-ed.
// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <iostream>
#include <exception>

using namespace std;

class Base
{
public:
	Base()
	{
		m_val = new int(17);		
		cout << "Base::Base(default) - set m_val to:" << *m_val << endl;
		const string exceptionMsg = "dummy excpetion from Base ctor";
		throw (exceptionMsg.c_str());
		cout << "Base::Base(default) - DONE !!" << endl;
	}

	Base(int val)
	{
		m_val = new int(val);		
		cout << "Base::Base - set m_val to:" << *m_val << endl;
	}

	virtual ~Base()
	{
		delete m_val;
		cout << "Base::~Base" << endl;
	}

	int* m_val;
};

void createBaseObjOnStack()
{
	cout << "createBaseObjOnStack - start" << endl;
	Base(12);
	cout << "createBaseObjOnStack - end" << endl;
}

void createBaseObjThatThrowsExceptionOnStack()
{
	cout << "createBaseObjThatThrowsExceptionOnStack - start" << endl;
	Base();	// 1)
	cout << "createBaseObjThatThrowsExceptionOnStack - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	
	createBaseObjOnStack();
	cout << "\n \n \n";
	
	// Un-comment this line to view a scenario where a ctor throws an exception 
	// which causes a memory leak
	// createBaseObjThatThrowsExceptionOnStack();
	

	cout << "main - end" << endl;	
	return 0;
}
