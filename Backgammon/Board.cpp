#include "stdafx.h"
#include "Board.h"


Board::Board()
{
	this->points[0] = { BLACK, 2 };
	this->points[5] = { WHITE, 2 };
	this->points[7] = { WHITE, 3 };
	this->points[11] = { BLACK, 5};
	this->points[12] = { WHITE, 5 };
	this->points[16] = { BLACK, 3};
	this->points[18] = { BLACK, 2 };
	this->points[23] = { WHITE, 2 };

	Point nullPoint = { NONE, 0 };
	this->points[1] = this->points[2] = this->points[3] = this->points[4]
		= this->points[6] = this->points[8] = this->points[9]
		= this->points[10] = this->points[13] = this->points[14]
		= this->points[15] = this->points[17] = this->points[19]
		= this->points[20] = this->points[21] = this->points[22] = nullPoint;

	this->blackCheckersOnBar = 0;
	this->whiteCheckersOnBar = 0;
	this->blackCheckersOff = 0;
	this->whiteCheckersOff = 0;
}

Board::Board(const Board &board) {
	this->points = board.points;
	this->blackCheckersOnBar = board.blackCheckersOnBar;
	this->whiteCheckersOnBar = board.whiteCheckersOnBar;
	this->blackCheckersOff = board.blackCheckersOff;
	this->whiteCheckersOff = board.whiteCheckersOff;
}

void Board::incrementOffCheckersNum(Color color) {
	switch (color)
	{
	case WHITE:
		this->whiteCheckersOff++;
		break;
	case BLACK:
		this->blackCheckersOff++;
		break;
	default:
		throw "invalid argument";
	}
}

void Board::decrementOffCheckersNum(Color color) {
	switch (color)
	{
	case WHITE:
		this->whiteCheckersOff--;
		break;
	case BLACK:
		this->blackCheckersOff--;
		break;
	default:
		throw "invalid argument";
	}
}

BoardState Board::getBoardState(Color color) {
	switch(color) {
	case WHITE:
		return BoardState(points, blackCheckersOnBar, whiteCheckersOnBar, blackCheckersOff, whiteCheckersOff);
	case BLACK:
		array<Point, 24> reversePoints;
		for (int i = 0; i < 24; i++) {
			reversePoints[i] = points[23 - i];
		}
		return BoardState(reversePoints, blackCheckersOnBar, whiteCheckersOnBar, blackCheckersOff, whiteCheckersOff);
	default:
		throw "ERROR: Board::getBoardState(Color color): color has to be WHITE or BLACK";
	}
}

void Board::addChecker(Color color, int pointIdx, bool isWhitePointOfView) {
	int zeroBasedPointIdx = pointIdx - 1;
	if (!isWhitePointOfView) {
		zeroBasedPointIdx = 23 - zeroBasedPointIdx;
	}
	Color currentColor = points[zeroBasedPointIdx].checkersColor;
	if (currentColor != NONE && color != currentColor) {
		throw "ERROR: Board::addChecker(Color color, int pointIdx, bool isWhitePointOfView): point can't contain both white and black checkers";
	}
	points[zeroBasedPointIdx].checkersColor = color;
	points[zeroBasedPointIdx].checkersNum++;

	this->decrementOffCheckersNum(color);
}

Color Board::removeChecker(int pointIdx, bool isWhitePointOfView) {
	int zeroBasedPointIdx = pointIdx - 1;
	if (!isWhitePointOfView) {
		zeroBasedPointIdx = 23 - zeroBasedPointIdx;
	}
	if (points[zeroBasedPointIdx].checkersNum == 0) {
		throw "ERROR: Board::removeChecker(int pointIdx, bool isWhitePointOfView): no checkers in this point";
	}
	Color removedCheckerColor = points[zeroBasedPointIdx].checkersColor;
	points[zeroBasedPointIdx].checkersNum--;
	if (points[zeroBasedPointIdx].checkersNum == 0) {
		points[zeroBasedPointIdx].checkersColor = NONE;
	}

	this->incrementOffCheckersNum(removedCheckerColor);

	return removedCheckerColor;
}

void Board::addCheckerToBar(Color color) {
	decrementOffCheckersNum(color);
	switch (color)
	{
	case WHITE:
		this->whiteCheckersOnBar++;
		break;
	case BLACK:
		this->blackCheckersOnBar++;
		break;
	default:
		throw "invalid argument";
		break;
	}
}

void Board::removeCheckerFromBar(Color color) {
	incrementOffCheckersNum(color);
	switch (color)
	{
	case WHITE:
		this->whiteCheckersOnBar--;
		break;
	case BLACK:
		this->blackCheckersOnBar--;
		break;
	default:
		throw "invalid argument";
		break;
	}
}

Board::~Board()
{
}
