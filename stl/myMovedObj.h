#include <iostream>

using namespace std;

class MyMovedObj 
{

public:
	MyMovedObj(int a) : m_pInt(new int(a))
	{
		cout <<"MyMovedObj::MyMovedObj - setting m_pInt to point to value:" << *m_pInt << " its address is:" << m_pInt << endl;
	}

	~MyMovedObj()
	{
		if (m_pInt != nullptr)
		{
			delete m_pInt;
		}

		cout <<"MyMovedObj::~MyMovedObj" << endl;
	}

	// copy ctor
	MyMovedObj(const MyMovedObj& other) : MyMovedObj(*(other.m_pInt))
	{	
		cout << "MyMovedObj::MyMovedObj (copy) - copied other.m_pInt value:" << *(other.m_pInt) << " into the new object's address:" << m_pInt << endl;
	}

	// copy assignment operator
	MyMovedObj& operator=(const MyMovedObj& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		
		delete this->m_pInt;	
		this->m_pInt = new int(*(rhs.m_pInt));
		cout << "MyMovedObj::operator= - assgined the value:" << *(rhs.m_pInt) << endl;
		return *this;	
	}

	// move ctor
	MyMovedObj(MyMovedObj&& rRef)
	{
		cout <<"MyMovedObj::MyMovedObj (move ctor&&)" << endl;
		this->m_pInt = rRef.m_pInt;
		rRef.m_pInt = nullptr;
	}

	// move assignment operator
	MyMovedObj& operator=(MyMovedObj&& rRef)
	{
		cout << "MyMovedObj::operator=" << endl;	
		if (&rRef == this)
		{
			return *this;
		}

		delete this->m_pInt;
		this->m_pInt = rRef.m_pInt;
		rRef.m_pInt = nullptr;
		return *this;
	}

	void SetValue(int val)
	{
		if (m_pInt != nullptr)
		{
			*m_pInt = val;
		}
	}

	int GetValue() const
	{
		return *m_pInt;
	}

	friend ostream& operator<<(ostream& out, const MyMovedObj& obj);

private:
	int* m_pInt;

};

 
ostream& operator<<(ostream& out, const MyMovedObj& obj)
{
	// Since operator<< is a friend of the Point class, we can access Point's members directly.
	if (obj.m_pInt != nullptr)
	{
		cout << "MyMovedObj(" << *obj.m_pInt << ", address:" << &obj << ")" << endl;
	}    

    return out;
}
