#ifndef _FAKENAME_H_
#define _FAKENAME_H_

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include ".\\Random.h"
#include ".\\Tokenizer.h"

class FakeName {
	private:
		Random random;
		Tokenizer tokens;
	public:
		stringstream getFakeName(string last, string middle, string first);
		FakeName& operator = (const FakeName& m);

};

#endif 
