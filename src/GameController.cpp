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
	:m_row_num{ 0 }, m_col_num{ 0 }, m_hasWon{false} ,m_score{0}, m_coinsCounter{0}, m_lives{3}, m_stage{0}
{
	m_levelFile.open("Board.txt"); // open file
	if (!m_levelFile.is_open()) { //cant open
		cerr << "Cannot open Board.txt file\n";
		exit(EXIT_FAILURE);
	}
	readBoard(); 
}



void GameController::readBoard(){
	//starting a stage won=false
	m_hasWon = false;
	//earse the board and members
	m_board.clear();
	m_coinsCounter = 0; 
	m_enemies.clear();

	m_stage++;
	//check if the file ended
	if (m_levelFile.peek() == EOF) {
		cout << "Game finished.\n";
		exit(0); 
	}


	//reading first number: cols
	string temp_row_num;
	if (!(std::getline(m_levelFile, temp_row_num)))
	{
		return;
	}

	m_row_num = std::stoi(temp_row_num);

	
	string temp_row;
	//read as long as row_num
	for (int i = 0; i < m_row_num; ++i) {
		if (!(std::getline(m_levelFile, temp_row))) {
			cerr << "coudnt read line: " << i << endl;
			exit(EXIT_FAILURE);
		}
		//save in the 2d vector array
		m_board.push_back(temp_row);
	}
	m_levelFile.ignore(); // skip line between a stage to stage

	if (!m_board.empty()) {
		searchObjects(); //check for objects in the game
	}
}


void GameController::searchObjects() {
	for (int i = 0; i < m_row_num; ++i) { //going throgh y
		for (int j = 0; j < m_board[i].size(); ++j) { //going thorugh x
			char box = m_board[i][j];
			//checking where the player is
			if (box == '@') {
			//	p.setPLocation(j, i);
				m_board[i][j] = ' '; //to delete the Player draw from board
				p.setStartingPLocation(j, i);
			}
			else if(box== '*'){
				m_coinsCounter++;
			}
			else if (box == '%') {//check for enemy
				m_enemies.push_back(Enemy(j, i));

				m_board[i][j] = ' '; //delete the enemy place
			}
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
			p.move("space", m_board);
		}
	}
}



void GameController::printGame() {
	Screen::resetLocation(); //cursor from start
	//delete 
	for (int i = 0; i < m_board.size(); ++i) {
		cout << m_board[i] << endl;
	}
	cout << "score : " << m_score << "        lives : " << m_lives <<
		"        stage : " <<  m_stage << endl;
	//draw enemy
	for (int j = 0; j < m_enemies.size(); j++) {
		Screen::setLocation(Location(m_enemies[j].getY(), m_enemies[j].getX()));
		cout << '%';
	}
	//draw player
	Screen::setLocation(Location(p.getY(), p.getX()));
	cout << '@';
}


void GameController::run() {
	printGame();

	while (true) {
		handleInput();

		HandleCollision();
		printGame();

		for (int i = 0; i < m_enemies.size(); ++i) {
			m_enemies[i].move(m_board, p.getX(), p.getY());
		}
		HandleCollision();
		printGame();

		if (m_hasWon) {
			system("cls");
			readBoard();

			printGame();
		}
	}
}


void GameController::HandleCollision() {
	int x = p.getX();
	int y = p.getY();

	char tile = m_board[y][x];

	if (tile == '*') {

		m_board[y][x] = ' ';
		m_coinsCounter--; 
		
		m_score += (m_stage * 2);
		if (m_coinsCounter == 0) {
			m_hasWon = true;
			m_score += (m_stage * 50);
		}
	}
	for (int i = 0; i < m_enemies.size(); ++i) {
		if (x == m_enemies[i].getX() && y == m_enemies[i].getY()) {
			m_lives--;
		 	p.resetToStart();
			if (m_lives <= 0) {
				system("cls");
				cout << "YOU LOST.\n";
				exit(0);
			}
		}
	}
}	