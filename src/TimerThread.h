 ///
 /// @file    TimerThread.h
 /// @author  heartinharbin
 /// @date    2017-05-16 16:26:08
 ///

#ifndef __WD_TIMERTHREAD_H__
#define __WD_TIMERTHREAD_H__

#include "Timer.h"
#include "Thread.h"

#include <iostream>
#include <functional>
using std::cout;
using std::endl;

namespace wd{

class TimerThread{
public:
	typedef std::function<void()> TimerCallback;
	TimerThread(int initTime, int intervalTime, TimerCallback cb);

	void start();
	void stop();
private:
	Timer _timer;
	Thread _thread;
};//end of class TimerThread



}//end of namespace wd

#endif
