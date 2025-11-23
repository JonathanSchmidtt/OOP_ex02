#include "Enemy.h"
#include <cstdlib>


Enemy::Enemy()
	:m_colEnemy{ 0 }, m_rowEnemy{ 0 }, m_direction{ 1 }
{
	
}

Enemy::Enemy(int x, int y) 
:m_colEnemy{x}, m_rowEnemy{y}
{
	m_direction = (rand() % 2 == 0) ? 1 : -1;
}


void Enemy::setLocation(int x, int y) {
	m_colEnemy = x;
	m_rowEnemy = y;
}


int Enemy::getX() const {
	return m_colEnemy;
}
	
int Enemy::getY() const {
	return m_rowEnemy;
}


void Enemy::move(const std::vector<std::string>& board, int playerX, int playerY) {
	int wantedDirection = m_direction; //movment dircetion
	bool chaseMode = false;

	if (m_rowEnemy == playerY) {
		int distance = playerX - m_colEnemy;
		if (std::abs(distance) <= 7) {
			if (distance > 0) {
				wantedDirection = 1;
			}
			else {
				wantedDirection = -1;
			}
			chaseMode = true;
		}
	}
	int nextX = m_colEnemy + wantedDirection;

	bool isWall = (board[m_rowEnemy][nextX] == '#'); // wall infront
	char floorBelow = board[m_rowEnemy + 1][nextX];  //ground
	bool hasFloor = (floorBelow == '#' || floorBelow == 'H'); //ground next
	//exception
	//if (board[m_rowEnemy][m_colEnemy] == '@') {
	//	hasFloor = true;
	//}

	//move if we have floor and no wall
	if (!isWall && hasFloor) {
		m_colEnemy = nextX;
		m_direction = wantedDirection;
	}
	else {
		if (!chaseMode) {
			m_direction *= -1;
		}
	}
}
