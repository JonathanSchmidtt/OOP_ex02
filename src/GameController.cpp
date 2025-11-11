#include "GameController.h"



GameController::GameController()
	:m_row_len{ 0 }, m_col_len{ 0 }, m_hasWon{false}
{
	readBoard();
}



void GameController::readBoard(){
	//starting a stage won=false
	m_hasWon = false;
	//open file
	auto levelList = std::ifstream("Board.txt");
	if (!levelList.is_open())
	{
		cerr << "Cannot open Board.txt file\n";
		exit(EXIT_FAILURE);
	}

	//earse the board
	m_board.clear();

	//reading first number: cols
	string temp_col_num;
	if (!(std::getline(levelList, temp_col_num)))
	{
		cerr << "Failed to read line length from Board.txt\n";
		exit(EXIT_FAILURE);
	}
	m_col_len = std::stoi(temp_col_num);

	//reading each line and printin
	string row;
	//read as long you can until you stumble an empy row
	while (std::getline(levelList, row) && !row.empty()) {
		//print
		cout << row << endl;
		m_board.push_back(row);
	}
}