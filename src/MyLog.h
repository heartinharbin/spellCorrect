 ///
 /// @file    MyLog.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-04-15 11:08:14
 ///
 
#ifndef __WD_MYLOG_H__
#define __WD_MYLOG_H__
 
#include <log4cpp/Category.hh>

#include <string>
#include <sstream>

using std::string;
using std::ostringstream;


class MyLog
{
public:
	static MyLog * getInstance();
	static void destroy();

	void warn(const char * msg);
	void error(const char * msg);
	void info(const char * msg);
	void debug(const char * msg);

private:
	MyLog();
	~MyLog();

private:
	log4cpp::Category & _cat;
	static MyLog * _pInstance;
};

inline string int2str(int num)
{
	ostringstream oss;
	oss << num;
	return oss.str();
}

#define prefix(msg) string("[ ").append(__FILE__).append(":")\
					.append(__func__).append(":")\
					.append(int2str(__LINE__)).append(" ]")\
					.append(msg).c_str()

void logError(const char * msg);
void logWarn(const char * msg);
void logInfo(const char * msg);
void logDebug(const char * msg);

#define LogError(msg) logError(prefix(msg))
#define LogWarn(msg) logWarn(prefix(msg))
#define LogInfo(msg) logInfo(prefix(msg))
#define LogDebug(msg) logDebug(prefix(msg))


#endif
