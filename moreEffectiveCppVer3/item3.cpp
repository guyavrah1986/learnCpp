// ====================================================================================================================================================================
/*
* 1) const pointer and pointer to const for primitive data types:
* --------------------------------------------------------------- 
* When declaring a pointer we have two options: 
* a) Non const pointer to non const data.
* b) In this specific case, although it seems that the pointer is both data and location non const -- this is NOT the case. In this type of declration, the content
*    that the pointer is poiting to is located in the TEXT segment of the process - thus it is invalid operation modifying (writing) to this location. 
* c) Declaring the pointer as a const, meaning we can NOT modify the location we are pointing to --> the const keyword is on the RIGHT side of the astrik (*).
* d) Declraing the pointer to point to a const "object", meaning we can NOT modifiy the content that the pointer is pointing to --> the const keyword is on the LEFT
*    side of the astrik (*).
*
* 2) const iterator and iterator_const of STL containers:
* -------------------------------------------------------
* The same goes for STL iterators.
* a) If we declare the iterator as const, it acts like a T* const --> the location it is poiting to can NOT be modified.
* b) If we declare the iterator as const_iterator, it acts like const T* --> the value (content) it is poiting to can NOT be modified. 
*
*/
// ====================================================================================================================================================================
#include <iostream>
#include <vector>

using namespace std;

void pointerToPrimitiveTypeUsageExample()
{
	cout << "pointerToPrimitiveTypeUsageExample - start" << endl;
	// a) In both cases (p1 & p2) we can modify the content of the 
	//    pointer and also the location it points to.
	char p1 [] = "string1"; 
	char* p2 = p1;
	*p2 = 'h';
	
	cout << "pointerToPrimitiveTypeUsageExample - p1 points to:" << p1 << endl;
	cout << "pointerToPrimitiveTypeUsageExample - p2 points to:" << p2 << endl;

	// b) 
	char* p3 = "string3"; 
	//*p3 = 'h'; --> Watch out, this line will crash the code !!
	
	// c) 
	char str4 [] = "string4";
	char str5 [] = "string5";
	char* const p4  = str4;
	cout << "pointerToPrimitiveTypeUsageExample - BEFORE modifying the first char that p4 points to:" << p4 << endl;
	*p4 = 'H';
	cout << "pointerToPrimitiveTypeUsageExample - AFTER modifying the first char that p4 points to:" << p4 << endl;
	//p4 = str5; --> This line will NOT compile 
	
	// d) 
	const char* p5 = str4;
	cout << "pointerToPrimitiveTypeUsageExample - BEFORE modifying the location that p5 points to:" << p5 << endl;
	p5 = str5;
	cout << "pointerToPrimitiveTypeUsageExample - AFTER modifying the location that p5 points to:" << p5 << endl;
	//*p5 = 'K'; --> This line does NOT compile
	
	cout << "\n \n pointerToPrimitiveTypeUsageExample - end" << endl;
}

void iteratorsUsageExample()
{
	cout << "iteratorsUsageExample - start" << endl;
	vector<int> vec = {1,2,3};
	size_t index = 0;
	vector<int>::iterator it1 = vec.begin();
	cout << "iteratorsUsageExample - BEFORE modifying the first element of the vector, vec[" << index << "] is:" << *it1 << endl;
	*it1 = 4;
	cout << "iteratorsUsageExample - AFTER modifying the first element of the vector, vec[" << index << "] is:" << *it1 << endl;

	// a)
	const vector<int>::iterator it2 = vec.begin();
	*it2 = 5;
	cout << "iteratorsUsageExample - AFTER modifying the first element of the vector, vec[" << index << "] is:" << *it2 << endl;
	//++it2; --> This line won't compile !!
	
	// b)
	vector<int>::const_iterator it3 = vec.begin();
	//*it3 = 9; --> This line won't compile !!
	cout << "iteratorsUsageExample - when assgining it to vec.begin() it points to:" << *it3 << endl;
	++it3;
	cout << "iteratorsUsageExample - after moving it forward by one location (it3++), it points to:" << *it3 << endl;

	cout << "\n \n iteratorsUsageExample - end" << endl;
}

void item3Usage()
{
	pointerToPrimitiveTypeUsageExample();
	iteratorsUsageExample();
	cout << "\n \n item3Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item3Usage();
	
	cout << "main - enter any key to terminate..." << endl;
	char c = 0;
	cin >> c;
	cout << "\n \n main - end" << endl;
	return 0;
}
