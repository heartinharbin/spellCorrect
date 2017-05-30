///
/// @file    TcpServer.cc
/// @author  heartinharbin
/// @date    2017-05-16 00:28:15
///


#include "TcpServer.h"
#include "InetAddress.h"
#include "SocketUtil.h"
#include <iostream>
using std::cout;
using std::endl;


namespace wd
{
TcpServer::TcpServer(const char * pIp, unsigned short port)
: _acceptor(createSocketFd(), InetAddress(pIp, port))
, _epollfd(_acceptor)
{
	_acceptor.ready();
}

TcpServer::TcpServer(unsigned short port)
: _acceptor(createSocketFd(), InetAddress(port))
, _epollfd(_acceptor){
	_acceptor.ready();
}

void TcpServer::start()
{
	_epollfd.loop();
}

void TcpServer::stop()
{
	_epollfd.unloop();
}

void TcpServer::setConnectionCallback(TcpServerCallback cb)
{	_epollfd.setConnectionCallback(cb);	}
void TcpServer::setMessageCallback(TcpServerCallback cb)
{	_epollfd.setMessageCallback(cb);	}
void TcpServer::setCloseCallback(TcpServerCallback cb)
{	_epollfd.setCloseCallback(cb);	}

}//end of namespace wd
