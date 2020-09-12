#ifndef _MANAGER_H_
#define _MANAGER_H_

#include<iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Static/Tokenizer.h"
#include "Static/Date.h"
#include "Music.h"

class Manager {
private:
	string m_manName, m_manPass;
public:
	Manager(string username);
	friend void changePassword(vector<Manager> manager, string username);
	friend void overwriteManagerName_txt(vector<Manager> manager,string username);
	friend void overwriteManagerFile_txt(vector<Manager> manager);
	friend void makeListofManagers(vector<Manager>& manager);
	void menu(string username);
};

#endif // !_MANAGER_H_

