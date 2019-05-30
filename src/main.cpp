#include "game.h"
#include <iostream>

int main(int arc, char * argv[]){
	//create game
	ttt::Game* game = new ttt::Game();
	bool anyWin = false;
	bool valid = false;
	int i;
	int j;
	char player = 'X';
	
	while(!anyWin){
		std::cout << game->showBoard();

		while(!valid){
			//receive input
			std::cout << "Line to play " << player << " : " << std::endl;
			std::cin >> i;
			std::cout << "Column to play " << player << " : " << std::endl;
			std::cin >> j;

			valid = game->play(i, j);

			if(!valid){
				std::cout << "Invalid play!" << std::endl;
			}
		}

		valid = false;

		//test win
		anyWin = game->testWin();

		game->changeTurn();

		if(game->getPlayerTurn()){
			player = 'X';
		} else{
			player = 'O';
		}
	}

	//game over
	game->showBoard();

	if(game->getDraw()){
		std::cout << "It's a draw!";
	} else{
		if(game->getWinner()){
			std::cout << "Player 1 wins!";
		} else{
			std::cout << "Player 2 wins";
		}
	}
	
}