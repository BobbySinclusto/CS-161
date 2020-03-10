/***************************************************************************
** Program: assignment2.cpp
** Author: Allen Benjamin
** Date: 10/25/2019
** Description: Tests the helper functions and displays test results
** Input: User input for get_int() function
** Output: Test results
**************************************************************************/

#include "helper_functions.h"
#include <iostream>
#include <string>

using namespace std;

void display_results(std::string function, std::string expected, std::string actual);
string int_to_string(int num);

/********************************************************
** Function: main
** Description: tests each helper function
** Input: user input for get_int() function
** Pre-Conditions: none
** Post-Conditions: print the results of testing each helper function
********************************************************/
int main() {
	
	display_results("check_range(-1, 2, 3)", "0", check_range(-1, 2, 3) ? "1" : "0");
	display_results("check_range(-1, 2, 2)", "1", check_range(-1, 2, 2) ? "1" : "0");
	display_results("check_range(3, -1, 2)", "0", check_range(3, -1, 2) ? "1" : "0");
	
	display_results("is_capital('A')", "1", is_capital('A') ? "1" : "0");
	display_results("is_capital('Z')", "1", is_capital('Z') ? "1" : "0");
	display_results("is_capital('e')", "0", is_capital('e') ? "1" : "0");
	display_results("is_capital('\\n')", "0", is_capital('\n') ? "1" : "0");
	
	display_results("is_even(2)", "1", is_even(2) ? "1" : "0");
	display_results("is_even(3)", "0", is_even(3) ? "1" : "0");
	display_results("is_even(-4)", "1", is_even(-4) ? "1" : "0");
	
	display_results("is_odd(3)", "1", is_odd(3) ? "1" : "0");
	display_results("is_odd(4)", "0", is_odd(4) ? "1" : "0");
	display_results("is_odd(-5)", "1", is_odd(-5) ? "1" : "0");
	
	display_results("equality_test(-4, -4)", "0", int_to_string(equality_test(-4, -4)));
	display_results("equality_test(-2, 5)", "-1", int_to_string(equality_test(-2, 5)));
	display_results("equality_test(6, 1)", "1", int_to_string(equality_test(6, 1)));
	
	display_results("float_is_equal(1.5, 2.0, 1.0)", "1", float_is_equal(1.5, 2.0, 1.0) ? "1" : "0");
	display_results("float_is_equal(-1.25, 1.2, 0.4)", "0", float_is_equal(-1.25, 1.2, 0.4) ? "1" : "0");
	
	display_results("is_int(\"1\")", "1", is_int("1") ? "1" : "0");
	display_results("is_int(\"-35\")", "1", is_int("-35") ? "1" : "0");
	display_results("is_int(\"asdf\")", "0", is_int("asdf") ? "1" : "0");
	display_results("is_int(\"352.45\")", "0", is_int("352.45") ? "1" : "0");
	display_results("is_int(\"\")", "0", is_int("") ? "1" : "0");
	
	display_results("numbers_present(\"90 mph\")", "1", numbers_present("90 mph") ? "1" : "0");
	display_results("numbers_present(\"the cat ran\")", "0", numbers_present("the cat ran") ? "1" : "0");
	display_results("numbers_present(\"235.367\")", "1", numbers_present("235.367") ? "1" : "0");
	display_results("numbers_present(\"\")", "0", numbers_present("") ? "1" : "0");
	
	display_results("letters_present(\"az\")", "1", letters_present("az") ? "1" : "0");
	display_results("letters_present(\"AZ\")", "1", letters_present("AZ") ? "1" : "0");
	display_results("letters_present(\"243754869\")", "0", letters_present("243754869") ? "1" : "0");
	display_results("letters_present(\"236 mph\")", "1", letters_present("236 mph") ? "1" : "0");
	display_results("letters_present(\"\")", "0", letters_present("") ? "1" : "0");
	
	display_results("contains_sub_string(\"Bob ran quickly\", \"ran\")", "1", contains_sub_string("Bob ran quickly", "ran") ? "1" : "0");
	display_results("contains_sub_string(\"blah blah blah\", \"blah\")", "1", contains_sub_string("blah blah blah", "blah") ? "1" : "0");
	display_results("contains_sub_string(\"asdfasdfasdf\", \"bob\")", "0", contains_sub_string("asdfasdfasdf", "bob") ? "1" : "0");
	display_results("contains_sub_string(\"This is a sentence\", \"\")", "1", contains_sub_string("This is a sentence", "") ? "1" : "0");
	
	display_results("word_count(\"two   words\")", "2", int_to_string(word_count("two   words")));
	display_results("word_count(\"three\\nwords\\nnow\")", "3", int_to_string(word_count("three\nwords\nnow")));
	display_results("word_count(\"   onlyOneWord\")", "1", int_to_string(word_count("   onlyOneWord")));
	display_results("word_count(\"\")", "0", int_to_string(word_count("")));
	display_results("word_count(\" \")", "0", int_to_string(word_count(" ")));
	
	display_results("to_upper(\"bob is a blob\")", "BOB IS A BLOB", to_upper("bob is a blob"));
	display_results("to_upper(\"WHaT HaPpeNs tO ThIs?\")", "WHAT HAPPENS TO THIS?", to_upper("WHaT HaPpeNs tO ThIs?"));
	display_results("to_upper(\"ASDF\")", "ASDF", to_upper("ASDF"));
	display_results("to_upper(\"\")", "", to_upper(""));
	
	display_results("to_lower(\"BOB IS A BLOB\")", "bob is a blob", to_lower("BOB IS A BLOB"));
	display_results("to_lower(\"WHaT HaPpeNs tO ThIs?\")", "what happens to this?", to_lower("WHaT HaPpeNs tO ThIs?"));
	display_results("to_lower(\"adsf\")", "asdf", to_lower("asdf"));
	display_results("to_lower(\"\")", "", to_lower(""));
	
	cout << "\nTesting get_int() function..." << endl;
	string input;
	do {
		cout << "Enter an integer: " << endl;
		getline(cin, input);
	} while (!is_int(input));
	display_results("get_int(\"" + input + "\")", input, int_to_string(get_int(input)));
	
	display_results("get_int(\"235afad4\")", "0", int_to_string(get_int("235afad4")));
	display_results("get_int(\"1.24\")", "0", int_to_string(get_int("1.24")));
	display_results("get_int(\"3256\")", "3256", int_to_string(get_int("3256")));
	display_results("get_int(\"-12567\")", "-12567", int_to_string(get_int("-12567")));
	display_results("get_int(\"\")", "0", int_to_string(get_int("")));
	
	return 0;
}

/********************************************************
** Function: display_results
** Description: displays results of testing a function
** Input: string function, string expected, string actual, bool passed
** Pre-Conditions: the inputs are strings
** Post-Conditions: print results
********************************************************/
void display_results(string function, string expected, string actual) {
	cout << "\nTesting " << function << "...\n";
	cout << "Expected: " << expected << "\t";
	cout << "Actual: " << actual;
	cout << "\t" << (expected == actual ? "PASSED" : "FAILED") << "\n";
}

/********************************************************
** Function: to_string
** Description: converts an int to a string
** Input: string num
** Pre-Conditions: the input is an int
** Post-Conditions: return the equivalent string
********************************************************/
string int_to_string(int num) {
	if (num == 0)
		return "0";
	string result = "";
	bool negative = false;
	if (num < 0) {
		negative = true;
		num = -num;
	}
	while (num != 0) {
		result += (char)(num % 10) + '0';
		num = num / 10;
	}
	if (negative)
		result += "-";
	for (int i=0; i<result.length()/2; i++) {
		char tmp = result.at(i);
		result.at(i) = result.at(result.length() - i - 1);
		result.at(result.length() - i - 1) = tmp;
	}
	return result;
}
