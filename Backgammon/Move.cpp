#include "stdafx.h"
#include "Move.h"


Move::Move(int numberOfSteps) : numberOfSteps(numberOfSteps) {}

int Move::getNumberOfSteps() {
	return this->numberOfSteps;
}

void Move::choosePointToMoveFrom(int pointIdx) {
	this->pointToMoveFrom = pointIdx;
}

int Move::getChosenPointToMoveFrom() {
	return this->pointToMoveFrom;
}

Move::~Move()
{
}
