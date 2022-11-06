#include <iostream>
#include <string.h> // for memset


using namespace std;

struct MyClass
{
public:
	MyClass(int i) : m_i(i)
	{
		cout << "MyClass::MyClass - set m_i to:" << this->m_i << endl;
	}

	virtual ~MyClass() 
	{
		cout << "MyClass::~MyClass" << endl;
	}

	virtual void virtFunc()
	{
		cout << "MyClass::virtFunc" << endl;	
	}

	int m_i;
}__attribute__ ((__packed__));;

void setVirtualPointerToNullManually()
{
	cout << "setVirtualPointerToNullManually - start" << endl;
	MyClass mc(17);
	cout << "setVirtualPointerToNullManually - the size of MyClass instance is:" << sizeof(mc) << endl;
	cout << "setVirtualPointerToNullManually - the size of int is:" << sizeof(int) << endl;
	cout << "setVirtualPointerToNullManually - the size of void* is:" << sizeof(void*) << endl;
	mc.virtFunc();
	int* pi = static_cast<int*>(&(mc.m_i));
	cout << "setVirtualPointerToNullManually - the address of mc.m_i is" << pi << endl;
	char* pv = (char*)(pi) - 8;
	cout << "setVirtualPointerToNullManually - about to memset the address pointed by pv:" << (void*)pv << endl;
	memset((void*)(pi), 0, sizeof(void*));
	/*	
	cout << "setVirtualPointerToNullManually - set the virtual pointer to NULL, press any key to contiunue and call the virtual function" << endl;
	char c;
	cin >> c;
	*/
	mc.virtFunc();
	cout << "setVirtualPointerToNullManually - m_i now is:" << mc.m_i << endl;
	cout << "setVirtualPointerToNullManually - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	setVirtualPointerToNullManually();
	cout << "main - end" << endl;
	return 0;
}
