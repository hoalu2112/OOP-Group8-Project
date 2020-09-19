#include "Customer.h"
using namespace std;
void Customer::Check_Membership()
{
	if (this->Total_amount() >= 10)
		m_flag = 1;
	else
		m_flag = 0;
}
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
		this->m_tokens = tokens;

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


void makeListOfCustomers(vector<Customer>& customer) {
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
			//string temp_password;
			//getline(fin, temp_password);
			customer_username.push_back(temp_username); // chi pushback ten dang nhap , mat khau khong dung toi.
		}
		for (int i = 0; i < customer_username.size(); i++) {
			Customer temp_customer(customer_username[i]);
			customer.push_back(temp_customer);
		}
		fin.close();
	}
}

void MakeListofCode(vector<Giftcode>& code) {
	ifstream input;
	input.open("secret\\giftcode.txt");
	if (!input.is_open())
		cout << "cant open file giftcode.txt";
	else {
		int n = 0;
		input >> n;
		input.ignore();
		double token;
		string tmp;
		for (int i = 0; i < n; i++) {
			getline(input, tmp);
			input >> token;
			input.ignore();
			Giftcode a(tmp, token);
			code.push_back(a);
		}
		input.close();
	}
}

void Customer::viewTransactionHistory() {
	cout << "___________VIEW HISTORY TRANSACTION ___________" << endl << endl;;

	for (int j = 0; j < this->m_trans.size(); j++) {
		this->m_trans[j].printHistoryTransaction();
	}
}

void overwriteFileCustomer_txt(vector<Customer> customer) {
	ofstream fout;
	fout.open("..\\..\\All_Users\\CUSTOMER\\Customer_Users.txt");
	if (!fout.is_open()) {
		std::cout << "Can not overwrite file !" << endl;
		return;
	}
	else {
		fout << customer.size() << endl;
		for (int i = 0; i < customer.size(); i++) {
			fout << customer[i].m_cusName << endl;
			//fout << customer[i].m_cusPass << endl;
		}
		fout.close();
	}
}

void Customer::overwriteCustomerName_txt() {
	ofstream fout;
	string link_customer = "..\\..\\All_Users\\CUSTOMER\\";
	stringstream ss;
	ss << link_customer << this->m_cusName << ".txt";

	fout.open(ss.str().c_str());
	if (!fout.is_open()) {
		cout << "Can not overwrite file !" << endl;
		return;
	}
	else {

		fout << this->m_cusName << endl;
		fout << this->m_cusPass << endl;
		fout << this->m_flag << endl;
		fout << this->m_tokens << endl;
		fout << this->m_trans.size() << endl;
		for (int j = 0; j < this->m_trans.size(); j++) {
			fout << this->m_trans[j].toString() << endl;
		}
	}
	fout.close();
}
void Customer::changePasswordCustomer() {
	cout << "_____CHANGE YOUR PASSWORD_______" << endl << endl;
	cout << "__Enter your old password: ";
	string old_pass;
	getline(cin, old_pass);
	getline(cin, old_pass);

	while (!this->check_pass(old_pass)) {
		cout << this->m_cusPass << endl;
		cout << "Old Password Is Incorrect!!" << endl;
		cout << "__Enter your old password: ";
		getline(cin, old_pass);

	}
	cout << "__Enter your new password: " << endl;
	string new_pass;
	getline(cin, new_pass);
	this->m_cusPass = new_pass;
	cout << "Your password has been changed!" << endl;
	return;

}

