#pragma once

#include "Enums.h"
#include "BoardState.h"
#include <array>

using std::array;

class Board
{

private:
	//White checkers go from point[23] toward point[0].
	//Black checkers go from point[0] toward point[23].
	
	array<Point,24> points;
	int blackCheckersOnBar;
	int whiteCheckersOnBar;
	int blackCheckersOff;
	int whiteCheckersOff;

	void incrementOffCheckersNum(Color color);
	void decrementOffCheckersNum(Color color);

public:
	//color - Color of player that moves from the 24th point to the 1st point.
	//					(The second player moves from the 1st point to the 24th point).
	Board();
	Board(const Board &board);

	//int getCheckersNum(Color color, int pointIdx);
	//int getBarCheckers(Color color);
	//int getOffCheckers(Color color);
	//Color getCheckersColor(int pointIdx);

	//color - color of the wanted player
	//Return BoardState acording to the wanted player point of view
	//i.e. the wanted player has to pass his checkers from point 24 toward point 1
	BoardState getBoardState(Color color);

	void addChecker(Color color, int pointIdx, bool isWhitePointOfView);
	Color removeChecker(int pointIdx, bool isWhitePointOfView);
	void addCheckerToBar(Color color);
	void removeCheckerFromBar(Color color);

	~Board();
};

