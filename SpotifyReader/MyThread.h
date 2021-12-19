#pragma once
#include <thread>


class MyThread {
public:
	MyThread();
	~MyThread();
	static MyThread* Current();
	void Start();
	void Stop();
	void Restart();
private:
	static MyThread* _instance;
	std::thread thread;
};
