#ifndef _FAKEADDRESS_H_
#define _FAKEADDRESS_H_
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include ".\\Tokenizer.h"
#include ".\\Random.h"

class Address
{
	private:
		string street ;
		string district;
		string ward;
	public:
		Address();
		Address getFakeAddress(string district, string ward, string street);
		Address& operator = (const Address& m);
		friend ostream& operator <<(ostream& os, Address p) {
		os <<p.street<< "/" << p.ward << "/" << p.district;
		return os;
	};
};

#endif

