#include "Music.h"
#include "Customer.h"
#include "Transaction.h"
#include "Manager.h"



////CUSTOMER.

int main() {
	Store store;
	vector<Manager> manager;
	makeListofManagers(manager);
	vector <Customer> customer;
	makeListOfCustomers(customer);
GOTO:
	cout << "___MENU___" << endl;
	cout << "1> Manager.\n";
	cout << "2> Customer.\n";
	cout << "3> Exit.\n";
	int choice;
	cout << "__Enter your choice: ";
	cin >> choice;

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
		int cur;
		cout << "__Enter your user:";
		getline(cin, user);

		for (int i = 0; i < manager.size(); i++) {
			if (manager[i].check_user(user)) {
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
			if (manager[cur].check_pass(password)) {
				manager[cur].menu(store);
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
					customer[cur].Menu(store);
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