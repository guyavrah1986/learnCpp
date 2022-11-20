// ===================================================================================================================================================================
// ===================================================================================================================================================================
//
// pointer-to-pointer and frefernce-to-pointer and their usage:
// ------------------------------------------------------------
// 1) Here we see the problem that might arise in some cases.When passing a pointer in C/C++, a "copy by value" is performed thus copying the value of the pointer to
//    the argument of the function.As a result, any modification on the pointer within the function such as poiting it to ANOTHER adress, will affect only the local 
//    variable of the function and not the original pointer.
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>

using namespace std;

int glob = 17; 

void funcWithProblem(int* p) // 1)
{
	p = &glob;
}

void ptrToPtrSolution(int** pp)
{
	*pp = &glob;
}

void refToPtrSoltion(int*& rp)
{
	rp = &glob;
}


// =======================================

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	
	int n = 12;
	int* pMain = &n;

	cout << "main - before calling ANY function, pMain points to value of:" << *pMain << " with address of:" << pMain << " the address of glob is:" << &glob << endl;

	funcWithProblem(pMain);
	cout << "main - after calling funcWithProblem function, pMain points to value of:" << *pMain << " with address of:" << pMain << endl;

	ptrToPtrSolution(&pMain);
	cout << "main - after calling ptrToPtrSolution function, pMain points to value of:" << *pMain << " with address of:" << pMain << endl;

	n = 15;
	pMain = &n;
	cout << "main - changing pMain to point to value of:" << *pMain << " with address of:" << pMain << endl;
	refToPtrSoltion(pMain);

	cout << "main - after calling refToPtrSoltion function, pMain points to value of:" << *pMain << " with address of:" << pMain << endl;

	cout << "\n \n main - end" << endl;
	return 0;
}
