// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 
// std::unique_ptr - my implementation
// -----------------------------------
// This short example I will (almost complelty) will immidate the way that the C++11 std::unique_ptr is implementated - for educational purposes.
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>
#include <utility>	// for std::move

using namespace std;

template <typename T>
class MyUniquePtr
{
public:
	MyUniquePtr(T* ptr)
		: m_ptr(ptr)
	{
		cout << "MyUniquePtr::MyUniquePtr - assgined the inner pointer with raw pointer with address of:" << m_ptr << endl;
	}

	~MyUniquePtr()
	{
		delete m_ptr;
		cout << "MyUniquePtr::~MyUniquePtr - deleted the inner pointer with address of:" << m_ptr << endl;
	}

	// do not allow to copy it
	MyUniquePtr(const MyUniquePtr& other) = delete;
	MyUniquePtr& operator=(const MyUniquePtr& rhs) = delete;

	// move ctor
	MyUniquePtr(MyUniquePtr&& other)
	{	
		cout << "MyUniquePtr::MyUniquePtr(move ctor)" << endl;
		this->m_ptr = other.m_ptr;	 
		other.m_ptr = nullptr;
	}

	// move assignment operator
	MyUniquePtr& operator=(MyUniquePtr&& rhs)
	{
		cout << "MyUniquePtr::operator=(move assgin)" << endl;
		if (rhs == *this)
		{
			return *this;
		}

		delete this->m_ptr;
		this->m_ptr = rhs.m_ptr;
		rhs.m_ptr = nullptr;
		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }

private:
	T* m_ptr;

};

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================



int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	cout << "main - end" << endl;
	return 0;
}
