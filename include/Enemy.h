#pragma once
#include <vector>
#include <string>

class GameController;

class Enemy {
public:
	Enemy();
	Enemy(int x, int y);
	void setLocation(int x, int y);
	int getX() const;
	int getY() const;
	void move(const std::vector<std::string>& board, int playerX, int playerY);



private:
	int m_colEnemy; //x
	int m_rowEnemy; //y
	int m_direction; //left or right
};