#include "stdafx.h"
#include "BoardState.h"

using std::array;

BoardState::BoardState(array<Point,24> points, int blackCheckersOnBar,
	int whiteCheckersOnBar, int blackCheckersOff, int whiteCheckersOff)
	: points(points), blackCheckersOnBar(blackCheckersOnBar), 
	whiteCheckersOnBar(whiteCheckersOnBar), blackCheckersOff(blackCheckersOff), 
	whiteCheckersOff(whiteCheckersOff) {}


Point BoardState::getPoint(int pointIdx) {
	int zeroBaedPointIdx = pointIdx - 1;
	return this->points[zeroBaedPointIdx];
}

int BoardState::getBarCheckers(Color color) {
	switch (color)
	{
	case WHITE:
		return whiteCheckersOnBar;
	case BLACK:
		return blackCheckersOnBar;
	default:
		throw "ERROR: BoardState::getBarCheckers(Color color): color has to be WHITE or BLACK";
	}
}

int BoardState::getOffCheckers(Color color) {
	switch (color)
	{
	case WHITE:
		return whiteCheckersOff;
	case BLACK:
		return blackCheckersOff;
	default:
		throw "ERROR: BoardState::getOffCheckers(Color color): color has to be WHITE or BLACK";
	}
}


BoardState::~BoardState()
{
}
