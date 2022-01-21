#include "Player.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

//Player constructor
template <class type>
Player<type>::Player(Board<type> currentBoard):board(currentBoard) {
	score = 0;
}

//function that oppens a card and return its value
template <class type>
type Player<type>::openCard(int row, int column) {
	return board.openCard(row, column);
}

//function that checks if a move is valid
template <class type>
bool Player<type>::validMove(int row, int column) {
	int boardRow = board.getRow();
	int boardColumn = board.getColumn();
	bool valid = true;
	if (row > boardRow) {
		return false;
	}
	else if (column > boardColumn) {
		return false;
	}
	else if(!board.isClosed(row, column)){
		return false;
	}
	else {
		return true;
	}
}

//function that increases a players score
template <class type>
void Player<type>::increaseNumberOfSuccess() {
	score++;
}

//function that returns the score of the player
template <class type>
int Player<type>::getNumberOfSuccess() {
	return score;
}