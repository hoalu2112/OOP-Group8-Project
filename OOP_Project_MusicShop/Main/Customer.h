#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
#include <iostream>
#include <string.h> 
#include <vector>
#include <fstream>
#include "Transaction.h"
using namespace std;


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
	friend void overwriteFileCustomer_txt(vector<Customer> customer); //ghi lai file Customer.TXT neu co chinh sua.
	friend void overwriteCustomerName_txt(vector<Customer> customer,string username); //ghi lai file tenkhachhang.TXT neu co chinh sua.
	friend void changePasswordCustomer(vector<Customer>customer, string username); // customer co the doi mat khau cua ho.
	void print() {
		cout << this->m_trans.size();
	}
};
void makeListOfCustomers(vector<Customer>& customer); // doc file Customer.txt --> luu het cac thong tin cua tung customer vao vector.

#endif
