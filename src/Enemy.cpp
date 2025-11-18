#include "Enemy.h"



Enemy::Enemy()
	:m_colEnemy{ 0 }, m_rowEnemy{ 0 }
{
}

void Enemy::setPLocation(int x, int y) {
	m_colEnemy = x;
	m_rowEnemy = y;
}


int Enemy::getX() const {
	return m_colEnemy;
}

int Enemy::getY() const {
	return m_rowEnemy;
}