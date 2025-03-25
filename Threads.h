#pragma once
#include <semaphore>
#include <thread>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

class Threads
{
public:
	Threads();
	void thread1();
	void thread2();
	void releaseEvent();
	std::string getSharedTxt();

private:
	bool theEnd;
	int pageCount;
	int pageTotal;
	int lineCount;
	std::string fileTxt;
	std::string fileName;
	std::string sharedTxt;

	std::binary_semaphore
		readThread{ 1 },
		writeThread{ 0 };
};

