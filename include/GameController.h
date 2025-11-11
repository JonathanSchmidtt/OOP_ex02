#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::vector;

class GameController {
	public:
		GameController();
		void readBoard();
		



	private:
		int m_row_len, m_col_len;
		bool m_hasWon;
		vector<string> m_board;
};