/***************************************************************************
 ** Program: assignment1.cpp
 ** Author: Allen Benjamin
 ** Date: 10/05/2019
 ** Description: Calculates gross income, taxes, and remaining income
 ** Input:  Monthly salary
 **         Number of months worked in a year
 **         Cost of a car
 **         Number of cars sold
 **         Number of misconducts observed
 **         Tax year
 **         State
 ** Output: Gross income
 **         Taxes
 **         Remaining income
 **************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <iomanip> // For setting precision
#include <typeinfo>
#include <climits>

using namespace std;

// Get a double from the user
double get_money_input(string message) {
	string tmp;
	double result = -1;
	bool failed;
	do {
		failed = false;
		cout << message;
		getline(cin, tmp);
		try {
			result = atof(tmp.c_str());
			if (tmp.find_first_not_of("0123456789.") != string::npos) {
				failed = true;
				cout << "Invalid input." << endl;
			}
		}
		catch (exception e) {
			failed = true;
			cout << "Invalid input." << endl;
		}
	} while (failed || result < 0);
	return result;
}

// Get an integer from the user, min and max are optional parameters
int get_int_input(string message, int min = 0, int max = INT_MAX) {
	string tmp;
	int result = -1;
	bool failed;
	do {
		failed = false;
		cout << message;
		getline(cin, tmp);
		try {
			result = atoi(tmp.c_str());
			if (tmp.find_first_not_of("0123456789") != string::npos || result < min || result > max) {
				failed = true;
				cout << "Invalid input." << endl;
			}
		}
		catch (exception e) {
			failed = true;
			cout << "Invalid input." << endl;
		}
	} while (failed);
	return result;
}

// Get a char from the user, can either be A, B, or C
int get_char_input(string message) {
	string tmp;
	string options = "ABCabc";
	bool failed;
	do {
		failed = false;
		cout << message;
		getline(cin, tmp);
		if (tmp.length() != 1 || options.find(tmp[0]) == string::npos) {
			failed = true;
			cout << "Invalid input." << endl;
		}
	} while (failed);
	return toupper(tmp[0]);
}

int main() {
	double salary = 0;
	int months = 0;
	double cost = 0;
	int cars_sold = 0;
	int misconducts = 0;
	int year = 1;
	char state = 'A';

	srand(time(NULL)); // Seed the random number generator
	cout << setprecision(2) << fixed; // Set precision of cout so double values will be rounded to 2 decimal places

	// Get input from user
	salary = get_money_input("Enter your monthly salary: ");

	months = get_int_input("Enter number of months you worked in the past year: ", 0, 12);

	cost = get_money_input("Enter the cost of the car: ");

	cars_sold = get_int_input("Enter number of cars you've sold in the past year: ");

	misconducts = get_int_input("Enter number of misconducts observed in the past year: ");

	year = get_int_input("Which tax year are you in, enter 1 for 2017, 2 for 2018: ", 1, 2);

	state = get_char_input("Which state are you in, enter A, B, or C: ");

	// Calculate gross income
	double annual_salary = salary * months;
	double average_price = cost * (1 + (rand() % 51 + 50) / 1000.0); // Generate random average selling price
	double profit = cars_sold * (average_price - cost);

	int deduction = 0;
	if (misconducts != 0)
		deduction = 100 * pow(2, misconducts - 1);

	double gross_income = annual_salary + 0.02 * profit - deduction;

	// Print results from calculating gross income with a random price
	cout << endl << "The average selling price, generated randomly, is $" << average_price << ", you will earn 2% of the profit, which is $" << profit * 0.02 << "." << endl << endl;

	cout << "The gross income is: $" << gross_income << endl;

	// Calculate taxes
	double taxes = 0;
	if (year == 1) {
		if (state == 'A') {
			taxes = 0.06 * gross_income;
		}
		else if (state == 'B') {
			if (gross_income >= 2000) {
				if (gross_income < 10000) {
					taxes = 100;
				}
				else {
					taxes = 0.1 * (gross_income - 10000) + 100;
				}
			}
		}
		else { //State == C, only other possibility, see get_char_input()
			if (gross_income < 3500) {
				taxes = 0.05 * gross_income;
			}
			else if (gross_income < 9000) {
				taxes = 0.07 * (gross_income - 3500) + 175;
			}
			else if (gross_income < 125000) {
				taxes = 0.09 * (gross_income - 9000) + 560;
			}
			else {
				taxes = 0.099 * (gross_income - 125000) + 11000;
			}
		}
	}
	else {
		if (state == 'A') {
			taxes = 0.08 * gross_income;
		}
		else if (state == 'B') {
			if (gross_income >= 2500) {
				if (gross_income < 10000) {
					taxes = 115;
				}
				else {
					taxes = 0.105 * (gross_income - 10000) + 115;
				}
			}
		}
		else { //State == C, only other possibility, see get_char_input()
			if (gross_income < 3450) {
				taxes = 0.05 * gross_income;
			}
			else if (gross_income < 8700) {
				taxes = 0.07 * (gross_income - 3450) + 172.5;
			}
			else if (gross_income < 125000) {
				taxes = 0.09 * (gross_income - 8700) + 540;
			}
			else {
				taxes = 0.099 * (gross_income - 125000) + 11007;
			}
		}
	}

	// Print results of calculating taxes
	cout << "The tax you need to pay is: $" << taxes << endl;
	cout << "Remaining: $" << gross_income - taxes << endl;

	return 0;
}
