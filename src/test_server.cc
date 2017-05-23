///
/// @file    test_server.cc
/// @author  heartinharbin
/// @date    2017-05-16 00:29:22
///

#if 0

#include "TcpServer.h"
#include "TcpConnection.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;


class Task{
public:
	void execute(){
		//conn->sendInLoop(msg);
	}
private:
	TcpConnectionPtr conn;
	string query;
};



void onConnection(const wd::TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
	conn->send("hello, welcome to Chat Server.\r\n");
}

void onMessage(const wd::TcpConnectionPtr &conn)
{
	std::string s(conn->receive());
	
	Task task(s, conn);

	threadpool.addTask(task);
}

void onClose(const wd::TcpConnectionPtr &conn)
{
	printf("%s close\n", conn->toString().c_str());
}

#endif

#define _LOG4CPP_

#include "MyLog.h"
#include "SpellCorrectServer.h"
#include "TimerThread.h"
#include <iostream>

using std::cout;
using std::endl;

void makeup(){
	::srand(::time(NULL));
	int number = ::rand() % 100;
	cout << "number = " << number << endl;
}

int main(int argc, const char *argv[])
{
	//timer 和  server颠倒顺序后不能成长运行
	wd::TimerThread timer(3, 6, &makeup);	
	timer.start();

	wd::SpellCorrectServer scs;
	scs.start();
		
	scs.stop();

	return 0;
}


