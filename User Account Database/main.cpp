//libraries
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <regex>
#include <vector>
#include "UserAccount.h"
using namespace std;

//function protocols
int mainMenu();
UserAccount* createUserAccount();
//database functions
void download_database(vector<string>&, vector<string>&, vector<string>&);
void download_usernames(vector<string>&);
void download_phoneNumbers(vector<string>&);
void download_emails(vector<string>&);
bool usernameFound(string);
bool phoneNumberFound(string);
bool emailFound(string);
string convert_to_hash(string);
string reverseHash(string);
void add_user_to_database(UserAccount*);
//verify functions
bool verifyUsername(string);
bool verifyPassword(string);
bool verifyPhoneNumber(string);
void formatPhoneNumber(string&);
bool verifyEmail(string);


int main() {

	bool database_online = false;
	vector<string> usernames, phoneNumbers, emails;

	//create/open/download database
	if (fstream("account_database.xlsx")) //if database already exists
		database_online = true;
	fstream userAccount_database("account_database.xlsx", ios::in | ios::out | ios::app); //open User Account database
	if (!database_online) {
		userAccount_database << "Username\tHash-Password\tPhone Number\tEmail Address\tPassword" << endl;
		fstream username_database("username_database.xlsx", ios::in | ios::out | ios::app);
		fstream phoneNumber_database("phoneNumber_database.xlsx", ios::in | ios::out | ios::app);
		fstream email_database("email_database.xlsx", ios::in | ios::out | ios::app);
	}
	download_database(usernames, phoneNumbers, emails);



	//DEBUGGING TOOL TO SEE FILE CONTENTS///////////////////////////////////////////////////////////////////////////////
	string line;
	int found;
	while (!userAccount_database.eof()) {
		getline(userAccount_database, line);
		cout << line << endl;
		found = line.find("Hash Password");
		if (found >= 0)
			cout << "Found in file" << endl;
		else
			cout << "Not found in file" << endl;

	}
	//^^^^^^^^ algorithm works, searches database line-by-line and compares literal string to string line
	
	//DEBUGGING TOOL TO SEE FILE CONTENTS///////////////////////////////////////////////////////////////////////////////


	int userInput = mainMenu();
	cout << "userInput = " << userInput << endl;
	
	if (userInput == 1) {
		//create user account
		UserAccount* newAccount = &UserAccount();
		newAccount = createUserAccount();


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
UserAccount* createUserAccount() {

	string input;
	UserAccount *newUser = &UserAccount();


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
			cout << "Username '" << input << "' is valid and available." << endl; //confirmation message

	} while (usernameFound(input) || !verifyUsername(input));
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
	newUser->setHash(convert_to_hash(input));

	//phone number
	do {
		cout << "\nPhone Number: ";
		cin >> input;

		if (!verifyPhoneNumber(input)) {
			cout << "ERROR. Phone Number '" << input << "' is invalid. Phone number must only contain 10 digits" << endl; //ERROR message
		}
		else if (phoneNumberFound(input))
			cout << "ERROR. Phone Number '" << input << "' is already registered with another account." << endl; //ERROR message
		else
			cout << "Phone Number '" << input << "' is now linked to your account." << endl; //confirmation message

	} while (phoneNumberFound(input) || !verifyPhoneNumber(input));
	newUser->setPhoneNumber(input);

	//email address
	do {
		cout << "\nEmail Address: ";
		cin >> input;

		if (!verifyEmail(input))
			cout << "ERROR. Email Address '" << input << "' is invalid." << endl; //ERROR message
		else if (emailFound(input))
			cout << "ERROR. Email Address '" << input << "' is already registered with another account." << endl; //ERROR message
		else
			cout << "Email Address '" << input << "' is now linked to your account." << endl; //confirmation message

	} while (emailFound(input) || !verifyEmail(input));
	newUser->setEmail(input);

	cout << "Account successfully created." << endl; //confirmation message
	return newUser;
}




bool usernameFound(string u) {
	//make sure username doesn't already exist in user account database
	return true; //delete code, only here for debugging
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
	regex special("~!@#$%^&*()_+=-`{}[]|:;'?/>.<,\\\"");
	regex number("1234567890");
	regex capital("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	regex lowercase("abcdefghijklmnopqrstuvwxyz");

	if (p.length() > 7 && regex_search(p, special) > 0 && regex_search(p, number) > 0 && regex_search(p, capital) > 0 && regex_search(p, lowercase) > 0)
		return true;
	else
		return false;

}
bool phoneNumberFound(string pn) {
	//make sure phone number (that has been formatted) doesn't already exist in user account database
	formatPhoneNumber(pn);
	//now read database and search for pn
	return true; //delete code, only here for debugging
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
void formatPhoneNumber(string& pn) {
	//format phone number to be just 10 numbers, no other characters
	string format = "";
	for (int i = 0; i < pn.length(); i++) {
		if (isdigit(pn.at(i)))
			format += pn.at(i);
	}
	pn = format;
}
bool emailFound(string e) {
	//make sure email doesn't already exist in user account database
	return true; //delete code, only here for debugging
}
bool verifyEmail(string e) {
	//make sure email is in correct format with regex (contains @ and . followed by 3 characters)
	regex email_format("[\\w.]+@\\w+\\.(com|net|gov|edu|org|ai|io)");
	if (regex_match(e, email_format))
		return true;
	else
		return false;

}
string convert_to_hash(string p) {
	//convert string (password) into a hash using a hash algorithm
	return ""; //delete code, only here for debugging
}
string reverseHash(string h) {
	//convert string (hash) into a password using a reverse-hash algorithm
	return ""; //delete code, only here for debugging
}
vector<string> download_database(vector<string>& usernames, vector<string>& phoneNumbers, vector<string>& emails) {
	download_usernames(usernames);
	download_phoneNumbers(phoneNumbers);
	download_emails(emails);
}
vector<string> download_usernames(vector<string> &usernames) {

}
vector<string> download_phoneNumbers(vector<string> &phoneNumbers) {

}
vector<string> download_emails(vector<string> &emails) {

}
void add_user_to_database(UserAccount *user) {
	//add user credentials to database
	fstream userAccount_database("account_database.xlsx", ios::in | ios::out | ios::app);
	userAccount_database << user->getUsername() << "\t" << user->getHash() << "\t" << user->getPhoneNumber() << "\t" << user->getEmail();
	//need to update all download structures (usernames, phoneNumbers, emails)

	userAccount_database.close();
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu