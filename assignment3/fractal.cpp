/***************************************************************************
** Program: fractal.cpp
** Author: Allen Benjamin
** Date: 11/11/2019
** Description: Asks the user for inputs, then displays the pattern
** Input: number of stars in longest line, number of columns to shift the pattern by
** Output: cool pattern thing
**************************************************************************/

#include <iostream>

using namespace std;

void pattern(int stars, int col);

/********************************************************
** Function: main
** Description: Asks the user for inputs, then displays the pattern
** Input: number of stars in the longest line, how much to indent the pattern
** Pre-Conditions: number of stars in the longest line is a positive odd integer, columns is an integer
** Post-Conditions: display the pattern
********************************************************/
int main() {
	int stars;
	int col;
	cout << "enter the number of stars in the longest line of the pattern: ";
	cin >> stars;
	cout << "enter the number of columns to shift the pattern: ";
	cin >> col;
	cout << endl;
	pattern(stars, col);
}

/********************************************************
** Function: pattern
** Description: displays a cool pattern thing
** Input: number of stars in longest line, number of columns to shift the pattern by
** Pre-Conditions: stars is a positive odd integer, columns is a positive integer
** Post-Conditions: display the pattern
********************************************************/
void pattern(int stars, int col) {
	if (stars < 1)
		return;
	pattern(stars - 2, col + 1);
	for (int i = 0; i < col; i++)
		cout << "  ";
	for (int i = 0; i < stars*2; i++)
		cout << (i % 2 == 0 ? "*" : " ");
	cout << endl;
	pattern(stars - 2, col + 1);
}