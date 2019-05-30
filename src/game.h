#ifndef GAME_H
#define GAME_H

#include <string>

namespace ttt {
	class Game {
		private:
			char board_[3][3];
			bool winner_;
			bool draw_;
			bool player_turn;

		public:
			Game();
			void initGame();
			bool play(int i, int j);
			std::string showBoard();
			bool getPlayerTurn();
			void changeTurn();
			bool testWin();
			bool getWinner();
			bool getDraw();

	};
};

#endif