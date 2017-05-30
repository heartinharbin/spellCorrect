 ///
 /// @file    Acceptor.h
 /// @author  heartinharbin
 /// @date    2017-05-15 22:46:55
 ///

#ifndef __WD_ACCEPTOR_H__
#define __WD_ACCEPTOR_H__

#include "Socket.h"
#include "InetAddress.h"

namespace wd{

class Acceptor{
public:
	Acceptor(int listenfd, const InetAddress & addr);

	void ready();
	int accept();

	int fd() const { return _listenSock.fd();}
private:
	void setReuseAddr(bool on);
	void setReusePort(bool on);
	void bind();
	void listen();

private:
	Socket _listenSock;
	InetAddress _addr;
};//end of class Acceptor

}//end of namespace wd

#endif

