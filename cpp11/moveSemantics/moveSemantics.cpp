// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 
// 1) r-value and l-value:
// -----------------------
// a) Generally speaking, l-value is every object in C++ that has a memory address assigned to. for instance: int x = 4; here x reside somewhere in memory.
// b) On the "complementary hand" - an r-value is everything which is not an l-value. Most of the times we will refer to literals (3), temporary expressions (x + 2) or
//    anonymous objects (MyClass(17)). 
// A key point to note here is the lifetime of each one of them.
// l-value: This is the more "intuitive" case - it is simply the scope of the object (variable).
// r-value: Usually it will be the lifetime of the expression that this r-value is defined in --> meaning, once the expression is done, the r-value is destroyed.

// 2) r-value reference:
// ---------------------
// a) C++11 introduces this new concept. The main purpose of this "new" value type for r-value is to have the capability to "expand" the life time of an 
//    "ordinary" r-value --> instead of having the "expression" lifetime, it has the r-value reference lifetime. 
// b) it is defined using a double ampersand like so (int&& rRef).It is most useful when we wish to use move semantics (instead of copy semantics).
// c) Usually, in the case of a "normal" temporary object assignment, the temporary object will be destructed once the expression in which it is created is done.
//    With r-value reference this is NOT the case. The r-value reference EXPANDS the lifetime of the temporary object untill the r-value reference itself goes 
//    out of scope. 

// 3) copy semantics Vs. move semantics:
// -------------------------------------
// a) The default behavior of creating objects in C++ is using the copy semantics. It means that for every object we pass (or return) by value we create an
//    additional copy along with the already existing object. Sometimes it is useful or a must , yet sometimes it is redundant.
// b) move semantics on the other hand, simply "transfers" the resources from one object to another - WITHOUT making a copy of the original object (that initially
//    held the resources). 
//
// 4) move constructor and move assignment operator:
// -------------------------------------------------
// a) In contrast to theier counterpart copy ctor and copy assignment operator:
//    # they will NOT create an additional instance of the object that is copied/assigned,
//    YET they will "transfer" the ownership of the resources of the "original" object to the "new" owner. This reduces the need to CREATE (construct) an additional
//    instance - which reduces both run-time and memory usage. 
//    # they will NOT be generated automatically by the complier unless there are some set of rules that apply (most likely they wont).
// b) When are the move constructor and move assignment called? 
//    # those functions have been defined, and 
//    # the argument for construction or assignment is an r-value. Most typically, this r-value will be a literal or temporary value.
//    Rule: If you want a move constructor and move assignment that do moves, you’ll need to write them yourself.
// c) Side Note: Sometimes, if we wish to return an object by value from a function, we can simply use a "regular" return statment of the local function's variable.
//    This is the best practice, cause we simply allowing the compiler to perfomr the famous RVO optimization that does not include copying NOR moving the object.
// 
// 5) std::move
// ------------
// a) In order to be able to send (or receive) arguments as r-value reference we need to explicitly tell the compiler to do so.
//    # First, offcourse, we need to define the argument (for a function for instance) as an r-value reference.
//    # Second, upon invoking this function, we must PROVIDE it an r-value reference. We can achieve that using the std::move method that will "convert" (cast )the sent
//      argument to be r-value reference.  
// b) So, in short, std::move enables us to use l-values as r-values , for instance, when sending an object to a function, therefore invoking the move semantics instead
//    of the copy semantics. 
// c) Note that since C++11, we can simply use vec.emplace_back - which does the move semantics for us, so a good practice will be to ALWAYS insert elements to a
//    std::vector using emplace_back() !!
//
// 6) Motivation to use std::move:
// -------------------------------
// The situations in which it will be usefull to use std::move (or move semantics) are the following (but not only):
// a) We wish to transfer ownership of an std::uniuqe_ptr, which in its implementation, has the move semantics capabilities.It, by its definition, does NOT have copy
//    semantics (this is why it is unique in the first place).
// b) We wish to initialize a STL container with objects that are temporary and/or we do not care that after the initialization they will not be valid anymore.
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <utility>	// for std::move
#include <thread>

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
 


// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================

void simpleRValueRefExample()
{
	cout << "simpleRValueRefExample - start" << endl;
	MyMovedObj&& rvalRef = MyMovedObj(12);			// 2c)
	cout << "simpleRValueRefExample - end" << endl;
}

void workerThreadFunc(MyMovedObj&& obj)
{
	cout << "workerThreadFunc - start, thread ID is:" << this_thread::get_id() << endl;
	cout << "workerThreadFunc - got object with value:" << obj.GetValue() << endl;
	cout << "workerThreadFunc - end, thread ID is:" << this_thread::get_id() << endl;
}

void movingObjectToStdThread()
{
	cout << "movingObjectToStdThread - start" << endl;
	MyMovedObj obj(15);
	thread th1(workerThreadFunc, move(obj));
	th1.join();
	cout << "movingObjectToStdThread - end" << endl;
}

void simpleMoveToAnotherFunction()
{
	cout << "simpleMoveToAnotherFunction - start, thread ID is:" << this_thread::get_id() << endl;
	workerThreadFunc(move(MyMovedObj(9)));
	cout << "simpleMoveToAnotherFunction - end, thread ID is:" << this_thread::get_id() << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	cout << "\n \n \n \n" << endl;	
	simpleMoveToAnotherFunction();
	cout << "\n \n \n \n" << endl; 
	movingObjectToStdThread();
	cout << "\n \n \n \n" << endl; 
	simpleRValueRefExample();
	cout << "\n \n \n \n" << endl; 
	cout << "main - back from simpleRValueRefExample" << endl;
	
	MyMovedObj obj(12);
	vector<MyMovedObj> vec;

	// this insertion will invoke the copy ctor - cause obj is refered to as an l-value
	vec.push_back(obj);

	cout <<"main - after pushing obj via copy semantics obj is:" << obj << endl;	

	// this insertion will invoke the move ctor - cause std::move will cast obj to an r-value
	vec.push_back(move(obj)); // 4c)

	cout <<"main - after pushing obj via move semantics obj is:" << obj << endl;	

	cout <<"main - vec[0]:" << vec[0] << " vec[1]:" << vec[1] << endl;
	return 0;
}

