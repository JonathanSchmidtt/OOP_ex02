#pragma once

class GameController;

class Enemy {
public:
	Enemy();
	void setPLocation(int x, int y);
	int getX() const;
	int getY() const;




private:
	int m_colEnemy; //x
	int m_rowEnemy; //y
	

};