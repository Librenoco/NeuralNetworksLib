#pragma once
#include "SFML/Graphics.hpp"
#include <time.h>
#include <iostream>
#include <string>
#include "ChessGame.h"

#define FILD_SIZE 8					// ������ �������� ����
#define CELL_SIZE 66				// ������ ������ �������� � ������� �������� (���� ������ ��� �������� ����� ����� ��������)
#define FONT_SIZE 24				// ������ ������
#define BLACK Color(0, 0, 0)		// ׸���� ����
#define WHITE Color(255, 255, 255)	// ����� ����
#define TEXT_TYPE Text::Bold		// ��� ������
#define TEXT_COLOR Color::Black		// ���� ������
#define COUNT_CHECKER 12

using namespace sf;

enum class CellType						//���� ������
{
	Blue,
	White,
	Green,
	Yellow
};

struct TextureAndText
{
	Font font;
	Text* txt;
	Text* txtInfo;

	Texture white;
	Texture blue;
	Texture green;
	Texture yellow;
	Texture newGameButton;

	/// <������>
	Texture PawnWH;
	Texture KnightWH;
	Texture BishopWH;
	Texture RookWH;
	Texture QueenWH;
	Texture KingWH;

	Texture PawnBL;
	Texture KnightBL;
	Texture BishopBL;
	Texture RookBL;
	Texture QueenBL;
	Texture KingBL;
	/// </������>

	Sprite whiteSprite;
	Sprite blueSprite;
	Sprite yellowSprite;
	Sprite greenSprite;
	Sprite newGameButtonSprite;
	/// <������>
	Sprite PawnWHSprite;
	Sprite KnightWHSprite;
	Sprite BishopWHSprite;
	Sprite RookWHSprite;
	Sprite QueenWHSprite;
	Sprite KingWHSprite;

	Sprite PawnBLSprite;
	Sprite KnightBLSprite;
	Sprite BishopBLSprite;
	Sprite RookBLSprite;
	Sprite QueenBLSprite;
	Sprite KingBLSprite;
	/// </������>

	
};

struct Board
{
	const ChessGame::Figure* gridLogic[FILD_SIZE][FILD_SIZE];
	CellType gridView[FILD_SIZE][FILD_SIZE];

	int size = 8;					// ������ �������� ���� � �������
	int arraySize = size * size;	// ������ ������� ������
	int fieldSize = 670;			// ������ �������� ���� � ��������
	int cellSize = 70;				// ������ ������ � ��������
};

struct WindowGame
{
	std::string name;
	int windowHight;
	int windowWidth;
	RenderWindow* app;
	Event e;
	Board gameBoard;
	TextureAndText gameTextureAndText;
};

class ChessMV
{
public:
	ChessMV();

	ChessMV(std::string name, int windowHight, int windowWidth);

	~ChessMV() { delete windowGame; }

	void Start();

	void ConnectGame(ChessGame* game) { this->game = game; };

private:

	void Events();

	void Select�heckers();
	void GameBoardInit();
	void GameBoardUpdate();
	void GameBoardTextUpdate();
	void GameBoardStaticUpdate();
	void GameBoardAnd�heckersUpdate();
	void LoadTexturesAndText();
	void StartNewGame();

	void UpdateFromGame();

	WindowGame* windowGame;
	ChessGame* game;
};