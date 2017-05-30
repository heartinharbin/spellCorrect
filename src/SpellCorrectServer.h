 ///
 /// @file    SpellCorrectServer.h
 /// @author  heartinharbin
 /// @date    2017-05-22 21:50:33
 ///


#ifndef __WD_SPELLCORRECTSERVER_H__
#define __WD_SPELLCORRECTSERVER_H__

#include "TcpServer.h"
#include "Threadpool.h"

namespace wd{

class SpellCorrectServer{

public:

	SpellCorrectServer()
	: _threadpool(10, 4)
	, _tcpserver("192.168.74.129", 9999)
	{} 
//	friend void onMessage(const TcpConnectionPtr & conn, Threadpoll & tp);  //友元函数实现
	void onConnection(const TcpConnectionPtr & conn);
	void onMessage(const TcpConnectionPtr & conn);
	void onClose(const TcpConnectionPtr & conn);

	void start();
	void stop();

private:
	Threadpool _threadpool;
	TcpServer _tcpserver;
};//end of class SpellCorrectServer


}//end of namespace wd

#endif
