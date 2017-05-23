 ///
 /// @file    Timer.h
 /// @author  heartinharbin
 /// @date    2017-05-16 12:08:30
 ///

#ifndef __WD_TIMER_H__
#define __WD_TIMER_H__

#include "Noncopyable.h"
#include <functional>

namespace wd{

class Timer
: Noncopyable{
public:
	typedef std::function<void()> TimerCallback;

	Timer(int initTime, int intervalTime, TimerCallback cb);
	~Timer();

	void start();
	void stop();


private:
	int createTimerfd();
	void setTimerfd(int initTime, int intervalTime);
	void handleRead();

private:
	int _fd;
	int _initTime;
	int _intervalTime;
	bool _isStarted;
	TimerCallback _cb;
};//end of class Timer


}//end of namespace 

#endif
