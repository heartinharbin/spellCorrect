///
/// @file    Task.h
/// @author  heartinharbin
/// @date    2017-05-22 22:09:46
///


#ifndef __WD_TASK_H__
#define __WD_TASK_H__

#include "MyResult.h"
#include "Mydict.h"
#include "TcpConnection.h"
#include <ctype.h>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <iostream>

using std::map;
using std::set;
using std::string;
using std::cout;
using std::endl;

int distance(const std::string & lhs, const std::string &rhs);

namespace wd{

class MyTask{
public:
	MyTask(string query, TcpConnectionPtr conn)
		: _conn(conn)
		  , _query(query){}

	MyTask(){}

	void execute(){
		cout << "MyTask::execute()"<< endl;
		cout << "_query:" << _query << endl;
		Mydict::getInstance();
		string msg = getMyresultQueue(_query);
		cout << "res: " << msg << endl;
		//执行具体的查询，得到结果msg之后，交给IO线程发送
		_conn->sendInLoop(msg);
	}

	string getMyresultQueue(string searchword){
		cout << "getMyresultQueue()" << endl;
		vector<pair<string, int> > _readDict = Mydict::getInstance()->getDict();
		unordered_map<string, set<int> > _dictIndex = Mydict::getInstance()->getIndexTable();
		std::priority_queue<MyResult> _resultQueue;
		cout << "init " << endl;
		cout << _readDict.size() << " -- " << _dictIndex.size() << endl;
		set<string> alpha_set;
		for(auto c : searchword){
			if(isalpha(c)){				//是字母再插入,防止插入一个回车换行
				alpha_set.insert(string(1, c));
			}
		}
		cout << "1" << endl;
		map<string, int> tmpCandicateMap;
		cout << "2" << endl;
		set<string>::iterator it;
#if 0	//显示各个变量中的数据	
		for(auto m : _readDict){
			cout << m.first << " " << m.second << endl;
		}

		for(int i = 0; i < 26; i++){
			cout <<	(char)('a' + i)<< " ";
			for(auto m :  _dictIndex[string(1,'a'+i)]){
				cout << m << " "; 
			}
			cout << endl;
		}
		
		cout << "size:" <<alpha_set.size() << endl;
			
		for(auto c : alpha_set){
			cout << c << " ";
		}
		cout << endl;
#endif
		for(auto c : alpha_set){
			for(auto no : _dictIndex.find(c)->second){
				tmpCandicateMap[_readDict[no].first] = _readDict[no].second;
			}		
		}
		cout << "3" << endl;
		for(auto p : tmpCandicateMap){
			int distance = ::distance(p.first, searchword);
			_resultQueue.push({p.first, p.second, distance});
		}
		cout << "begin  my world" << endl;
	//	cout << _resultQueue.top() << endl;
		string res;
		int cnt = 10;
		while(!_resultQueue.empty() && cnt--){
			cout << _resultQueue.top() << endl;
			res += (_resultQueue.top().candicate_word + " ");
			_resultQueue.pop();
		}
		return res;
	}

private:
	TcpConnectionPtr _conn;
	string _query;
};//end of class Task

}//end of namespace wd


#endif
