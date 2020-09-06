#ifndef RANDOM_H
#define RANDOM_H
#include <iostream>
#include <ctime>
using namespace std;

class Random
{
	public:
		//Random ();
		int next ();
		int next (int value);
		Random& operator = (const Random & m);
};

#endif
