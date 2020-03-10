#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <iostream>
#include <string>
#include <cmath>

bool check_range(int lower_bound, int upper_bound, int test_value);
bool is_capital(char letter);
bool is_even(int num);
bool is_odd(int num);
int equality_test(int num1, int num2);
bool float_is_equal(float num1, float num2, float precision);
bool is_int(std::string num);
bool numbers_present(std::string sentence);
bool letters_present(std::string sentence);
bool contains_sub_string(std::string sentence, std::string sub_string);
int word_count(std::string sentence);
std::string to_upper(std::string sentence);
std::string to_lower(std::string sentence);
int get_int(std::string prompt);

#endif
