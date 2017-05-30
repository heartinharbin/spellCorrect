 ///
 /// @file    CacheManger.cc
 /// @author  heartinharbin
 /// @date    2017-05-23 22:33:25
 ///


#include "Cache.h"
#include "CacheManger.h"
#include "Configuration.h"

#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;



namespace wd{

CacheManger * CacheManger::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new CacheManger();
		atexit(destroy);
	}	
	return _pInstance;
}

void CacheManger::destroy(){
	if(_pInstance)
		delete _pInstance;
}

CacheManger * CacheManger::_pInstance = getInstance();

void CacheManger::init(){
	cout << "CacheManger::init()" << endl;
	auto cfgMap = Configuration::getInstance()->getConfigMap();
	int threadnum = atoi(cfgMap.find("threadnum")->second.c_str());
	Cache c;
	c.readFromFile("./data/cache.dat");		
	_cacheList.push_back(c);
	
	//公共的cache在vector中下标为0，其余下标分别为1-threadnum
	for(int i = 1; i <= threadnum; ++i){
	//	Cache tmp(c);				//_cacheList中的元素就是Cache
		_cacheList.push_back(c);
	}
}


Cache & CacheManger::getCache(size_t num){
	return _cacheList[num];
}

void CacheManger::periodicUpdate(){
	cout << "CacheManger::periodicUpdate()" << endl;
	auto cfgMap = Configuration::getInstance()->getConfigMap();
	int threadnum = atoi(cfgMap.find("threadnum")->second.c_str());

	for(int i = 1; i <= threadnum; ++i){
		_cacheList[0].update(_cacheList[i]);	
	}

	for(int i = 1; i <= threadnum; ++i){
		_cacheList[i].update(_cacheList[0]);
	}

	_cacheList[0].writeToFile("./data/cache.dat");
}

}//end of namespace wd
