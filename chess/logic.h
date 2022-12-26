#pragma once
#define LENGTH 7
#define BLACK_PAWN 1
#define WHITE_PAWN -1
#define BLACK_ROOK 2
#define WHITE_ROOK -2
#define BLACK_KNIGHT 3
#define WHITE_KNIGHT -3
#define BLACK_BITSHOP 4
#define WHITE_BITSHOP -4
#define BLACK_QUEEN 5
#define WHITE_QUEEN -5
#define BLACK_KING 6
#define WHITE_KING -6

// Pozition struct
struct poz {
	int x, y;
} oldPoz, whiteKing, blackKing, transformWHITE, transformBLACK;

// Board array
int size = 100, isMoving;
int board[8][8] = {
	2, 3, 4, 5, 6, 4, 3, 2,
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-2, -3, -4, -5, -6, -4, -3, -2,
};

// 0 - white, 1 - black
int move;

// Check variables
int rightWhiteRookM, leftWhiteRookM, whiteKingFirstMove;
int rightBlackRookM, leftBlackRookM, blackKingFirstMove;
int checkWhite, checkBlack;
int transformationWhite, transformationBlack;

// Move and check (logic) functions
int PawnW(int old_x, int old_y, int new_x, int new_y) {
	if (oldPoz.y == 6) {
		if ((new_y == old_y - 1 && new_x == old_x && board[old_y - 1][old_x] == 0) ||
			(new_y == old_y - 2 && new_x == old_x && board[old_y - 1][old_x] == 0 && board[old_y - 2][old_x] == 0)) {
			return 1;
		}
	}
	else if (new_y == old_y - 1 && new_x == old_x && board[old_y - 1][old_x] == 0) {
		return 1;
	}

	if (board[old_y - 1][old_x - 1] > 0) {
		if (new_y == old_y - 1 && new_x == old_x - 1) {
			return 1;
		}
	}
	if (board[old_y - 1][old_x + 1] > 0) {
		if (new_y == old_y - 1 && new_x == old_x + 1) {
			return 1;
		}
	}
	return 0;
}

int PawnB(int old_x, int old_y, int new_x, int new_y) {
	if (oldPoz.y == 1) {
		if ((new_y == old_y + 1 && new_x == old_x && board[old_y + 1][old_x] == 0) ||
			(new_y == old_y + 2 && new_x == old_x && board[old_y + 1][old_x] == 0 && board[old_y + 2][old_x] == 0)) {
			return 1;
		}
	}
	else if (new_y == old_y + 1 && new_x == old_x && board[old_y + 1][old_x] == 0) {
		return 1;
	}

	if (board[old_y + 1][old_x - 1] < 0) {
		if (new_y == old_y + 1 && new_x == old_x - 1) {
			return 1;
		}
	}
	if (board[old_y + 1][old_x + 1] < 0) {
		if (new_y == old_y + 1 && new_x == old_x + 1) {
			return 1;
		}
	}
	return 0;
}

int RookW(int old_x, int old_y, int new_x, int new_y) {
	for (int i = old_x - 1; i >= 0; i--) {
		if (board[old_y][i] >= 0 && (new_x == i && new_y == old_y)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][old_x] >= 0 && (new_y == i && new_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	for (int i = old_x + 1; i <= LENGTH; i++) {
		if (board[old_y][i] >= 0 && (new_y == old_y && new_x == i)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][old_x] >= 0 && (new_y == i && new_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	return 0;
}

int RookB(int old_x, int old_y, int new_x, int new_y) {
	for (int i = old_x - 1; i >= 0; i--) {
		if (board[old_y][i] <= 0 && (new_x == i && new_y == old_y)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][old_x] <= 0 && (new_y == i && new_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	for (int i = old_x + 1; i <= LENGTH; i++) {
		if (board[old_y][i] <= 0 && (new_y == old_y && new_x == i)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][old_x] <= 0 && (new_y == i && new_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	return 0;
}

int BitshopW(int old_x, int old_y, int new_x, int new_y) {
	int j = old_x - 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] >= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] >= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	j = old_x - 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] >= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] >= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	return 0;
}

int BitshopB(int old_x, int old_y, int new_x, int new_y) {
	int j = old_x - 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] <= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] <= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	j = old_x - 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] <= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] <= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	return 0;
}

