 ///
 /// @file    Threadpool.cc
 /// @author  heartinharbin
 /// @date    2017-05-13 14:39:18
 ///

#include "Threadpool.h"
//#include "MyTask.h"
#include "Thread.h"
#include <unistd.h>
#include <iostream>
#include <functional>

using std::cout;
using std::endl;

namespace wd{

Threadpool::Threadpool(size_t buffsize, size_t threadNum)
: _buffsize(buffsize)
, _threadNum(threadNum)
, _buffer(_buffsize)
, _isExit(false){}

Threadpool::~Threadpool(){
	if(!_isExit){
		stop();
	}
}

void Threadpool::start(){
	for(size_t idx = 0; idx != _threadNum; ++idx){
		shared_ptr<Thread> sp(new Thread(std::bind(&Threadpool::threadFunc, this)));
		_threads.push_back(sp);
		sp->start();
	}
}

void Threadpool::stop(){
	cout << "Threadpool::stop()" << endl;
	if(!_isExit){
		while(!_buffer.empty()){
			sleep(1);
		}
		
		_isExit = true;
		_buffer.wakeup();

		for(auto & elem : _threads){
			elem->join();
		}

	}
}

void Threadpool::addTask(Task task){
	_buffer.push(task);
}

Task Threadpool::getTask(){
	return _buffer.pop();
}

void Threadpool::threadFunc(){
	while(!_isExit){
		Task task = getTask();
		if(task)
			task();
	}	
}


}//end of namespace wd
