#pragma once

#include "Enums.h"
#include <array>

struct Point {
	Color checkersColor;
	int checkersNum;
};

using std::array;

class BoardState
{

private:
	array<Point, 24> points;
	int blackCheckersOnBar;
	int whiteCheckersOnBar; 
	int blackCheckersOff; 
	int whiteCheckersOff;

public:
	BoardState(array<Point, 24> points, int blackCheckersOnBar, int whiteCheckersOnBar, int blackCheckersOff, int whiteCheckersOff);

	//virtual int getCheckersNum(Color color, int pointIdx) = 0;
	//virtual Color getCheckersColor(int pointIdx) = 0;
	Point getPoint(int pointIdx);
	int getBarCheckers(Color color);
	int getOffCheckers(Color color);
	
	~BoardState();
};