int QueenW(int old_x, int old_y, int new_x, int new_y) {
	for (int i = old_x - 1; i >= 0; i--) {
		if (board[old_y][i] >= 0 && (new_x == i && new_y == old_y)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][old_x] >= 0 && (new_y == i && new_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	for (int i = old_x + 1; i <= LENGTH; i++) {
		if (board[old_y][i] >= 0 && (new_y == old_y && new_x == i)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][old_x] >= 0 && (new_y == i && new_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	int j = old_x - 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] >= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] >= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	j = old_x - 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] >= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] >= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	return 0;
}

int QueenB(int old_x, int old_y, int new_x, int new_y) {
	for (int i = old_x - 1; i >= 0; i--) {
		if (board[old_y][i] <= 0 && (new_x == i && new_y == old_y)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][old_x] <= 0 && (new_y == i && new_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	for (int i = old_x + 1; i <= LENGTH; i++) {
		if (board[old_y][i] <= 0 && (new_y == old_y && new_x == i)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][old_x] <= 0 && (new_y == i && new_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	int j = old_x - 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] <= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] <= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	j = old_x - 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] <= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] <= 0 && (new_y == i && new_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	return 0;
}

int KnightW(int old_x, int old_y, int new_x, int new_y) {
	if (old_y - 2 >= 0 && old_x - 1 >= 0 && new_y == old_y - 2 && new_x == old_x - 1 && board[new_y][new_x] >= 0) {
		return 1;
	}
	if (old_y - 2 >= 0 && old_x + 1 <= LENGTH && new_y == old_y - 2 && new_x == old_x + 1 && board[new_y][new_x] >= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && old_x + 2 <= LENGTH && new_y == old_y - 1 && new_x == old_x + 2 && board[new_y][new_x] >= 0) {
		return 1;
	}
	if (old_y + 1 <= LENGTH && old_x + 2 <= LENGTH && new_y == old_y + 1 && new_x == old_x + 2 && board[new_y][new_x] >= 0) {
		return 1;
	}
	if (old_y + 2 <= LENGTH && old_x + 1 <= LENGTH && new_y == old_y + 2 && new_x == old_x + 1 && board[new_y][new_x] >= 0) {
		return 1;
	}
	if (old_y + 2 <= LENGTH && old_x - 1 >= 0 && new_y == old_y + 2 && new_x == old_x + 1 && board[new_y][new_x] >= 0) {
		return 1;
	}
	if (old_y + 1 <= LENGTH && old_x - 2 >= 0 && new_y == old_y + 1 && new_x == old_x - 2 && board[new_y][new_x] >= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && old_x - 2 >= 0 && new_y == old_y - 1 && new_x == old_x - 2 && board[new_y][new_x] >= 0) {
		return 1;
	}
	return 0;
}

int KnightB(int old_x, int old_y, int new_x, int new_y) {
	if (old_y - 2 >= 0 && old_x - 1 >= 0 && new_y == old_y - 2 && new_x == old_x - 1 && board[new_y][new_x] <= 0) {
		return 1;
	}
	if (old_y - 2 >= 0 && old_x + 1 <= LENGTH && new_y == old_y - 2 && new_x == old_x + 1 && board[new_y][new_x] <= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && old_x + 2 <= LENGTH && new_y == old_y - 1 && new_x == old_x + 2 && board[new_y][new_x] <= 0) {
		return 1;
	}
	if (old_y + 1 <= LENGTH && old_x + 2 <= LENGTH && new_y == old_y + 1 && new_x == old_x + 2 && board[new_y][new_x] <= 0) {
		return 1;
	}
	if (old_y + 2 <= LENGTH && old_x + 1 <= LENGTH && new_y == old_y + 2 && new_x == old_x + 1 && board[new_y][new_x] <= 0) {
		return 1;
	}
	if (old_y + 2 <= LENGTH && old_x - 1 >= 0 && new_y == old_y + 2 && new_x == old_x + 1 && board[new_y][new_x] <= 0) {
		return 1;
	}
	if (old_y + 1 <= LENGTH && old_x - 2 >= 0 && new_y == old_y + 1 && new_x == old_x - 2 && board[new_y][new_x] <= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && old_x - 2 >= 0 && new_y == old_y - 1 && new_x == old_x - 2 && board[new_y][new_x] <= 0) {
		return 1;
	}
	return 0;
}

int PawnWCheck(int old_x, int old_y, int king_x, int king_y) {
	if (board[old_y - 1][old_x - 1] >= 0) {
		if (old_y - 1 == king_y && old_x - 1 == king_x) {
			return 1;
		}
	}
	if (board[old_y - 1][old_x + 1] >= 0) {
		if (old_y - 1 == king_y && old_x + 1 == king_x) {
			return 1;
		}
	}
	return 0;
}

int RookWCheck(int old_x, int old_y, int king_x, int king_y) {
	for (int i = old_x - 1; i >= 0; i--) {
		if (board[old_y][i] >= 0 && (king_x == i && king_y == old_y)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][old_x] >= 0 && (king_y == i && king_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	for (int i = old_x + 1; i <= LENGTH; i++) {
		if (board[old_y][i] >= 0 && (king_y == old_y && king_x == i)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][old_x] >= 0 && (king_y == i && king_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	return 0;
}

int BitshopWCheck(int old_x, int old_y, int king_x, int king_y) {
	int j = old_x - 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] >= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] >= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	j = old_x - 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] >= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] >= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	return 0;
}

int QueenWCheck(int old_x, int old_y, int king_x, int king_y) {
	for (int i = old_x - 1; i >= 0; i--) {
		if (board[old_y][i] >= 0 && (king_x == i && king_y == old_y)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][old_x] >= 0 && (king_y == i && king_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	for (int i = old_x + 1; i <= LENGTH; i++) {
		if (board[old_y][i] >= 0 && (king_y == old_y && king_x == i)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][old_x] >= 0 && (king_y == i && king_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	int j = old_x - 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] >= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] >= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	j = old_x - 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] >= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] >= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	return 0;
}

int KnightWCheck(int old_x, int old_y, int king_x, int king_y) {
	if (old_y - 2 >= 0 && old_x - 1 >= 0 && king_y == old_y - 2 && king_x == old_x - 1 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_y - 2 >= 0 && old_x + 1 <= LENGTH && king_y == old_y - 2 && king_x == old_x + 1 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && old_x + 2 <= LENGTH && king_y == old_y - 1 && king_x == old_x + 2 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_y + 1 <= LENGTH && old_x + 2 <= LENGTH && king_y == old_y + 1 && king_x == old_x + 2 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_y + 2 <= LENGTH && old_x + 1 <= LENGTH && king_y == old_y + 2 && king_x == old_x + 1 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_y + 2 <= LENGTH && old_x - 1 >= 0 && king_y == old_y + 2 && king_x == old_x + 1 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_y + 1 <= LENGTH && old_x - 2 >= 0 && king_y == old_y + 1 && king_x == old_x - 2 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && old_x - 2 >= 0 && king_y == old_y - 1 && king_x == old_x - 2 && board[king_y][king_x] >= 0) {
		return 1;
	}
	return 0;
}

int KingWCheck(int old_x, int old_y, int king_x, int king_y) {
	if (old_x - 1 >= 0 && old_y - 1 >= 0 && king_y == old_y - 1 && king_x == old_x - 1 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && king_y == old_x && king_y == old_y - 1 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && old_x + 1 < LENGTH && king_x == old_x + 1 && king_y == old_y - 1 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_x + 1 <= LENGTH && king_y == old_y && king_x == old_x + 1 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_x + 1 <= LENGTH && old_y + 1 <= LENGTH && king_y == old_y + 1 && king_x == old_x + 1 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_y + 1 <= LENGTH && king_y == old_y + 1 && king_x == old_x && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_x - 1 >= 0 && old_y + 1 <= LENGTH && king_x == old_x + 1 && king_y == old_y + 1 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_x - 1 >= 0 && king_y == old_y && king_x == old_x - 1 && board[king_y][king_x] <= 0) {
		return 1;
	}
	return 0;
}

int PawnBCheck(int old_x, int old_y, int king_x, int king_y) {
	if (board[old_y + 1][old_x - 1] <= 0) {
		if (king_y == old_y + 1 && king_x == old_x - 1) {
			return 1;
		}
	}
	if (board[old_y + 1][old_x + 1] <= 0) {
		if (king_y == old_y + 1 && king_x == old_x + 1) {
			return 1;
		}
	}
	return 0;
}

int RookBCheck(int old_x, int old_y, int king_x, int king_y) {
	for (int i = old_x - 1; i >= 0; i--) {
		if (board[old_y][i] <= 0 && (king_x == i && king_y == old_y)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][old_x] <= 0 && (king_y == i && king_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	for (int i = old_x + 1; i <= LENGTH; i++) {
		if (board[old_y][i] <= 0 && (king_y == old_y && king_x == i)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][old_x] <= 0 && (king_y == i && king_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	return 0;
}

int BitshopBCheck(int old_x, int old_y, int king_x, int king_y) {
	int j = old_x - 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] <= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] <= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	j = old_x - 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] <= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] <= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	return 0;
}

int QueenBCheck(int old_x, int old_y, int king_x, int king_y) {
	for (int i = old_x - 1; i >= 0; i--) {
		if (board[old_y][i] <= 0 && (king_x == i && king_y == old_y)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][old_x] <= 0 && (king_y == i && king_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	for (int i = old_x + 1; i <= LENGTH; i++) {
		if (board[old_y][i] <= 0 && (king_y == old_y && king_x == i)) {
			return 1;
		}
		else if (board[old_y][i] != 0) {
			break;
		}
	}
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][old_x] <= 0 && (king_y == i && king_x == old_x)) {
			return 1;
		}
		else if (board[i][old_x] != 0) {
			break;
		}
	}
	int j = old_x - 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] <= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y - 1; i >= 0; i--) {
		if (board[i][j] <= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	j = old_x - 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] <= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j--;
	}
	j = old_x + 1;
	for (int i = old_y + 1; i <= LENGTH; i++) {
		if (board[i][j] <= 0 && (king_y == i && king_x == j)) {
			return 1;
		}
		else if (board[i][j] != 0) {
			break;
		}
		j++;
	}
	return 0;
}

