/***************************************************************************
** Program: connect_four.cpp
** Author: Allen Benjamin
** Date: 12/08/2019
** Description: Connect Four game
** Input: Command line arguments for number of players, columns, and rows
** Output: Display game progress
**************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

void init_board(char **&board, int *size);
void delete_board(char **board, int *size);
void play_game(char **board, int *size, int players);
void check_arguments(int argc, char **argv, int *size, int &players);
void reset_game(char **&board, int *size, int &players);
int get_input_range(const char *prompt, int min, int max);

/********************************************************
** Function: main
** Description: Plays a game of connect four.
** Input: Command line arguments: Number of players, number of columns, number of rows
** Pre-Conditions: None
** Post-Conditions: Play a game of connect four
********************************************************/
int main(int argc, char **argv) {
	srand(time(NULL));
	int size[2];
	int players;
	check_arguments(argc, argv, size, players);
	char **board;
	init_board(board, size);
	while (true) {
		play_game(board, size, players);
		if (get_input_range("Would you like to play again? (0-no, 1-yes): ", 0, 1))
			reset_game(board, size, players);
		else
			break;
	}
	
	delete_board(board, size);
	return 0;
}

/********************************************************
** Function: get_string
** Description: Gets a C-Style string from the user.
** Input: Pointer to the character array where the result will be stored
** Pre-Conditions: User doesn't try to input stuff with line breaks
** Post-Conditions: input points to the character array with the result
********************************************************/
void get_string(char *&input){
	int size = 15;
	input = new char[size];
	int i = 0;
	do {
		if (i >= size) {
			char *tmp = new char[size + 256];
			memmove(tmp, input, size);
			delete [] input;
			input = tmp;
			size += 256;
		}
		cin.get(input[i]);
		i++;
	} while (input[i-1] != '\n');
	input[i-1] = '\0';
}

/********************************************************
** Function: get_input_range
** Description: gets an integer value from the user
** Input: c-string prompt, int min, int max
** Pre-Conditions: prompt is a null-terminated character array
** Post-Conditions: return the int that the user inputs
********************************************************/
int get_input_range(const char *prompt, int min, int max) {
	while (true) {
		cout << prompt;
		char *input;
		get_string(input);
		int result = atoi(input);
		delete [] input;
		if (result >= min && result <= max)
			return result;
		cout << "Invalid input." << endl;
	}
}

/********************************************************
** Function: init_game
** Description: Initializes game variables based on user input.
** Input: Size of board, number of players
** Pre-Conditions: size is an array of integers of size 2
** Post-Conditions: Variables are initialized with values from user
********************************************************/
void init_game(int *size, int &players) {
	players = get_input_range("Enter the number of players (1 or 2): ", 1, 2);
	size[0] = get_input_range("Enter the number of rows (must be between 4 and 20): ", 4, 20);
	size[1] = get_input_range("Enter the number of columns (must be between 4 and 20): ", 4, 20);
}

/********************************************************
** Function: validate_arguments
** Description: Validates command line arguments and asks user for input if necessary.
** Input: Size of board, number of players
** Pre-Conditions: size is an array of integers of size 2
** Post-Conditions: size and players hold valid values given by the user
********************************************************/
void validate_arguments(int *size, int &players) {
	if (size[0] < 4 || size[0] > 20) {
			cout << "Invalid argument: Number of rows must be between 4 and 20." << endl;
			size[0] = get_input_range("Enter the number of rows (must be between 4 and 20): ", 4, 20);
		}
		if (size[1] < 4 || size[1] > 20) {
			cout << "Invalid argument: Number of columns must be between 4 and 20." << endl;
			size[1] = get_input_range("Enter the number of columns (must be between 4 and 20): ", 4, 20);
		}
		if (players < 1 || players > 2) {
			cout << "Invalid argument: Number of players must be either 1 or 2." << endl;
			players = get_input_range("Enter the number of players (1 or 2): ", 1, 2);
	}
}

/********************************************************
** Function: check_arguments
** Description: checks the arguments and recovers from bad inputs.
** Input: char **board, int *size
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: if there is a diagonal line, the piece is stored in player
********************************************************/
void check_arguments(int argc, char **argv, int *size, int &players) {
	if (argc < 4) {
		cout << "Not enough arguments. Next time, use\n./connect_four [players] [columns] [rows]" << endl;
		init_game(size, players);
	}
	else if (argc == 4) {
		size[0] = atoi(argv[3]);
		size[1] = atoi(argv[2]);
		players = atoi(argv[1]);
		validate_arguments(size, players);
	}
	else {
		cout << "Too many arguments. Next time, use\n./connect_four [players] [columns] [rows]" << endl;
		init_game(size, players);
	}
}

