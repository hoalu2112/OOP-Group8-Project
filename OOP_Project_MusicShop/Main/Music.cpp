#define _CRT_SECURE_NO_WARNINGS
#include "Music.h"


Store::Store() {
	ifstream fin;
	fin.open("..\\..\\Store.txt");
	if (!fin.is_open()) {
		cout << "Can not open file store." << endl;
		return;
	}
	else {
		makeListOfAlbums(this->m_album);
		int num_albums; //number of albums.
		fin >> num_albums;
		for (int i = 0; i < num_albums; i++) {
			int fake_id;
			fin >> fake_id;

			int import_album;
			fin >> import_album;
			this->m_import.push_back(import_album);


			int export_album;
			fin >> export_album;
			this->m_export.push_back(export_album);
		}
		fin.close();
	}
}



vector<Song> Song::readFile(int id) {
	string link_album = "..\\..\\Album\\";
	stringstream ss;
	ss << link_album << id << "\\Song_" << id << ".txt";

	vector <Song> songs;
	ifstream fin;
	fin.open(ss.str().c_str());
	if (!fin.is_open()) {
		cout << "Can not open file Song" << endl;
	}
	else {
		int song_numbers;
		fin >> song_numbers;
		fin.ignore();
		
		for (int i = 0; i < song_numbers; i++) {
			string name_song;
			getline(fin, name_song);
			this->m_name = name_song;

			string name_singers;
			getline(fin, name_singers);
			this->m_singer = Tokenizer::split(name_singers, "-");

			string name_authors;
			getline(fin, name_authors);
			this->m_author = Tokenizer::split(name_authors, "-");

			songs.push_back(*this);
		}

		fin.close();
	}

	return songs;
}

void Song::printInfoSong() {
	cout << "Track:" << this->m_name << endl;
	cout << "Singers: ";
	for (int i = 0; i < this->m_singer.size(); i++) {
		if (i == this->m_singer.size() - 1) {
			cout << this->m_singer[i];
			break;
		}
		cout << this->m_singer[i] << " x ";
	}
	cout << endl;
	cout << "Authors: ";
	for (int i = 0; i < this->m_author.size(); i++) {
		if (i == this->m_author.size() - 1) {
			cout << this->m_author[i];
			break;
		}
		cout << this->m_author[i] << " x ";
	}
	cout << endl;

}

Album::Album(int id) {
	string link_album = "..\\..\\Album\\";
	stringstream ss;
	ss << link_album << id <<"\\Info_" << id << ".txt";

	ifstream fin;
	fin.open(ss.str().c_str());
	if (!fin.is_open()) {
		cout << "Can not open file info id" << endl;
	}
	else {
		this->m_id = id;
		string name;
		getline(fin, name);
		this->m_albumName = name;

		string link_song;
		getline(fin, link_song);
		this->m_demo = link_song;

		string link_poster;
		getline(fin, link_poster);
		this->m_poster = link_poster;

		string release;
		getline(fin, release);
		this->m_release = this->m_release.parse(release);

		int price;
		fin >> price;
		this->m_price = price;

		int rateCounts;
		fin >> rateCounts;
		this->m_rateCounts = rateCounts;

		double total_rate;
		fin >> total_rate;
		this->m_totalPoint = total_rate;

		Song song;
		this->m_song = song.readFile(id);

		fin.close(); // close file.
	}
}

void Album::printPoster() {
	system("cls");
	ifstream f1;
	FILE* f = NULL;
	Color a;
	int width = 0;
	int height = 0;
	Pixel_Array pa;
	BMPFile bmp;
	is_bitmap_file(f, this->m_poster);
	readBmpHeader(f, bmp, this->m_poster);
	readBmpDib(f, bmp, this->m_poster);
	readBmpPixelArray(f, bmp, this->m_poster);

	draw(bmp);
	getchar();
	Sleep(500);
	system("pause");

	//getchar();
	releaseBmpPixelArray(bmp);
}

