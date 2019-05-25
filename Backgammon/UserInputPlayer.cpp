#include "stdafx.h"
#include "UserInputPlayer.h"
#include <iostream>

using std::cout;
using std::cin;

string pointRepresentation(Point p) {
	string representation{ "" };
	representation += std::to_string(p.checkersNum);
	switch (p.checkersColor)
	{
	case BLACK:
		representation += "B";
		break;
	case WHITE:
		representation += "W";
		break;
	default:
		break;
	}
	return representation;
}

void printBoard(BoardState boardState) {
	cout << "chekers on bar: WHITE: " << boardState.getBarCheckers(WHITE) << "\n";
	cout << "                BLACK: " << boardState.getBarCheckers(BLACK) << "  (bar index is 25)\n";
	for (int i = 24; i > 0; i--) {
		printf("%2d\t",i);
	}
	cout << "\n";
	for (int i = 24; i > 0; i--) {
		cout << pointRepresentation(boardState.getPoint(i)) << "\t";
	}
	cout << "\n";
}

UserInputPlayer::UserInputPlayer()
{
	static int playerNum;
	this->name = "player" + std::to_string(++playerNum);
}

UserInputPlayer::UserInputPlayer(string name)
{
	this->name = name;
}

void UserInputPlayer::chooseMoves(BoardState boardState, Move &moveForDie1, Move &moveForDie2) {
	int pointIdxForDie1{ 0 }, pointIdxForDie2{ 0 };
	bool valid{ false };
	while(!valid) {
		cout << this->name << ", please choose your moves. The state of the board is:\n";
		printBoard(boardState);
		cout << "The dice are " << moveForDie1.getNumberOfSteps() << " and " << moveForDie2.getNumberOfSteps() << "\n";
		cout << "Please enter point index for die1 (" << moveForDie1.getNumberOfSteps() <<"):\n";
		cin >> pointIdxForDie1;
		cout << "Please enter point index for die2 (" << moveForDie2.getNumberOfSteps() << "):\n";
		cin >> pointIdxForDie2;
		moveForDie1.choosePointToMoveFrom(pointIdxForDie1);
		moveForDie2.choosePointToMoveFrom(pointIdxForDie2);
		valid = (pointIdxForDie1 >= 1 && pointIdxForDie1 <= 25 && pointIdxForDie2 >= 1 && pointIdxForDie2 <= 25);
		if (!valid) {
			cout << "Indexes should be between 1 and 25. Please try again.\n";
		}
	}
}

void UserInputPlayer::chooseMoves(BoardState boardState, Move &move1, Move &move2, Move &move3, Move &move4) {
	int pointIdxForMove1{ 0 }, pointIdxForMove2{ 0 }, pointIdxForMove3{ 0 }, pointIdxForMove4{ 0 };
	bool valid{ false };
	while (!valid) {
		cout << this->name << ", please choose your moves. The state of the board is:\n";
		printBoard(boardState);
		cout << "The dice are " << move1.getNumberOfSteps() << " and " << move2.getNumberOfSteps() << " (doubles). You have to choose 4 moves\n";
		cout << "Please enter point index for move1 (" << move1.getNumberOfSteps() << "):\n";
		cin >> pointIdxForMove1;
		cout << "Please enter point index for move2 (" << move2.getNumberOfSteps() << "):\n";
		cin >> pointIdxForMove2;
		cout << "Please enter point index for move3 (" << move3.getNumberOfSteps() << "):\n";
		cin >> pointIdxForMove3;
		cout << "Please enter point index for move4 (" << move4.getNumberOfSteps() << "):\n";
		cin >> pointIdxForMove4;
		move1.choosePointToMoveFrom(pointIdxForMove1);
		move2.choosePointToMoveFrom(pointIdxForMove2);
		move3.choosePointToMoveFrom(pointIdxForMove3);
		move4.choosePointToMoveFrom(pointIdxForMove4);
		valid = (pointIdxForMove1 >= 1 && pointIdxForMove1 <= 25 && pointIdxForMove2 >= 1 && pointIdxForMove2 <= 25
			&& pointIdxForMove3 >= 1 && pointIdxForMove3 <= 25 && pointIdxForMove4 >= 1 && pointIdxForMove4 <= 25);
		if (!valid) {
			cout << "Indexes should be between 1 and 25. Please try again.\n";
		}
	}
}

UserInputPlayer::~UserInputPlayer()
{
}
