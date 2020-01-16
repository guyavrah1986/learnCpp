#include <iostream>
#include <glog/logging.h>
#include <thread>
#include <unistd.h>

using namespace std;

void rcpd_thread(size_t buffSize)
{
	char* buff = new char[buffSize];
	LOG(INFO) << "rcpd_thread - allocated " << buffSize << " bytes";
	unsigned int numSecToSleep = 5;
	while (true)
	{
		sleep(numSecToSleep);
		LOG(INFO) << "rcpd_thread - hey there";
	}
}

int main(int argc, char** argv)
{
	cout << "main - start, got log folder:" << argv[1] << endl;

   	// this flag should be set before google::InitGoogleLogging
	const char* logDir = argv[1];
   	FLAGS_log_dir = logDir; //"/tmp/guyaLogs/";
	google::InitGoogleLogging(logDir);

	size_t buffSize = 1024;
	thread rcpdThread(rcpd_thread, buffSize);
	rcpdThread.join();

	LOG(INFO) << "main - end";
}