int KnightBCheck(int old_x, int old_y, int king_x, int king_y) {
	if (old_y - 2 >= 0 && old_x - 1 >= 0 && king_y == old_y - 2 && king_x == old_x - 1 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_y - 2 >= 0 && old_x + 1 <= LENGTH && king_y == old_y - 2 && king_x == old_x + 1 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && old_x + 2 <= LENGTH && king_y == old_y - 1 && king_x == old_x + 2 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_y + 1 <= LENGTH && old_x + 2 <= LENGTH && king_y == old_y + 1 && king_x == old_x + 2 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_y + 2 <= LENGTH && old_x + 1 <= LENGTH && king_y == old_y + 2 && king_x == old_x + 1 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_y + 2 <= LENGTH && old_x - 1 >= 0 && king_y == old_y + 2 && king_x == old_x + 1 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_y + 1 <= LENGTH && old_x - 2 >= 0 && king_y == old_y + 1 && king_x == old_x - 2 && board[king_y][king_x] <= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && old_x - 2 >= 0 && king_y == old_y - 1 && king_x == old_x - 2 && board[king_y][king_x] <= 0) {
		return 1;
	}
	return 0;
}

int KingBCheck(int old_x, int old_y, int king_x, int king_y) {
	if (old_x - 1 >= 0 && old_y - 1 >= 0 && king_y == old_y - 1 && king_x == old_x - 1 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && king_y == old_x && king_y == old_y - 1 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_y - 1 >= 0 && old_x + 1 < LENGTH && king_x == old_x + 1 && king_y == old_y - 1 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_x + 1 <= LENGTH && king_y == old_y && king_x == old_x + 1 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_x + 1 <= LENGTH && old_y + 1 <= LENGTH && king_y == old_y + 1 && king_x == old_x + 1 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_y + 1 <= LENGTH && king_y == old_y + 1 && king_x == old_x && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_x - 1 >= 0 && old_y + 1 <= LENGTH && king_x == old_x + 1 && king_y == old_y + 1 && board[king_y][king_x] >= 0) {
		return 1;
	}
	if (old_x - 1 >= 0 && king_y == old_y && king_x == old_x - 1 && board[king_y][king_x] >= 0) {
		return 1;
	}
	return 0;
}

