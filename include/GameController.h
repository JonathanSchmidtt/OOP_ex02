#pragma once
#include "Player.h"
#include "Enemy.h"
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "io.h"


class GameController {
	public:
		GameController();
		void readBoard(); //first reading board and print
		void searchObjects(); //getting place for each object
		void handleInput(); //handling user input
		void printGame(); // printing board
		void run();
		void HandleCollision();
	private:
		int m_row_num, m_col_num, m_score, m_coinsCounter, m_lives, m_stage;
		bool m_hasWon;
		std::ifstream m_levelFile;
		std::vector<std::string> m_board;
		Player p;
		std::vector<Enemy> m_enemies;
};