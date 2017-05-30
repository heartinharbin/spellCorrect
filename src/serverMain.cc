///
/// @file    test_server.cc
/// @author  heartinharbin
/// @date    2017-05-16 00:29:22
///

#include "CacheManger.h"
#include "MyLog.h"
#include "SpellCorrectServer.h"
#include "TimerThread.h"

#include <signal.h>

#include <iostream>

using std::cout;
using std::endl;

namespace wd{

void timeTask(){
	/*
	::srand(::time(NULL));
	int number = ::rand() % 100;
	cout << "number = " << number << endl;
	*/
	cout << "timeTask()" << endl;
	CacheManger::getInstance()->periodicUpdate();
}

}//end of namespace wd


//修改此处  打开 运行在线main
#if 1
int main(int argc, const char *argv[])
{
	//timer 和  server颠倒顺序后不能成长运行
	signal(SIGPIPE, SIG_IGN);	
	wd::CacheManger::getInstance()->init();
	wd::TimerThread timer(3, 30, &wd::timeTask);	
	timer.start();

	wd::SpellCorrectServer scs;
	scs.start();
		
	scs.stop();

	return 0;
}

#endif
