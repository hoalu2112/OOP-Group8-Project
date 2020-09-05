#ifndef _FAKEEMAIL_H_
#define _FAKEEMAIL_H_
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> // use lowercase for string.
#include ".\\Random.h"
#include ".\\Tokenizer.h"
#include ".\\FakeName.h"


using namespace std;

class FakeEmail : public FakeName{
private:
	Tokenizer tokens;
	Random random;
public:
	string getFakeEmail(string fullname, string domain);
};



#endif