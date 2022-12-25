// ================================================================================================================================================
// ================================================================================================================================================
// Chapter 8 - type conversions:
// ----------------------------
// 1) In C/C++ when some operation between two types is being conducted it is CRUCIAL to understand how the compiler treats this operation.
// 2) https://anteru.net/blog/2007/c-background-static-reinterpret-and-c-style-casts/
// 3) One of the main benefits of using static_cast is that it will raise compilation error when an inappropriate cating, mainly of pointers, will
//    take place.
// 4) Pointing on an "in-compatible" type can cause issue, like in the example in this case. Note that it is possible only using the C-style cast
//    and would have not been possible with static_cast.
// =================================================================================================================================================
// =================================================================================================================================================

#include <iostream>

using namespace std;

struct __attribute__ ((packed)) adjusentVars
{
	char c1;
	int x1;
};

class ParentWithoutVtable
{    
    char empty;
};

class ParentWithVTable
{
    public:
        virtual ~ParentWithVTable () { }
};

class Derived : public ParentWithoutVtable, public ParentWithVTable
{
};

void objectCastedViaDifferentTypesOfCasting()
{

}

void integersDivisionVsDoubleDivision()
{
	string funcName = "integersDivisionVsDoubleDivision - ";
	cout << funcName + "start" << endl;
	double d1 = 10 / 4; //1)
	cout << funcName + "the result of performing two literals division is:" << d1 << endl;
	d1 = static_cast<double>(10) / 4;
	cout << funcName + "the result of performing two literals division when one is casted to double is:" << d1 << endl;
	char c = 5;
	int* p = (int*)&c;
	cout << funcName + "the address of c is:" << (void*)(&c) << ", and its value is:" << +c << endl;
	*p = 17;
	cout << funcName + "after setting *p = 17, the value of c is:" << +c << endl;
	int x = 0x01020304;	
	char* cp = (char*)&x;
	//char* cp = static_cast<char*>(&x); //3)
	cout << funcName + "about to print values of x (int) pointed by char*" << endl;
	char* p1 = cp;
	for (char i = 0; i < sizeof(int); ++i)
	{
		cout << std::hex << +(*p1);
		++p1;
	}
	
	cout << endl;
	

	
	struct adjusentVars sampleStruct {100,0};
	cout << funcName + "the address of c1 is:" << (void*)(&sampleStruct.c1) << ", and its value is:" << +(sampleStruct.c1) << endl;
	cout << funcName + "the address of x1 is:" << (void*)(&sampleStruct.x1) << ", and its value is:" << sampleStruct.x1 << endl;
	p = (int*)&sampleStruct.c1;
	cout << funcName + "sampleStruct.c1 is being pointed by an int* at address:" << (void*)p << endl;
	*p = 0x01020304; // 4)
	cout << funcName + "after sampleStruct.c1 was pointed by an int* and it was assgined with value, is it now:" << +(sampleStruct.c1) << endl;
	cout << funcName + "after sampleStruct.c1 was with value while it was pointed to via an int*, the bytes of sampleStruct.x1 are:" << endl;
	p1 = (char*)&sampleStruct.x1;
	for (char i = 0; i < sizeof(int); ++i)
	{
		cout << std::hex << +(*p1);
		++p1;
	}
	
	cout << endl;
	cout << funcName + "end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	integersDivisionVsDoubleDivision();
	cout << "main - end" << endl;
	return 0;
}
