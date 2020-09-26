// User Account Database.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdlib.h>

using namespace std;

//protocols
int mainMenu();

int main() {

	int userInput = mainMenu();

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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
