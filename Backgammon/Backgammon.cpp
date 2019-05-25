// Backgammon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UserInputPlayer.h"
#include "Logic.h"
#include <array>
#include <iostream>

//#include "Move.h"

//void set(Move &m) {
//	m.choosePointToMoveFrom(3);
//	std::cout << "set:" <<  m.getChosenPointToMoveFrom() << "\n";
//}


int main()
{
	//std::cout << "alert1234\v";

	//Move m(1);
	//set(m);
	//std::cout << m.getChosenPointToMoveFrom() << "\n"; 
	//std::array<int, 2> a = { 1, 2 };
	//std::cout << a[0] << a[1] << "\n";
	printf("hello\n");
	Board board = Board();
	Player* p1w = new UserInputPlayer("white player");
	Player* p2b = new UserInputPlayer("black player");
	Logic logic = Logic(board, p1w, p2b);
	logic.startGame();
	delete(p1w);
	delete(p2b);
	getchar();
    return 0;
}
