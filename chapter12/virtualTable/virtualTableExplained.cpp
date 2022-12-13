// ===================================================================================================================================================================
// ===================================================================================================================================================================
// NOTE: Compile the program with the following line:
// g++ -g -O0 -c -fverbose-asm -Wa,-adhln virtualTableExplained.cpp > test.lst
//
// 1) When accessing data members without inheritence, the only offset that needs to take place is the "constant" offset that is known in advance. For example,
//    when accessing the two members of the classes that have or don't have virtual table and pointer the following takes place:
/*
343              	# virtualTableExplained.cpp:140: 	AwithoutVirtualPointer* pa1 = &a1;
 140:virtualTableExplained.cpp **** 	AwithoutVirtualPointer* pa1 = &a1;
 344              		.loc 1 140 0
 345 002e 488D45C8 		leaq	-56(%rbp), %rax	#, tmp89
 346 0032 488945B8 		movq	%rax, -72(%rbp)	# tmp89, pa1
 347              	# virtualTableExplained.cpp:144: 	int x1 = pa1->m_a;
 144:virtualTableExplained.cpp **** 	int x1 = pa1->m_a;
 348              		.loc 1 144 0
 349 0036 488B45B8 		movq	-72(%rbp), %rax	# pa1, tmp90
 350 003a 8B00     		movl	(%rax), %eax	# pa1_4->m_a, tmp91
 351 003c 8945A8   		movl	%eax, -88(%rbp)	# tmp91, x1
 352              	# virtualTableExplained.cpp:145: 	int y1 = pa1->m_b;
 145:virtualTableExplained.cpp **** 	int y1 = pa1->m_b;
 353              		.loc 1 145 0
 354 003f 488B45B8 		movq	-72(%rbp), %rax	# pa1, tmp92
 355 0043 8B4004   		movl	4(%rax), %eax	# pa1_4->m_b, tmp93
 356 0046 8945AC   		movl	%eax, -84(%rbp)	# tmp93, y1


 357              	# virtualTableExplained.cpp:147: 	A a2(12,17);

 366              	# virtualTableExplained.cpp:148: 	A* pa2 = &a2;
 148:virtualTableExplained.cpp **** 	A* pa2 = &a2;
 367              		.loc 1 148 0
 368 005f 488D45D0 		leaq	-48(%rbp), %rax	#, tmp95
 369 0063 488945C0 		movq	%rax, -64(%rbp)	# tmp95, pa2
 370              	# virtualTableExplained.cpp:149: 	int x2 = pa2->m_a;
 149:virtualTableExplained.cpp **** 	int x2 = pa2->m_a;
 371              		.loc 1 149 0
 372 0067 488B45C0 		movq	-64(%rbp), %rax	# pa2, tmp96
 373 006b 8B4008   		movl	8(%rax), %eax	# pa2_8->m_a, tmp97
 374 006e 8945B0   		movl	%eax, -80(%rbp)	# tmp97, x2
 375              	# virtualTableExplained.cpp:150: 	int y2 = pa2->m_b;
 150:virtualTableExplained.cpp **** 	int y2 = pa2->m_b;
 376              		.loc 1 150 0
 377 0071 488B45C0 		movq	-64(%rbp), %rax	# pa2, tmp98
 378 0075 8B400C   		movl	12(%rax), %eax	# pa2_8->m_b, tmp99
 379 0078 8945B4   		movl	%eax, -76(%rbp)	# tmp99, y2
*/
// Class members location upon multiple inheritance:
// -------------------------------------------------
// 1) When a derived class inherites from two (or more) "base" classes, the layout of all her members (hers + the inherited ones) are according to the order of the 
//    inheritence:
//    # Base1's members
//    # Base2's members
//    # Derived's members
// 2) The address of the "this" pointer of the Derived class is the same as the address of the first member of her -- which is the first member of the "first"
//    base class.
//    NOTE: The term "first base class" referes to the actuall first base class name in the dervied class definition. For example, as in the case below where the dervied class is 
//    defined as follows:class Derived : public Base1 , public Base2 --> Base1 is the "first base class" and Base2 is the second.
// 
// virtual table under the hood:
// -----------------------------
// Some notes about virtual functions and virtual tables:
// 0) Once a class has AT LEAST one virtual function --> it implies that it will have a virtual table + virtual pointer.
// 1) A virtual table is created ONCE for each class. It is located (implementation specific) somewhere (probably) in the BSS segment (all the data
//    which is relevant for constructing the virtual table is known at compile time so it could be placed there).It is static. 
// 2) The objective of the virtual pointer is to point to the virtual table.Its location will be (usually) at the first 4/8 bytes of the object (32/64 bit).
// 3) Virtual table is basically a structure that holds all the function pointers to all the VIRTUAL functions of an object. Note: It DOES NOT hold the 
//    pointers to non-virtual functions.
// 4) In the case of multiple inheritence, the derived class will inherite all it's base class(es) virtual pointer, thus increasing its size respectevly. 
//    Note that there will be no need for an additional virtual pointer "specifically" for the derived object (so in the example below - only two virtual pointers
//    will be added to the derived class). 
//    The layout will be as follows: (for the case below fo class Derived : public Base1, public Base2):
//    NOTES: 
//    - We assume "theoretically" there is no padding.
//    - Size of int and pointer is 4 bytes.
// 
//    bytes |           data
//    ---------------------------------  
//    0-3   |  vptr for Base1 v-table.
//    4-7   |  Base1 member (int)
//    8-11  |  vptr for Base2 v-table.
//    12-15 |  Base2 member (int)
//    16-19 |  Derived member (int)
//
//  5) The "extra" code that does the initialization of the v-table for each class in inserted by the compiler (for each ctor) right after the class's base class 
//     is done (in case there is one) and just before the body of the ctor is executed.
//     --> Due to this fact, calling a virtual function within a ctor, will invoke the current "most derived version" and NOT the absoulute most derived version 
//     ( as we wish...). 
//  
//  6) Some impacts of using v-table:
//     a) Calling a virtual function costs us in an extra read of the address of the actual function to be invoked during run-time (not so bad).
//        The exact arithmetic being done is pointer read + offset manipulation. 
//     b) Virtual functions CAN NOT be inline !!
//     c) For each class that has a virtual table - a table with X entires of pointers will be created ONCE.For example, if class A has 3 virtual functions in it,
//        then a virtual "table" (which usually be implemented by an array of pointers) will have 3 "entires" in it --> which will "cost" the program in 3 pointers
//        in the memory. 
//     d) For each instance of this class there will be an additional 4/8 bytes in its "size" due to the virtual pointer. 
//        IMPORTANT NOTE: In case class A derived from TWO classes which each one of them has a vritual table of its own, then the "extra" size in memory for erach 
//        instance of this class is 3 * size of pointer.
//     
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <iostream>

