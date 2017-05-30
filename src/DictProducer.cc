 ///
 /// @file    DictProducer.cc
 /// @author  heartinharbin
 /// @date    2017-05-21 20:53:18
 ///

#include "DictProducer.h"
#include "MyLog.h"
#include <sys/types.h>
#include <dirent.h>
//#include <boost/regex.hpp>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::set;


namespace wd{

DictProducer * DictProducer::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new DictProducer("./data/dictSource");
	}
	return _pInstance;
}

void DictProducer::destroy(){
	if(_pInstance){
		delete _pInstance;
	}
}

DictProducer * DictProducer::_pInstance = getInstance();

DictProducer::DictProducer(string strDir)
: _dir(strDir){
	DIR * dir;
	dir = opendir(_dir.c_str());
	if(NULL == dir){
		perror("opendir");
		return;
	}
	struct dirent * p;
	while((p = readdir(dir)) != NULL){
		if(!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
			continue;
		_files.push_back(_dir + "/" + p->d_name);
	}
	closedir(dir);
}

void DictProducer::build_dict(){
	cout << "build_dict()" << endl;
	vector<string>::iterator it;
	for(it = _files.begin(); it != _files.end(); ++it){
		cout << *it << " ";
		ifstream ifs((*it).c_str());
		if(!ifs.good()){
			cout << "ifstream open error!" << endl;
			return;
		}

		string line, word;
		while(getline(ifs, line)){
	//		cout << "1:" << line << endl;
			for(auto &c : line){
				if(!isalpha(c)){
					c = ' ';
				}else if(isupper(c)){
					c = tolower(c);
				}
			}
	//		cout << "2:" << line << endl;
	//		boost::regex reg("[^a-zA-Z]");
	//		line = boost::regex_replace(line, reg, " ");
			istringstream iss(line);
			while(iss >> word){
				++_dict[word];
			}
		}
	}
	cout << endl;	
}

void DictProducer::store_dict(const char * filepath){
	ofstream ofs(filepath);
	if(!ofs.good()){
		cout << "ofstream open error!" << endl;
	}
	for(auto & elem : _dict){
		ofs << elem.first << " " << elem.second << endl;
	}
	ofs.close();
}

void DictProducer::create_index(){
	//初始化_dictIndex
	for(int i = 0; i < 26; ++i){
		_dictIndex[string(1, 'a'+i)];
	}

	ifstream ifs("./data/mydict.dat");
	if(!ifs.good()){
		cout << "ifstream open error" << endl;
		return;
	}
	string word, strFreq;
	int ans = 0;
	string line;
//	cout << "----------------" << endl;
	
	while(getline(ifs, line)){
		istringstream iss(line);
		iss >> word >> strFreq;
	//	cout << word << " " << strFreq << endl;
		_readDict.push_back({word, atoi(strFreq.c_str())});
		for(auto c : word){
			_dictIndex.find(string(1, c))->second.insert(ans);
		}
		++ans;
	}
	ifs.close();
	ofstream ofs("./data/index.dat");
	if(!ofs.good()){
		cout << "ofstream open error" << endl;
		return;
	}
	for(int i = 'a'; i <= 'z'; ++i){
		ofs << (char)i << " "; 
		for(auto w : _dictIndex.find(string(1, i))->second){
			ofs << w << " ";
		}	
		ofs << endl;
	}
	ofs.close();
}

//std::priority_queue<MyResult> & DictProducer::getMyresultQueue(string searchword){
std::string DictProducer::getMyresultQueue(string searchword){
	set<string> alpha_set;
	for(auto c : searchword){
		alpha_set.insert(string(1, c));
	}
	
	map<string, int> tmpCandicateMap;

	//set<string>::iterator it;
	for(auto c : alpha_set){
		for(auto no : _dictIndex.find(c)->second){
			tmpCandicateMap[_readDict[no].first] = _readDict[no].second;
		}		
	}
	
	for(auto p : tmpCandicateMap){
		int distance = ::distance(p.first, searchword);
		_resultQueue.push({p.first, p.second, distance});
	}
	cout << "begin  my world" << endl;
//	cout << _resultQueue.top() << endl;
	int cnt = 10;
	string res;
	while(!_resultQueue.empty() && cnt--){
		cout << _resultQueue.top() << endl;
		res += (_resultQueue.top().candicate_word + " ");
		_resultQueue.pop();
	}
	return res;
}

}//end of namespace wd
