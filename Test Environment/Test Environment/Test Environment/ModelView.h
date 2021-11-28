//#pragma once
//#include "SFML/Graphics.hpp"
//#include <time.h>
//#include <iostream>
//#include <string>
//#include "CheckersGame.h"
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
//class ModelView
//{
//public:
//	ModelView();
//
//	ModelView(std::string name, int windowHight, int windowWidth);
//
//	~ModelView() { delete windowGame; }
//
//	void Start();
//
//	void ConnectGame(CheckersGame* game) { this->game = game; };
//
//private:
//
//	void Events();
//
//	void Select�heckers();
//	void GameBoardInit();
//	void GameBoardUpdate();
//	void GameBoardTextUpdate();
//	void GameBoardStaticUpdate();
//	void GameBoardAnd�heckersUpdate();
//	void LoadTexturesAndText();
//	void StartNewGame();
//
//	void UpdateFromGame();
//
//	WindowGame* windowGame;
//	CheckersGame* game;
//};