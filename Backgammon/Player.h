#pragma once

#include "Move.h"
#include "BoardState.h"

//(the player has to pass his checkers from point 24 toward point 1)
class Player
{
public:
	Player();

	//choose checkers to move in case of different numbers on dice
	virtual void chooseMoves(BoardState boardState, Move &moveForDie1, Move &moveForDie2) = 0;
	
	//choose checkers to move in case of doubles
	virtual void chooseMoves(BoardState boardState, Move &move1, Move &move2, Move &move3, Move &move4) = 0;

	~Player();
};

