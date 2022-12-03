#include <iostream>

#include "file1.hpp"
//#include "file2.hpp"

using namespace std;

int main(int argc, char** argv)
{
	string funcName = "main - ";
	cout << funcName + "start" << endl;
	cout << funcName + "about to call function from lib1 (file1) " << endl;
	f1();
	cout << funcName + "end" << endl;
	return 0;
}
