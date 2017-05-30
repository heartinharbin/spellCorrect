 ///
 /// @file    SocketIO.h
 /// @author  heartinharbin
 /// @date    2017-05-15 16:46:12
 ///

#ifndef __WD_SOCKETIO_H__
#define __WD_SOCKETIO_H__
#include <stdio.h>

namespace wd{

class SocketIO{

public:
	SocketIO(int sockfd);

	size_t readn(char * buf, size_t count);
	size_t writen(const char * buf, size_t count);
	size_t readline(char * buf, size_t max_len);
private:
	size_t recv_peek(char * buf, size_t count);

private:
	int _sockfd;
};//end of class SocketIO

}//end of namespace wd

#endif
