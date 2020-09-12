#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
#include <iostream>
#include <string.h> 
#include <vector>
#include <fstream>
#include "Transaction.h"
#include "Music.h"
using namespace std;

class Store;

class Customer{
protected:
	string m_cusName; //ten dang nhap.
	string m_cusPass; //mat khau.
	int m_flag; // khach hang than thiet. 1: discount 10%.
	double m_tokens; // tokens left in account.
	vector <Transaction> m_trans;//  lich su giao dich;

public:
	Customer(string username);
	double getTokens() { return m_tokens; } // xem tokens con lai trong tai khoan.
	void viewTransactionHistory(vector<Customer>customer, string username); //xem lich su giao dich.
	void overwriteFileCustomer_txt(vector<Customer> customer); //ghi lai file Customer.TXT neu co chinh sua.
	void overwriteCustomerName_txt(vector<Customer> customer,string username); //ghi lai file tenkhachhang.TXT neu co chinh sua.
	void changePasswordCustomer(vector<Customer>customer, string username); // customer co the doi mat khau cua ho.
	void print();
	void Menu(Store& store );
	bool check_user(string user) { return this->m_cusName == user; }
	bool check_pass(string pass) { return this->m_cusPass == pass; }
};
void makeListOfCustomers(vector<Customer>& customer); // doc file Customer.txt --> luu het cac thong tin cua tung customer vao vector.

#endif
