// ================================================================================================================================================
// ================================================================================================================================================
// Chapter 8 - auto type deduction:
// --------------------------------
// 1) In C++ the auto keyword was introduced to enable the developer to "forget" about type declration. In this case the variable x will be of
//    type int.
// 2) In case one wishes to declare a variable using the auto keyword ("type") he needs to take into account that the const-ness of the variable 
//    needs to be added excplicitly - so in this case d2 is NOT const doubel but "only" double.
// 3) Note that the compiler needs, neverthelss, some sort of "clue" 
// =================================================================================================================================================
// =================================================================================================================================================

#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	auto x = 17; // 1) 
	const double d1 = 13.2;
	auto d2 {d1}; // 2)
	auto y; // 3)
	


	cout << "main - end" << endl;
	return 0;
}
