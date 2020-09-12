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

class Song{
private:
	string m_name; //name of the song.
	vector<string> m_singer;
	vector<string> m_author;
public:
	vector<Song> readFile(int id); //read file "Song_ID.txt".
	void printInfoSong();
};

class Album {
private:
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
	Album (int id); // constructor used to read file which relate to the album (ID).
	void printPoster(); // print the poster of the album (bmp files).
	void printInfo(); // print every information of the album.
	friend void printListOfAlbums(vector<Album> album);//CUSTOMER.
	void playDemo(); //listen to 30s demo of special song of the album.
	void rateAlbum(); //customer rate album quality (max 5*).//CUSTOMER.
	void writeFileInfo(); //override to text file "INFO_ID.txt".
	friend void searchAlbum(vector<Album> album); // search info of albums //CUSTOMER.
	friend void printBestRate_Seller(vector<Album> album, Store store); // print best seller/ best rate for customer.
	int getID();
	int getPrice();
	
	int Tel_price() { return m_price; }
	
	
};

class Store {
private:
	vector<Album> m_album;
	vector<int> m_import;
	vector<int> m_export; //sold.
public: 
	Store();
	friend void printBestRate_Seller(vector<Album> album, Store store); // print best seller/ best rate for customer.
	void importItem(string ID, int items);
	void exportItem(string ID, int items);
	int calcProfit();
	int calcLeavings();
	int calcItemSold();
	int totalExport();
};

class Cart {
protected:
	vector<Album> m_album;
public:
	double total_price();
	void Buy_ALL(const Customer& Current_Cus);
	void add();
	void delete_album();
};


void makeListOfAlbums(vector<Album> &album); // read all file of Album "Info_ID.txt".

//CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER 
void albumOption(vector<Album> album); // customer_choice =2
#endif
