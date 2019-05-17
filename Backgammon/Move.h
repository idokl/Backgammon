#pragma once
class Move
{
private:
	int numberOfSteps;
	int pointToMoveFrom;

public:
	Move(int numberOfSteps);

	int getNumberOfSteps();

	//point - number between 1 and 25 (25 represents the bar) the player's checker will move from pointIdx to (pointIdx - numberOfSteps).
	//(the checkers move toward 0 index).
	void choosePointToMoveFrom(int pointIdx);

	int getChosenPointToMoveFrom();

	~Move();
};

