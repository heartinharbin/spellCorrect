 ///
 /// @file    Cache.cc
 /// @author  heartinharbin
 /// @date    2017-05-23 21:46:16
 ///

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

Cache::Cache(int num){}

Cache::Cache(const Cache & cache){
	_hashMap = cache._hashMap;
}

void Cache::addElement(const string &key, const string &value){
	_hashMap[key] = value;
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
		ofs << i.first << " " << i.second ;
	}
	ofs.close();
}

void Cache::update(const Cache & rhs){
	MutexLockGuard guard(_mutex);
	for(auto m : rhs._hashMap){
		_hashMap[m.first] = m.second;	
	}	
}


}//end of namespace wd
