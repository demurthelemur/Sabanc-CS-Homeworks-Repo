#ifndef PLAYER
#define PLAYER
#include "Board.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

template <class type>
class Player {
private:
	int score;
	Board<type>& board;
public:
	Player(Board<type> board);
	type openCard(int row, int column);
	bool validMove(int row, int column);
	void increaseNumberOfSuccess();
	int getNumberOfSuccess();
};

#include "Player.cpp"
#endif