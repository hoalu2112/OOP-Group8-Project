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

class Giftcode {
private:
	string m_code;
	double m_token=0;
public:
	Giftcode(string CODE, double Token) {
		//cout << (int)m_token << endl;
		this->m_code = CODE;
		this->m_token = Token;
		cout << m_token << " " << Token << endl;
	}
	Giftcode(const Giftcode &another) {
		this->m_code = another.m_code;
		this->m_token = another.m_token;
	}
	bool check(string code) { return m_code == code; }
	double Get_token() { return this->m_token; }
	string get_code() { return m_code; }
};

void MakeListofCode(vector<Giftcode>& code);
class Customer{
protected:
	string m_cusName; //ten dang nhap.
	string m_cusPass; //mat khau.
	int m_flag; // khach hang than thiet. 1: discount 10%.
	double m_tokens; // tokens left in account.
	vector <Transaction> m_trans;//  lich su giao dich;

public:
	int Total_amount() {
		int total=0;
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
	void Menu(Store& store );
	bool check_user(string user) { return this->m_cusName == user; }
	bool check_pass(string pass) { return this->m_cusPass == pass; }
};
void makeListOfCustomers(vector<Customer>& customer); // doc file Customer.txt --> luu het cac thong tin cua tung customer vao vector.

#endif
