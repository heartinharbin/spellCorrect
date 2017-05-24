 ///
 /// @file    CacheManger.cc
 /// @author  heartinharbin
 /// @date    2017-05-23 22:33:25
 ///



#include "CacheManger.h"

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

Cache & CacheManger::getCache(size_t num){
	return _cacheList[num];
}

void CacheManger::periodicUpdate(){

}

}//end of namespace wd