using namespace std;

class AwithoutVirtualPointer
{
public:	
	AwithoutVirtualPointer(int a, int b) : m_a(a), m_b(b)
	{
		cout << "AwithoutVirtualPointer::AwithoutVirtualPointer" << endl;
	}

	~AwithoutVirtualPointer()
	{
		cout << "AwithoutVirtualPointer::~AwithoutVirtualPointer" << endl;
	}

	int m_a;
	int m_b;
};

class A
{
public:
	A(int a, int b) : m_a(a), m_b(b)
	{
		cout << "A::A - setting m_a to:" << m_a << ", and m_b to:" << m_b << endl;
	}

	virtual ~A()
	{
		cout << "A::~A" << endl;
	}
	
	int m_a;
	int m_b;
};

/*
void displayBothClassA()
{
	string funcName = "displayBothClassA - ";
	cout << funcName + "start" << endl;
	cout << funcName + "creating A on the stack of the function" << endl;
	A a(12,17);
	A* pa = &a;
	void* addressOfA = static_cast<void*>(pa);
	cout << funcName + "the address of &a is:" << static_cast<void*>(addressOfA) << endl;
	cout << funcName + "the address of the first member of A is:" << static_cast<void*>(&pa->m_a) << endl;

	AwithoutVirtualPointer a2(12,17);
	AwithoutVirtualPointer* pa2 = &a2;
	void* addressOfA2 = static_cast<void*>(pa2);
	cout << funcName + "the address of &a2 is:" << static_cast<void*>(addressOfA2) << endl;
	cout << funcName + "the address of the first member of AwithoutVirtualPointer is:" << static_cast<void*>(&pa2->m_a) << endl;
	cout << funcName + "end" << endl;
}
*/

void accessDataMembersOfBothClassA()
{
	//string funcName = "accessDataMembersOfBothClassA - ";
	//cout << funcName + "start" << endl;
	//cout << funcName + "creating AwithoutVirtualPointer on the stack of the function" << endl;
	AwithoutVirtualPointer a1(12,17);
	AwithoutVirtualPointer* pa1 = &a1;
	//void* addressOfAwithoutVirtualPointer = static_cast<void*>(pa2);
	//cout << funcName + "the address of &a2 is:" << static_cast<void*>(addressOfAwithoutVirtualPointer) << endl;
	//cout << funcName + "the address of the first member of AwithoutVirtualPointer is:" << static_cast<void*>(&pa2->m_a) << endl;
	int x1 = pa1->m_a;
	int y1 = pa1->m_b;

	A a2(12,17);
	A* pa2 = &a2;
	int x2 = pa2->m_a;
	int y2 = pa2->m_b;
	//cout << funcName + "end" << endl;
}

int main(int argc, char** argv)
{
	cout << "virtualTableExplained - start " << endl;
	cout << "virtualTableExplained - sizeof(int) is:" << sizeof(int) << " bytes " << endl;
	//cout << "virtualTableExplained - sizeof(Derived) is:" << sizeof(Derived) << " bytes " << endl;
	cout << "virtualTableExplained - sizeof(void*) is:" << sizeof(void*) << " bytes " << endl;
	cout << "virtualTableExplained - creating Derived object on the heap" << endl;
	
	//displayBothClassA();	
	accessDataMembersOfBothClassA();
	
	/*
	Derived* d = new Derived;
	
	cout << "virtualTableExplained - calling d->func1()" << endl;
	d->func1();
	cout << "virtualTableExplained - deleting the Derived object" << endl;
	delete (d);
	*/
	cout << "virtualTableExplained - end" << endl;
	return 0;
}


