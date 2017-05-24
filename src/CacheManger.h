 ///
 /// @file    CacheManger.h
 /// @author  heartinharbin
 /// @date    2017-05-23 22:26:12
 ///


#ifndef __WD_CACHEMANGER_H__
#define __WD_CACHEMANGER_H__

#include "Cache.h"
#include <vector>

using std::vector;


namespace wd{

class CacheManger{
public:
	static CacheManger * getInstance();
	static void destroy();

	void init();
	Cache & getCache(size_t num);
	void periodicUpdate();
private:
	CacheManger(){}
	~CacheManger(){}

private:
	static CacheManger * _pInstance;
	vector<Cache> _cacheList;
	
};//end of class CacheManger


}//end of namespace wd


#endif
