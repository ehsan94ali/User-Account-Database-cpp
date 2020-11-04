//libraries
#include <iostream>
#include <string>
#include <stdlib.h>
#include <direct.h>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>
#include "UserAccount.h"
using namespace std;


//function protocols
int mainMenu();
void createUserAccount(UserAccount*, vector<string>&, vector<string>&, vector<string>&, vector<string>&);
//database functions
bool usernameFound(string, vector<string>&);
bool phoneNumberFound(string, vector<string>&);
bool emailFound(string, vector<string>&);
string convertToHash(string);
string reverseHash(string);
void update_database(UserAccount*, vector<string>&, vector<string>&, vector<string>&, vector<string>&);
//verify functions
bool verifyUsername(string);
bool verifyPassword(string);
bool verifyPhoneNumber(string);
void formatPhoneNumber(string&);
bool verifyEmail(string);


int main() {

	bool database_online = false;
	vector<string> usernames, hashes, phoneNumbers, emails;

	
	//create/open/download database
	if (fstream("Databases/account_database.xlsx")) //if database already exists
		database_online = true;
	else
		_mkdir("Databases");

	fstream userAccount_database("Databases/account_database.xlsx", ios::in | ios::out | ios::app);
	fstream username_database("Databases/username_database.txt", ios::in | ios::out | ios::app);
	fstream hash_database("Databases/hash_database.txt", ios::in | ios::out | ios::app);
	fstream phoneNumber_database("Databases/phoneNumber_database.txt", ios::in | ios::out | ios::app);
	fstream email_database("Databases/email_database.txt", ios::in | ios::out | ios::app);

	if (!database_online) {
		userAccount_database << "Username\tHash-Password\tPhone Number\tEmail Address" << endl;
	}
	else {
		string data;
		//download usernames
		while (!username_database.eof()) {
			getline(username_database, data);
			usernames.push_back(data);
		}
		//download hashes
		while (!hash_database.eof()) {
			getline(hash_database, data);
			hashes.push_back(data);
		}
		//download phoneNumbers
		while (!phoneNumber_database.eof()) {
			getline(phoneNumber_database, data);
			phoneNumbers.push_back(data);
		}
		//download emails
		while (!email_database.eof()) {
			getline(email_database, data);
			emails.push_back(data);
		}
	}

	int userInput = mainMenu();
	cout << "userInput = " << userInput << endl;
	
	if (userInput == 1) {
		//create user account
		UserAccount* newAccount = &UserAccount();
		createUserAccount(newAccount, usernames, hashes, phoneNumbers, emails);
		//update database files
		userAccount_database << newAccount->getUsername() << "\t" << newAccount->getHash() << "\t" << newAccount->getPhoneNumber() << "\t" << newAccount->getEmail() << endl;
		username_database << newAccount->getUsername() << endl;
		hash_database << newAccount->getHash() << endl;
		phoneNumber_database << newAccount->getPhoneNumber() << endl;
		email_database << newAccount->getEmail() << endl;



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

	int userInput_int = userInput - '0';
	return userInput_int;
}
void createUserAccount(UserAccount *newUser, vector<string> &usernames, vector<string> &hashes, vector<string> &phoneNumbers, vector<string> &emails) {

	string input;
	cout << "\nCreate New Account" << endl;
	cout << "===================" << endl;

	//username
	do {
		cout << "\nUsername: ";
		cin >> input;

		if (!verifyUsername(input))
			cout << "ERROR. Username '" << input << "' is invalid. Username CANNOT contain spaces." << endl; //ERROR message
		else if (usernameFound(input, usernames))
			cout << "ERROR. Username '" << input << "' already exists." << endl; //ERROR message
		else
			cout << "Username '" << input << "' is valid and available." << endl; //confirmation message

	} while (usernameFound(input, usernames) || !verifyUsername(input));
	newUser->setUsername(input);

	//password
	do {
		cout << "\nPassword: ";
		cin >> input;

		if (!verifyPassword(input))
			cout << "ERROR. Invalid password. Password must be at least 8 characters " << endl
			<< "and contain a special character, a number, AND a capital letter." << endl; //ERROR message
		else
			cout << "Password accepted." << endl; //confirmation message

		//add *verify password* option by entering twice

	} while (!verifyPassword(input));
	newUser->setHash(convertToHash(input));

	//phone number
	do {
		cout << "\nPhone Number: ";
		cin >> input;

		if (!verifyPhoneNumber(input)) {
			cout << "ERROR. Phone Number '" << input << "' is invalid. Phone number must only contain 10 digits" << endl; //ERROR message
		}
		else if (phoneNumberFound(input, phoneNumbers))
			cout << "ERROR. Phone Number '" << input << "' is already registered with another account." << endl; //ERROR message
		else
			cout << "Phone Number '" << input << "' is now linked to your account." << endl; //confirmation message

	} while (phoneNumberFound(input, phoneNumbers) || !verifyPhoneNumber(input));
	formatPhoneNumber(input);
	newUser->setPhoneNumber(input);

	//email address
	do {
		cout << "\nEmail Address: ";
		cin >> input;

		if (!verifyEmail(input))
			cout << "ERROR. Email Address '" << input << "' is invalid." << endl; //ERROR message
		else if (emailFound(input, emails))
			cout << "ERROR. Email Address '" << input << "' is already registered with another account." << endl; //ERROR message
		else
			cout << "Email Address '" << input << "' is now linked to your account." << endl; //confirmation message

	} while (emailFound(input, emails) || !verifyEmail(input));
	newUser->setEmail(input);

	update_database(newUser, usernames, hashes, phoneNumbers, emails);
	cout << "Account successfully created." << endl; //confirmation message
}




bool usernameFound(string u, vector<string> &usernames) {
	//make sure username doesn't already exist in user account database
	return binary_search(usernames.begin(), usernames.end(), u);
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
	//make password restrictions (i.e. special character, number, capital letter, lowercase letter, minimum of 8 characters)
	if (p.length() < 8)
		return false;

	bool containsSpecial=false, containsCapital=false, containsLower=false, containsNumber=false;
	for (char c : p) {
		if (containsSpecial && containsCapital && containsLower && containsNumber)
			return true;
		else {
			if (isupper(c))
				containsCapital = true;
			else if (islower(c))
				containsLower = true;
			else if (isdigit(c))
				containsNumber = true;
			else
				containsSpecial = true;
		}
	}

	return (containsSpecial && containsCapital && containsLower && containsNumber);
}
bool phoneNumberFound(string pn, vector<string> &phoneNumbers) {
	//make sure phone number (that has been formatted) doesn't already exist in user account database
	formatPhoneNumber(pn);
	return binary_search(phoneNumbers.begin(), phoneNumbers.end(), pn);
}
bool verifyPhoneNumber(string pn) {
	//make sure string contains 10 digits
	if (pn.length() > 14)
		return false;
	int digitCounter = 0;
	for (int i = 0; i < pn.length(); i++) {
		if (isalpha(pn.at(i)))
			return false;
		else if (isdigit(pn.at(i)))
		{
			digitCounter++;
			if (digitCounter > 10)
				return false;
		}
	}
	if (digitCounter != 10)
		return false;
	else
		return true;
}
void formatPhoneNumber(string &pn) {
	//format phone number to be just 10 numbers, no other characters
	string format = "";
	for (int i = 0; i < pn.length(); i++) {
		if (isdigit(pn.at(i)))
			format += pn.at(i);
	}
	pn = format;
}
bool emailFound(string e, vector<string> &emails) {
	//make sure email doesn't already exist in user account database
	return binary_search(emails.begin(), emails.end(), e);
}
bool verifyEmail(string e) {
	//make sure email is in correct format with regex (contains @ and . followed by 3 characters)
	regex email_format("[\\w.]+@\\w+\\.(com|net|gov|edu|org|ai|io)");
	if (regex_match(e, email_format))
		return true;
	else
		return false;

}
string convertToHash(string p) {
	//convert string (password) into a hash using a hash algorithm
	for (int i = 0; i < p.length(); i++)
		p[i] = p[i] + 5;
	return p; //delete code, only here for debugging
}
string reverseHash(string h) {
	//convert string (hash) into a password using a reverse-hash algorithm
	for (int i = 0; i < h.length(); i++)
		h[i] = h[i] - 5;
	return h; //delete code, only here for debugging
}
void update_database(UserAccount *user, vector<string> &usernames, vector<string> &hashes, vector<string> &phoneNumbers, vector<string> &emails) {
	//add user credentials to database
	usernames.push_back(user->getUsername());
	hashes.push_back(user->getHash());
	phoneNumbers.push_back(user->getPhoneNumber());
	emails.push_back(user->getEmail());
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu