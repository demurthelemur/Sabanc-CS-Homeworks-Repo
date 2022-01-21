
#ifndef BOARD
#define BOARD
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

template <class type>
struct Card {
	bool closed;
	type value;
	Card() {
		closed = true;
		value = NULL;
	}
};

template <class type>
class Board {
private:
	int columns;								//private member for columns of the array
	int rows;									//private member for the rows of the array
	Card<type> **array;								//private member for the pointer for 
public:
	Board(int columns, int rows);				//constructor for Board clas, creates a matrix
	~Board();									//destructor for Board class
	void readBoardFromFile(ifstream &file);		//reads the board layout and creates a matrix
	void displayBoard();						//prints out the current state of the board
	void closeCard(int row, int column);		//changes the closed status from false to true
	int getRow();								//returns the row value for the matrix
	int getColumn();							//returns the column value for the matrix
	bool isClosed(int row, int column);			//function to check the boolean value for closed
	type openCard(int row, int column);			//function to open a card and return its value
};
#include "Board.cpp"




#endif // !BOARD
