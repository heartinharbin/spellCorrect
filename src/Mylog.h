 ///
 /// @file    Mylog.h
 /// @author  heartinharbin
 /// @date    2017-04-14 22:20:34
 ///
 
#ifndef _MYLOG_H_
#define _MYLOG_H_

#include <log4cpp/Category.hh>
#include <iostream>

enum Priority{
	ERROR,
	WARN,
	INFO,
	DEBUG
};

class Mylog{
public:
	static Mylog& getInstance();
	static void destroy();

	void setPriority(Priority priority);
	void error(const char* msg);
	void warn(const char* msg);
	void info(const char* msg);
	void debug(const char* msg);


private:
	Mylog();

private:
	static Mylog * _plog;
	log4cpp::Category & _category_ref;
};//end of class Mylog

inline std::string int2string(int line){
	std::ostringstream oss;
	oss << line;
	return oss.str();
}

#define suffix(msg) std::string(msg).append(" ##") \
	.append(__FILE__).append(":").append(__func__) \
	.append(":").append(int2string(__LINE__)) \
	.append("##").c_str()


#ifdef _LOG4CPP_
Mylog &log = Mylog::getInstance();
#else
extern Mylog &log;
#endif

#define logError(msg) log.error(suffix(msg))
#define logWarn(msg) log.warn(suffix(msg))
#define logInfo(msg) log.info(suffix(msg))
#define logDebug(msg) log.debug(suffix(msg))

#endif
