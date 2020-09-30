// User Account Database.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

//protocols
int mainMenu();
bool is_empty(fstream);

int main() {

	bool database_online = false;

	//determine if file already exists
	if (fstream("account_database.xlsx"))
		database_online = true;
	fstream userAccount_database("account_database.xlsx", ios::in | ios::out | ios::app); //open User Account database
	
	if (!database_online)
		userAccount_database << "Username\tPassword\tPhone Number" << endl;


	int userInput = mainMenu();

	userAccount_database.close();
}

int mainMenu() {

	char userInput;

	do {
		cout << "\nUser Account Database" << endl;
		cout << "=====================" << endl;
		cout << "1)Create New Account";
		cout << "\n2)Sign in" << endl;
		cout << "User input: ";
		cin >> userInput;

		if (userInput != '1' && userInput != '2')
			cout << "\nERROR. Invalid user input." << endl;
	} while (userInput != '1' && userInput != '2');

	int userInput_int = (int)userInput;
	return userInput_int;
}

bool is_empty(fstream &file) {
	
	return file.peek() == fstream::traits_type::eof();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
