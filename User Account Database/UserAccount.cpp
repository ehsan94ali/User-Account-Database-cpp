//libraries
#include "UserAccount.h"
#include <iostream>
using namespace std;

//function definitions

//default constructor
UserAccount::UserAccount() {
	this->username = "";
	this->hash_password = "";
	this->phoneNumber = "";
	this->email = "";
}
//overloaded constructor
UserAccount::UserAccount(string u, string hp, string pn, string e) {
	this->username = u;
	this->hash_password = hp;
	this->phoneNumber = pn;
	this->email = e;
}

//set functions
void UserAccount::setUsername(string u) {
	this->username = u;
}
void UserAccount::setHash(string hp) {
	this->hash_password = hp;
}
void UserAccount::setPhoneNumber(string pn) {
	this->phoneNumber = pn;
}
void UserAccount::setEmail(string e) {
	this->email = e;
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

