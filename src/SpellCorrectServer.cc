 ///
 /// @file    SpellCorrectServer.cc
 /// @author  heartinharbin
 /// @date    2017-05-22 21:58:40
 ///

#include "SpellCorrectServer.h"
#include "MyTask.h"

#include <unistd.h>
#include <iostream>

#include <functional>

using std::cout;
namespace wd{

void whatare(){
	::srand(::time(NULL));
	int number = ::rand() % 100;
	cout << "produce a number:" << number << endl;
	sleep(1);
}

void SpellCorrectServer::onConnection(const TcpConnectionPtr & conn){
	printf("%s has connected!\n", conn->toString().c_str());
	conn->send("welcome to server\n");
}

void SpellCorrectServer::onMessage(const TcpConnectionPtr & conn){
	std::string s(conn->receive());	
	MyTask task(s, conn);
	_threadpool.addTask(std::bind(&MyTask::execute, &task));
}

void SpellCorrectServer::onClose(const TcpConnectionPtr & conn){
	printf("%s close\n", conn->toString().c_str());	
}

void SpellCorrectServer::start(){

	_threadpool.start();
	/*
	size_t cnt = 20;
	while(cnt--){
		_threadpool.addTask(&whatare);
	}
	*/
	_tcpserver.setMessageCallback(std::bind(&SpellCorrectServer::onMessage, this, std::placeholders::_1));
	_tcpserver.setConnectionCallback(std::bind(&SpellCorrectServer::onConnection, this, std::placeholders::_1));
//	_tcpserver.setMessageCallback(std::bind(&onMessage, std::placeholders::_1, std::ref(_threadpool)));
	_tcpserver.setCloseCallback(std::bind(&SpellCorrectServer::onClose, this, std::placeholders::_1));

	_tcpserver.start();
}

void SpellCorrectServer::stop(){
	cout << "SpellCorrectServer::stop()" << endl;
	_tcpserver.stop();
	_threadpool.stop();
}


}//end of namespace wd
