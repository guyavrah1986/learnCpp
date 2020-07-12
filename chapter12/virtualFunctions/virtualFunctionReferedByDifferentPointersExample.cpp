#include <iostream>

using namespace std;


class A 
{
public:
	A(){ cout << "A:A()" << endl; }
	A(const A& a){ cout << "A::A(A)" << endl; }
	~A(){ cout << "A::~A()" << endl; }
	void f1(){ cout << "A::f1()" << endl; f2(); }
	virtual void f2(){ cout << "A::f2()" << endl; f3(); }
	void f3(){ cout << "A::f3()" << endl; f2(); }
};

class B :public A 
{
private:
	char* m_cp;
public:
	B(){ cout << "B:B()" << endl; m_cp = new char[4]; }
	B(const B& b){ cout << "B::B(B)" << endl; }
	~B(){ delete m_cp; cout << "B::~B()" << endl; }

	void f1(){ cout << "B::f1" << endl; f4(); }
	virtual void f2(){ cout << "B::f2()" << endl; f4(); }
	virtual void f4(){ cout << "B::f4()" << endl; }
};

class C :public B 
{
	public:
	C(){ cout << "C:C()" << endl; }
	C(const C& c) { cout << "C::C(C)" << endl; }
	~C(){ cout << "C::~C()" << endl; }

	virtual void f1(){ cout << "C::f1()" << endl; f4(); }
	virtual void f4(){ cout << "C::f4()" << endl; }
};


int main(int argc, char** argv)
{
	string funcName = "main - ";
	cout << funcName + "start" << endl;
	// line 1
	cout << funcName + "line 1 output is:" << endl;
	C* cptr = new C();
	cout << "\n \n" << endl;


	// line 2:
	cout << funcName + "line 2 output is:" << endl;
	A* aptr = new C(*cptr);
	cout << "\n \n" << endl;

	// line 3:
	cout << funcName + "line 3 output is:" << endl;
	cptr->f1();
	cout << "\n \n" << endl;

	// line 4:
	cout << funcName + "line 4 output is:" << endl;
	cptr->f2();
	cout << "\n \n" << endl;

	// line 5:
	cout << funcName + "line 5 output is:" << endl;
	aptr->f1();
	cout << "\n \n" << endl;

	// line 6:
	cout << funcName + "line 6 output is:" << endl;
	aptr->f3();
	cout << "\n \n" << endl;

	// line 7:
	cout << funcName + "line 7 output is:" << endl;
	delete aptr;
	cout << "\n \n" << endl;

	// line 8:
	cout << funcName + "line 8 output is:" << endl;
	delete cptr;
	cout << "\n \n" << endl;

	// extra line
	cout << funcName + "extra line output is:" << endl;

	A obj = B();
	cout << funcName + "end" << endl;
	return 0;
}
//
