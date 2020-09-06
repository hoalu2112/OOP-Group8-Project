#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class Tokenizer {
	public:
		static vector <string> split(string haystack, string separator); // split a string.
		static vector <int> splitInt(string intString, string separator); // Calculate sum of integer number from a string.
};


#endif
