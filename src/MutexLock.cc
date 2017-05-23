 ///
 /// @file    MutexLock.cc
 /// @author  heartinharbin
 /// @date    2017-05-22 19:51:48
 ///

#include "MutexLock.h"
#include <iostream>

using std::cout;
using std::endl;

namespace wd{

MutexLock::MutexLock(){
	pthread_mutex_init(&_mutex, NULL);
}

MutexLock::~MutexLock(){
	pthread_mutex_destroy(&_mutex);
}

void MutexLock::lock(){
	pthread_mutex_lock(&_mutex);
}

void MutexLock::unlock(){
	pthread_mutex_unlock(&_mutex);
}

pthread_mutex_t * MutexLock::getMutexLockPtr(){
	return &_mutex;
}

}//end of namespace wd
