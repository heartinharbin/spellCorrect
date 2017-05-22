 ///
 /// @file    main.cc
 /// @author  heartinharbin
 /// @date    2017-05-21 16:16:35
 ///

#define _LOG4CPP_

#include "Mylog.h"
//#include "func.h"
#include "Configuration.h"
#include "DictProducer.h"
#include <iostream>
#include <map>

using std::map;
using std::cout;
using std::endl;

int main(void){
#if 0
	logError("error allen");
	logWarn("warn allen");
	func();
#endif

#if 0
	map<string, string> cm= wd::Configuration::getInstance()->getConfigMap();
	cout << cm["ip"] << endl;
	cout << cm["port"] << endl;
	cout << cm["num"] << endl;
#endif

	wd::DictProducer::getInstance() -> build_dict();
	wd::DictProducer::getInstance() -> store_dict("./data/mydict.dat");
	wd::DictProducer::getInstance() -> create_index();
	wd::DictProducer::getInstance() -> getMyresultQueue("hel");
	
	return 0;
}
