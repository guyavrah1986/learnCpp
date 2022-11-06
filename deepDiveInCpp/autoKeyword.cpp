#include <iostream>

using namespace std;

class Base 
{
public:
	void show()
	{
		cout << "Base::show" << endl;
	}

};


class Derived : public Base 
{

public:
	void show()
	{
		cout << "Derived::show" << endl;		
	}
};

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	Derived d;
	d.show();
	Base* pd = &d;
	cout << "main - calling show of Derived object with Base pointer" << endl;
	pd->show();
	cout << "main - end" << endl;
	return 0;
}

