 ///
 /// @file    ttt.cc
 /// @author  heartinharbin
 /// @date    2017-05-22 15:06:10
 ///
#include "MyResult.h" 
#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::priority_queue;


int test1(void){
	priority_queue<wd::MyResult> pq;
	wd::MyResult mr1 = {"i", 9, 3};
	wd::MyResult mr2 = {"d", 9, 3};
	wd::MyResult mr3 = {"s", 10, 5};
	pq.push(mr1);
	pq.push(mr2);
	pq.push(mr3);

	auto res = pq.top();
	cout << res.candicate_word << ": "<< res.frequency << ":" << res.distance << endl;
	while(!pq.empty()){
		cout << pq.top() << endl;	
		pq.pop();
	}
	return 0;
}
