// =============================================================================================================================================
/*
*  Item 1: Pointers and references
*  -------------------------------
*  1) Refernce Must always refer to an object which it will always refer to, so:
*  a) We can not declare a refernce without initialize it.
*  1a) # One exception is when we declare a class member as a reference - in this case, in the line where the reference is declared, indeed 
*      we aren't initialize it, YET we MUST do it in the ctor.
*      # Note that assgining is NOT initializing.
*  b) Once the reference is assgined to an object, it will always refer to this object, so if we set the reference to refer to another object
*     the "old value" will be modified, yet the pointer will point to the same address.
*
*  2) For conclusion, you should use:
*  a) pointer - if you wish to have the ability NOT to point to an object (set the pointer to NULL) OR point to a different object.
*  b) reference - if you know in advance that you will always refer to an (valid) object (which can NOT be NULL) and ONLY to that object.  
*
*/
// =============================================================================================================================================
#include <iostream>
#include <string>

using namespace std;

class SampleClass
{
	SampleClass(string str="defaultVal") : m_str(str)
	{
		cout << "SampleClass::SampleClass" << endl;
	}

	private:
		string& m_str;
};

void item1Usage()
{
	cout << "item1Usage - start" << endl;
	
	// 1a)
	//string& str; //--> won't compile
	string str1("first string");
	string str2("second string");
	cout << "item1Usage - address of str1:" << &str1 << " its content:" << str1 << endl;
	cout << "item1Usage - address of str2:" << &str2 << " its content:" << str2 << endl;
	
	string& ref1 = str1;
	string* ptr1 = &str1;

	cout << "item1Usge - ptr1:" << *ptr1 << " and it points to address" << ptr1 << endl;
	ptr1 = &str2;
	cout << "item1Usge - after re-assgin ptr1 = &str2,  *ptr1 is:" << *ptr1 << " and it points to address" << ptr1 << endl;
	
	// 1b) 
	ref1 = str2;
	cout << "item1Usge - after re-assgin ref1 = str2, str1 is:" << str1 << " it address is still:" << &str1 << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item1Usage();
	cout << "\n \n main - end" << endl;
	return 0;
}