/********************************************************
** Function: init_board
** Description: Initializes the game board based on size.
** Input: Reference to board variable, size
** Pre-Conditions: size is an array of integers of size 2
** Post-Conditions: board points to a dynamically allocated 2d array
********************************************************/
void init_board(char **&board, int *size) {
	board = new char*[size[0]];
	for (int i = 0; i < size[0]; i++) {
		board[i] = new char[size[1]];
		for (int j = 0; j < size[1]; j++) {
			board[i][j] = ' ';
		}
	}
}

/********************************************************
** Function: delete_board
** Description: Deallocates memory in use by board
** Input: char **board, int *size
** Pre-Conditions: none
** Post-Conditions: memory in use by board is deallocated
********************************************************/
void delete_board(char **board, int *size) {
	for (int i = 0; i < size[0]; i++)
		delete [] board[i];
	delete [] board;
}

/********************************************************
** Function: print_board
** Description: Prints the game board.
** Input: char **board, int *size
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: print board
********************************************************/
void print_board(char **board, int *size) {
	for (int i = 0; i < size[1]; i++)
		cout << (i > 9 ? " " : "  ") << i + 1 << " ";
	cout << endl;
	for (int i = 0; i < size[0]; i++) {
		for (int j = 0; j < size[1]; j++) {
			if (i % 2 == 0 && j % 2 == 0)
				cout << "|\033[30;47m " << board[i][j] << " ";
			else if (i % 2 == 1 && j % 2 == 1)
				cout << "|\033[30;47m " << board[i][j] << " ";
			else
				cout << "|\033[0m " << board[i][j] << " ";
			cout << "\033[0m"; 
		}
		cout << "|" << endl;
	}
}

/********************************************************
** Function: check_diagonals
** Description: Checks the diagonals of the board for lines of the same piece.
** Input: char **board, int *size, int &player
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: if there is a diagonal line, the piece is stored in player
********************************************************/
void check_diagonals(char **board, int *size, char &player) {
	char winner;
	for (int i = 0; i <= size[0]-4; i++) {
		for (int j = 0; j <= size[1]-4; j++) {
			int k;
			if (board[i][j] != ' ') {
				winner = board[i][j];
				for (k = 1; k < 4; k++) {
					if (board[i+k][j+k] != winner) break;
				}
				if (k == 4)
					player = winner;
			}
			if (board[size[0] - i - 1][j] != ' ') {
				winner = board[size[0] - i - 1][j];
				for (k = 1; k < 4; k++) {
					if (board[size[0]-i-1 - k][j+k] != winner) break;
				}
				if (k == 4)
					player = winner;
			}
		}
	}
}

/********************************************************
** Function: check_vertical
** Description: Checks the verticals of the board for lines of the same piece.
** Input: char **board, int *size, int &player
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: if there is a vertical line, the piece is stored in player
********************************************************/
void check_vertical(char **board, int *size, char &player) {
	char winner;
	for (int i = 0; i <= size[0]-4; i++) {
		for (int j = 0; j < size[1]; j++) {
			if (board[i][j] != ' ') {
				winner = board[i][j];
				int k;
				for (k = 1; k < 4; k++) {
					if (board[i + k][j] != winner)
						break;
				}
				if (k == 4)
					player = winner;
			}
		}
	}
}

/********************************************************
** Function: check_horizontal
** Description: Checks the horizontals of the board for lines of the same piece.
** Input: char **board, int *size, int &player
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: if there is a horizontal line, the piece is stored in player
********************************************************/
void check_horizontal(char **board, int *size, char &player) {
	char winner;
	for (int i = 0; i < size[0]; i++) {
		for (int j = 0; j <= size[1]-4; j++) {
			if (board[i][j] != ' ') {
				winner = board[i][j];
				int k;
				for (k = 1; k < 4; k ++) {
					if (board[i][j + k] != winner)
						break;
				}
				if (k == 4)
					player = winner;
			}
		}
	}
}

