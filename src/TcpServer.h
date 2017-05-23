///
/// @file    TcpServer.h
/// @author  heartinharbin
/// @date    2017-05-16 00:26:42
///

#ifndef __WD_TCPSERVER_H__
#define __WD_TCPSERVER_H__

#include "InetAddress.h"
#include "Acceptor.h"
#include "EpollPoller.h"
#include <string>

using std::string;

namespace wd
{


class TcpServer
{
public:
	typedef TcpConnection::TcpConnectionCallback TcpServerCallback;
	TcpServer(const char * pIp, unsigned short port);
	TcpServer(unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);
private:
	Acceptor _acceptor;
	EpollPoller _epollfd;

	TcpServerCallback _connectionCb;
	TcpServerCallback _messageCb;
	TcpServerCallback _closeCb;
};


}//end of namespace wd

#endif

