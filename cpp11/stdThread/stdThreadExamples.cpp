// ===================================================================================================================================
// ===================================================================================================================================
// 
//
//
// ===================================================================================================================================
// ===================================================================================================================================
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include "myMovedObj.h"

using namespace std;

class SharedObj
{
public:
	SharedObj()
		: m_val(0)
	{
		cout << "SharedObj::SharedObj - setting m_val to:" << m_val << endl;	
	}

	~SharedObj()
	{
		cout << "SharedObj::~SharedObj" << endl;	
	}

	int GetVal() const
	{
		return this->m_val;
	}

	void UpdateVal()
	{
		lock_guard<mutex> localLock(m_mutex);
		cout << "UpdateVal - thread ID is:" << this_thread::get_id() << endl;
		++m_val;
	}

private:
	int m_val;
	mutex m_mutex;
};

void workerThreadFuncArgsByVal(int x, string str)
{
	cout << "workerThreadFuncArgsByVal - thread ID is:" << this_thread::get_id() << endl;
	cout << "workerThreadFuncArgsByVal - x is:" << x << " str is:" << str << endl;
	str = "new_string";
	x = 10;
}

void workerThreadFuncArgsByConstRef(const int& x, const string& str)
{
	cout << "workerThreadFuncArgsByRef - thread ID is:" << this_thread::get_id() << endl;
	cout << "workerThreadFuncArgsByRef - got x is:" << x << " str is:" << str << endl;
	int& y = const_cast<int&>(x);
	y++;	
	string& strRef = const_cast<string&>(str);
	strRef = "new_str";
	cout << "workerThreadFuncArgsByRef - set x to:" << x << " str to:" << str << endl;
}

void workerThreadFuncArgsByRef(int& x, string& str)
{
	cout << "workerThreadFuncArgsByRef - thread ID is:" << this_thread::get_id() << endl;
	cout << "workerThreadFuncArgsByRef - got x is:" << x << " str is:" << str << endl;
	x = 10;
	str = "new_string";
	cout << "workerThreadFuncArgsByRef - set x to:" << x << " str to:" << str << endl;
}

void illustrateUsageOfLockGuard()
{	
	size_t numOfWorkerThreads = 5;
	cout << "illustrateUsageOfLockGuard - starting " <<  numOfWorkerThreads << " threads" << endl;
	vector<thread> threads;
	threads.reserve(numOfWorkerThreads);	
	SharedObj obj;
	for (size_t i = 0; i < numOfWorkerThreads; ++i)
	{
		threads.emplace_back(thread(&SharedObj::UpdateVal, &obj));
	}

	for (size_t i = 0; i < numOfWorkerThreads; ++i)
	{
		threads[i].join();
	}

	cout << "illustrateUsageOfLockGuard - done joining " <<  numOfWorkerThreads << " threads, obj.m_val is:" << obj.GetVal() << endl;
}

// ===================================================================================================================================
// ===================================================================================================================================

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	string str = "main_str";	
	int x = 9;
	cout << "main - BEFORE calling workerThreadFuncArgsByVal" << endl;
	thread th1(workerThreadFuncArgsByVal,x, str);
	th1.join();
	cout << "main - AFTER calling workerThreadFuncArgsByVal, x is:" << x << " str is:" << str << endl;
	cout << "\n \n \n" << endl;

	cout << "main - BEFORE calling workerThreadFuncArgsByConstRef" << endl;
	thread th2(workerThreadFuncArgsByConstRef, x, str);
	th2.join();
	cout << "main - AFTER calling workerThreadFuncArgsByConstRef, x is:" << x << " str is:" << str << endl;
	cout << "\n \n \n" << endl;

	cout << "main - BEFORE calling workerThreadFuncArgsByConstRef(with std::ref(arg))" << endl;
	thread th3(workerThreadFuncArgsByConstRef, ref(x), ref(str));
	th3.join();
	cout << "main - AFTER calling workerThreadFuncArgsByConstRef, x is:" << x << " str is:" << str << endl;
	cout << "\n \n \n" << endl;
	
	cout << "main - BEFORE calling workerThreadFuncArgsByRef(with std::ref(arg))" << endl;
	thread th4(workerThreadFuncArgsByRef, ref(x), ref(str));
	th4.join();
	cout << "main - AFTER calling workerThreadFuncArgsByRef, x is:" << x << " str is:" << str << endl;
	cout << "\n \n \n" << endl;

	cout << "main - BEFORE calling workerThreadFuncArgsByRef" << endl;
	thread th5(workerThreadFuncArgsByRef, ref(x), ref(str));
	th5.join();
	cout << "main - AFTER calling workerThreadFuncArgsByRef, x is:" << x << " str is:" << str << endl;
	cout << "\n \n \n" << endl;

	MyMovedObj obj(12);
	cout << "main - BEFORE calling MyMovedObj::SetValue" << obj << endl;
	thread th6(&MyMovedObj::SetValue, &obj, 17);
	th6.join();
	cout << "main - AFTER calling MyMovedObj::SetValue" << obj << endl;

	cout << "main - calling illustrateUsageOfLockGuard" << endl;
	illustrateUsageOfLockGuard();

	cout << "main - end" << endl;
	return 0;
}
