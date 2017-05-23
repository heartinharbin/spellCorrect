 ///
 /// @file    MyLog.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-04-15 11:11:28
 ///
 

#include "MyLog.h"

#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>

#include <iostream>
using std::cout;
using std::endl;

MyLog * MyLog::_pInstance = NULL;


MyLog * MyLog::getInstance()
{
	if(NULL == _pInstance)
		_pInstance = new MyLog;
	return _pInstance;
}

void MyLog::destroy()
{
	if(_pInstance)
	{
		delete _pInstance;
	}
}


MyLog::MyLog()
: _cat(log4cpp::Category::getRoot().getInstance("mycat"))
{
	log4cpp::PatternLayout * ptn1 = new log4cpp::PatternLayout();
	ptn1->setConversionPattern("%d [%p] %c:%m%n");

	log4cpp::PatternLayout * ptn2 = new log4cpp::PatternLayout();
	ptn2->setConversionPattern("%d [%p] %c:%m%n");

	log4cpp::OstreamAppender * os = new log4cpp::OstreamAppender("os", &cout);
	os->setLayout(ptn1);
	
	log4cpp::FileAppender * file = new log4cpp::FileAppender("file", "./log/server.log");
	file->setLayout(ptn2);

	_cat.addAppender(os);
	_cat.addAppender(file);
	_cat.setPriority(log4cpp::Priority::DEBUG);
}


MyLog::~MyLog()
{
	log4cpp::Category::shutdown();
}


void MyLog::warn(const char * msg)
{
	_cat.warn(msg);
}

void MyLog::error(const char * msg)
{
	_cat.error(msg);
}

void MyLog::info(const char * msg)
{
	_cat.info(msg);
}

void MyLog::debug(const char * msg)
{
	_cat.debug(msg);
}


void logError(const char * msg)
{
	MyLog::getInstance()->error(msg);
}

void logWarn(const char * msg)
{
	MyLog::getInstance()->warn(msg);
}
void logInfo(const char * msg)
{
	MyLog::getInstance()->info(msg);
}
void logDebug(const char * msg)
{
	MyLog::getInstance()->debug(msg);
}
