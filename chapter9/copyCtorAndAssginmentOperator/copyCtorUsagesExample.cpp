// ===================================================================================================================================================================
// ===================================================================================================================================================================
// copy Ctor:
// ----------
// 1) Has the signature that accept a const refernce to another (usually called "other") class type object. It is important to distinguish it from the assginment 
//    operator in the fact that it is used to initiate a NEW object from an exsisting one. The assginment operator is used to initialize ("copy contents") an already 
//    exisisting object from another object. So for example:
//    MyStr myStr1; --> defualt ctor
//    MyStr myStr2 = myStr1; --> copy ctor
//    MyStr myStr3(myStr1);  --> copy ctor
//    MyStr myStr2 = myStr3; --> assginment operator= 
// 2) The default copy ctor that the compiler produces perfroms SHALLOW copy.
//    BIG NOTE: In case our class has a member(s) that allocated dynamically memory, this (shallow copying) could lead to undefined behaviour. 
// 
// 3) Upon performing a copy of an anonymous instance, usually the compiler optimizes this procedure and simply initiate the object without calling the copy ctor. It 
//    refered usually as "elision optimization". Note that none of the code in the copy ctor body will be executated !!!
//    It can be illustrated with the following example:
//    MyStr myStr = MyStr("some_string"); --> is basically equivalent to this (copy initialization)
//    MyStr myStr(MyStr("some_string")); --> which , according to elision can be optimized to this
//    MyStr myStr("some_string"); (direct initialization)
// 
// 4) There are cases where elision can take place and cases where it can not take place.
// 4a)


// Some notes:
// -----------
// a) The fact that we call the argument (regular) ctor from within the initialization list of the copy ctor (or of any other ctor) is possible only if we compile this code
//    with C++11 compiler. Otherwise we will get a warning, or worse - undefined behaviour. 
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>
#include <cstring>

using namespace std; 

class InnerObjValue 
{

public:
	InnerObjValue() : m_a(17)
	{
		cout << "InnerObjValue::InnerObjValue - setting m_a to:" << m_a << endl;
	}

private:
	int m_a;
};


class MyStr
{

public:
	MyStr(const char* str) : m_cStr(nullptr), m_b(11)
	{
		if (str != nullptr)
		{
			m_strLen = strlen(str);
			m_cStr = new char [m_strLen + 1];
			strcpy(m_cStr, str);
			cout << "MyStr::MyStr - setting m_cStr to:" << m_cStr << " for a new object in the address of:" << this << endl;
		}
	}

	virtual ~MyStr()
	{
		cout << "MyStr::~MyStr - delete object in the address of:" << this << endl;	
		if (m_cStr != nullptr)
		{
			delete [] m_cStr;
		}
	}

	
	MyStr(const MyStr& other) : MyStr(other.m_cStr) //a) 
	{
		cout << "MyStr::MyStr& other (copy Ctor) - got other in the address of:" << &other << " ,created a copy in the address of:" << this << endl;	
	}

	char* GetStr() const { return this->m_cStr; }
	int m_b;	

private:
	size_t m_strLen;
	char* m_cStr;
};


void passByValue(MyStr myStr)
{
	cout << "passByValue - got MyStr object with the string:" << myStr.GetStr() << " its address is:" << &myStr << endl;
}


MyStr returnByVlaueWithElision(const char* str)
{

	cout << "returnByVlaueWithElision - got string:" << str << endl;
	MyStr tmp(str);
	cout << "returnByVlaueWithElision - created MyStr with string:" << str << " in the address:" << &tmp << endl;
	return tmp;
}

MyStr returnByValueNoElision(MyStr obj)
{
	cout << "returnByValueNoElision - got obj in the address of:" << &obj << endl;
	// modify the m_b member
	obj.m_b = 17;
	return obj;
}


// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================


int main(int argc, char** argv)
{

	cout << "main - start" << endl;

	const char* str = "test_str";	
	MyStr myStr(str);
	// 2) Let call the passByValue to see the copy Ctor in action
	std::cout << "main - before calling passByValue, myStr address is:" << &myStr << std::endl;
	passByValue(myStr);

	// 3) Lets call the returnByVlaue to see the copy Ctor in action
	const char* tmpStr = "returnByValueStr";
	std::cout << "main - before calling returnByVlaueWithElision" << std::endl;
	MyStr tmp = returnByVlaueWithElision(tmpStr);
	std::cout << "main - after returning from returnByVlaueWithElision, tmp (local variable of main) is in the address:" << &tmp << " m_cStr is:" << tmp.GetStr() << std::endl;

	std::cout << "main - before calling returnByValueNoElision" << std::endl;
	MyStr tmp2 = returnByValueNoElision(tmpStr);
	std::cout << "main - after returning from returnByValueNoElision, tmp2 (local variable of main) is in the address:" << &tmp2 << " m_cStr is:" << tmp2.GetStr() <<
	" and m_b is:" << tmp2.m_b << std::endl;

	std::cout << "main - end" << std::endl;
	return 0;
}



