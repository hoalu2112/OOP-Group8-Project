#include "Manager.h"

Manager::Manager(string username) {
	string link_customer = "C:\\Users\\user\\Desktop\\All_Users\\";
	stringstream ss;
	ss << link_customer << username << ".txt";
	ifstream fin;
	fin.open(ss.str().c_str());
	if (!fin.is_open()) {
		cout << "Can not open file" << endl;
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

void overwriteManagerName_txt(vector<Manager> manager, string username) {
	ofstream fout;
	string link_customer = "C:\\Users\\user\\Desktop\\All_Users\\";
	stringstream ss;
	ss << link_customer << username << ".txt";

	fout.open(ss.str().c_str());
	if (!fout.is_open()) {
		cout << "Can not overwrite file !" << endl;
		return;
	}
	else {
		for (int i = 0; i < manager.size(); i++) {
			if (manager[i].m_manName == username) {
				fout << manager[i].m_manName << endl;
				fout << manager[i].m_manPass << endl;
			}
		}
		fout.close();
	}
}

void overwriteManagerFile_txt(vector<Manager> manager) {
	ofstream fout;
	fout.open("C:\\Users\\user\\Desktop\\Manager_Users.txt");
	if (!fout.is_open()) {
		cout << "Can not overwrite file !" << endl;
		return;
	}
	else {
		fout << manager.size() << endl;
		for (int i = 0; i < manager.size(); i++) {
			fout << manager[i].m_manName << endl;
			fout << manager[i].m_manPass << endl;
		}
		fout.close();
	}
}

void makeListofManagers(vector<Manager>& manager) {
	ifstream fin;
	fin.open("C:\\Users\\user\\Desktop\\Manager_Users.txt");
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
			string tmp_pass;
			getline(fin, tmp_pass);
			manager_username.push_back(tmp_user);
		}
		for (int i = 0; i < manager_username.size(); i++) {
			Manager tmp_manager(manager_username[i]);
			manager.push_back(tmp_manager);
		}
		fin.close();
	}
}

void changePassword(vector<Manager> manager, string username) {
	cout << "_____CHANGE YOUR PASSWORD_______" << endl << endl;
	cout << "__Enter your old password: ";
	string old_pass;
	getline(cin, old_pass);
	for (int i = 0; i < manager.size(); i++) {
		if (username == manager[i].m_manName) {
			while(old_pass != manager[i].m_manPass) {
				cout << "Old Password Is Incorrect!!" << endl;
				cout << "__Enter your old password: ";
				getline(cin, old_pass);
			}
			cout << "__Enter your new password: " << endl;
			string new_pass;
			getline(cin, new_pass);
			manager[i].m_manPass = new_pass;
			overwriteManagerName_txt(manager, username);
			overwriteManagerFile_txt(manager);
			cout << "Your password has been changed!" << endl;
			return;
		}
	}
}

void Manager::menu(string username) {
	vector<Album> album;
	Store store;
	vector<Manager> manager;
	makeListOfAlbums(album);
	makeListofManagers(manager);

	cout << "___MENU___" << endl;
	cout << "1> Calculate which albums have been sold.\n";
	cout << "2> Calculate items sold.\n";
	cout << "3> Calculate leavings in store.\n";
	cout << "4> Calculate profit.\n";
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


}