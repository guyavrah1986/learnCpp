// ========================================================================================================================================================================
/*
* :
* --------------------------
* 
*
*/
// ======================================================================================================================================================================

#include <iostream>

using namespace std;

class UpInt 
{
	public:
	UpInt() : UpInt(0)
	{	
		cout << "UpInt::UpInt(default)" << endl;
	}

	UpInt(int val) : m_int(val)
	{
		cout << "UpInt::UpInt - setting m_int to:" << m_int << endl; 
	}
	
	friend const UpInt operator+(const UpInt& lhs, const UpInt& rhs);

	int m_int;
};

const UpInt operator+(const UpInt& lhs, const UpInt& rhs)
{
	return UpInt(lhs.m_int + rhs.m_int);
}

void item21Usage()
{
	cout << "item21Usage - start" << endl;

	UpInt ui1, ui(3);
	cout << "\n \n item21Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item21Usage();
	
	cout << "\n \n main - end" << endl;
	return 0;
}
