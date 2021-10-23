//#pragma once
//#include "SFML/Graphics.hpp"
//#include <time.h>
//#include <iostream>
//#include <string>
//
//#define FILD_SIZE 8					// ������ �������� ����
//#define CELL_SIZE 66				// ������ ������ �������� � ������� �������� (���� ������ ��� �������� ����� ����� ��������)
//#define FONT_SIZE 24				// ������ ������
//#define BLACK Color(0, 0, 0)		// ׸���� ����
//#define WHITE Color(255, 255, 255)	// ����� ����
//#define TEXT_TYPE Text::Bold		// ��� ������
//#define TEXT_COLOR Color::Black		// ���� ������
//#define COUNT_CHECKER 12
//
//using namespace sf;
//
//enum CellType						//���� ������
//{
//	Blue = 0,
//	White = 1,
//	Green = 2
//};
//
//enum CheckerTypeBoard				//���� �����
//{
//	BlackChecker = 2,
//	WhiteChecker = 1,
//	EmptyChecker = 0
//};
//
//struct TextureAndText
//{
//	Font font;
//	Text* txt;
//
//	Texture white;
//	Texture blue;
//	Texture green;
//	Texture black�hecker;
//	Texture white�hecker;
//
//	Sprite* whiteSprite;
//	Sprite* blueSprite;
//	Sprite* greenSprite;
//	Sprite* black�heckerSprite;
//	Sprite* white�heckerSprite;
//};
//
//struct Board
//{
//	int gridLogic[FILD_SIZE][FILD_SIZE];
//	int gridView[FILD_SIZE][FILD_SIZE];
//
//	int size = 8;					// ������ �������� ���� � �������
//	int arraySize = size * size;	// ������ ������� ������
//	int fieldSize = 670;			// ������ �������� ���� � ��������
//	int cellSize = 70;				// ������ ������ � ��������
//};
//
//struct WindowGame
//{
//	std::string name;
//	int windowHight;
//	int windowWidth;
//	RenderWindow* app;
//	Event e;
//	Board gameBoard;
//	TextureAndText gameTextureAndText;
//};
//
//class ModelView
//{
//private:
//	WindowGame* game;
//
//public:
//	ModelView();
//
//	ModelView(std::string name, int windowHight, int windowWidth);
//
//	~ModelView()
//	{
//		free(game);
//	}
//
//	void Start();
//	void Events();
//
//	void Select�heckers();
//	void GameBoardInit();
//	void GameBoardUpdate();
//	void LoadTexturesAndText();
//
//};