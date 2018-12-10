/*extern*/ int g_x = 17;
static int g_y = 15;

#include <iostream>

using namespace std;

void fooInGlobalFile()
{
	cout << "fooInGlobalFile - g_x is:" << g_x << endl;
	cout << "fooInGlobalFile - g_y is:" << g_y << endl;
}

static void fooStatic()
{
	cout << "fooStatic - g_y is:" << g_y << endl;
}
