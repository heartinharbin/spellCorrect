 ///
 /// @file    Configuration.cc
 /// @author  heartinharbin
 /// @date    2017-05-21 16:48:14
 ///


#include "Configuration.h"
#include "MyLog.h"

#include <iostream>
#include <fstream>
#include <sstream>
using std::ifstream;
using std::stringstream;

namespace wd{

Configuration * Configuration::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new Configuration("./conf/server.conf");
		atexit(destroy);
	}
	return _pInstance;
}

void Configuration::destroy(){
	if(_pInstance)
		delete _pInstance;
}

Configuration * Configuration::_pInstance = getInstance();


void Configuration::init(){
	ifstream ifs(_filepath.c_str());
	if(!ifs.good()){
		LogError("open file error!");
	}	
	string tmpline;
	stringstream ss;
	string key, value;
	while(getline(ifs, tmpline)){
		ss << tmpline;
		ss >> key >> value;
		_configMap[key] = value;
		LogDebug((key + " " + value).c_str());
		ss.clear();
	}
	ifs.close();
}

map<string, string> & Configuration::getConfigMap(){
	return _configMap;
}

}//end of namespace wd
