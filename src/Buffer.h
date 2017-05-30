 ///
 /// @file    Buffer.h
 /// @author  heartinharbin
 /// @date    2017-05-13 00:09:26
 ///

#ifndef __WD_BUFFER_H__
#define __WD_BUFFER_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>

using std::queue;

namespace wd{

typedef std::function<void()> Task;
typedef Task ElemType;

class Buffer{
public:
	Buffer(size_t sz);

	bool full();
	bool empty();
	void push(const ElemType &);
	ElemType pop();

	void wakeup();

private:
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
	size_t _sz;
	queue<ElemType> _que;
	bool _flag;
};//end of class Buffer

}//end of namespace wd

#endif
