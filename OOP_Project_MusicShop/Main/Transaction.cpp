#include "Transaction.h"

Transaction::Transaction() {
	this->id = 0;
	this->amount = 0;
	this->total_price = 0;
}

Transaction::Transaction(const Transaction& p) {
	this->id = p.id;
	this->amount = p.amount;
	this->total_price = p.total_price;
	this->date = p.date;
}

string Transaction::toString() {
	stringstream ss;
	ss << this->id << "-" << this->date.toString() << "-" << this->amount << "-" << this->total_price;
	return ss.str();
}

Transaction& Transaction::stringToTransaction(string transaction) {
	vector<string> temp = Tokenizer::split(transaction, "-");
	this->id = stoi(temp[0]);
	this->date = this->date.parse(temp[1]);
	this->amount = stoi(temp[2]);
	this->total_price = stoi(temp[3]);

	return *this;
}
void Transaction::printHistoryTransaction() {
	cout << "ID: " << this->id << endl;
	cout << "Transaction Date:" << this->date << endl;
	cout << "Amount: " << this->amount << endl;
	cout << "Total Price: " << this->total_price << endl << endl;
}