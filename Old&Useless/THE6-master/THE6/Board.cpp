#include "Board.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

//constructor function
template <class type>
Board<type>::Board(int col, int row) {
	columns = col;
	rows = row;
	array = new Card<type> *[rows];
	for (int i = 0; i < rows; i++){
		array[i] = new Card<type> [columns];
	}
}

//destructor function
template <class type>
Board<type>::~Board() {
	for (int i = 0; i < rows; i++) {
		delete array[i];
	}
	delete[] array;
}

//function to read data from the file and place it in the matrix
template <class type>
void Board<type>::readBoardFromFile(ifstream &file) {
	while (!file.eof()) {
		string line;
		type item;
		getline(file, line);
		stringstream currentLine(line);
		for (int i = 0; i < rows; i++) {
			for (int k = 0; k < columns; k++) {
				currentLine >> item;
				array[i][k].value = item;
			}
		}
		
	}
}

//function to display board
template <class type>
void Board<type>::displayBoard(){
	for(int i = 0; i < rows; i++){
		for(int k = 0; k < columns; k++){
			cout << array[i][k].value << " ";
		}
		cout << endl;
	}
}

//function to close the selected card
template <class type>
void Board<type>::closeCard(int row, int column){
	array[row][column].closed = true;
}

//function to get the row value
template <class type>
int Board<type>::getRow(){
	return rows;
}

//function to get the column value
template <class type>
int Board<type>::getColumn(){
	return columns;
}

//function to check the closed value of the selected tile
template <class type>
bool Board<type>::isClosed(int row, int column) {
	return array[row][column].closed;
}

//function to open a card and return its value
template <class type>
type Board<type>::openCard(int row, int column) {
	array[row][column].closed = false;
	return array[row][column].value;
}