/***************************************************************************
** Program: fraction.cpp
** Author: Allen Benjamin
** Date: 11/10/2019
** Description: Gets a fraction from the user and simplifies it. Makes sure the inputs are valid.
** Input: numerator and denominator from user
** Output: simplified fraction
**************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

int g_c_d(int a, int b);
bool to_lowest_terms(int &numerator, int &denominator);
int get_int(string prompt);
void get_fraction(int &numerator, int &denominator);
bool get_bool(string prompt);

/********************************************************
** Function: main
** Description: Gets a fraction from the user and outputs the simplified fraction.
** Input: numerator and denominator from the user
** Pre-Conditions: none
** Post-Conditions: print the simplified fraction
********************************************************/
int main() {
	do {
		int a, b;
		get_fraction(a, b);
		to_lowest_terms(a, b);
		cout << endl << "The lowest terms of your fraction: ";
		if ((a < 0) != (b < 0)) cout << "-";
		a = abs(a);
		b = abs(b);
		if (b == 1) cout << a << endl << endl;
		else cout << a << "/" << b << endl << endl;
	} while (get_bool("Do you want to do another conversion? (0-no, 1-yes): "));

	return 0;
}


/********************************************************
** Function: to_lowest_terms
** Description: simplifies fractions
** Input: int numerator, int denominator
** Pre-Conditions: the inputs are the numerator and denominator of a fraction
** Post-Conditions: numerator and denominator are changed to what they would be for a simplified fraction
********************************************************/
bool to_lowest_terms(int &numerator, int &denominator) {
	if (denominator == 0) return false;
	int gcd = g_c_d(numerator, denominator);
	numerator = numerator / gcd;
	denominator = denominator / gcd;
	return true;
}

/********************************************************
** Function: g_c_d
** Description: gets the greatest common denominator
** Input: int a, int b
** Pre-Conditions: the inputs are integers
** Post-Conditions: return the gcd
********************************************************/
int g_c_d(int a, int b) {
	int tmp;
	while (b != 0) {
		int tmp = a;
		a = b;
		b = tmp % b;
	}
	return abs(a);
}

/********************************************************
** Function: get_fraction
** Description: gets a fraction from the user
** Input: int &numerator, int &denominator
** Pre-Conditions: the inputs are integers
** Post-Conditions: parameters are changed to values the user inputs
********************************************************/
void get_fraction(int &numerator, int &denominator) {
	numerator = get_int("Enter your numerator: ");
	denominator = get_int("Enter your denominator: ");
	while (denominator == 0) {
		cout << "Invalid input, denominator cannot be 0!" << endl;
		denominator = get_int("Enter your denominator: ");
	}
}

/********************************************************
** Function: is_int
** Description: checks whether or not a string is an 
**   integer. This is over 15 lines because it includes
**   unique error messages for different types of errors.
** Input: string num
** Pre-Conditions: the input is a string
** Post-Conditions: return whether or not the number is an integer
********************************************************/
bool is_int(string num) {
	string max = "2147483647"; 
	if (num.length() == 0) {
		cout << "You didn't enter anything." << endl;
		return false;
	}
	int is_negative = 0;
	if (num.at(0) == '-') {
		max = "2147483648";
		is_negative = 1;
	}
	if (num.length() > max.length() + is_negative) {
		cout << "Input is too long." << endl;
		return false;
	}
	for (int i = is_negative; i<num.length(); i++) {
		if (num.at(i) < '0' || num.at(i) > '9') {
			cout << "Invalid input, enter whole numbers only!" << endl;
			return false;
		}
		if ((num.length() == max.length()+is_negative && num.at(i) > max.at(i-is_negative))) {
			cout << "Integer is too " << (is_negative ? "small." : "big.") << endl;
			return false;
		}
	}
	return true;
}

/********************************************************
** Function: get_int
** Description: gets an int from the user and provides helpful feedback if they do it wrong
** Input: string prompt
** Pre-Conditions: the input is a string
** Post-Conditions: return an integer
********************************************************/
int get_int(string prompt) {
	string input;
	do {
		cout << prompt;
		getline(cin, input);
	} while (!is_int(input));

	bool is_negative = false;
	is_negative = input.at(0)=='-';
	int result = 0;
	for (int i=is_negative?1:0; i<input.length(); i++) {
		char current = input.at(i);
		if (current < '0' || current > '9')
			return 0;
		result += (is_negative ? -1 : 1) * ((int)(current - '0') * pow(10, input.length()-i-1));
	}
	return result;
}

/********************************************************
** Function: get_bool
** Description: gets a boolean value from the user
** Input: string prompt
** Pre-Conditions: the input is a string
** Post-Conditions: return the boolean that the user inputs
********************************************************/
bool get_bool(string prompt) {
	while (true) {
		cout << prompt;
		string input;
		getline(cin, input);
		if (input.length() == 1 && input.at(0) <= '1' && input.at(0) >= '0') return input.at(0) == '1';
		cout << "Invalid input." << endl;
	}
}