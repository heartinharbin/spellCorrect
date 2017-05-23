 ///
 /// @file    Threadpool.h
 /// @author  heartinharbin
 /// @date    2017-05-13 14:30:45
 ///

#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__

#include "Buffer.h"
#include <iostream>
#include <vector>
#include <memory>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;



namespace wd{

class ThreadpoolThread;
class Thread;
class Threadpool{
	friend ThreadpoolThread;
public:
	typedef std::function<void()> Task;

	Threadpool(size_t buffsize, size_t threadNum);
	~Threadpool();

	void addTask(Task );
	void start();
	void stop();

private:
	Task getTask();
	void threadFunc();
private:
	size_t _buffsize;
	size_t _threadNum;
	vector<shared_ptr<Thread> > _threads;
	Buffer _buffer;
	bool _isExit;
};//end of class Threadpool

}//end of namespace wd

#endif
