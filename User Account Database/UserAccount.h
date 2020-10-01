#pragma once
#ifndef USERACCOUNT_H
#define USERACCOUNT_H

class UserAccount
{
private:
	string username;
	string hash_password;
	string phoneNumber;
	string email;
public:
	UserAccount(); //default constructor
	UserAccount(string, string, string, string); //overloaded constructor
	//set functions
	void setUsername(string);
	void setHash(string);
	void setPhoneNumber(string);
	void setEmail(string);
	//get functions
	string getUsername();
	string getHash();
	string getPhoneNumber();
	string getEmail();

	~UserAccount(); //destructor


};

#endif //USERACCOUNT_H