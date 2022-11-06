// ################################################################################################################################
// ################################################################################################################################
// ################################################################################################################################
// Virtual pointer "offset phenomena":
// ----------------------------------- 
// 1) This simple example illustrate the "offest" in the class members that takes place once the virtual pointer exists.
// 2) In case you uncomment both the comment section notes by 2), you will observe what happens when a class has at least one 
//    virtual function (in this case it is the dtor). When this happens ALL the class members are being "offseted" by a size of 
//    a pointer (4/8 bytes typically), so in case you wish to "treat" (point) on a C++ class via a "simple" equivalent struct,
//    an "adjsument" MUST take place - otherwise the struct pointer will be in offset. 
// ################################################################################################################################
// ################################################################################################################################
// ################################################################################################################################


#include <iostream>

using namespace std;

struct SampleStrcut
{
	unsigned char m_a;
	unsigned char m_b;
	unsigned char m_c;
	unsigned char m_d;
}
__attribute__((packed));

class SampleObj
{

public:
	SampleObj(char a, char b, char c, char d) : m_a(a), m_b(b), m_c(c), m_d(d)
	{
		cout << "SampleObj::SampleObj - setting m_a to:" << int(this->m_a) << ", m_b to:" << int(this->m_b) << ", m_c to:" << int(this->m_c) << ", m_d to:" << int(this->m_d) << endl;
	}

	/*	// 2)
	virtual ~SampleObj()
	{
		cout << "SampleObj::~SampleObj" << endl;
	}
	*/
	//	
	unsigned char m_a;
	unsigned char m_b;
	unsigned char m_c;
	unsigned char m_d;

}__attribute__((packed));

void passCppClassWithVirtualPointerToStrcutInC()
{ 
	string funcName = "passCppClassWithVirtualPointerToStrcutInC - ";
	cout << funcName + "start" << endl;
	cout << funcName + "creating SampleObj instance on the stack" << endl;
	SampleObj sampleObj(1, 2, 3, 4);
	unsigned char sizeOfVoidPointer =  sizeof(void*);	
	cout << funcName + "size of char is:" << sizeof(unsigned char) << endl;
	cout << funcName + "size of int is:" << sizeof(int) << endl;
	cout << funcName + "size of void* is:" << sizeOfVoidPointer << endl;
	cout << funcName + "size of SampleObj class is:" << sizeof(SampleObj) << endl;
	cout << funcName + "size of SampleStrcut strcut is:" << sizeof(SampleStrcut) << endl;

	SampleObj* p1 = &sampleObj;
	cout << funcName + "address of p1 (SampleObj*) is:" << static_cast<void*>(p1) << endl;
	cout << funcName + "address of p1->m_a is:" << static_cast<void*>(&(p1->m_a)) << ", p1->m_a is:" << int(p1->m_a) << endl;
	cout << funcName + "address of p1->m_b is:" << static_cast<void*>(&(p1->m_b)) << ", p1->m_b is:" << int(p1->m_b) << endl;
	cout << funcName + "address of p1->m_c is:" << static_cast<void*>(&(p1->m_c)) << ", p1->m_c is:" << int(p1->m_c) << endl;
	cout << funcName + "address of p1->m_d is:" << static_cast<void*>(&(p1->m_d)) << ", p1->m_d is:" << int(p1->m_d) << endl;

	// SampleObj is WITHOUT virtual pointer 
	SampleStrcut* p2 = (SampleStrcut*)&sampleObj;
	cout << funcName + "after assgining unsigned char* p2 = (SampleStrcut*)&sampleObj, p2 points to:" << static_cast<void*>(p2) << endl;
	cout << funcName + "p2->m_a value is:" << int(p2->m_a) << endl;
	cout << funcName + "p2->m_b value is:" << int(p2->m_b) << endl;
	cout << funcName + "p2->m_c value is:" << int(p2->m_c) << endl;
	cout << funcName + "p2->m_d value is:" << int(p2->m_d) << endl;
	  
	/* SampleObj is WITH virtual pointer 	//2)
	unsigned char* p2 = (unsigned char*)&sampleObj;
	cout << funcName + "after assgining unsigned char* p2 = (unsigned char*)&sampleObj, p2 points to:" << static_cast<void*>(p2) << endl;
	p2 = p2 + sizeOfVoidPointer;
	cout << funcName + "(*p2[0]) value is:" << int(*p2) << endl;
	p2 = p2 + 1;
	cout << funcName + "(*p2[1]) value is:" << int(*p2) << endl;
	p2 = p2 + 1;
	cout << funcName + "(*p2[2]) value is:" << int(*p2) << endl;
	p2 = p2 + 1;
	cout << funcName + "(*p2[3]) value is:" << int(*p2) << endl;
	*/

	cout << funcName + "end" << endl;

}


int main(int argc, char** argv)
{
	string funcName = "main - ";
	cout << funcName + "start" << endl;
	passCppClassWithVirtualPointerToStrcutInC();
	cout << funcName + "end" << endl;
	return 0;
}
