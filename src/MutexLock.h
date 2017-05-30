 ///
 /// @file    MutexLock.h
 /// @author  heartinharbin
 /// @date    2017-05-22 19:45:26
 ///

#ifndef __WD_MUTEXLOCK_H__
#define __WD_MUTEXLOCK_H__

#include "Noncopyable.h"
#include <pthread.h>

namespace wd{

class MutexLock
: Noncopyable{
public:
	MutexLock();
	~MutexLock();

	pthread_mutex_t * getMutexLockPtr();

	void lock();
	void unlock();
private:
	pthread_mutex_t _mutex;
};//end of class MutexLock

class MutexLockGuard{
public:
	MutexLockGuard(MutexLock & mutex)
	: _mutex(mutex){
		_mutex.lock();
	}

	~MutexLockGuard(){
		_mutex.unlock();
	}
private:
	MutexLock & _mutex;
};//end of class MutexLockGuard

}//end of namespace wd


#endif
