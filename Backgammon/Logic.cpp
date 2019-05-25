#include "stdafx.h"
#include "Logic.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <time.h>
#include <string>

Logic::Logic(Board &gameBoard, Player* whitePlayer, Player* blackPlayer)
	: gameBoard(gameBoard) {
	players = array<Player*, 2>();
	players[0] = whitePlayer;
	players[1] = blackPlayer;
}

static bool areAllCheckersHome(Color color, BoardState boardState) {
	if (boardState.getBarCheckers(color) > 0)
		return false;
	for (int i = 1; i <= 18; i++) {
		if (boardState.getPoint(i).checkersColor == color)
			return false;
	}
	return true;
}

bool isValidMove(Move move, Color color, BoardState boardState) {
	//BoardState boardState = gameBoard.getBoardState(color);
	int idxOfPointToMoveFrom = move.getChosenPointToMoveFrom();
	if (idxOfPointToMoveFrom < 1 || idxOfPointToMoveFrom > 25) {
		//throw "ERROR: Logic::tryMove(Move move, Color color): the method move.getChosenPointToMoveFrom() has to return value between 1 and 25";
		return false;
	}
	//if there is checker on the bar, can't move other checker
	if (boardState.getBarCheckers(color) != 0 && idxOfPointToMoveFrom != 25) {
		return false;
	}
	//check existence of player's checker in the point to move from
	if (idxOfPointToMoveFrom == 25) {
		if (boardState.getBarCheckers(color) == 0) {
			return false;
		}
	}
	else {
		Point pointToMoveFrom = boardState.getPoint(idxOfPointToMoveFrom);
		if (pointToMoveFrom.checkersColor != color || pointToMoveFrom.checkersNum < 1) {
			return false;
		}
	}
	//check ability to move these steps (to the destination point)
	int idxOfDestinationPoint = idxOfPointToMoveFrom - move.getNumberOfSteps();
	if (idxOfDestinationPoint <= 0) {
		if (areAllCheckersHome(color,boardState)) {
			return true;
		}
		else {
			return false;
		}
	}
	Point destinationPoint = boardState.getPoint(idxOfDestinationPoint);
	if (destinationPoint.checkersColor != color && destinationPoint.checkersNum > 1) {
		return false;
	}

	return true;
}

Result Logic::tryMove(Move move, Color color) {
	BoardState boardState = gameBoard.getBoardState(color);
	if (!isValidMove(move, color, boardState)) {
		return FAILURE;
	}
	bool isWhitePlayer = (color == WHITE);
	int idxOfPointToMoveFrom = move.getChosenPointToMoveFrom();
	if (idxOfPointToMoveFrom == 25) {
		gameBoard.removeCheckerFromBar(color);
	}
	else {
		gameBoard.removeChecker(idxOfPointToMoveFrom, isWhitePlayer);
	}
	int destinationPointIdx = idxOfPointToMoveFrom - move.getNumberOfSteps();
	if (destinationPointIdx <= 0) {
		return SUCCESS;
	}
	Point destinationPoint = boardState.getPoint(destinationPointIdx);
	//eat opponent's checker if exist
	if (destinationPoint.checkersColor != color && destinationPoint.checkersNum == 1) {
		Color opponentCheckerColor = gameBoard.removeChecker(destinationPointIdx, isWhitePlayer);
		gameBoard.addCheckerToBar(opponentCheckerColor);
	}
	gameBoard.addChecker(color, destinationPointIdx, isWhitePlayer);
	return SUCCESS;
}

Result Logic::makeMoves(list<Move> moves, Color color) {
	Board boardBeforeMoves = Board(gameBoard);
	int movesNum = moves.size();
	for (int i = 0; i < movesNum && !moves.empty(); i++) {
		list<Move>::iterator it = moves.begin();
		while (it != moves.end()) {
			if (tryMove(*it, color) == SUCCESS) {
				moves.erase(it++);
			}
			else
			{
				it++;
			}
		}
	}
	if (moves.empty()) {
		return SUCCESS;
	}
	else {
		this->gameBoard = boardBeforeMoves;
		return FAILURE;
	}
}

void Logic::startGame() {
	Color colors[2] = { WHITE, BLACK };
	srand(time(NULL));
	int currentPlayerIdx = rand() % 2;
	int dice[2];
	bool gameOver{ false };
	while(!gameOver) {
		std::string currentPlayerColor = currentPlayerIdx ? "BLACK" : "WHITE";
		std::cerr << "INFO: Turn of " << currentPlayerColor << " player\n";
		dice[0] = rand() % 6 + 1;
		dice[1] = rand() % 6 + 1;
		Move move1(dice[0]), move2(dice[1]), move3(dice[0]), move4(dice[1]);
		BoardState boardState = gameBoard.getBoardState(colors[currentPlayerIdx]);
		Result result{ FAILURE };
		do {
			list<Move> movesList{};
			if (dice[0] == dice[1]) {
				players[currentPlayerIdx]->chooseMoves(boardState, move1, move2, move3, move4);
				movesList.push_back(move3);
				movesList.push_back(move4);
			}
			else
			{
				players[currentPlayerIdx]->chooseMoves(boardState, move1, move2);
			}
			movesList.push_back(move1);
			movesList.push_back(move2);
			result = makeMoves(movesList, colors[currentPlayerIdx]);
			if (result == FAILURE) {
				std::cerr << "INFO: INVALID MOVE OF " << currentPlayerColor << " PLAYER\n";
			}
		} while (result == FAILURE);

		//if (dice[0] == dice[1]) {
		//	do {
		//		players[currentPlayerIdx]->chooseMoves(boardState, move1, move2, move3, move4);
		//		list<Move> movesList{};
		//		movesList.push_back(move1);
		//		movesList.push_back(move2);
		//		movesList.push_back(move3);
		//		movesList.push_back(move4);
		//		result = makeMoves(movesList, colors[currentPlayerIdx]);
		//	} while (result == FAILURE);
		//}
		//else {
		//	do {
		//		(players[currentPlayerIdx])->chooseMoves(boardState, move1, move2);
		//		list<Move> movesList{};
		//		movesList.push_back(move1);
		//		movesList.push_back(move2);
		//		result = makeMoves(movesList, colors[currentPlayerIdx]);
		//	} while (result == FAILURE);
		//}

		//check whether game over
		currentPlayerIdx = 1 - currentPlayerIdx;
	}
}

Player* Logic::getWinner() {
	return NULL;
}

Logic::~Logic()
{
}
