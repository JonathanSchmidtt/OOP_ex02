#pragma once


#include <string>
#include <vector>
#include <iostream>

class GameController;

class Player {
public:
	Player();
	void setPLocation(int x, int y);
	int getX() const;
	int getY() const;
	void setStartingPLocation(int x, int y);
	void resetToStart();
	void move(std::string s, std::vector<std::string>& m_board);
	bool CheckMoveUp(std::vector<std::string>& m_board);
	bool CheckMoveDown(std::vector<std::string>& m_board);
	bool CheckMoveLeft(std::vector<std::string>& m_board);
	bool CheckMoveRight(std::vector<std::string>& m_board);
private:
	int m_colPlayer; //x
	int m_rowPlayer; //y
	int m_startCol;
	int m_startRow;
};