 ///
 /// @file    Socket.h
 /// @author  heartinharbin
 /// @date    2017-05-15 17:50:05
 ///

#ifndef __WD_SOCKET_H__
#define __WD_SOCKET_H__

#include "Noncopyable.h"

namespace wd{

class InetAddress;

class Socket : Noncopyable{
public:
	Socket(int sockfd);
	Socket();
	~Socket();

	void shutdownWrite();
	int fd() const { return _sockfd; }

	void nonblock();

	static InetAddress getLocalAddr(int sockfd);
	static InetAddress getPeerAddr(int sockfd);
private:
	int _sockfd;

};//end of class Socket


}//end of namespace wd

#endif