void Album::printInfo() {
	cout << "___________________________INFO OF THE ALBUM___________________________" << endl;
	cout << "ID: " << this->m_id << endl;
	cout << "Album's name: " << this->m_albumName << endl;
	cout << "Tokens: " << this->m_price << endl;
	cout << "Date release: " << this->m_release << endl;
	cout << "Rate: " << this->m_totalPoint / this->m_rateCounts << endl << endl;
	cout << "___________________________INFO OF THE ALBUM'S SONGS___________________________" << endl;
	cout << "Numbers of song: " << this->m_song.size() << endl << endl;
	for (int i = 0; i < this->m_song.size(); i++) {
		this->m_song[i].printInfoSong();
		cout << endl;
	}
	/*system("pause");
	system("cls");*/

}

void printListOfAlbums(const Store& store) {
	cout << "List of albums:" << endl;
	for (int i = 0; i < store.m_album.size(); i++) {
		cout << i + 1 << ">" << store.m_album[i].m_albumName << endl;
	}
}
void Album::playDemo() {
	cout << "~~~Enjoy the demo, you have 30s (-_^)";
	const wstring my_str(this->m_demo.begin(), this->m_demo.end()); // convert string to wstring.
	LPCWSTR wide_string; //define an array with size of my_str + 1
	wide_string = my_str.c_str();
	PlaySound(my_str.c_str(), NULL, SND_NODEFAULT);

	system("pause");
}

void Album::rateAlbum() {

	double rate;
	cout << "Enter your rate (max 5*): ";
	cin >> rate;
	while (rate < 0 || rate > 5) {
		cout << "Invalid!!" << endl;
		cout << "Enter your rate (max 5*): ";
		cin >> rate;
	}
	this->m_rateCounts++;
	this->m_totalPoint += rate;
	cout << "Thank you for your survey (^-^)" << endl << endl;
	this->writeFileInfo();
}

void Album::writeFileInfo() {
	string link_album = "..\\..\\Album\\";
	stringstream ss;
	ss << link_album << this->m_id << "\\Info_" << this->m_id << ".txt";

	ofstream fout;
	fout.open(ss.str().c_str());
	if (!fout.is_open()) {
		cout << "Can not override file." << endl;
	}
	else {
		fout << this->m_albumName << endl;
		fout << this->m_demo << endl;
		fout << this->m_poster << endl;
		fout << this->m_release.toString() << endl;
		fout << this->m_price << endl;
		fout << this->m_rateCounts << endl;
		fout << this->m_totalPoint << endl;
		fout.close();
	}
}






void searchAlbum(Store& store) {
	cout << "__________________________________SEARCH ALBUM________________________________________" << endl;

	string search;
	cout << "\\(^O^)/? :";
	getline(cin, search);
	getline(cin, search);
	search = _strupr((char*)search.c_str()); //UPPER letters.

	int count = 0; // increase when can not find result.

	for (int i = 0; i < store.m_album.size(); i++) {

		const char* name = strstr(search.c_str(), store.m_album[i].m_albumName.c_str()); //search by name.
		 
		const char* release_date = strstr(search.c_str(), store.m_album[i].m_release.toString().c_str());//search by release date.

		//search by price.
		stringstream s;
		s << store.m_album[i].m_price;
		const char* price = strstr(search.c_str(), s.str().c_str());

		//search by id.
		stringstream ss;
		ss << store.m_album[i].m_id;
		const char* id = strstr(search.c_str(), ss.str().c_str());

		if (name || release_date || price || id) {
			store.m_album[i].printInfo();
			cout << endl;
		}
		else {
			count++;
		}
	}
	if(count == store.m_album.size())
		cout << "(-_-) Can't find your album." << endl;
	return;

}


