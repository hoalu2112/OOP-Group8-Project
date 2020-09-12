#include "Customer.h"

Customer::Customer(string username) {
	string link_customer = "..\\..\\All_Users\\CUSTOMER\\";
	stringstream ss;
	ss << link_customer << username << ".txt";
	ifstream fin;
	fin.open(ss.str().c_str());
	if (!fin.is_open()) {
		cout << "Can not open file or wrong user name" << endl;
		return;
	}
	else {
		string name;
		getline(fin, name);
		this->m_cusName = name;

		string password;
		getline(fin, password);
		this->m_cusPass = password;

		int flag;
		fin >> flag;
		this->m_flag = flag;

		double tokens;
		fin >> tokens;
		this->m_tokens  = tokens;

		int number_transaction;
		fin >> number_transaction;
		fin.ignore(); 
		for (int i = 0; i < number_transaction; i++) {
			string transaction;
			getline(fin, transaction);
			Transaction p;
			p.stringToTransaction(transaction);
			this->m_trans.push_back(p);
		}
		fin.close(); // close file.
	}
}


void makeListOfCustomers(vector<Customer> &customer) {
	ifstream fin;
	fin.open("..\\..\\All_Users\\CUSTOMER\\Customer_Users.txt");
	if (!fin.is_open()) {
		cout << "Can not open file" << endl;
		return;
	}
	else {
		int numbers_of_customers;
		fin >> numbers_of_customers;
		fin.ignore();

		vector<string> customer_username;
		for (int i = 0; i < numbers_of_customers; i++) {
			string temp_username;
			getline(fin, temp_username);
			string temp_password;
			getline(fin, temp_password);
			customer_username.push_back(temp_username); // chi pushback ten dang nhap , mat khau khong dung toi.
		}
		for (int i = 0; i < customer_username.size(); i++) {
			Customer temp_customer(customer_username[i]);
			customer.push_back(temp_customer);
		}
		fin.close();
	}
}

void Customer:: viewTransactionHistory(vector<Customer> customer, string username) {
	cout << "___________VIEW HISTORY TRANSACTION ___________" << endl << endl;;
	for (int i = 0; i < customer.size(); i++) {
		if (customer[i].m_cusName == username) {
			for (int j = 0; j < customer[i].m_trans.size(); j++) {
				customer[i].m_trans[j].printHistoryTransaction();
			}
		}
	}
}

void Customer:: overwriteFileCustomer_txt(vector<Customer> customer) {
	ofstream fout;
	fout.open("..\\..\\All_Users\\CUSTOMER\\Customer_Users.txt");
	if (!fout.is_open()) {
		cout << "Can not overwrite file !" << endl;
		return;
	}
	else {
		fout << customer.size() << endl;
		for (int i = 0; i < customer.size(); i++) {
			fout << customer[i].m_cusName << endl;
			fout << customer[i].m_cusPass << endl;
		}
		fout.close();
	}
}

void Customer:: overwriteCustomerName_txt(vector<Customer> customer,string username) {
	ofstream fout;
	string link_customer = "..\\..\\All_Users\\CUSTOMER\\";
	stringstream ss;
	ss << link_customer << username << ".txt";

	fout.open(ss.str().c_str());
	if (!fout.is_open()) {
		cout << "Can not overwrite file !" << endl;
		return;
	}
	else {
		for (int i = 0; i < customer.size(); i++) {
			if (customer[i].m_cusName == username) {
				fout << customer[i].m_cusName << endl;
				fout << customer[i].m_cusPass << endl;
				fout << customer[i].m_flag << endl;
				fout << customer[i].m_tokens << endl;
				fout << customer[i].m_trans.size() << endl;
				for (int j = 0; j < customer[i].m_trans.size(); j++) {
					fout << customer[i].m_trans[j].toString() << endl;
				}
				
			}
		}
		fout.close();
	}
}
void Customer::changePasswordCustomer(vector<Customer>customer, string username) {
	cout << "_____CHANGE YOUR PASSWORD_______" << endl <<endl;
	cout << "__Enter your old password: ";
	string old_pass;
	getline(cin, old_pass);
	getline(cin, old_pass);
	for (int i = 0; i < customer.size(); i++) {
		while (username == customer[i].m_cusName && old_pass != customer[i].m_cusPass) {
			cout << customer[i].m_cusPass << endl;
			cout << "Old Password Is Incorrect!!" << endl;
			cout << "__Enter your old password: ";
			getline(cin, old_pass);

		}
		cout << "__Enter your new password: " << endl;
		string new_pass;
		getline(cin, new_pass);
		customer[i].m_cusPass = new_pass;
		overwriteFileCustomer_txt(customer);
		overwriteCustomerName_txt(customer, username);
		cout << "Your password has been changed!" << endl;
		return;
	}
	
}

void Customer::Menu(Store& store)
{
LOOP:
	cout << "___MENU___" << endl; //menu cho khach hang.
	cout << "1> Check tokens." << endl; //kiem tra token con lai trong tk.
	cout << "2> View full list of albums." << endl; // xem full danh sach album.
	cout << "3> Search albums." << endl; // tim kiem album.
	cout << "4> View transaction history." << endl; //lich su giao dich.
	cout << "5> View your cart." << endl; //xem gio hang.
	cout << "6> Buy album(s)" << endl; // mua hang.
	cout << "7> View Best_Rate & Best_Seller:" << endl; // danh gia tot nhat + ban chay nhat.
	cout << "8> Deposit Tokes." << endl; // nap token vao tai khoan
	cout << "9> Change password." << endl; // doi mat khau
	cout << "10> Log out." << endl << endl << endl;// dang xuat.

	int customer_choice;
	cout << "__Enter your choice: ";
	cin >> customer_choice;
	while (customer_choice <= 0 || customer_choice > 10) {
		cout << "Invalid!!" << endl;
		cout << "__Enter your choice: ";
		cin >> customer_choice;
	}
	if (customer_choice == 1) {
		cout << "Your Tokens:= "; //username nay la luc ng dung dang nhap, dung username do de thuc hien chuong trinh. ///nho them vo gettoken
		goto LOOP;
	}
	else if (customer_choice == 2) {
		albumOption(store);
		goto LOOP;
	}
	else if (customer_choice == 3) {
		searchAlbum(store);
		goto LOOP;
	}
	else if (customer_choice == 4) {
		//Customer::viewTransactionHistory(customer, username);
		goto LOOP;
	}
	else if (customer_choice == 7) {
		printBestRate_Seller(store);
		goto LOOP;
	}
	else if (customer_choice == 9) {
		//changePasswordCustomer(customer, username);
		goto LOOP;
	}
	else if (customer_choice == 10) {
		cout << "You have been log out." << endl;
		return ;
	}
}
