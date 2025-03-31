//PasswordManagerXOR
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>


using namespace std;

string encryptDecrypt(string data, char key = 'K') {
	for (char& c : data) {
		c ^= key;
	}
	return data;
}

string generatePassword(int length) {

	const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
	string  password;
	for (int i = 0; i < length; ++i)
	{
		password += chars[rand() % chars.size()];
	}
	return password;
}

void savePassword(const string& service, const string& login, const string& passowrd) {
	ofstream file("passwords.txt", ios::app);
	if (file.is_open()) {
		file << service << " " << login << " " << encryptDecrypt(passowrd) << endl;
		file.close();
		cout << "Password saved!" << endl;
	}
	else
	{
		cerr << "File failed!" << endl;
	}
}


void findPassword(const string& service) {
	ifstream file("passwords.txt");
	if (!file) {
		cerr << "Error opening file!" << endl;
		return;
	}
	string line;
	bool found = false;
	while (getline(file, line)) {
		size_t firstSpace = line.find(' ');
		size_t secondSpace = line.find(' ', firstSpace + 1);

		if (firstSpace == string::npos || secondSpace == string::npos) {
			continue;
		}
		string serv = line.substr(0, firstSpace);
		string login = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
		string encryptedPassword = line.substr(secondSpace + 1);

		if (serv == service) {
			cout << "Service: " << serv << "\nLogin: " << login << "\nPassword: " << encryptDecrypt(encryptedPassword) << endl;
			found = true;
			break;
		}
	}
	file.close();

	if (!found) {
		cout << "Password not found." << endl;
	}
}
int main() {
	srand(time(nullptr));

	int choice;
	string service, login, password;

	while (true) {
		cout << "\nPassword manager:" << endl;
		cout << "1. Save password" << endl;
		cout << "2. Find password" << endl;
		cout << "3. Generate password" << endl;
		cout << "4. Exit" << endl;
		cout << "Choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter service: ";
			cin >> service;
			cout << "Enter your login: ";
			cin >> login;
			cout << "Enter your password: ";
			cin >> password;
			savePassword(service, login, password);
			break;
		case 2:
			cout << "Enter service: ";
			cin >> service;
			findPassword(service);
			break;
		case 3:
			int length;
			cout << "Enter password length: ";
			cin >> length;
			cout << "Generated password: " << generatePassword(length) << endl;
			break;
		case 4:
			return 0;
		default:
			cout << "Wrong choice!" << endl;
		}
	}
}