void Customer::Buy_album(Store& store)
{
	double price;
	int album_order;
	cout << "__Enter album's order: ";
	cin >> album_order;

	while (album_order < 0 || album_order > store.get_album().size()) {
		cout << "Invalid!!" << endl;
		cout << "__Enter album's order: ";
		cin >> album_order;
	}
	int quality;
	cout << "Number of that item in the store:" << store.Cal_albumI_leaveing(album_order) << endl;
	cout << "__Enter quality you wanna buy: ";
	cin >> quality;
	bool flag = true;
	while (flag) {
		price = store.cal_price_AlbumI_quality(album_order, quality);
		//if the customer have membership, they'll be discount 20%
		if (m_flag) {
			price *= 0.8;
		}
		if (quality > store.Cal_albumI_leaveing(album_order)) {
			cout << "Invalid!!" << endl;
			cout << "Shop Dont have enough item" << endl;
			cout << "__Enter quality you wanna buy: ";
			cin >> quality;
		}
		else
			if (m_tokens < price)
			{
				int choice;
				cout << "Invalid!!" << endl;
				cout << "You Dont have enough token " << endl;
				cout << "Do you wanna get some more token !" << endl;
				cout << "1> Yes." << endl;
				cout << "2> No." << endl;
				cout << "_Enter:";
				cin >> choice;
				if (choice == 1);
				///chua viet ty nho them vo nha ~~ loi tui
				/// 
				else
					return;
			}
			else {
				flag = false;
			}

	}
	store.Buy_AlbumI(album_order, quality);
	m_tokens -= price;

	Date tmp;
	//cout << tmp.toString() << endl;
	Transaction Tran(store.get_album()[album_order - 1].getID(), tmp, quality, store.cal_price_AlbumI_quality(album_order, quality));
	m_trans.push_back(Tran);
	overwriteCustomerName_txt();
	store.overwriteStore_txt();
}

void Customer::Menu(Store& store)
{
LOOP:
	cout << "___MENU___" << endl; //menu cho khach hang.
	cout << "1> Check tokens." << endl; //kiem tra token con lai trong tk.
	cout << "2> View full list of albums." << endl; // xem full danh sach album.
	cout << "3> Search albums." << endl; // tim kiem album.
	cout << "4> View transaction history." << endl; //lich su giao dich.
	cout << "5> Buy album(s)" << endl; // mua hang.
	cout << "6> View Best_Rate & Best_Seller:" << endl; // danh gia tot nhat + ban chay nhat.
	cout << "7> Deposit Tokens." << endl; // nap token vao tai khoan
	cout << "8> Change password." << endl; // doi mat khau
	cout << "9> Log out." << endl << endl << endl;// dang xuat.

	int customer_choice;
	cout << "__Enter your choice: ";
	cin >> customer_choice;
	system("cls");
	while (customer_choice <= 0 || customer_choice > 9) {
		cout << "Invalid!!" << endl;
		cout << "__Enter your choice: ";
		cin >> customer_choice;
	}
	system("cls");
	if (customer_choice == 1) {
		cout << "Your Tokens:= " << getTokens() << endl; //username nay la luc ng dung dang nhap, dung username do de thuc hien chuong trinh. ///nho them vo gettoken
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
		viewTransactionHistory();
		goto LOOP;
	}
	else if (customer_choice == 5) {
		printListOfAlbums(store);
		Buy_album(store);
		cout << "Buy album(s) successfully." << endl;
		goto LOOP;
	}
	else if (customer_choice == 6) {
		printBestRate_Seller(store);
		goto LOOP;
	}
	else if (customer_choice == 7) {
		Deposit_Token(store);
		overwriteCustomerName_txt();
		goto LOOP;
	}
	else if (customer_choice == 8) {
		changePasswordCustomer();
		overwriteCustomerName_txt();
		goto LOOP;
	}
	else if (customer_choice == 9) {
		cout << "You have been log out." << endl;
		return;
	}
}

void Customer::Deposit_Token(Store& store)
{
	cin.ignore();
	string g_code;
	cout << "Input Gift Code:";
	getline(cin, g_code);
	for (int i = 0; i < store.Code.size(); i++) {
		if (store.Code[i].check(g_code)) {
			m_tokens += store.Code[i].Get_token();
			cout << "Deposit successful\n";
			return;
		}
	}
	cout << "Your Code is Invalid!!\n";
}