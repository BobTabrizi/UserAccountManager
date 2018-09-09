#ifndef LinkedUsers_H
#define LinkedUsers_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
class User {
	string username;
	string password;
	string type;
	string email;
	User* next;
public:
	User() {
		username = "";
		password = "";
		type = "";
		email = "";
		next = NULL;
	}
	User(string uname, string pwd, string typ, string em) {
		username = uname;
		password = pwd;
		type = typ;
		email = em;
		next = NULL;
	}
	void setNext(User* nextptr) {
		next = nextptr;
	}
	User* getNext() {
		return next;
	}
	string getUsername() {
		return username;
	}
	string getEmail() {
		return email;
	}
	string getType() {
		return type;
	}
	string getPassword() {
		return password;
	}
	bool checkPassword(string pwd) {
		if (password == pwd)
			return true;
		return false;
	}
};

User* login(User* head, string uname, string pwd) {
	User* curr = head->getNext();
	while (curr != NULL) {
		if (uname == curr->getUsername() && curr->checkPassword(pwd)) {
			return curr;
		}
		curr = curr->getNext();
	}
	return NULL;
}

void show(User* curr) {
	while (curr != NULL) {
		cout << "USERNAME(" << curr->getUsername() << ") EMAIL(" << curr->getEmail() << ")\n";
		curr = curr->getNext();
	}
}

void add(User* head) {
	cout << "Please enter username, password, role and email: ";
	string eachLine;
	string uname, pwd, typ, em;
	cin >> uname >> pwd >> typ >> em;
	User* newuser = new User(uname, pwd, typ, em);
	User* curr = head;
	while (curr->getNext() != NULL) {
		curr = curr->getNext();
	}
	curr->setNext(newuser);
	cout << "Successfully added\n";
}

void deleteuser(User* head) {
	string name;
	cout << "Please enter the username: ";
	cin >> name;
	User* curr = head->getNext();
	User* prev = head;
	while (curr != NULL) {
		if (name == curr->getUsername()) {
			prev->setNext(curr->getNext());
			delete(curr);
			cout << "Successfully deleted\n";
			return;
		}
		curr = curr->getNext();
		prev = prev->getNext();
	}
	cout << "Not found\n";
}


void saveToFile(char* fname, User* curr) {
	ofstream fp(fname);
	while (curr != NULL) {
		fp << curr->getUsername() << " " << curr->getPassword() << " " << curr->getType() << " " << curr->getEmail() << endl;
		curr = curr->getNext();
	}
	fp.close();
}
#endif
