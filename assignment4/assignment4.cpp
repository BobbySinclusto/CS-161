/***************************************************************************
** Program: assignment4.cpp
** Author: Allen Benjamin
** Date: 11/23/2019
** Description: Palindrome detector and word frequency counter.
** Input: String to perform the operation on, which operation to perform
** Output: results of chosen operation
**************************************************************************/

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

void get_string(char **input);
int get_input_range(char *prompt, char min, char max);
int get_int(char *prompt);
void get_words(char ***words, int *size);
void display_cstring(char *str);
char *purge_string(char *str);
bool is_palindrome(char *str);
void all_words_frequency(char *str, char ***words, int **frequencies, int *size);
void some_words_frequency(char *str, char ***words, int **frequencies, int *size);
void display_frequency(char **words, int *frequencies, int size);
void delete_array(char **words);
void display_results(char *input, int choice);

/********************************************************
** Function: main
** Description: Displays results of the selected operation on the given string.
** Input: String to perform the operation on, which operation to perform
** Pre-Conditions: none
** Post-Conditions: display results
********************************************************/
int main() {
	char prompt[] = "Would you like to try another string? (0-no, 1-yes): ";
	do {
		cout << "Enter the sentence or paragraph: " << endl;
		char *input;
		get_string(&input);
		
		cout << "\nChoose an option:\n  1. Palindrome Detector\n  2. Frequency of all words\n  3. Frequency of given words\n\n";
		char prompt[] = "Enter your choice (1-3): ";
		int choice = get_input_range(prompt, '1', '3');
		cout << endl;
		
		display_results(input, choice);
		cout << endl;
	} while (get_input_range(prompt, '0', '1'));
	
}

/********************************************************
** Function: display_results
** Description: Displays results of the selected operation on the given string.
** Input: String to perform the operation on, which operation to perform
** Pre-Conditions: none
** Post-Conditions: display results
********************************************************/
void display_results(char *input, int choice) {
	char **words;
	int *frequencies;
	int size;
	
	if (choice == 1) {
		display_cstring(input);
		cout << (is_palindrome(input)? " is" : " is not") << " a palindrome." << endl;
	}
	else {
		if (choice == 2)
			all_words_frequency(input, &words, &frequencies, &size);
		else
			some_words_frequency(input, &words, &frequencies, &size);
		display_frequency(words, frequencies, size);
		for (int i = 0; i < size; i++)
			delete [] words[i];
		delete [] words;
		delete [] frequencies;
	}
	delete [] input;
}

/********************************************************
** Function: get_string
** Description: Gets a C-Style string from the user.
** Input: Pointer to the character array where the result will be stored
** Pre-Conditions: User doesn't try to input stuff with line breaks
** Post-Conditions: input points to the character array with the result
********************************************************/
void get_string(char **input){
	int size = 256;
	*input = new char[size];
	int i = 0;
	do {
		if (i >= size) {
			char *tmp = new char[size + 256];
			memmove(tmp, *input, size);
			delete [] *input;
			*input = tmp;
			size += 256;
		}
		cin.get((*input)[i]);
		i++;
	} while ((*input)[i-1] != '\n');
	(*input)[i-1] = '\0';
}

/********************************************************
** Function: get_input_range
** Description: gets an integer value from the user
** Input: c-string prompt, int min, int max
** Pre-Conditions: prompt is a null-terminated character array, min is between 0 and 9, max is between 0 and 9
** Post-Conditions: return the option that the user chooses
********************************************************/
int get_input_range(char *prompt, char min, char max) {
	while (true) {
		cout << prompt;
		char *input;
		get_string(&input);
		if (strlen(input) == 1 && input[0] >= min && input[0] <= max) {
			int result = input[0] - '0';
			delete [] input;
			return result;
		}
		cout << "Invalid input." << endl;
		delete [] input;
	}
}

/********************************************************
** Function: display_cstring
** Description: Displays the contents of a c-string
** Input: c-string to display
** Pre-Conditions: The input is a null-terminated character array
** Post-Conditions: print the string
********************************************************/
void display_cstring(char *str) {
   for (int i = 0; i < strlen(str); i++) {
      cout << str[i];
   }
}

/********************************************************
** Function: purge_string
** Description: gets rid of special characters in a c-string
** Input: c-string to purge
** Pre-Conditions: the input is a null-terminated character array
** Post-Conditions: return the purged string
********************************************************/
char *purge_string(char *str) {
	char *result = new char[strlen(str) + 1];
	int j = 0;
	for (int i = 0; i < strlen(str); i++) {
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')) {
			result[j] = str[i];
			j++;
		}
		else if (str[i] >= 'a' && str[i] <= 'z') {
			result[j] = str[i] + 'A' - 'a';
			j++;
		}
	}
	result[j] = '\0';
	return result;
}

/********************************************************
** Function: is_palindrome
** Description: Checks whether or not the input is a palindrome
** Input: c-string to check
** Pre-Conditions: the input is a null-terminated character array
** Post-Conditions: return whether or not the input is a palindrome
********************************************************/
bool is_palindrome(char *str) {
	char *purged = purge_string(str);
	for (int i = 0; i < strlen(purged)/2; i++) {
		if (purged[i] != purged[strlen(purged) - i - 1]) {
			delete [] purged;
			return false;
		}
	}
	delete [] purged;
	return true;
}

