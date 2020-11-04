//libraries
#include "UserAccount.h"
#include <iostream>
#include <string>
using namespace std;

//function definitions

//default constructor
UserAccount::UserAccount() {
	username = "";
	hash_password = "";
	phoneNumber = "";
	email = "";
}
//overloaded constructor
UserAccount::UserAccount(string u, string hp, string pn, string e) {
	username = u;
	hash_password = hp;
	phoneNumber = pn;
	email = e;
}

//set functions
void UserAccount::setUsername(string u) {
	username = u;
}
void UserAccount::setHash(string hp) {
	hash_password = hp;
}
void UserAccount::setPhoneNumber(string pn) {
	phoneNumber = pn;
}
void UserAccount::setEmail(string e) {
	email = e;
}

//get functions
string UserAccount::getUsername() {
	return this->username;
}
string UserAccount::getHash() {
	return this->hash_password;
}
string UserAccount::getPhoneNumber() {
	return this->phoneNumber;
}
string UserAccount::getEmail() {
	return this->email;
}

//destructor
UserAccount::~UserAccount() {

}

