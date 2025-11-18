#include <Player.h>
#include <io.h>


Player::Player() 
	:m_colPlayer{ 0 }, m_rowPlayer{ 0 }, m_lives{ 3 }
{
}

void Player::setPLocation(int x, int y){
	m_colPlayer = x;
	m_rowPlayer = y;
}


int Player::getX() const {
	return m_colPlayer;
}

int Player::getY() const {
	return m_rowPlayer;
}

int Player::getLives() const {
	return m_lives;
}





//=========================   movment functions    ============================
void Player::move(std::string s, std::vector<std::string>& m_board) {

	if (s == "up" && CheckMoveUp(m_board)) {
		m_rowPlayer--;
	}
	if (s == "down" && CheckMoveDown(m_board)) {
		m_rowPlayer++;
	}
	if (s == "left" && CheckMoveLeft(m_board)) {
		m_colPlayer--;
	}
	if (s == "right" && CheckMoveRight(m_board)) {
		m_colPlayer++;
	}
	if (s == "space") {
		//skip turn
		return;
	}
}

bool Player::CheckMoveUp(std::vector<std::string>& m_board) {
	int nextRow = m_rowPlayer - 1;
	char PlayerBox = m_board[m_rowPlayer][m_colPlayer];

	char targetBox = m_board[nextRow][m_colPlayer];
	if (PlayerBox == 'H' && targetBox=='H') {
		return true;
	}
	return false;
}


bool Player::CheckMoveDown(std::vector<std::string>& m_board) {
	int nextRow = m_rowPlayer + 1;
	char PlayerBox = m_board[m_rowPlayer][m_colPlayer];

	char targetBox = m_board[nextRow][m_colPlayer];
	if (PlayerBox == 'H' && (targetBox == 'H')) {
		return true;
	}
	return false;
}


bool Player::CheckMoveLeft(std::vector<std::string>& m_board) {
	int nextCol = m_colPlayer - 1;

	char targetBox = m_board[m_rowPlayer][nextCol];
	if (targetBox == '#') {
		return false;
	}
	char groundBelowTarget = m_board[m_rowPlayer + 1][nextCol];

	//top of a solam, solam or there is ground
	if (groundBelowTarget == '#' || groundBelowTarget == 'H' || targetBox == 'H' ||
		targetBox == '-') {
		return true;
	}

	return false;
}

bool Player::CheckMoveRight(std::vector<std::string>& m_board) {
	int nextCol = m_colPlayer + 1;

	char targetBox = m_board[m_rowPlayer][nextCol];
	if (targetBox == '#') {
		return false;
	}
	char groundBelowTarget = m_board[m_rowPlayer + 1][nextCol];

	//top of a solam, solam or there is ground
	if (groundBelowTarget == '#' || groundBelowTarget == 'H' || targetBox == 'H' || targetBox == '-') {
		return true;
	}
	return false;
}

