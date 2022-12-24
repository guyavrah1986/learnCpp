// ================================================================================================================================================
// ================================================================================================================================================
// Chapter 1 - name conflicts:
// ---------------------------
// In this example the phenomen of name conflicts will be illustrate. 
// 1) In C++, every identifier (variable or function name) within a project MUST be unique. In case it is not, when we will build the project
//    there will be either compilation, or more likely, linking errors.
// 2) Consider the 3 files in this example: 
// a) When you ONLY compile them, with the command (note the -c option at the end):
//    $  g++ file1.cpp file2.cpp main.cpp -c
//    everything will work well, each one of them, ON ITS OWN, is 100% fine.
// 3) The problem will arise once you will link the 3 outputs of the compilation process, object files, into a single executable, with the command:
//    $ g++ -o myexecutable file1.o main.o file2.o
//    In this case, using g++ an error like the following will arise:
//    file2.o: In function `foo(int)':
//    file2.cpp:(.text+0x0): multiple definition of `foo(int)'
//    file1.o:file1.cpp:(.text+0x0): first defined here
//    collect2: error: ld returned 1 exit status
//    --> which says in a direct manner that there is multiple defintion here, so the linker is a bit confused on how to resolve this situation.
// 4) Linker:
// =================================================================================================================================================
// =================================================================================================================================================
#include <iostream>

using namespace std;

// forward declration of foo function
int foo(int x);

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	int res = foo(17);
	cout << "main - end" << endl;
	return 0;
}
