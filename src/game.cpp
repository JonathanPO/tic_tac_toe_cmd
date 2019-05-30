#include <iostream>
#include <sstream>
#include "game.h"

ttt::Game::Game(){
	initGame();
}

void ttt::Game::initGame(){
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){
			board_[i][j] = '_';
		}	
	}

	player_turn = true;
}

bool ttt::Game::play(int i, int j){
	if((board_[i][j] != '_') || i>=3 || j>=3){
		return false;
	} else{
		if(player_turn){
			board_[i][j] = 'x';
		} else{
			board_[i][j] = 'o';
		}
	}

	return true;

}

std::string ttt::Game::showBoard(){
	td::stringstream os;

	os << board_[0][0] << ' ' << board_[0][1] << ' ' << board_[0][2] << std::endl 
	<< board_[1][0] << ' ' << board_[1][1] << ' ' << board_[1][2] << std::endl 
	<< board_[2][0] << ' ' << board_[2][1] << ' ' << board_[2][2] << std::endl;

	return os.str();
	
}

bool ttt::Game::getPlayerTurn(){
	return player_turn;
}

void ttt::Game::changeTurn(){
	if(player_turn){
		player_turn = false;
	} else{
		player_turn = true;
	}
}


bool ttt::Game::testWin(){
	bool anyWin = false;
	bool tempWinner = false;
	bool tempDraw = true;
	char toTestWin = 'o';

	if(player_turn){
		toTestWin = 'x';
		tempWinner = true;
	}

	//HORIZONTAL
	if(board_[0][0] == toTestWin && board_[0][1] == toTestWin && board_[0][2] == toTestWin){
		anyWin = true;
		winner_ = tempWinner;
	}

	if(board_[1][0] == toTestWin && board_[1][1] == toTestWin && board_[1][2] == toTestWin){
		anyWin = true;
		winner_ = tempWinner;
	}

	if(board_[2][0] == toTestWin && board_[2][1] == toTestWin && board_[2][2] == toTestWin){
		anyWin = true;
		winner_ = tempWinner;
	}


	//VERTICAL
	if(board_[0][0] == toTestWin && board_[1][0] == toTestWin && board_[2][0] == toTestWin){
		anyWin = true;
		winner_ = tempWinner;
	}

	if(board_[0][1] == toTestWin && board_[1][1] == toTestWin && board_[2][1] == toTestWin){
		anyWin = true;
		winner_ = tempWinner;
	}

	if(board_[0][2] == toTestWin && board_[1][2] == toTestWin && board_[2][2] == toTestWin){
		anyWin = true;
		winner_ = tempWinner;
	}

	//DIAGONAL
	if(board_[0][0] == toTestWin && board_[1][1] == toTestWin && board_[2][2] == toTestWin){
		anyWin = true;
		winner_ = tempWinner;
	}

	if(board_[0][2] == toTestWin && board_[1][1] == toTestWin && board_[2][0] == toTestWin){
		anyWin = true;
		winner_ = tempWinner;
	}

	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){
			if(board_[i][j] == '_'){
				tempDraw = false;
			}
		}	
	}

	if(!anyWin){
		draw_ = tempDraw;

		if(draw_){
			anyWin = true;
		}
	}

	return anyWin;
}

bool ttt::Game::getWinner(){
	return winner_;
}

bool ttt::Game::getDraw(){
	return draw_;
}
