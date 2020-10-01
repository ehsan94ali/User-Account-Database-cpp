//libraries
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "UserAccount.h"
using namespace std;

//function protocols
int mainMenu();
void createUserAccount();
bool usernameFound(string);
bool phoneNumberFound(string);
bool emailFound(string);
bool verifyUsername(string);
bool verifyPassword(string);
bool verifyPhoneNumber(string);
bool verifyEmail(string);
string convert_to_hash(string);
string reverseHash(string);
void add_user_to_database(UserAccount);

int main() {

	bool database_online = false;

	//create/open database
	if (fstream("account_database.xlsx"))
		database_online = true;
	fstream userAccount_database("account_database.xlsx", ios::in | ios::out | ios::app); //open User Account database
	if (!database_online)
		userAccount_database << "Username\tHash-Password\tPhone Number\tEmail Address\tPassword" << endl;


	int userInput = mainMenu();

	
	if (userInput == 1) {
		//create user account
		createUserAccount();


	}
	else {
		//user sign in
	}
	





	userAccount_database.close();
}






//function definitions
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
			cout << "\nERROR. Invalid user input." << endl; //ERROR message
	} while (userInput != '1' && userInput != '2');

	int userInput_int = (int)userInput;
	return userInput_int;
}
void createUserAccount() {

	string input;
	UserAccount newUser;


	cout << "\nCreate New Account" << endl;
	cout << "===================" << endl;

	//username
	do {
		cout << "\nUsername: ";
		cin >> input;

		if (!verifyUsername(input))
			cout << "ERROR. Username '" << input << "' is invalid. Username CANNOT contain spaces." << endl; //ERROR message
		else if (usernameFound(input))
			cout << "ERROR. Username '" << input << "' already exists." << endl; //ERROR message
		else
			cout << "Username '" << input << "' is valid and available." << endl;

	} while (usernameFound(input) || !verifyUsername(input));
	newUser.setUsername(input);

	//password
	do {
		cout << "\nPassword: ";
		cin >> input;

		if (!verifyPassword(input))
			cout << "ERROR. Invalid password. Password must contain " << endl
			<< "a special character, a number, AND a capital letter." << endl; //ERROR message
		else
			cout << "Password accepted." << endl;

		//add *verify password* option by entering twice

	} while (!verifyPassword(input));
	newUser.setHash(convert_to_hash(input));

	//phone number
	do {
		cout << "\nPhone Number: ";
		cin >> input;

		if (!verifyPhoneNumber(input))
			cout << "ERROR. Phone Number '" << input << "' is invalid." << endl; //ERROR message
		else if (phoneNumberFound(input))
			cout << "ERROR. Phone Number '" << input << "' is already registered with another account." << endl; //ERROR message
		else
			cout << "Phone Number '" << input << "' is now linked to your account." << endl;

	} while (phoneNumberFound(input) || !verifyPhoneNumber(input));
	newUser.setPhoneNumber(input);

	//email address
	do {
		cout << "\nEmail Address: ";
		cin >> input;

		if (!verifyEmail(input))
			cout << "ERROR. Email Address '" << input << "' is invalid." << endl; //ERROR message
		else if (emailFound(input))
			cout << "ERROR. Email Address '" << input << "' is already registered with another account." << endl; //ERROR message
		else
			cout << "Email Address '" << input << "' is now linked to your account." << endl;

	} while (emailFound(input) || !verifyEmail(input));
	newUser.setEmail(input);

	add_user_to_database(newUser);

	cout << "Account successfully created." << endl; //confirmation message
}




bool usernameFound(string u) {
	//make sure username doesn't already exist in user account database

}
bool verifyUsername(string u) {
	//make sure username doesn't contain spaces
	for (int i = 0; i < u.length(); i++) {
		if (isspace(u.at(i)))
			return false;
	}
	return true;
}
bool verifyPassword(string p) {
	//make password restrictions (i.e. special character, number, capital letter, lowercase letter)
}
bool phoneNumberFound(string pn) {
	//make sure phone number doesn't already exist in user account database
}
bool verifyPhoneNumber(string pn) {
	//make sure string contains 10 digits
}
bool emailFound(string e) {
	//make sure email doesn't already exist in user account database
}
bool verifyEmail(string e) {
	//make sure email is in correct format with regex (contains @ and . followed by 3 characters)
}
string convert_to_hash(string p) {
	//convert string (password) into a hash using a hash algorithm
}
string reverseHash(string h) {
	//convert string (hash) into a password using a reverse-hash algorithm
}
void add_user_to_database(UserAccount user) {

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
