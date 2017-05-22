 ///
 /// @file    MyResult.h
 /// @author  heartinharbin
 /// @date    2017-05-22 14:55:20
 ///

#ifndef __WD_MYRESULT_H__
#define __WD_MYRESULT_H__

#include <iostream>

namespace wd{

struct MyResult{
	std::string candicate_word;
	int frequency;
	int distance;
	
	friend std::ostream & operator<<(std::ostream & os, const MyResult & rhs);
	friend bool operator<(const MyResult & lhs, const MyResult & rhs);
};


}//end of namespace wd


#endif
