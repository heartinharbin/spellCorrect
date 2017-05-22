 ///
 /// @file    Mylog2.cc
 /// @author  heartinharbin
 /// @date    2017-04-14 22:33:55
 ///
#include "Mylog.h"
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <iostream>
using std::cout;
using std::endl;

Mylog *Mylog::_plog = NULL;

Mylog & Mylog::getInstance(){
	if(NULL == _plog){
		_plog = new Mylog;
	}
	return *_plog;
}

void Mylog::destroy(){
	if(_plog){
		_plog->_category_ref.info("Mylog destroy");
		_plog->_category_ref.shutdown();
		delete _plog;
	}
}

Mylog::Mylog()
:_category_ref(log4cpp::Category::getRoot()){
	log4cpp::PatternLayout *ptn1 = new log4cpp::PatternLayout;
	ptn1->setConversionPattern("%d : %p %c %x:%m%n");

	log4cpp::PatternLayout *ptn2 = new log4cpp::PatternLayout;
	ptn2->setConversionPattern("%d : %p %c %x:%m%n");

	log4cpp::OstreamAppender *os_apd = new log4cpp::OstreamAppender("OstreamAppender", &cout);
	os_apd->setLayout(ptn1);

	log4cpp::FileAppender *file_apd = new log4cpp::FileAppender("fileappender", "./log/server.log");//此处先写死了
	file_apd->setLayout(ptn2);

	_category_ref.setPriority(log4cpp::Priority::DEBUG);
	_category_ref.addAppender(os_apd);
	_category_ref.setAppender(file_apd);

	_category_ref.info("Serverlog created!");
}

void Mylog::setPriority(Priority priority){
	switch(priority){
		case (ERROR):
			_category_ref.setPriority(log4cpp::Priority::ERROR);
			break;
		case (WARN):
			_category_ref.setPriority(log4cpp::Priority::WARN);
			break;
		case (DEBUG):
			_category_ref.setPriority(log4cpp::Priority::DEBUG);
			break;
		case (INFO):
			_category_ref.setPriority(log4cpp::Priority::INFO);
			break;
		default:
			_category_ref.setPriority(log4cpp::Priority::DEBUG);
			break;
	}
}

void Mylog::error(const char *msg){
	_category_ref.error(msg);
}

void Mylog::warn(const char *msg){
	_category_ref.warn(msg);
}

void Mylog::info(const char *msg){
	_category_ref.info(msg);
}

void Mylog::debug(const char *msg){
	_category_ref.debug(msg);
}
