 ///
 /// @file    Timer.cc
 /// @author  heartinharbin
 /// @date    2017-05-16 12:13:28
 ///


#include "Timer.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <poll.h>
#include <sys/timerfd.h>

#include <iostream>
using std::cout;
using std::endl;


namespace wd{

Timer::Timer(int initTime, int intervalTime, TimerCallback cb)
: _fd(createTimerfd())
, _initTime(initTime)
, _intervalTime(intervalTime)
, _isStarted(false)
, _cb(cb){}

Timer::~Timer(){
	if(_isStarted)
		stop();
}

void Timer::start(){
	_isStarted = true;
	setTimerfd(_initTime, _intervalTime);

	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;
	int nready;
	while(_isStarted){
		nready = poll(&pfd, 1, 5000);
		if(nready == -1){
			if(errno == EINTR)
				continue;
			perror("poll error");
			return;
		}else if(nready == 0){
			cout << "> poll timeout!" << endl;
		}else{
			if(pfd.fd == _fd && (pfd.revents & POLLIN)){
				handleRead();
				if(_cb)
					_cb();
			}
		}
	}
}

void Timer::stop(){
	if(_isStarted){
		setTimerfd(0, 0);
		_isStarted = false;
		cout << "Timer::stop()" << endl;
		return;
	}
	cout << "Timer::stop()2222" << endl;
}

int Timer::createTimerfd(){
	int fd = timerfd_create(CLOCK_REALTIME, 0);
	if(-1 == fd){
		perror("timerfd_create error!");
	}
	return fd;
}

void Timer::setTimerfd(int initTime, int intervalTime){
	struct itimerspec value;
	value.it_value.tv_sec = initTime;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = intervalTime;
	value.it_interval.tv_nsec = 0;

	int ret = timerfd_settime(_fd, 0, &value, NULL);
	if(ret == -1){
		perror("timerfd_settime error!");
	}
}

void Timer::handleRead(){
	uint64_t howmany;
	int ret = read(_fd, &howmany, sizeof(howmany));
	if(ret != sizeof(howmany)){
		perror("read error");
	}
}





}//end of namespace wd
