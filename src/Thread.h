 ///
 /// @file    Thread.h
 /// @author  heartinharbin
 /// @date    2017-05-12 23:53:22
 ///

#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

namespace wd{

namespace currend_thread{
	extern __thread int a;
}


class Thread
: Noncopyable{
public:
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback cb);
	~Thread();

	pthread_t getThreadid() const{
		return _pthId;
	}

	bool isRunning() const{
		return _isRunning;
	}

//	virtual void run() = 0;
	void start();
	void join();

private:
	static void * threadFunc(void *);
private:
	pthread_t _pthId;
	bool _isRunning;
	ThreadCallback _cb;
};//end of class Thread


}//end of namespace wd

#endif