int BlackKingCheck(int posKing_x, int posKing_y) {
	int ok = 0;
	for (int i = 0; i <= LENGTH; i++) {
		for (int j = 0; j <= LENGTH; j++) {
			if (board[i][j] <= 0) {
				if (board[i][j] == WHITE_PAWN) {
					ok = PawnWCheck(j, i, posKing_x, posKing_y);
				}
				if (board[i][j] == WHITE_ROOK) {
					ok = RookWCheck(j, i, posKing_x, posKing_y);
				}
				if (board[i][j] == WHITE_KNIGHT) {
					ok = KnightWCheck(j, i, posKing_x, posKing_y);
				}
				if (board[i][j] == WHITE_BITSHOP) {
					ok = BitshopWCheck(j, i, posKing_x, posKing_y);
				}
				if (board[i][j] == WHITE_QUEEN) {
					ok = QueenWCheck(j, i, posKing_x, posKing_y);
				}
				if (board[i][j] == WHITE_KING) {
					ok = KingWCheck(j, i, posKing_x, posKing_y);
				}
				if (ok == 1) {
					return 0;
				}
			}
		}
	}
	return 1;
}

int KingB(int old_x, int old_y, int new_x, int new_y) {
	if (old_x - 1 >= 0 && old_y - 1 >= 0 && new_y == old_y - 1 && new_x == old_x - 1 && board[new_y][new_x] <= 0) {
		int ok = BlackKingCheck(old_x - 1, old_y - 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_y - 1 >= 0 && new_y == old_x && new_y == old_y - 1 && board[new_y][new_x] <= 0) {
		int ok = BlackKingCheck(old_x, old_y - 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_y - 1 >= 0 && old_x + 1 < LENGTH && new_x == old_x + 1 && new_y == old_y - 1 && board[new_y][new_x] <= 0) {
		int ok = BlackKingCheck(old_x + 1, old_y - 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_x + 1 <= LENGTH && new_y == old_y && new_x == old_x + 1 && board[new_y][new_x] <= 0) {
		int ok = BlackKingCheck(old_x + 1, old_y);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_x + 1 <= LENGTH && old_y + 1 <= LENGTH && new_y == old_y + 1 && new_x == old_x + 1 && board[new_y][new_x] <= 0) {
		int ok = BlackKingCheck(old_x + 1, old_y + 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_y + 1 <= LENGTH && new_y == old_y + 1 && new_x == old_x && board[new_y][new_x] <= 0) {
		int ok = BlackKingCheck(old_x, old_y + 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_x - 1 >= 0 && old_y + 1 <= LENGTH && new_x == old_x + 1 && new_y == old_y + 1 && board[new_y][new_x] <= 0) {
		int ok = BlackKingCheck(old_x - 1, old_y + 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_x - 1 >= 0 && new_y == old_y && new_x == old_x - 1 && board[new_y][new_x] <= 0) {
		int ok = BlackKingCheck(old_x - 1, old_y);
		if (ok == 1) {
			return 1;
		}
	}
	if (rightBlackRookM == 0 && blackKingFirstMove == 0 &&
		board[0][5] == 0 && board[0][6] == 0 &&
		new_y == 0 && new_y == 6) {

		int ok = BlackKingCheck(4, 0);
		if (ok == 1) {
			ok = BlackKingCheck(5, 0);
			if (ok == 1) {
				ok = BlackKingCheck(6, 0);
				if (ok == 1) {
					blackKingFirstMove = 1;
					rightBlackRookM = 1;
					board[0][7] = 0;
					board[0][5] = BLACK_ROOK;
					return 1;
				}
			}
		}
	}
	if (leftBlackRookM == 0 && blackKingFirstMove == 0 &&
		board[0][3] == 0 && board[0][2] == 0 && board[0][1] == 0 &&
		new_y == 0 && new_y == 2) {

		int ok = BlackKingCheck(4, 0);
		if (ok == 1) {
			ok = BlackKingCheck(3, 0);
			if (ok == 1) {
				ok = BlackKingCheck(2, 0);
				if (ok == 1) {
					ok = BlackKingCheck(1, 0);
					if (ok == 1) {
						blackKingFirstMove = 1;
						leftBlackRookM = 1;
						board[0][0] = 0;
						board[0][3] = BLACK_ROOK;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int WhiteKingCheck(int posKing_x, int posKing_y) {
	int ok = 0;
	for (int i = 0; i <= LENGTH; i++) {
		for (int j = 0; j <= LENGTH; j++) {
			if (board[i][j] > 0) {
				if (board[i][j] == BLACK_PAWN) {
					ok = PawnBCheck(j, i, posKing_x, posKing_y);
				}
				if (board[i][j] == BLACK_ROOK) {
					ok = RookBCheck(j, i, posKing_x, posKing_y);
				}
				if (board[i][j] == BLACK_KNIGHT) {
					ok = KnightBCheck(j, i, posKing_x, posKing_y);
				}
				if (board[i][j] == BLACK_BITSHOP) {
					ok = BitshopBCheck(j, i, posKing_x, posKing_y);
				}
				if (board[i][j] == BLACK_QUEEN) {
					ok = QueenBCheck(j, i, posKing_x, posKing_y);
				}
				if (board[i][j] == BLACK_KING) {
					ok = KingBCheck(j, i, posKing_x, posKing_y);
				}
				if (ok == 1) {
					return 0;
				}
			}
		}
	}
	return 1;
}

int KingW(int old_x, int old_y, int new_x, int new_y) {
	if (old_x - 1 >= 0 && old_y - 1 >= 0 && new_y == old_y - 1 && new_x == old_x - 1 && board[new_y][new_x] >= 0) {
		int ok = WhiteKingCheck(old_x - 1, old_y - 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_y - 1 >= 0 && new_y == old_x && new_y == old_y - 1 && board[new_y][new_x] >= 0) {
		int ok = WhiteKingCheck(old_x, old_y - 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_y - 1 >= 0 && old_x + 1 < LENGTH && new_x == old_x + 1 && new_y == old_y - 1 && board[new_y][new_x] >= 0) {
		int ok = WhiteKingCheck(old_x + 1, old_y - 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_x + 1 <= LENGTH && new_y == old_y && new_x == old_x + 1 && board[new_y][new_x] >= 0) {
		int ok = WhiteKingCheck(old_x + 1, old_y);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_x + 1 <= LENGTH && old_y + 1 <= LENGTH && new_y == old_y + 1 && new_x == old_x + 1 && board[new_y][new_x] >= 0) {
		int ok = WhiteKingCheck(old_x + 1, old_y + 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_y + 1 <= LENGTH && new_y == old_y + 1 && new_x == old_x && board[new_y][new_x] >= 0) {
		int ok = WhiteKingCheck(old_x, old_y + 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_x - 1 >= 0 && old_y + 1 <= LENGTH && new_x == old_x + 1 && new_y == old_y + 1 && board[new_y][new_x] >= 0) {
		int ok = WhiteKingCheck(old_x - 1, old_y + 1);
		if (ok == 1) {
			return 1;
		}
	}
	if (old_x - 1 >= 0 && new_y == old_y && new_x == old_x - 1 && board[new_y][new_x] >= 0) {
		int ok = WhiteKingCheck(old_x - 1, old_y);
		if (ok == 1) {
			return 1;
		}
	}
	if (whiteKingFirstMove == 0 && rightWhiteRookM == 0 && board[7][5] == 0 && board[7][6] == 0 && new_y == 7 && new_x == 6) {
		int ok = WhiteKingCheck(4, 7);
		if (ok == 1) {
			ok = WhiteKingCheck(5, 7);
			if (ok == 1) {
				ok = WhiteKingCheck(6, 7);
				if (ok == 1) {
					board[7][7] = 0;
					board[7][5] = WHITE_ROOK;
					whiteKingFirstMove = 1;
					rightWhiteRookM = 1;
					return 1;
				}
			}
		}
	}
	if (whiteKingFirstMove == 0 && rightWhiteRookM == 0 && board[7][3] == 0 && board[7][2] == 0 && board[7][1] == 0 && new_y == 7 && new_x == 2) {
		int ok = WhiteKingCheck(4, 7);
		if (ok == 1) {
			ok = WhiteKingCheck(3, 7);
			if (ok == 1) {
				ok = WhiteKingCheck(2, 7);
				if (ok == 1) {
					ok = WhiteKingCheck(1, 7);
					if (ok == 1) {
						board[7][0] = 0;
						board[7][3] = WHITE_ROOK;
						whiteKingFirstMove = 1;
						leftWhiteRookM = 1;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

void posWhiteKing() {
	for (int i = 0; i <= LENGTH; i++) {
		for (int j = 0; j <= LENGTH; j++) {
			if (board[i][j] == WHITE_KING) {
				whiteKing.x = j;
				whiteKing.y = i;
				break;
			}
		}
	}
}

void posBlackKing() {
	for (int i = 0; i <= LENGTH; i++) {
		for (int j = 0; j <= LENGTH; j++) {
			if (board[i][j] == BLACK_KING) {
				blackKing.x = j;
				blackKing.y = i;
				break;
			}
		}
	}
}