/********************************************************
** Function: is_full
** Description: Checks whether or not the board is full.
** Input: char **board, int *size
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: return whether or not the board is full
********************************************************/
bool is_full(char **board, int *size) {
	for (int i = 0; i < size[0]; i++) {
		for (int j = 0; j < size[1]; j++) {
			if (board[i][j] == ' ') {
				return false;
			}
		}
	}
	return true;
}

/********************************************************
** Function: check_win
** Description: Checks whether or not a player has won.
** Input: char **board, int *size
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: Print a message if a player wins, return whether or not a player has won
********************************************************/
bool check_win(char **board, int *size) {
	char winner = '\0';
	check_diagonals(board, size, winner);
	check_vertical(board, size, winner);
	check_horizontal(board, size, winner);
	if (is_full(board, size)) {
		cout << "It's a tie!" << endl;
		return true;
	}
	if (winner != '\0') {
		cout << winner << "'s win!" << endl;
		return true;
	}
	return false;
}

/********************************************************
** Function: place_piece
** Description: Places either an X or an O in the highest possible position in the column.
**   Returns whether or not the move made someone win
** Input: char **board, int *size, int col, char player
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: Place the piece, then print the board, return whether or not someone won
********************************************************/
bool place_piece(char **board, int *size, int col, char player) {
	for (int i = size[0] - 1; i >= 0; i--) {
		if (board[i][col - 1] == ' ') {
			board[i][col - 1] = player;
			break;
		}
	}
	print_board(board, size);
	return check_win(board, size);
}

/********************************************************
** Function: is_valid_column
** Description: Checks whether or not the specified column is valid.
** Input: char **board, int *size, int col, bool computer
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: print an error if the column is full, return whether or not the column is valid
********************************************************/
bool is_valid_column(char **board, int *size, int col,  bool computer) {
	for (int i = 0; i < size[0]; i++) {
		if (board[i][col - 1] == ' ')
			return true;
	}
	if (!computer)
		cout << "That column is full!" << endl;
	return false;
}

/********************************************************
** Function: user_column
** Description: Gets a column from the user, makes sure it is valid.
** Input: char **board, int *size
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: return the column
********************************************************/
int user_column(char **board, int *size) {
	int col;
	do {
		col = get_input_range("Enter a column: ", 1, size[1]);
	} while (!is_valid_column(board, size, col, false));
	return col;
}

/********************************************************
** Function: computer_column
** Description: This is the super fancy AI that I made.
** Input: char **board, int *size
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: return the column
********************************************************/
int computer_column(char **board, int *size) {
	int col;
	do {
		col = rand() % size[1] + 1;
	} while (!is_valid_column(board, size, col, true));
	return col;
}

/********************************************************
** Function: computer_game
** Description: Plays a game against the computer.
** Input: char **board, int *size
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: display game progress
********************************************************/
void computer_game(char **board, int *size) {
	if (get_input_range("Would you like to go first or second? (enter 1 or 2): ", 1, 2) == 1) {
		print_board(board, size);
		place_piece(board, size, user_column(board, size), 'X');
	}
	while (true) {
		cout << "Computer's turn (O):" << endl;
		if (place_piece(board, size, computer_column(board, size), 'O'))
			break;
		cout << "Your turn (X):" << endl;
		if (place_piece(board, size, user_column(board, size), 'X'))
			break;
	}
}

/********************************************************
** Function: user_game
** Description: Plays a game between two humans.
** Input: char **board, int *size
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: display game progress
********************************************************/
void user_game(char **board, int *size) {
	print_board(board, size);
	while (true) {
		cout << "Player 1 (X): " << endl;
		if (place_piece(board, size, user_column(board, size), 'X'))
			break;
		cout << "Player 2 (O): " << endl;
		if (place_piece(board, size, user_column(board, size), 'O'))
			break;
	}
}

/********************************************************
** Function: play_game
** Description: Plays the game.
** Input: char **board, int *size, int players
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: display game progress
********************************************************/
void play_game(char **board, int *size, int players) {
	if (players == 1) {
		computer_game(board, size);
	}
	else {
		user_game(board, size);
	}
}

/********************************************************
** Function: reset_game
** Description: resets the game.
** Input: char **&board, int *size, int &players
** Pre-Conditions: size is the dimensions of board
** Post-Conditions: the board is reset with new values from the user
********************************************************/
void reset_game(char **&board, int *size, int &players) {
	delete_board(board, size);
	init_game(size, players);
	init_board(board, size);
}






























