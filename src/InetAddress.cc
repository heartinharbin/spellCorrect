 ///
 /// @file    InetAddress.cc
 /// @author  heartinharbin
 /// @date    2017-05-15 16:34:38
 ///

#include "InetAddress.h"
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

namespace wd{

InetAddress::InetAddress(short port){
	::memset(&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;
}

InetAddress::InetAddress(const char *pIp, short port){
	::memset(&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = inet_addr(pIp);
}

InetAddress::InetAddress(const struct sockaddr_in &addr)
: _addr(addr){}

const struct sockaddr_in * InetAddress::getSockAddrPtr() const{
	return &_addr;
}

std::string InetAddress::ip() const{
	return std::string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port() const{
	return ntohs(_addr.sin_port);
}

}//end of namespace wd
