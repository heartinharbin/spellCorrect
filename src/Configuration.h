 ///
 /// @file    Configuration.h
 /// @author  heartinharbin
 /// @date    2017-05-21 16:35:34
 ///

#ifndef __WD_CONFIGURATION_H__
#define __WD_CONFIGURATION_H__

#include <string>
#include <map>
using std::string;
using std::map;

namespace wd{

class Configuration{
public:
	static Configuration * getInstance(); 
	static void destroy();
	
	//void setFilepath(string filepath);
	
	map<string, string> & getConfigMap();

private:
	Configuration(string filepath)
	: _filepath(filepath){
		init();
	};
	~Configuration(){};
	void init();
private:
	static Configuration * _pInstance;
	string _filepath;
	map<string, string> _configMap;
};//end of class Configuration

}//end of class wd


#endif
