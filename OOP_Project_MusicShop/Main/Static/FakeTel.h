#ifndef _FAKETEL_H_
#define _FAKETEL_H_
#include <iostream> 
#include <ctime>
#include <sstream>
#include ".\\Tokenizer.h"
#include ".\\Random.h"
using namespace std;

class FakeTel {
private:
	Tokenizer tokens;
	Random random;
public:
	stringstream getFakeTel(string first_three);
};

#endif 