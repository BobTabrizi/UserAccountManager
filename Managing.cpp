#include <iostream>
#include <string>
#include "LinkedUsers.h"
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Invalid Syntax\nUsage:\nManageLinkedUsers user-data-file-name\n";
		return 0;
	}
	User* head = new User();
	ifstream fp(argv[1]);
	if (fp.eof()) {
		cout << "Empty file, exiting!\n";
		return 0;
	}
	string eachLine;
	while (getline(fp, eachLine)) {
		stringstream ss(eachLine);
		string uname, pwd, typ, em;
		ss >> uname >> pwd >> typ >> em;
		User* newuser = new User(uname, pwd, typ, em);
		User* curr = head;
		while (curr->getNext() != NULL) {
			curr = curr->getNext();
		}
		curr->setNext(newuser);
	}
	fp.close();
	string uname;
	string pwd;
	cout << "username: ";
	cin >> uname;
	cout << "password: ";
	cin >> pwd;
	User* ptr = login(head, uname, pwd);
	if (ptr == NULL) {
		cout << "Invalid login\n";
		return 0;
	}
	cout << "Successful login\n";
	if (ptr->getType() == "reg") {
		cout << "USERNAME(" << ptr->getUsername() << ") EMAIL(" << ptr->getEmail() << ")\n";
		return 0;
	}
	while (true) {
		cout << "Enter a command (SHOW, ADD, DELETE, SAVE, EXIT): ";
		string comm;
		cin >> comm;
		if (comm == "EXIT" || comm == "exit") {
			cout << "Thank You\n";
			break;
		}
		else if (comm == "show" || comm == "SHOW") {
			show(head->getNext());
		}
		else if (comm == "add" || comm == "ADD") {
			add(head);
		}
		else if (comm == "DELETE" || comm == "delete") {
			deleteuser(head);
		}
		else if (comm == "SAVE" || comm == "save") {
			saveToFile(argv[1], head->getNext());
		}
		else {
			cout << "Invalid Command\n";
		}
	}
	return 0;
}
