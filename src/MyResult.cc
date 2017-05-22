 ///
 /// @file    MyResult.cc
 /// @author  heartinharbin
 /// @date    2017-05-22 17:06:27
 ///

#include "MyResult.h"

namespace wd{

std::ostream & operator<<(std::ostream & os, const MyResult & rhs){
	os  << "(" << rhs.candicate_word
	<< "," << rhs.frequency
	<< "," << rhs.distance
	<< ")";
	return os;
}
 
bool operator<(const MyResult & lhs, const MyResult & rhs){
	if(lhs.distance != rhs.distance)
		return lhs.distance > rhs.distance;
	else if(lhs.frequency != rhs.frequency)                                                                          
		return lhs.frequency < rhs.frequency;
	else
		return lhs.candicate_word.compare(rhs.candicate_word) >= 0;
}


}//end of namespace wd
