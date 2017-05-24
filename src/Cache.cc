 ///
 /// @file    Cache.cc
 /// @author  heartinharbin
 /// @date    2017-05-23 21:46:16
 ///
//#include "Thread.h"
#include "Cache.h"
#include <fstream>
#include <sstream>
#include <iostream>


using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;
namespace wd{



Cache::Cache(){}

Cache::Cache(const Cache & cache){
	_hashMap = cache._hashMap;
}

void Cache::addElement(const string &key, const string &value){
	cout << "Cache::addElement()" << endl;
	cout << "size:" << _hashMap.size() << endl; 
	_hashMap[key] = value;
	cout << "size:" << _hashMap.size() << endl;
}

void Cache::readFromFile(const string &filename){
	ifstream ifs(filename);
	if(!ifs.good()){
		cout << "ifstream open error" << endl;
		return;
	}
	string key, value, line;
	while(getline(ifs, line)){
		istringstream iss(line);
		iss >> key >> value;
		_hashMap[key] = value;
	}
	ifs.close();
}

void Cache::writeToFile(const string &filename){
	ofstream ofs(filename);
	if(!ofs.good()){
		cout << "ofstream open error" << endl;
		return;
	}
	for(auto i : _hashMap){
		ofs << i.first << " " << i.second << endl;
	}
	ofs.close();
}

void Cache::update(const Cache & rhs){
//	cout << "update:" << wd::current_thread::a << endl;
	MutexLockGuard guard(_mutex);
	cout << "size:" << rhs._hashMap.size() << endl;
	for(auto m : rhs._hashMap){
//		cout << m.first << " " << m.second << endl;
		_hashMap.insert(m);	
	}	
}

string Cache::query(const string & searchword){
	cout << "Cache::query()" << endl;
	cout << "size " << _hashMap.size() << endl;
	cout << "query: " << searchword << endl;
	for(auto m : _hashMap){
		cout << m.first << " " << m.second << endl;
	}
	auto it = _hashMap.find(searchword);
	if(it != _hashMap.end()){
		return it->second;
	}else{
		return string();
	}	
}


}//end of namespace wd
