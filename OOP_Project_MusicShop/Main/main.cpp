#include "Music.h"
#include "Customer.h"
#include "Transaction.h"
int main() {
	string username = "khuong3072001";
	vector<Album> album;
	Store store;
	makeListOfAlbums(album);
	////CUSTOMER.
	vector <Customer> customer;
	makeListOfCustomers(customer);


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
		cout << "Your Tokens:= " ; //username nay la luc ng dung dang nhap, dung username do de thuc hien chuong trinh. ///nho them vo gettoken
	}
	else if (customer_choice == 2) {
		albumOption(album);
	}
	else if (customer_choice == 3) {
		searchAlbum(album);
	}
	else if (customer_choice == 4) {
		//Customer::viewTransactionHistory(customer, username);
	}
	else if (customer_choice == 7) {
		printBestRate_Seller(album, store);
	}
	else if (customer_choice == 9) {
		//changePasswordCustomer(customer, username);
	}
	else if (customer_choice == 10) {
		cout << "You have been log out." << endl;
		return 0;
	}

	return 0;
}