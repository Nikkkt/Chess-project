#include <SFML/Graphics.hpp>
#include <iostream>
#include "logic.h"
using namespace sf;

int main() {
	// отрисовка экрана
	RenderWindow window(VideoMode(800, 800), "Chess made by ShoSho");

	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;
	t1.loadFromFile("images/board.png");
	t2.loadFromFile("images/BlackPawn.png");
	t3.loadFromFile("images/WhitePawn.png");
	t4.loadFromFile("images/WhiteRook.png");
	t5.loadFromFile("images/BlackRook.png");
	t6.loadFromFile("images/WhiteKnight.png");
	t7.loadFromFile("images/BlackKnight.png");
	t8.loadFromFile("images/WhiteBitshop.png");
	t9.loadFromFile("images/BlackBitshop.png");
	t10.loadFromFile("images/WhiteQueen.png");
	t11.loadFromFile("images/BlackQueen.png");
	t12.loadFromFile("images/BlackKing.png");
	t13.loadFromFile("images/WhiteKing.png");
	t14.loadFromFile("images/TransformationWhite.png");
	t15.loadFromFile("images/TransformationBlack.png");

	Sprite Table(t1);
	Sprite BlackPawn(t2);
	Sprite WhitePawn(t3);
	Sprite WhiteRook(t4);
	Sprite BlackRook(t5);
	Sprite WhiteKnight(t6);
	Sprite BlackKnight(t7);
	Sprite WhiteBitshop(t8);
	Sprite BlackBitshop(t9);
	Sprite WhiteQueen(t10);
	Sprite BlackQueen(t11);
	Sprite BlackKing(t12);
	Sprite WhiteKing(t13);
	Sprite WhiteTransformation(t14);
	Sprite BlackTransformation(t15);
	Sprite MoveImages;

	float dx = 0, dy = 0;
	int noMovedPiece = 0;

	while (window.isOpen()) {
		Vector2i pos = Mouse::getPosition(window);

		int x = pos.x / size;
		int y = pos.y / size;
		Event e;

		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) { 
				window.close(); 
			}
			window.clear();

			if (e.type == Event::MouseButtonPressed) {
				if (e.key.code == Mouse::Left) {
					if (transformationWhite == 1) {
						if (pos.y >= transformWHITE.y * size && pos.y <= (transformWHITE.y + 1) * size && pos.x >= transformWHITE.x * size && pos.x <= (transformWHITE.x + 1) * size) {
							int xx = pos.x % size;
							int yy = pos.y % size;
							if (xx < 50 && yy < 50 && xx > 0 && yy > 0) {
								board[transformWHITE.y][transformWHITE.x] = WHITE_ROOK;
								transformationWhite = 0;
							}
							if (xx > 50 && yy > 50 && xx < 100 && yy < 100) {
								board[transformWHITE.y][transformWHITE.x] = WHITE_KNIGHT;
								transformationWhite = 0;
							}
							if (xx > 0 && yy > 50 && xx < 50 && yy < 100) {
								board[transformWHITE.y][transformWHITE.x] = WHITE_BITSHOP;
								transformationWhite = 0;
							}
							if (transformationWhite == 0) {
								posBlackKing();
								int h = BlackKingCheck(blackKing.x, blackKing.y);
								if (h == 0) {
									checkBlack = 1;
								}
							}
						}
					}
					if (transformationBlack == 1) {
						if (pos.y >= transformBLACK.y * size && pos.y <= (transformBLACK.y + 1) * size && pos.x >= transformBLACK.x * size && pos.x <= (transformBLACK.x + 1) * size) {
							int xx = pos.x % size;
							int yy = pos.y % size;
							if (xx > 0 && yy > 0 && xx < 50 && yy < 50) {
								board[transformBLACK.y][transformBLACK.x] = BLACK_ROOK;
								transformationBlack = 0;
							}
							if (xx > 50 && yy > 0 && xx < 100 && yy < 50) {
								board[transformBLACK.y][transformBLACK.x] = BLACK_QUEEN;
								transformationBlack = 0;
							}
							if (xx > 50 && yy > 50 && xx < 100 && yy < 100) {
								board[transformBLACK.y][transformBLACK.x] = BLACK_KNIGHT;
								transformationBlack = 0;
							}
							if (xx > 0 && yy > 50 && xx < 50 && yy < 100) {
								board[transformBLACK.y][transformBLACK.x] = BLACK_BITSHOP;
								transformationBlack = 0;
							}
							if (transformationBlack == 0) {
								posWhiteKing();
								int h = WhiteKingCheck(whiteKing.x, whiteKing.y);
								if (h == 1) {
									checkWhite = 1;
								}
							}
						}
					}
					// трансформация
					if (board[y][x] != 0) {
						dx = pos.x - x * size;
						dy = pos.y - y * size;

						// пешки
						if (board[y][x] == BLACK_PAWN && move == 1)  {
							noMovedPiece = BLACK_PAWN;
							MoveImages = BlackPawn;
							board[y][x] = 0;
						}
						if (board[y][x] == WHITE_PAWN && move == 0) {				   
							noMovedPiece = WHITE_PAWN;
							MoveImages = WhitePawn;
							board[y][x] = 0;
						}

						// ладьи
						if (board[y][x] == WHITE_ROOK && move == 0) {
							noMovedPiece = WHITE_ROOK;
							MoveImages = WhiteRook;
							board[y][x] = 0;
						}
						if (board[y][x] == BLACK_ROOK && move == 1) {
							noMovedPiece = BLACK_ROOK;
							MoveImages = BlackRook;
							board[y][x] = 0;
						}

						// слоны
						if (board[y][x] == WHITE_KNIGHT && move == 0) {
							noMovedPiece = WHITE_KNIGHT;
							MoveImages = WhiteKnight;
							board[y][x] = 0;
						}
						if (board[y][x] == BLACK_KNIGHT && move == 1) {
							noMovedPiece = BLACK_KNIGHT;
							MoveImages = BlackKnight;
							board[y][x] = 0;
						}

						// кони
						if (board[y][x] == WHITE_BITSHOP && move == 0) {
							noMovedPiece = WHITE_BITSHOP;
							MoveImages = WhiteBitshop;
							board[y][x] = 0;
						}
						if (board[y][x] == BLACK_BITSHOP && move == 1) {
							noMovedPiece = BLACK_BITSHOP;
							MoveImages = BlackBitshop;
							board[y][x] = 0;
						}

						// королевы
						if (board[y][x] == WHITE_QUEEN && move == 0) {
							noMovedPiece = WHITE_QUEEN;
							MoveImages = WhiteQueen;
							board[y][x] = 0;
						}
						if (board[y][x] == BLACK_QUEEN && move == 1) {
							noMovedPiece = BLACK_QUEEN;
							MoveImages = BlackQueen;
							board[y][x] = 0;
						}

						// короли
						if (board[y][x] == WHITE_KING && move == 0) {
							noMovedPiece = WHITE_KING;
							MoveImages = WhiteKing;
							board[y][x] = 0;
						}
						if (board[y][x] == BLACK_KING && move == 1) {
							noMovedPiece = BLACK_KING;
							MoveImages = BlackKing;
							board[y][x] = 0;
						}

						if (board[y][x] == 0) {
							isMoving = 1;
							oldPoz.x = x;
							oldPoz.y = y;
						}
 					}
				}
			}
			if (e.type == Event::MouseButtonReleased) {
				if (e.key.code == Mouse::Left) {
					int ok;
					if (noMovedPiece == WHITE_PAWN && isMoving == 1) {
						ok = PawnW(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedPiece == BLACK_PAWN && isMoving == 1) {
						ok = PawnB(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedPiece == WHITE_ROOK && isMoving == 1) {
						ok = RookW(oldPoz.x, oldPoz.y, x, y);
						if (ok == 1 && leftWhiteRookM == 0 && oldPoz.y == 7 && oldPoz.x == 0) {
							leftWhiteRookM = 1;
						}
						if (ok == 1 && rightWhiteRookM == 0 && oldPoz.y == 7 && oldPoz.x == 7) {
							rightWhiteRookM = 1;
						}
					}
					if (noMovedPiece == BLACK_ROOK && isMoving == 1) {
						ok = RookB(oldPoz.x, oldPoz.y, x, y);
						if (ok == 1 && leftBlackRookM == 0 && oldPoz.y == 0 && oldPoz.x == 0) {
							leftBlackRookM = 1;
						}
						if (ok == 1 && rightBlackRookM == 0 && oldPoz.y == 0 && oldPoz.x == 7) {
							rightBlackRookM = 1;
						}
					}
					if (noMovedPiece == WHITE_BITSHOP && isMoving == 1) {
						ok = BitshopW(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedPiece == BLACK_BITSHOP && isMoving == 1) {
						ok = BitshopB(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedPiece == WHITE_QUEEN && isMoving == 1) {
						ok = QueenW(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedPiece == BLACK_QUEEN && isMoving == 1) {
						ok = QueenB(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedPiece == WHITE_KNIGHT && isMoving == 1) {
						ok = KnightW(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedPiece == BLACK_KNIGHT && isMoving == 1) {
						ok = KnightB(oldPoz.x, oldPoz.y, x, y);
					}
					if (noMovedPiece == WHITE_KING && isMoving == 1) {
						ok = KingW(oldPoz.x, oldPoz.y, x, y);
						if (ok == 1 && whiteKingFirstMove == 0) {
							whiteKingFirstMove = 1;
						}
					}
					if (noMovedPiece == BLACK_KING && isMoving == 1) {
						ok = KingB(oldPoz.x, oldPoz.y, x, y);
						if (ok == 1 && blackKingFirstMove == 0) {
							blackKingFirstMove = 1;
						}
					}
					if (ok == 1) {
						int nr = board[y][x];
						board[y][x] = noMovedPiece;
						if (y == 0 && noMovedPiece == WHITE_PAWN) {
							transformationWhite = 1;
							transformWHITE.x = x;
							transformWHITE.y = y;
						}
						if (y == 7 && noMovedPiece == BLACK_PAWN) {
							transformationBlack = 1;
							transformBLACK.x = x;
							transformBLACK.y = y;
							board[y][x] = 0;
						}
						if (move == 0) {
							if (checkWhite == 1) {
								posWhiteKing();
								int s = WhiteKingCheck(whiteKing.x, whiteKing.y);
								if (s == 0) {
									board[oldPoz.y][oldPoz.x] = noMovedPiece;
									board[y][x] = nr;
								}
								else {
									checkWhite = 0;
									posBlackKing();
									int check = BlackKingCheck(blackKing.x, blackKing.y);
									if (check == 0) {
										checkBlack = 1;
									}
									move = 1;
								}
							}
							else {
								posWhiteKing();
								int sa = WhiteKingCheck(whiteKing.x, whiteKing.y);
								if (sa == 0) {
									board[oldPoz.y][oldPoz.x] = noMovedPiece;
									board[y][x] = nr;
								}
								else {
									posBlackKing();
									int check = BlackKingCheck(blackKing.x, blackKing.y);
									if (check == 0) {
										checkBlack = 1;
									}
									move = 1;
								}
							}
						}
						else {
							if (checkBlack == 1) {
								int s = BlackKingCheck(blackKing.x, blackKing.y);
								if (s == 0) {
									board[oldPoz.y][oldPoz.x] = noMovedPiece;
									board[y][x] = nr;
								}
								else {
									checkBlack = 0;
									posWhiteKing();
									int check = WhiteKingCheck(whiteKing.x, whiteKing.y);
									if (check == 0) {
										checkWhite = 1;
									}
									move = 0;
								}
							}
							else {
								posBlackKing();
								int sa = BlackKingCheck(blackKing.x, blackKing.y);
								if (sa == 0) {
									board[oldPoz.y][oldPoz.x] = noMovedPiece;
									board[y][x] = nr;
								}
								else {
									posWhiteKing();
									int check = WhiteKingCheck(whiteKing.x, whiteKing.y);
									if (check == 0) {
										checkWhite = 1;
									}
									move = 0;
								}
							}
						}
					}
					else if (ok == 0) {
						board[oldPoz.y][oldPoz.x] = noMovedPiece;
					}
					isMoving = 0;
				}
			}
		}
		window.clear();

		window.draw(Table);
		if (transformationWhite == 1) {
			WhiteTransformation.setPosition(transformWHITE.x* size, transformWHITE.y* size);
			window.draw(WhiteTransformation);
		}
		if (transformationBlack == 1) {
			BlackTransformation.setPosition(transformBLACK.x* size, transformBLACK.y* size);
			window.draw(BlackTransformation);
		}
		if (isMoving == 1) {
			MoveImages.setPosition(pos.x - dx, pos.y - dy);
			window.draw(MoveImages);
		}

		// table
		for (int i = 0; i <= LENGTH; i++) {
			for (int j = 0; j <= LENGTH; j++) {
				if (board[i][j] != 0) {

					// пешки
					if (board[i][j] == BLACK_PAWN) {
						BlackPawn.setPosition(j* size, i* size);
						window.draw(BlackPawn);
					}
					if (board[i][j] == WHITE_PAWN) {
						WhitePawn.setPosition(j* size, i* size);
						window.draw(WhitePawn);
					}

					// ладьи
					if (board[i][j] == WHITE_ROOK) {
						WhiteRook.setPosition(j* size, i* size);
						window.draw(WhiteRook);
					}
					if (board[i][j] == BLACK_ROOK) {
						BlackRook.setPosition(j* size, i* size);
						window.draw(BlackRook);
					}

					// слоны
					if (board[i][j] == WHITE_KNIGHT) {
						WhiteKnight.setPosition(j* size, i* size);
						window.draw(WhiteKnight);
					}
					if (board[i][j] == BLACK_KNIGHT) {
						BlackKnight.setPosition(j* size, i* size);
						window.draw(BlackKnight);
					}
					
					// кони
					if (board[i][j] == WHITE_BITSHOP) {
						WhiteBitshop.setPosition(j* size, i* size);
						window.draw(WhiteBitshop);
					}
					if (board[i][j] == BLACK_BITSHOP) {
						BlackBitshop.setPosition(j* size, i* size);
						window.draw(BlackBitshop);
					}

					// королевы
					if (board[i][j] == WHITE_QUEEN) {
						WhiteQueen.setPosition(j* size, i* size);
						window.draw(WhiteQueen);
					}
					if (board[i][j] == BLACK_QUEEN) {
						BlackQueen.setPosition(j* size, i* size);
						window.draw(BlackQueen);
					}
					
					// короли
					if (board[i][j] == WHITE_KING) {
						WhiteKing.setPosition(j* size, i* size);
						window.draw(WhiteKing);
					}
					if (board[i][j] == BLACK_KING) {
						BlackKing.setPosition(j* size, i* size);
						window.draw(BlackKing);
					}
				}
			}
		}
		window.display();
	}
	return 0;
}