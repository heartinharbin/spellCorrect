 ///
 /// @file    TimerThread.cc
 /// @author  heartinharbin
 /// @date    2017-05-16 16:29:40
 ///

#include "TimerThread.h"
#include <iostream>


using std::cout;
using std::endl;


namespace wd{

TimerThread::TimerThread(int initTime, int intervalTime, TimerCallback cb)
: _timer(initTime, intervalTime, cb)
, _thread(std::bind(&Timer::start, &_timer)){
}

void TimerThread::start(){
	_thread.start();
}

void TimerThread::stop(){
	cout << "TimerThread::stop()" << endl;
	_timer.stop();
	_thread.join();
}


}//end of namespace wd
