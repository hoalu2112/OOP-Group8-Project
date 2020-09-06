#ifndef _FAKEBDAY_H_
#define _FAKEBDAY_H_
#include <iostream> 
#include <ctime>
#include <sstream>
#include ".\\Random.h"
#include ".\\Date.h"
using namespace std;


class FakeBDay {
private:
	Date birth_day;
	Random random;
public:
	Date getFakeBDay();
};

#endif