 ///
 /// @file    Mydict.cc
 /// @author  heartinharbin
 /// @date    2017-05-23 18:01:56
 ///

#include "Mydict.h"

#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;

namespace wd{


Mydict * Mydict::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new Mydict();
		atexit(destroy);
	}
	return _pInstance;
}

void Mydict::destroy(){
	if(_pInstance){
		delete _pInstance;
	}
}

Mydict * Mydict::_pInstance = getInstance();

void Mydict::init(const char * dictEnPath, const char * dictCnPath){
	//初始化_index_table
	for(int i = 0; i < 26; ++i){
		_index_table[string(1, 'a'+i)];
	}

	ifstream ifs("./data/mydict.dat");
	if(!ifs.good()){
		cout << "ifstream open error" << endl;
		return;
	}

	string word, strFreq;
	string line;
	while(getline(ifs, line)){
		istringstream iss(line);
		iss >> word >> strFreq;
		_dict.push_back({word, atoi(strFreq.c_str())});
	}
	ifs.close();
	
	ifstream ifs2("./data/index.dat");
	string alpha, tmp;
	while(getline(ifs2, line)){
		istringstream iss(line);
		iss >> alpha;
		while(iss >> tmp){
			_index_table[alpha].insert(atoi(tmp.c_str()));
		}
//		iss.clear();
	}
	ifs2.close();
}

vector<pair<string, int> > & Mydict::getDict(){
	return _dict;
}

unordered_map<string, set<int> > & Mydict::getIndexTable(){
	return _index_table;
}

}//end of namespace wd




