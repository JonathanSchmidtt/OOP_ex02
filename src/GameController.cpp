#include "GameController.h"
#include <conio.h>
#include "io.h"



using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::vector;






GameController::GameController()
	:m_row_num{ 0 }, m_col_num{ 0 }, m_hasWon{false} ,m_coins{0}
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
	string temp_row_num;
	if (!(std::getline(levelList, temp_row_num)))
	{
		cerr << "Failed to read line length from Board.txt\n";
		exit(EXIT_FAILURE);
	}
	m_row_num = std::stoi(temp_row_num);

	
	string temp_row;
	//read as long as row_num
	for (int i = 0; i < m_row_num; ++i) {
		if (!(std::getline(levelList, temp_row))) {
			std::cerr << "coudnt read line: " << i << endl;
			exit(EXIT_FAILURE);
		}
		//print
		cout << temp_row << endl;
		m_board.push_back(temp_row);
	}
	if (!m_board.empty()) {
		searchObjects();
	}
}


void GameController::searchObjects() {
	for (int i = 0; i < m_row_num; ++i) { //going throgh y
		for (int j = 0; j < m_board[i].size(); ++j) { //going thorugh x
			char box = m_board[i][j];
			//checking where the player is
			if (box == '@') {
				p.setPLocation(j, i);
				m_board[i][j] = ' '; //to delete the Player draw from board
			}
			//check for enemy
		}
	}
	
}


void GameController::handleInput() {
	auto ch = _getch();

	if ((0 == ch) || (224 == ch)) {
		ch = _getch();
		switch (ch)
		{
		case SpecialKeys::UP:
			p.move("up", m_board);
			break;
		case SpecialKeys::DOWN:
			p.move("down", m_board);
			break;
		case SpecialKeys::LEFT:
			p.move("left", m_board);
			break;
		case SpecialKeys::RIGHT:
			p.move("right", m_board);
			break;
		}
	}
	else {
		if (ch == 32) {
			std::cout << "SPACE pressed\n";
			p.move("space", m_board);
		}
	}
}



void GameController::printGame() {
	Screen::resetLocation(); //cursor from start
	//delete 
	for (int i = 0; i < m_board.size(); ++i) {
		std::cout << m_board[i] << std::endl;
	}
	cout << "coins : " << m_coins << "        lives : " << p.getLives() <<
		"        stage : " << endl;
	//draw player
	Screen::setLocation(Location(p.getY(), p.getX()));
	std::cout << '@';
}


void GameController::run() {
	printGame();

	while (true) {
		handleInput();
		HandleCollision();
		printGame();

		if (p.getLives() == 0) {
			m_hasWon = false;
		}
	}
}


void GameController::HandleCollision() {
	int x = p.getX();
	int y = p.getY();

	char tile = m_board[y][x];

	if (tile == '*') {

		m_board[y][x] = ' ';
		m_coins += 1;
	}
}