#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_
#include<iostream>
#include <string>
#include "Static/Tokenizer.h"
#include "Static/Date.h"
using namespace std;
class Transaction {
private:
	int id; //id cua album da mua
	Date date; // ngay giao dich
	int amount;// so luong album do da mua.
	double total_price; // tong tien cua cuoc giao dich;
public:
	Transaction();
	Transaction(int ID, Date DATE, int Amount, double TOTAL_price) {
		id = ID;
		date = DATE;
		total_price = TOTAL_price;
		amount = Amount;
	}
	Transaction(const Transaction& p);
	string toString();
	Transaction& stringToTransaction(string transaction);
	void printHistoryTransaction();
	int GetAmount() { return amount; }
};

#endif