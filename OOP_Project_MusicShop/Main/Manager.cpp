#include "Manager.h"

Manager::Manager(string username) {
	string link_customer = "..\\..\\All_Users\\MANAGER\\";
	stringstream ss;
	ss << link_customer << username << ".txt";
	ifstream fin;
	fin.open(ss.str().c_str());
	if (!fin.is_open()) {
		cout << "Can not open file!" << endl;
		return;
	}
	else {
		string name;
		getline(fin, name);
		m_manName = name;

		string pass;
		getline(fin, pass);
		m_manPass = pass;
	}
	fin.close();
}

void Manager::overwriteManagerName_txt() {
	ofstream fout;
	string link_customer = "..\\..\\All_Users\\MANAGER\\";
	stringstream ss;
	ss << link_customer << this->m_manName << ".txt";

	fout.open(ss.str().c_str());
	if (!fout.is_open()) {
		cout << "Can not overwrite file !" << endl;
		return;
	}
	else {

		fout << this->m_manName << endl;
		fout << this->m_manPass << endl;
		fout.close();
	}
}

void overwriteManagerFile_txt(vector<Manager> manager) {
	ofstream fout;
	fout.open("..\\..\\All_Users\\MANAGER\\Manager_Users.txt");
	if (!fout.is_open()) {
		cout << "Can not overwrite file !" << endl;
		return;
	}
	else {
		fout << manager.size() << endl;
		for (int i = 0; i < manager.size(); i++) {
			fout << manager[i].m_manName << endl;
			//fout << manager[i].m_manPass << endl;
		}
		fout.close();
	}
}

void makeListofManagers(vector<Manager>& manager) {
	ifstream fin;
	fin.open("..\\..\\All_Users\\MANAGER\\Manager_Users.txt");
	if (!fin.is_open()) {
		cout << "Can not open file" << endl;
		return;
	}
	else {
		int number_of_manager;
		fin >> number_of_manager;
		fin.ignore();

		vector<string> manager_username;
		for (int i = 0; i < number_of_manager; i++) {
			string tmp_user;
			getline(fin, tmp_user);
			//string tmp_pass;
			//getline(fin, tmp_pass);
			manager_username.push_back(tmp_user);
		}
		for (int i = 0; i < manager_username.size(); i++) {
			Manager tmp_manager(manager_username[i]);
			manager.push_back(tmp_manager);
		}
		fin.close();
	}
}

void Manager::changePassword() {
	cout << "_____CHANGE YOUR PASSWORD_______" << endl << endl;
	cout << "__Enter your old password: ";
	string old_pass;
	getline(cin, old_pass);
	while (!this->check_pass(old_pass)) {
		cout << this->m_manName << endl;
		cout << "Old Password Is Incorrect!!" << endl;
		cout << "__Enter your old password: ";
		getline(cin, old_pass);

	}
	cout << "__Enter your new password: " << endl;
	string new_pass;
	getline(cin, new_pass);
	this->m_manPass = new_pass;
	cout << "Your password has been changed!" << endl;
	return;
}

void Manager::menu(Store& store) {
LOOP:
	cout << "___MENU___" << endl;
	cout << "1> Calculate which albums have been sold.\n";
	cout << "2> Calculate items sold.\n";
	cout << "3> Calculate leavings in store.\n";
	cout << "4> Calculate income.\n";
	cout << "5> Import items.\n";
	cout << "6> Edit album.\n";
	cout << "7> Change password.\n";
	cout << "8> Log out.\n";

	int choice;
	cout << "__Enter your choice: ";
	cin >> choice;

	while (choice <= 0 || choice >= 9) {
		cout << "Invalid!!\n";
		cout << "__Enter your choice: ";
		cin >> choice;
	}
	if (choice == 1) {
		int sold = store.calcItemSold();
		if (sold > 1)
			cout << sold << " albums have been sold.\n";
		else
			cout << sold << " album has been sold.\n";
		goto LOOP;
	}
	else if (choice == 2) {
		int sold = store.totalExport();
		if (sold > 1)
			cout << sold << " items have been sold.\n";
		else
			cout << sold << " item has been sold.\n";
		goto LOOP;
	}
	else if (choice == 3) {
		cout << store.calcLeavings() << "items left in the store.\n";
		goto LOOP;
	}
	else if (choice == 4) {
		cout << "Total income: " << store.calcProfit() << endl;
		goto LOOP;
	}
	else if (choice == 5) {
		int items;
		string id;
		cout << "Enter album's ID: ";
		getline(cin, id);
		cout << "Enter value to import: ";
		cin >> items;
		store.importItem(id,items);
		goto LOOP;
	}
	else if (choice == 6) {
		store.edit();
		goto LOOP;
	}
	else if (choice == 7) {
		changePassword();
		overwriteManagerName_txt();
		goto LOOP;
	}
	else if (choice == 8) {
		cout << "You've been log out.\n";
		store.overwriteStore_txt();
		return;
	}

}
