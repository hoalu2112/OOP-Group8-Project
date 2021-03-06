#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "Customer.h"
#include<iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Static/Tokenizer.h"
#include "Static/Date.h"
//used to play demo song.
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//used tp print poster.
#include "Static/bitmap.h"
using namespace std;


class Store;

class Giftcode {
private:
	string m_code;
	double* m_token;
public:
	Giftcode(string& CODE, double& Token) {
		//cout << (int)m_token << endl;
		this->m_code = CODE;
		this->m_token = new double;
		*this->m_token = Token;
	}
	Giftcode(const Giftcode& another) {
		this->m_code = another.m_code;
		this->m_token = new double(*another.m_token);
	}
	bool check(string code) { return m_code == code; }
	double Get_token() {
		return *m_token;
	}
	string get_code() { return m_code; }
	~Giftcode() {
		delete this->m_token;
	}
};

void MakeListofCode(vector<Giftcode>& code);
class Song {
protected:
	string m_name; //name of the song.
	vector<string> m_singer;
	vector<string> m_author;
public:
	vector<Song> readFile(int id); //read file "Song_ID.txt".
	void printInfoSong();
};

class Album {
protected:
	int m_id; // id of album.
	string m_albumName; //name album.
	string m_demo;//link to 30s.
	string m_poster;//link to poster.
	Date m_release; // date release album.
	int m_price;// price by tokens.
	int m_rateCounts;// times rate from customers.
	double m_totalPoint; // total rate from customers.
	vector<Song> m_song; // list songs of album.
public:
	Album(int id); // constructor used to read file which relate to the album (ID).
	void printPoster(); // print the poster of the album (bmp files).
	void printInfo(); // print every information of the album.
	friend void printListOfAlbums(const Store& store);//CUSTOMER.
	void playDemo(); //listen to 30s demo of special song of the album.
	void rateAlbum(); //customer rate album quality (max 5*).//CUSTOMER.
	void writeFileInfo(); //override to text file "INFO_ID.txt".
	friend void searchAlbum(Store& store); // search info of albums //CUSTOMER.
	friend void printBestRate_Seller(const Store& store); // print best seller/ best rate for customer.
	friend void albumOption(Store& store);
	int getID();
	int getPrice();

	int Tel_price() { return m_price; }
	void editPrice(int price);
	void editAlbumName(string name);
	void editReleaseDate(string date);
	void albumOverwrite_Info();
	void print_short_info();
	string getName() { return m_albumName; }
	string getReleaseDate() { return m_release.toString(); }
};

class Store {
protected:
	vector<Album> m_album;
	vector<int> m_import;
	vector<int> m_export; //sold.
public:
	vector <Giftcode> Code;
	Store();
	friend void printBestRate_Seller(const Store& store); // print best seller/ best rate for customer.
	friend void printListOfAlbums(const Store& store);
	friend void searchAlbum(Store& store);
	friend void albumOption(Store& store);
	void importItem(string ID, int items);
	void exportItem(string ID, int items);
	int calcProfit();
	int calcLeavings();
	int calcItemSold();
	int totalExport();
	int Cal_albumI_leaveing(int i) {
		return (m_import[i - 1] - m_export[i - 1]);
	}
	double cal_price_AlbumI_quality(int i, int quality) {
		return (m_album[i - 1].getPrice() * quality);
	}
	void Buy_AlbumI(int i, int quality) {
		m_export[i - 1] += quality;
	}
	vector<Album> get_album() { return this->m_album; }
	Album getAlbum(int i) { return this->m_album[i]; }
	int getExport(int i) { return this->m_export[i]; }
	int getLeavings(int i) {
		if (this->m_import[i] >= this->m_export[i])
			return this->m_import[i] - this->m_export[i];
		else
			return 0;
	}
	void overwriteStore_txt();
	void edit();
};


void makeListOfAlbums(vector<Album>& album);
// read all file of Album "Info_ID.txt".

//CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER 
 // customer_choice =2
#endif