void printBestRate_Seller(const Store& store)
{
	cout << "_____Best Rate:______" << endl;
	double best_rate = store.m_album[0].m_totalPoint / store.m_album[0].m_rateCounts; // assigned max for first element.

	for (int i = 1; i < store.m_album.size(); i++) {
		if (store.m_album[i].m_totalPoint / store.m_album[i].m_rateCounts > best_rate) {
			best_rate = store.m_album[i].m_totalPoint / store.m_album[i].m_rateCounts;
		}
	}
	for (int i = 0; i < store.m_album.size(); i++) {
		if (store.m_album[i].m_totalPoint / store.m_album[i].m_rateCounts == best_rate) {
			cout << "ID: " << store.m_album[i].m_id << endl;
			cout << "Album's name: " << store.m_album[i].m_albumName << endl;
			cout << "Tokens: " << store.m_album[i].m_price << endl;
			cout << "Date release: " << store.m_album[i].m_release << endl;
			cout << "Rate: " << store.m_album[i].m_totalPoint / store.m_album[i].m_rateCounts << endl << endl;
		}
	}

	cout << "_____Best Seller:______" << endl;
	int best_sell = store.m_export[0];
	for (int i = 1; i < store.m_export.size(); i++) {
		if (store.m_export[i] > best_sell) {
			best_sell = store.m_export[i];
		}
	}

	for (int i = 1; i < store.m_export.size(); i++) {
		if (store.m_export[i] == best_sell) {
			cout << "ID: " << store.m_album[i].m_id << endl;
			cout << "Album's name: " << store.m_album[i].m_albumName << endl;
			cout << "Tokens: " << store.m_album[i].m_price << endl;
			cout << "Date release: " << store.m_album[i].m_release << endl;
			cout << "Rate: " << store.m_album[i].m_totalPoint / store.m_album[i].m_rateCounts << endl;
			cout << "Total Sale: " << best_sell << endl << endl;
		}
	}
}

void Store::importItem(string ID, int items)
{
	int i;
	for (i = 0; i < this->m_album.size(); i++) {
		if (stoi(ID) == m_album[i].getID()) {
			this->m_import[i] += items;
			cout << "Import succeed\n";
			break;
		}
	}
	if (i >= this->m_album.size()) {
		cout << "!! ID not found !!\n";
	}
}

void Store::exportItem(string ID, int items)
{
	int i;
	for (i = 0; i < this->m_album.size(); i++) {
		if (stoi(ID) == m_album[i].getID()) {
			this->m_export[i] += items;
			cout << "Export succeed\n";
			break;
		}
	}
	if (i >= this->m_album.size()) {
		cout << "!! ID not found !!\n";
	}
}

int Store::calcProfit()
{
	int profit = 0;
	for (int i = 0; i < m_album.size(); i++) {
		profit += m_export[i] * m_album[i].getPrice();
	}
	return profit;
}

int Store::calcLeavings()
{
	int leavings = 0;
	for (int i = 0; i < m_album.size(); i++) {
		leavings = m_import[i] - m_export[i];
	}
	return leavings;
}

int Store::calcItemSold()
{
	int items = 0;
	for (int i = 0; i < m_album.size(); i++) {
		if (m_export[i] != 0) {
			items++;
		}
	}
	return items;
}

int Store::totalExport()
{
	int out = 0;
	for (int i = 0; i < m_album.size(); i++) {
		out += m_export[i];
	}
	return out;
}

void makeListOfAlbums(vector<Album>& album) {
	ifstream fin;
	fin.open("..\\..\\Album\\ID_Album.txt");
	if (!fin.is_open()) {
		cout << "Can not open file album" << endl;
		return;
	}
	else {
		int numbers_of_album;
		fin >> numbers_of_album;
		vector<int> album_id;
		for (int i = 0; i < numbers_of_album; i++) {
			int temp_id;
			fin >> temp_id;
			album_id.push_back(temp_id);
		}

		for (int i = 0; i < album_id.size(); i++) {
			Album temp_album(album_id[i]);
			album.push_back(temp_album);
		}
		fin.close();
	}
}


//CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER //CUSTOMER 
void albumOption(Store& store) {
	printListOfAlbums(store);
	cout << "______Album's options:" << endl;
	cout << "1> Print Information Of The Album." << endl;
	cout << "2> Play Demo(30s) From The Album." << endl;
	cout << "3> Rate The Album." << endl;
	cout << "4> Back. " << endl;

	int album_option;
	cout << "__Enter your choice: ";
	cin >> album_option;

	while (album_option < 0 || album_option > 4) {
		cout << "Invalid!!" << endl;
		cout << "__Enter your choice: ";
		cin >> album_option;
	}
	if (album_option == 4) {
		return;
	}

	int album_order;
	cout << "__Enter album's order: "; //so thu tu cua album.
	cin >> album_order;
	while (album_order <= 0 || album_order > store.m_album.size()) {
		cout << "Invalid!!" << endl;
		cout << "__Enter album's order: ";
		cin >> album_order;
	}

	if (album_option == 1) {
		store.m_album[album_order - 1].printPoster();
		store.m_album[album_order - 1].printInfo();
		albumOption(store);
	}
	else if (album_option == 2) {
		store.m_album[album_order - 1].playDemo();
		albumOption(store);
	}
	else if (album_option == 3) {
		store.m_album[album_order - 1].rateAlbum();
		albumOption(store);
	}
}

