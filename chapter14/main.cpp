// ===================================================================================================================================================================
// ===================================================================================================================================================================
// RAII wrapper for std::exception class:
// --------------------------------------
// In this sample we can see the use case where after an StdThreadRaiiWrapper has been created on the "main stack", yet not neccessarly finished to run its
// function AND while an exception is thrown from the main program (thread) --> the StdThreadRaiiWrapper is still being "cleaned up" properly, due to the fact 
// that in its destructor we join it with its "parent thread" (in this case the main thread).
//
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>

#include "stdThreadRaiiWrapper.h"

using namespace std;

void workerThreadWhileLoopThatThrowsException()
{
	cout << "workerThreadWhileLoopThatThrowsException" << endl;
	size_t numOfSecToWorkUntillExceptionIsThrown = 2;
	size_t numSecPassed = 0;

	while (true)
	{
		cout << "workerThreadWhileLoopThatThrowsException - in iteration:" << ++numSecPassed << endl;
		this_thread::sleep_for((chrono::seconds(1)));
		if (numSecPassed == numOfSecToWorkUntillExceptionIsThrown)
		{
			return;
		}
	}

	cout << "workerThreadWhileLoopThatThrowsException - end" << endl;
}


int main(int argc, char** argv)
{
	cout << "main - start thread ID:" << this_thread::get_id() << endl;
	try
	{
		StdThreadRaiiWrapper workerThread1(thread(workerThreadWhileLoopThatThrowsException), &thread::join);
		cout << "main - after creating the StdThreadRaiiWrapper on the main stack" << endl; 	
		string msg("throwing from main");
		throw runtime_error(msg);

		// should not get here at all...		
		cout << "main - after throwing runtime_error with message:" << msg << endl; 	
	}	
	catch (const exception& e)
	{
		cout << "main - caught an std::exception, e.what:" << e.what() << endl;
	}

	cout << "main - end" << endl;
	return 0;
}
