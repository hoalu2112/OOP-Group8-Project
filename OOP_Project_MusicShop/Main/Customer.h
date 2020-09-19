#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
#include <iostream>
#include <string.h> 
#include <vector>
#include <fstream>
#include "Transaction.h"
#include "Music.h"
#include <string>
using namespace std;

class Store;


class Customer {
protected:
	string m_cusName; //ten dang nhap.
	string m_cusPass; //mat khau.
	int m_flag; // khach hang than thiet. 1: discount 10%.
	double m_tokens; // tokens left in account.
	vector <Transaction> m_trans;//  lich su giao dich;

public:
	int Total_amount() {
		int total = 0;
		for (int i = 0; i < m_trans.size(); i++) {
			total += m_trans[i].GetAmount();
		}
		return total;
	}
	void Check_Membership();
	Customer(string username);
	double getTokens() { return m_tokens; } // xem tokens con lai trong tai khoan.
	void viewTransactionHistory(); //xem lich su giao dich.
	friend void overwriteFileCustomer_txt(vector<Customer> customer); //ghi lai file Customer.TXT neu co chinh sua.
	void overwriteCustomerName_txt(); //ghi lai file tenkhachhang.TXT neu co chinh sua.
	void changePasswordCustomer(); // customer co the doi mat khau cua ho.
	void Buy_album(Store& store);
	void Menu(Store& store);
	bool check_user(string user) { return this->m_cusName == user; }
	bool check_pass(string pass) { return this->m_cusPass == pass; }
	void Deposit_Token(Store& store);
};
void makeListOfCustomers(vector<Customer>& customer); // doc file Customer.txt --> luu het cac thong tin cua tung customer vao vector.

#endif