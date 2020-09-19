#include "Music.h"
#include "Customer.h"
#include "Transaction.h"
#include "Manager.h"
#include <iomanip>


////CUSTOMER.

int main() {
	Store store;
	vector<Manager> manager;
	makeListofManagers(manager);
	vector <Customer> customer;
	makeListOfCustomers(customer);
	for (int i = 0; i < customer.size(); i++) {
		customer[i].Check_Membership();
	}
GOTO:
	cout << "___MENU___" << endl;
	cout << "1> Manager.\n";
	cout << "2> Customer.\n";
	cout << "3> Exit.\n";
	int choice;
	cout << "__Enter your choice: ";
	cin >> choice;
	system("cls");
	while (choice <= 0 || choice >= 4) {
		cout << "Invalid!!\n";
		cout << "__Enter your choice: ";
		cin >> choice;
	}
	if (choice == 1) {
		cin.ignore();
		bool flag = false;
		string user;
		string password;
		int mana;
		cout << "__Enter your user:";
		getline(cin, user);

		for (int i = 0; i < manager.size(); i++) {
			if (manager[i].check_user(user)) {
				flag = true;
				mana = i;
				break;
			}
		}
		if (!flag) {
			cout << "That user_name doesn't exist." << endl;
		}
		else
		{
			cout << "__Enter your password:";
			getline(cin, password);
			if (manager[mana].check_pass(password)) {
				system("cls");
				manager[mana].menu(store);
				return 0;
			}
			else {
				system("cls");
				cout << "Wrong password." << endl << endl;
				goto GOTO;
			}
		}
	}
	else
		if (choice == 2) {
			cin.ignore();
			bool flag = false;
			string user;
			string password;
			int cur;
			cout << "__Enter your user:";
			getline(cin, user);

			for (int i = 0; i < customer.size(); i++) {
				if (customer[i].check_user(user)) {
					flag = true;
					cur = i;
					break;
				}
			}
			if (!flag) {
				cout << "That user_name doesn't exist." << endl;
			}
			else
			{
				cout << "__Enter your password:";
				getline(cin, password);
				if (customer[cur].check_pass(password)) {
					system("cls");
					customer[cur].Menu(store);
					return 0;
				}
				else {
					system("cls");
					cout << "Wrong password." << endl << endl;
					goto GOTO;
				}
			}
		}
		else
			if (choice == 3) {
				return 0;
			}
	overwriteFileCustomer_txt(customer);

	return 0;
}