 ///
 /// @file    Task.h
 /// @author  heartinharbin
 /// @date    2017-05-22 22:09:46
 ///


#ifndef __WD_TASK_H__
#define __WD_TASK_H__

#include "TcpConnection.h"
#include <string>

using std::string;

namespace wd{

class MyTask{
public:
	MyTask(string query, TcpConnectionPtr conn)
	: _conn(conn)
	, _query(query){}

	void execute(){
		string msg("iloveyou");
		//执行具体的查询，得到结果msg之后，交给IO线程发送
		_conn->sendInLoop(msg);
	}
private:
	TcpConnectionPtr _conn;
	string _query;
};//end of class Task

}//end of namespace wd


#endif
