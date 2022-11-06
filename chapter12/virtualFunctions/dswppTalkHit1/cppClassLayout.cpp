// ===================================================================================================================================================================
// ===================================================================================================================================================================
// C++ class layout:
// -----------------
// 1) Each class in C++ can contain class members and class methods.
// 2) The class members are "stored" within the class instance in the EXACT order of their declration within the class.
// 2.1) Memory layout is mostly left to the implementation. The key exception is that member variables for a given access specifier will be in order of their declaration.
//
// References:
// a) https://stackoverflow.com/questions/25377877/first-member-of-class
// b) https://stackoverflow.com/questions/1632600/memory-layout-c-objects
// c) https://stackoverflow.com/questions/32509820/address-of-static-member-in-a-class
// d) https://stackoverflow.com/questions/50763943/using-attribute-packed-for-classes-in-gcc
// e) https://stackoverflow.com/questions/4842056/do-static-members-of-a-class-occupy-memory-if-no-object-of-that-class-is-created
// f) https://stackoverflow.com/questions/648647/in-c-where-in-memory-are-class-functions-put
// g) https://stackoverflow.com/questions/137038/how-do-you-get-assembler-output-from-c-c-source-in-gcc
// h) https://stackoverflow.com/a/452982/1971003
// i) https://stackoverflow.com/a/41912747/1971003
// j) https://johnysswlab.com/the-true-price-of-virtual-functions-in-c/
// k) https://medium.com/@calebleak/fast-virtual-functions-hacking-the-vtable-for-fun-and-profit-25c36409c5e0
// l) https://stackoverflow.com/questions/24200064/assembler-code-for-virtual-function
// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <iostream>

#include "accessClassMembersSingleInheritence.h"
#include "accessClassMembersChainedInheritence.h"
#include "accessClassMembersMultipleInheritence.h"
#include "accessVirtualFunction.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	int choice;
	cout << "main - please enter the number of function to execute:" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1: accessClassMembersSingleInheritence();
		break;
	case 2:	accessClassMembersChainedInheritence();
		break;
	case 3:	accessClassMembersMultipleInheritence();
		break;
	case 4: accessVirtualFunction();
		break;
	default:
		cout << "main - invalid choice" << endl;		
		break;
	}

	cout << "main - end" << endl;
	return 0;
}
