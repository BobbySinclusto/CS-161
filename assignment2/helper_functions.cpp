#include "helper_functions.h"

using namespace std;

/********************************************************
** Function: check_range
** Description: checks if a given integer value is within the given range
** Input: int lower_bound, int upper_bound, int test_value
** Pre-Conditions: the inputs are integers
** Post-Conditions: return whether or not the value is in the range
********************************************************/
bool check_range(int lower_bound, int upper_bound, int test_value) {
	return test_value >= lower_bound && test_value <= upper_bound;
}

/********************************************************
** Function: is_capital
** Description: checks whether or not a character is capital
** Input: char letter
** Pre-Conditions: the input is a character
** Post-Conditions: return whether or not the character is capital
********************************************************/
bool is_capital(char letter) {
	return letter >= 'A' && letter <= 'Z';
}

/********************************************************
** Function: is_even
** Description: checks whether or not a number is even
** Input: int num
** Pre-Conditions: the input is an integer
** Post-Conditions: return whether or not the number is even
********************************************************/
bool is_even(int num) {
	return num % 2 == 0;
}

/********************************************************
** Function: is_odd
** Description: checks whether or not a number is odd
** Input: int num
** Pre-Conditions: the input is an integer
** Post-Conditions: return whether or not the number is odd
********************************************************/
bool is_odd(int num) {
	return !is_even(num);
}

/********************************************************
** Function: equality_test
** Description: checks whether or not two integers are equal
** Input: int num1, int num2
** Pre-Conditions: the inputs are integers
** Post-Conditions: return -1 if num1<num2, 1 if num1>num2, 0 if num1==num2
********************************************************/
int equality_test(int num1, int num2) {
	return num1<num2 ? -1 : (num1>num2 ? 1 : 0);
}

/********************************************************
** Function: float_is_equal
** Description: checks whether or not two floats are equal within a certain precision
** Input: float num1, float num2, float precision
** Pre-Conditions: the inputs are floats
** Post-Conditions: return whether or not the floats are equal within a certain precision
********************************************************/
bool float_is_equal(float num1, float num2, float precision) {
	return abs(num1 - num2) <= precision;
}

/********************************************************
** Function: is_int
** Description: checks whether or not a string is an integer
** Input: string num
** Pre-Conditions: the input is a string
** Post-Conditions: return whether or not the number is an integer
********************************************************/
bool is_int(string num) {
	if (num.length() == 0)
		return false;
	if ((num.at(0) < '0' || num.at(0) > '9') && num.at(0) != '-')
		return false;
	for (int i=1; i<num.length(); i++) {
		if (num.at(i) < '0' || num.at(i) > '9')
			return false;
	}
	return true;
}

/********************************************************
** Function: numbers_present
** Description: checks whether or not a string contains numbers
** Input: string sentence
** Pre-Conditions: the input is a string
** Post-Conditions: return whether or not the string contains numbers
********************************************************/
bool numbers_present(string sentence) {
	for (int i=0; i<sentence.length(); i++) {
		if (sentence.at(i) >= '0' && sentence.at(i) <= '9')
			return true;
	}
	return false;
}

/********************************************************
** Function: letters_present
** Description: checks whether or not a string contains letters
** Input: string sentence
** Pre-Conditions: the input is a string
** Post-Conditions: return whether or not the string contains letters
********************************************************/
bool letters_present(string sentence) {
	for (int i=0; i<sentence.length(); i++) {
		if ((sentence.at(i) >= 'A' && sentence.at(i) <= 'Z') || (sentence.at(i) >= 'a' && sentence.at(i) <= 'z'))
			return true;
	}
	return false;
}

/********************************************************
** Function: contains_sub_string
** Description: checks whether or not a string contains the specified substring
** Input: string sentence, string sub_string
** Pre-Conditions: the inputs are strings
** Post-Conditions: return whether or not the string contains the specified substring
********************************************************/
bool contains_sub_string(string sentence, string sub_string) {
	if (sub_string.length() == 0)
		return true;
	for (int i=0; i <= (int)sentence.length() - (int)sub_string.length(); i++) {
		for (int j=0; j<sub_string.length(); j++) {
			if (sub_string.at(j) == sentence.at(i+j)) {
				if (j == sub_string.length() - 1)
					return true;
			}
			else {
				break;
			}
		}
	}
	return false;
}

/********************************************************
** Function: word_count
** Description: counts the words in a string
** Input: string sentence
** Pre-Conditions: the input is a string
** Post-Conditions: return the number of words in the string
********************************************************/
int word_count(string sentence) {
	int result = 0;
	bool in_word = false;
	for (int i=0; i<sentence.length(); i++) {
		if (sentence.at(i) == ' ' || sentence.at(i) == '\n' || sentence.at(i) == '\t') {
			if (in_word)
				result++;
			in_word = false;
		}
		else {
			in_word = true;
		}
	}
	if (in_word)
		result++;
	return result;
}

/********************************************************
** Function: to_upper
** Description: turns all lowercase letters in a string into uppercase letters
** Input: string sentence
** Pre-Conditions: the input is a string
** Post-Conditions: return the uppercase string
********************************************************/
string to_upper(string sentence) {
	for (int i=0; i<sentence.length(); i++)
		if (sentence.at(i) >= 'a' && sentence.at(i) <= 'z')
			sentence.at(i) = sentence.at(i) + 'A' - 'a';
	return sentence;
}

/********************************************************
** Function: to_lower
** Description: turns all uppercase letters in a string into lowercase letters
** Input: string sentence
** Pre-Conditions: the input is a string
** Post-Conditions: return the lowercase string
********************************************************/
string to_lower(string sentence) {
	for (int i=0; i<sentence.length(); i++)
		if (sentence.at(i) >= 'A' && sentence.at(i) <= 'Z')
			sentence.at(i) = sentence.at(i) + 'a' - 'A';
	return sentence;
}

/********************************************************
** Function: get_int
** Description: gets an int from the user and provides helpful feedback if they do it wrong
** Input: string prompt
** Pre-Conditions: the input is a string
** Post-Conditions: return an integer
********************************************************/
int get_int(string prompt) {
	if (!is_int(prompt))
		return 0;
	bool is_negative = false;
	is_negative = prompt.at(0)=='-'? true : false;
	int result = 0;
	for (int i=is_negative?1:0; i<prompt.length(); i++) {
		char current = prompt.at(i);
		if (current < '0' || current > '9')
			return 0;
		result += ((int)(current - '0') * pow(10, prompt.length()-i-1));
	}
	return is_negative? -result : result;
}
