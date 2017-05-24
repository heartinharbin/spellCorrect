 ///
 /// @file    Mydict.h
 /// @author  heartinharbin
 /// @date    2017-05-23 17:52:55
 ///

#ifndef __WD_MYDICT_H__
#define __WD_MYDICT_H__

#include <vector>
#include <map>
#include <string>
#include <set>
#include <unordered_map>

using std::vector;
using std::map;
using std::set;
using std::string;
using std::pair;
using std::unordered_map;

namespace wd{

class Mydict{
public:
	static Mydict * getInstance();
	static void destroy();

	void init(const char * dictEnPath, const char * dictCnPath);
	vector<pair<string, int> > & getDict();
	unordered_map<string, set<int> > & getIndexTable();
private:
	Mydict(){
		init(NULL, NULL);
	}
	~Mydict(){}

private:
	static Mydict * _pInstance;
	vector<pair<string, int> > _dict;
	unordered_map<string, set<int> > _index_table;

};//end of class Mydict
}//end of namespace wd

#endif
