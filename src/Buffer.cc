 ///
 /// @file    Buffer.cc
 /// @author  heartinharbin
 /// @date    2017-05-13 00:13:34
 ///

#include "Buffer.h"

namespace wd{

Buffer::Buffer(size_t sz)
: _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
, _sz(sz)
, _flag(true){}

bool Buffer::full(){
	return _sz == _que.size();
}

bool Buffer::empty(){
	return _que.empty();
}

void Buffer::push(const ElemType & elem){
	MutexLockGuard guard(_mutex);
	while(full()){
		_notFull.wait();
	}
	_que.push(elem);
	_notEmpty.notify();
}

ElemType Buffer::pop(){
	MutexLockGuard guard(_mutex);
	while(_flag && empty()){
		_notEmpty.wait();
	}
	if(_flag){
		ElemType tmp = _que.front();
		_que.pop();
		_notFull.notify();
		return tmp;
	}else{
		return NULL;//此处的逻辑
	}
}

void Buffer::wakeup(){
	_flag = false;
	_notEmpty.notifyall();
}


}//end of namespace wd
