#pragma once
#include "SFML/Graphics.hpp"
#include <time.h>
#include <iostream>
#include <string>
#include "CheckersGame.h"

#define FILD_SIZE 8					// ������ �������� ����
#define CELL_SIZE 66				// ������ ������ �������� � ������� �������� (���� ������ ��� �������� ����� ����� ��������)
#define FONT_SIZE 24				// ������ ������
#define BLACK Color(0, 0, 0)		// ׸���� ����
#define WHITE Color(255, 255, 255)	// ����� ����
#define TEXT_TYPE Text::Bold		// ��� ������
#define TEXT_COLOR Color::Black		// ���� ������
#define COUNT_CHECKER 12

using namespace sf;

class ModelView
{
public:
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
		Texture black�hecker;
		Texture white�hecker;
		Texture black�heckerDM;
		Texture white�heckerDM;
		Texture newGameButton;

		Sprite whiteSprite;
		Sprite blueSprite;
		Sprite yellowSprite;
		Sprite greenSprite;
		Sprite black�heckerSprite;
		Sprite white�heckerSprite;
		Sprite black�heckerSpriteDM;
		Sprite white�heckerSpriteDM;
		Sprite newGameButtonSprite;
	};

	struct Board
	{
		const Checker* gridLogic[FILD_SIZE][FILD_SIZE];
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

	ModelView();

	ModelView(std::string name, int windowHight, int windowWidth);

	~ModelView() { delete windowGame; }

	void Start();

	void ConnectGame(CheckersGame* game) { this->game = game; };

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
	CheckersGame* game;
};