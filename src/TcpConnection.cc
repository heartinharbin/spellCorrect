 ///
 /// @file    TcpConnection.cc
 /// @author  heartinharbin
 /// @date    2017-05-15 23:16:44
 ///

#include "TcpConnection.h"
#include "EpollPoller.h"
#include <string.h>
#include <stdio.h>

namespace wd{

TcpConnection::TcpConnection(int sockfd, EpollPoller * loop)
: _sockfd(sockfd)
, _sockIO(sockfd)
, _localAddr(wd::Socket::getLocalAddr(sockfd))
, _peerAddr(wd::Socket::getPeerAddr(sockfd))
, _isShutdownWrite(false)
, _loop(loop){
	_sockfd.nonblock();
}

TcpConnection::~TcpConnection(){
	if(!_isShutdownWrite){
		_isShutdownWrite = true;
		shutdown();
	}
	printf("~TcpConnection()\n");
}

std::string TcpConnection::receive(){
	char buf[65536];
	memset(buf, 0, sizeof(buf));
	size_t ret = _sockIO.readline(buf , sizeof(buf));
	if(0 == ret){
		return std::string();
	}else{
		return std::string(buf);
	}
}

void TcpConnection::send(const std::string & msg){
	_sockIO.writen(msg.c_str(), msg.size());
}

void TcpConnection::sendAndClose(const std::string & msg){
	send(msg);
	shutdown();
}

void TcpConnection::sendInLoop(const std::string & msg){
	_loop->runInloop(std::bind(&TcpConnection::sendAndClose, this, msg));
}

void TcpConnection::shutdown(){
	if(!_isShutdownWrite)
		_sockfd.shutdownWrite();
	_isShutdownWrite = true;
}

std::string TcpConnection::toString(){
	char str[100];
	snprintf(str, sizeof(str), "%s:%d -> %s:%d",
			_localAddr.ip().c_str(),
			_localAddr.port(),
			_peerAddr.ip().c_str(),
			_peerAddr.port());
	return std::string(str);
}

void TcpConnection::setConnectionCallback(TcpConnectionCallback cb){
	_onConnectionCb = cb;
}

void TcpConnection::setMessageCallback(TcpConnectionCallback cb){
	_onMessageCb = cb;
}

void TcpConnection::setCloseCallback(TcpConnectionCallback cb){
	_onCloseCb = cb;
}

void TcpConnection::handleConnectionCallback(){
	if(_onConnectionCb)
		_onConnectionCb(shared_from_this());
}

void TcpConnection::handleMessageCallback(){
	if(_onMessageCb)
		_onMessageCb(shared_from_this());
}

void TcpConnection::handleCloseCallback(){
	if(_onCloseCb)
		_onCloseCb(shared_from_this());
}

}//end of namespace wd
