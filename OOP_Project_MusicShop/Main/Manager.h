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
	void changePassword();
	void overwriteManagerName_txt();
	friend void overwriteManagerFile_txt(vector<Manager> manager);
	void menu(Store& store);
	bool check_user(string user) { return this->m_manName == user; }
	bool check_pass(string pass) { return this->m_manPass == pass; }
};
void makeListofManagers(vector<Manager>& manager);

#endif // !_MANAGER_H_
