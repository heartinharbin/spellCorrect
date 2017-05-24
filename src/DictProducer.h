 ///
 /// @file    DictProducer.h
 /// @author  heartinharbin
 /// @date    2017-05-21 20:24:11
 ///

#ifndef __WD_DICTPRODUCER_H__
#define __WD_DICTPRODUCER_H__

#include "MyResult.h"

#include <map>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <queue>

using std::map;
using std::vector;
using std::string;
using std::unordered_map;
using std::set;
using std::pair;

int distance(const std::string & lhs, const std::string & rhs);

namespace wd{

class DictProducer{
public:
	static DictProducer * getInstance();
	static void destroy();

	void build_dict();
	void build_cn_dict();
	void store_dict(const char * filepath);
	
	void create_index();
	void create_cn_index();

	void show_files() const;
	void show_dict() const;

	vector<pair<string, int> > & getReadDictVector(){
		return _readDict;
	}

	unordered_map<string, set<int> > & getDictIndexMap(){
		return _dictIndex;
	}

	//std::priority_queue<MyResult> & getMyresultQueue(string searchword);
	std::string getMyresultQueue(string searchword);
		
private:
	DictProducer(string dir);
	~DictProducer(){}

private:
	static DictProducer * _pInstance;
	string _dir;
	vector<string> _files;
	map<string,int> _dict;

	vector<pair<string, int> > _readDict;
	unordered_map<string, set<int> > _dictIndex;
	std::priority_queue<MyResult> _resultQueue;

};//end of class DictProducer

}//end of namespace wd


#endif
