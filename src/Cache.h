 ///
 /// @file    Cache.h
 /// @author  heartinharbin
 /// @date    2017-05-23 21:39:57
 ///

#ifndef __WD_CACHE_H__
#define __WD_CACHE_H__

#include "MutexLock.h"
#include <string>
#include <map>
#include <unordered_map>

using std::string;
using std::map;
using std::unordered_map;

namespace wd{

class Cache{
public:
	Cache(int num);
	Cache(const Cache & cache);
	void addElement(const string &key, const string &value);
	void readFromFile(const string &filename);
	void writeToFile(const string &filename);
	void update(const Cache & rhs);

private:
	unordered_map<string, string> _hashMap;
	MutexLock _mutex;
};//end of class Cache

}//end of namespace wd

#endif
