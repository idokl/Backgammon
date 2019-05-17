#pragma once
#include "Player.h"
#include <string>

using std::string;

class UserInputPlayer :
	public Player
{
private:
	string name;
public:
	UserInputPlayer();
	UserInputPlayer(string name);

	void chooseMoves(BoardState boardState, Move & moveForDie1, Move & moveForDie2);
	void chooseMoves(BoardState boardState, Move &move1, Move &move2, Move &move3, Move &move4);
	~UserInputPlayer();
};