/********************************************************
** Function: purge_no_num
** Description: gets rid of special characters and numbers in a c-string
** Input: c-string to purge
** Pre-Conditions: the input is a null-terminated character array
** Post-Conditions: return the purged string
********************************************************/
char *purge_no_num(char *str) {
	char *result = new char[strlen(str) + 1];
	int j = 0;
	for (int i = 0; i < strlen(str); i++) {
		if ((str[i] >= 'A' && str[i] <= 'Z') || str[i] == ' ') {
			result[j] = str[i];
			j++;
		}
		else if (str[i] >= 'a' && str[i] <= 'z') {
			result[j] = str[i] + 'A' - 'a';
			j++;
		}
	}
	result[j] = '\0';
	return result;
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
bool is_int(char *num) {
	char max[] = "2147483647";
	if (strlen(num) == 0) {
		cout << "You didn't enter anything." << endl;
		return false;
	}
	int is_negative = 0;
	if (num[0] == '-') {
		max[9] = '8';
		is_negative = 1;
	}
	if (strlen(num) > strlen(max) + is_negative) {
		cout << "Input is too long." << endl;
		return false;
	}
	for (int i = is_negative; i<strlen(num); i++) {
		if (num[i] < '0' || num[i] > '9') {
			cout << "Invalid input, enter whole numbers only!" << endl;
			return false;
		}
		if (strlen(num) == strlen(max)+is_negative && num[i] > max[i-is_negative]) {
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
int get_int(char *prompt) {
	char *input;
	while (true) {
		cout << prompt;
		get_string(&input);
		if (is_int(input))
			break;
		delete [] input;
	}

	bool is_negative = false;
	is_negative = input[0]=='-';
	int result = 0;
	for (int i=is_negative?1:0; i<strlen(input); i++) {
		result += (is_negative ? -1 : 1) * ((int)(input[i] - '0') * pow(10, strlen(input)-i-1));
	}
	delete [] input;
	return result;
}

/********************************************************
** Function: word_count
** Description: counts the words in a string
** Input: string sentence
** Pre-Conditions: the input is a string
** Post-Conditions: return the number of words in the string
********************************************************/
int word_count(char *sentence) {
	int result = 0;
	bool in_word = false;
	for (int i=0; i<strlen(sentence); i++) {
		if (sentence[i] == ' ' || sentence[i] == '\n' || sentence[i] == '\t') {
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
** Function: all_words_frequency
** Description: counts frequency of all words
** Input: c-string containing the words to count, pointer to array to store words in, pointer to array to store frequencies in
** Pre-Conditions: the input is a null-terminated character array
** Post-Conditions: words array contains all words in the string, frequencies array contains the corresponding frequencies
** This is longer than 15 lines because it doesn't make sense to subdivide this task any further.
********************************************************/
void all_words_frequency(char *str, char ***words, int **frequencies, int *size) {
	char *purged = purge_no_num(str);
	*size = word_count(purged);
	*words = new char*[*size];
	*frequencies = new int[*size];
	int i = 0;
	char *tmp = strtok(purged, " ");
	while (tmp != NULL) {
		bool is_new = true;
		for (int j = 0; j < i; j++) {
			if (strcmp(tmp, (*words)[j]) == 0) {
				(*frequencies)[j] ++;
				(*size) --;
				is_new = false;
				break;
			}
		}
		if (is_new) {
			(*words)[i] = new char[strlen(tmp) + 1];
			memmove((*words)[i], tmp, strlen(tmp) + 1);
			(*frequencies)[i] = 1;
			i++;
		}
		tmp = strtok(NULL, " ");
	}
	delete [] purged;
}

/********************************************************
** Function: some_words_frequency
** Description: counts frequency of given words
** Input: c-string containing the words to count, pointer to array with given words, pointer to array to store frequencies in
** Pre-Conditions: the input is a null-terminated character array
** Post-Conditions: words array contains given words, frequencies array contains the corresponding frequencies
** This is longer than 15 lines because it doesn't make sense to subdivide this task any further.
********************************************************/
void some_words_frequency(char *str, char ***words, int **frequencies, int *size) {
	get_words(words, size);
	*frequencies = new int[*size];
	for (int i = 0; i < *size; i++) {
		(*frequencies)[i] = 0;
	}
	
	char **all_words;
	int *all_frequencies;
	int all_size;
	
	all_words_frequency(str, &all_words, &all_frequencies, &all_size);
	
	for (int i = 0; i < *size; i++) {
		for (int j = 0; j < all_size; j++) {
			if (strcmp((*words)[i], all_words[j]) == 0) {
				(*frequencies)[i] = all_frequencies[j];
			}
		}
	}
	
	
	for (int i = 0; i < all_size; i++)
		delete [] all_words[i];
	delete [] all_words;
	delete [] all_frequencies;
}

/********************************************************
** Function: display_frequency
** Description: displays the frequency list
** Input: char **words, int *frequencies, int size
** Pre-Conditions: the inputs are good
** Post-Conditions: the frequency list is displayed
********************************************************/
void display_frequency(char **words, int *frequencies, int size) {
	cout << "Word Frequency List:" << endl;
	for (int i = 0; i < size; i++) {
		display_cstring(words[i]);
		cout << ":\t" << frequencies[i] << endl;
	}
}

/********************************************************
** Function: get_words
** Description: gets a list of words from the user
** Input: char ***words
** Pre-Conditions: the inputs are good
** Post-Conditions: words points to the list of words that the user inputs
********************************************************/
void get_words(char ***words, int *size) {
	char prompt[] = "Enter the number of words you wish to search for: ";
	*size = get_int(prompt);
	*words = new char*[*size];
	for (int i = 0; i < *size; i++) {
		char *tmp;
		cout << "Enter word " << i + 1 << ": ";
		get_string(&tmp);
		char *tmp2 = purge_string(tmp);
		char *tmp3 = purge_no_num(tmp2);
		delete [] tmp2;
		delete [] tmp;
		tmp = tmp3;
		(*words)[i] = new char[strlen(tmp) + 1];
		memmove((*words)[i], tmp, strlen(tmp) + 1);
		delete [] tmp;
	}
	cout << endl;
}
