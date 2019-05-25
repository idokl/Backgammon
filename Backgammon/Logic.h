#pragma once

#include "Player.h"
#include "Board.h"
#include <array>
#include <list>

bool isValidMove(Move move, Color color, BoardState boardState);

using std::list;
using std::array;

class Logic
{
private:
	array<Player*, 2> players;
	Board gameBoard;
	Result tryMove(Move move, Color color);
	Result makeMoves(list<Move> moves, Color color);

public:
	Logic(Board &gameBoard, Player* whitePlayer, Player* blackPlayer);

	void startGame();

	Player* getWinner();

	~Logic();
};