int Album::getID() {
	return m_id;
}

int Album::getPrice() {
	return m_price;
}
void Album::editAlbumName(string name) {
	this->m_albumName = name;
}

void Album::editPrice(int price) {
	this->m_price = price;
}

void Album::editReleaseDate(string date) {
	this->m_release = this->m_release.parse(date);
}

void Album::albumOverwrite_Info() {
	string link_album = "..\\..\\Album\\";
	stringstream ss;
	ss << link_album << this->m_id << "\\Info_" << this->m_id << ".txt";

	ofstream ofs;
	ofs.open(ss.str().c_str());
	if (!ofs.is_open()) {
		cout << "!!Can not open file info id!!" << endl;
		return;
	}
	else {
		ofs << this->m_albumName << endl;
		ofs << this->m_demo << endl;
		ofs << this->m_poster << endl;
		ofs << this->m_release.toString() << endl;
		ofs << this->m_price << endl;
		ofs << this->m_rateCounts << endl;
		ofs << this->m_totalPoint << endl;
		ofs.close();
	}
}

void Store::overwriteStore_txt() {
	ofstream ofs;
	ofs.open("..\\..\\Store.txt");
	if (!ofs.is_open()) {
		cout << "!!Can not open file store.!!" << endl;
		return;
	}
	else {
		ofs << this->m_album.size() << endl;
		for (int i = 0; i < this->m_album.size(); i++) {
			ofs << this->m_album[i].getID() << endl;
			ofs << this->m_import[i] << endl;
			ofs << this->m_export[i] << endl;
		}
		ofs.close();
	}
}

void Store::edit() {
	string id;
	int choice;
	cin.ignore();
	printListOfAlbums(*this);
	cout << "__Enter album's order: ";
	cin >> choice;
	id = to_string(this->get_album()[choice - 1].getID());
	int i;
	for (i = 0; i < this->m_album.size(); i++) {
		if (stoi(id) == m_album[i].getID()) {
			int choice;
			cout << "1> Edit album's name.\n";
			cout << "2> Edit album's price.\n";
			cout << "3> Edit album's release date.\n";
			cout << "4> Exit.\n";
			cout << "\n__Enter your choice: ";
			cin >> choice;
			while (choice <= 0 || choice >= 5) {
				cout << "Invalid!!\n";
				cout << "__Enter your choice: ";
				cin >> choice;
			}
			if (choice == 1) {
				string name;
				cout << "Current name: " << this->m_album[i].getName() << endl;
				cin.ignore();

				cout << "__Enter new name of album: ";
				getline(cin, name);
				this->m_album[i].editAlbumName(name);
			}
			else if (choice == 2) {
				int price;
				cout << "Curret price: " << this->m_album[i].getPrice() << endl;
				cout << "__Enter new price of album: ";
				cin >> price;
				this->m_album[i].editPrice(price);
			}
			else if (choice == 3) {
				string date;
				cout << "Current release date: " << this->m_album[i].getReleaseDate() << endl;
				cin.ignore();
				cout << "__Enter new release date(DD/MM/YYYY): ";
				getline(cin, date);
				this->m_album[i].editReleaseDate(date);
			}

			this->m_album[i].albumOverwrite_Info();
			this->m_album[i].print_short_info();
			break;
		}
	}
	if (i >= this->m_album.size())
		cout << "!!ID not found.!!\n";
}

void Album::print_short_info() {
	cout << "___________________________INFO OF THE ALBUM___________________________" << endl;
	cout << "ID: " << this->m_id << endl;
	cout << "Album's name: " << this->m_albumName << endl;
	cout << "Tokens: " << this->m_price << endl;
	cout << "Date release: " << this->m_release << endl;
	cout << "Rate: " << this->m_totalPoint / this->m_rateCounts << endl << endl;
}