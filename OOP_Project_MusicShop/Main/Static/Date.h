#ifndef _DATE_H_
#define _DATE_H_
#include <iostream> 
#include <ctime>
#include <sstream>
#include ".\\Tokenizer.h"
using namespace std;

class Date {
private:
	int day;
	int month;
	int year;
public:
	Date();
	Date(int day, int month, int year);
	string toString();
	Date parse(string date);
	bool tryParse(string date);
	bool isValid(string date);
	bool isLeapYear(string);
	friend ostream& operator << (ostream& os, Date p);
	Date& operator = (const Date& m);
};

#endif
