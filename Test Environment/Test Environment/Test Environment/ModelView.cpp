#include "ModelView.h"

ModelView::ModelView()
{
	game = new WindowGame;
	game->app = new (RenderWindow)(VideoMode(1024, 768), "SFML Checkers!", Style::Close | sf::Style::Titlebar);
	LoadTexturesAndText();
}

ModelView::ModelView(std::string name, int windowHight, int windowWidth)
{
	game = new WindowGame;
	game->app = new (RenderWindow)(VideoMode(windowHight, windowWidth), name, Style::Close | sf::Style::Titlebar);
	LoadTexturesAndText();
}

void ModelView::LoadTexturesAndText()
{
	//������� ��� ������� �����
	game->gameTextureAndText.whiteSprite = new Sprite[FILD_SIZE * (FILD_SIZE / 2)];
	game->gameTextureAndText.blueSprite = new Sprite[FILD_SIZE * (FILD_SIZE / 2)];
	game->gameTextureAndText.greenSprite = new Sprite[FILD_SIZE * FILD_SIZE];

	//������� ��� �����
	game->gameTextureAndText.black�heckerSprite = new Sprite[COUNT_CHECKER];
	game->gameTextureAndText.white�heckerSprite = new Sprite[COUNT_CHECKER];

	game->gameTextureAndText.font.loadFromFile("..\\Debug\\fonts\\CyrilicOld.TTF");
	game->gameTextureAndText.white.loadFromFile("..\\Debug\\textures\\White.png");
	game->gameTextureAndText.blue.loadFromFile("..\\Debug\\textures\\Blue.png");
	game->gameTextureAndText.green.loadFromFile("..\\Debug\\textures\\Green.JPG");
	game->gameTextureAndText.black�hecker.loadFromFile("..\\Debug\\textures\\blackCh.png");
	game->gameTextureAndText.white�hecker.loadFromFile("..\\Debug\\textures\\whiteCh.png");

	for (size_t i = 0; i < (game->gameBoard.size * (game->gameBoard.size / 2)); i++)
	{
		game->gameTextureAndText.whiteSprite[i].setTexture(game->gameTextureAndText.white);
		game->gameTextureAndText.blueSprite[i].setTexture(game->gameTextureAndText.blue);
	}
	//	greenSprite->setTexture(green);
	//
	for (size_t i = 0; i < COUNT_CHECKER; i++)
	{
		game->gameTextureAndText.black�heckerSprite[i].setTexture(game->gameTextureAndText.black�hecker);
		game->gameTextureAndText.white�heckerSprite[i].setTexture(game->gameTextureAndText.white�hecker);
	}

	//�����
	game->gameTextureAndText.txt = new Text;
	game->gameTextureAndText.txt->setFont(game->gameTextureAndText.font);
	game->gameTextureAndText.txt->setCharacterSize(FONT_SIZE);
	game->gameTextureAndText.txt->setFillColor(TEXT_COLOR);
	game->gameTextureAndText.txt->setStyle(TEXT_TYPE);
}

void ModelView::Start()
{
	GameBoardInit();

	while (game->app->isOpen())
	{
		game->app->clear(Color::Black);
		Events();
		GameBoardUpdate();
		game->app->display();
	}
}

void ModelView::Events()
{
	while (game->app->pollEvent(game->e))
	{
		if (game->e.type == Event::Closed)
			game->app->close();

		if (game->e.type == Event::MouseButtonPressed)//���� ������ ������� ����
			if (game->e.key.code == Mouse::Left) {//�����
				Select�heckers();
			}
	}
}


void ModelView::GameBoardInit()
{
	//��������� ����������� ���� ����������
	for (int i = 0; i < FILD_SIZE; i++)
		for (int j = 0; j < FILD_SIZE; j++)
		{
			if (i % 2 == 0)
			{
				game->gameBoard.gridView[i][j] = (j % 2 == 0) ? White : Blue;
			}
			else
			{
				game->gameBoard.gridView[i][j] = (j % 2 == 0) ? Blue : White;
			}
		}

	//��������� ���������� ���� ����������
	for (int i = 0; i < FILD_SIZE; i++)
		for (int j = 0; j < FILD_SIZE; j++)
		{
			if (i % 2 != 0)
			{
				if (j < FILD_SIZE - 5)
					game->gameBoard.gridLogic[i][j] = (j % 2 == 0) ? WhiteChecker : EmptyChecker;
				if (j > FILD_SIZE - 4)
					game->gameBoard.gridLogic[i][j] = (j % 2 == 0) ? BlackChecker : EmptyChecker;
				if ((j == 3 || j == 4))
					game->gameBoard.gridLogic[i][j] = EmptyChecker;
			}
			else
			{
				if (j < FILD_SIZE - 5)
					game->gameBoard.gridLogic[i][j] = (j % 2 == 0) ? EmptyChecker : WhiteChecker;
				if (j > FILD_SIZE - 4)
					game->gameBoard.gridLogic[i][j] = (j % 2 == 0) ? EmptyChecker : BlackChecker;
				if ((j == 3 || j == 4))
					game->gameBoard.gridLogic[i][j] = EmptyChecker;
			}
		}

}

void ModelView::GameBoardUpdate()
{
	//������� ����� ������������� (������� �������� �����) 
	RectangleShape rectangleBoardWhite(Vector2f((game->gameBoard.cellSize * (game->gameBoard.size + 1)), (game->gameBoard.cellSize * (game->gameBoard.size + 1))));
	//���������� ��� � ������ ��� ������ �� ��������������
	rectangleBoardWhite.move((game->gameBoard.cellSize / 2), (game->gameBoard.cellSize / 2));
	//������������� ��� ����
	rectangleBoardWhite.setFillColor(WHITE);
	//��������� ��������������
	game->app->draw(rectangleBoardWhite);

	//������� ������ ������������� (���������� ����������� ����� ��������) (5 � 10 �������� � �������� �� ������ �����)
	RectangleShape rectangleBoardBlack(Vector2f(game->gameBoard.cellSize * game->gameBoard.size + 10, game->gameBoard.cellSize * game->gameBoard.size + 10));
	//���������� ��� � ������ ��� ������ �� ��������������
	rectangleBoardBlack.move(game->gameBoard.cellSize - 5, game->gameBoard.cellSize - 5);
	//������������� ��� ����
	rectangleBoardBlack.setFillColor(BLACK);
	//��������� ��������������
	game->app->draw(rectangleBoardBlack);

	//��������� ���� � ���� �� ����
	//���������� ��� ����
	int digitStartPosLeftX = game->gameBoard.cellSize - game->gameBoard.cellSize / 3;
	int digitStartPosRightX = (game->gameBoard.cellSize * 9) + game->gameBoard.cellSize / 6;
	//���������� ��� ����
	int charPosX = game->gameBoard.cellSize + game->gameBoard.cellSize / 3;
	int	charStartPosTopY = game->gameBoard.cellSize / 2;
	int	charStartPosBottomY = (game->gameBoard.cellSize * 9);

	for (int i = 1, digitPosY = (game->gameBoard.cellSize + (game->gameBoard.cellSize / 5)); i < 9; i += 1, digitPosY += game->gameBoard.cellSize)
	{
		game->gameTextureAndText.txt->setPosition(digitStartPosLeftX, digitPosY);
		game->gameTextureAndText.txt->setString(std::to_string(i));
		game->app->draw(*game->gameTextureAndText.txt);

		game->gameTextureAndText.txt->setPosition(digitStartPosRightX, digitPosY);
		game->gameTextureAndText.txt->setString(std::to_string(i));
		game->app->draw(*game->gameTextureAndText.txt);
	}

	for (char ch = 'a'; ch < 'i'; ch += 1, charPosX += game->gameBoard.cellSize)
	{
		game->gameTextureAndText.txt->setPosition(charPosX, charStartPosTopY);
		game->gameTextureAndText.txt->setString(ch);
		game->app->draw(*game->gameTextureAndText.txt);

		game->gameTextureAndText.txt->setPosition(charPosX, charStartPosBottomY);
		game->gameTextureAndText.txt->setString(ch);
		game->app->draw(*game->gameTextureAndText.txt);
	}

	//��������� ����������� ��������� �� ���� � �����
	int whiteSpriteIndex = 0;
	//int greenSpriteIndex = 0;
	int blueSpriteIndex = 0;
	int white�heckerSpriteIndex = 0;
	int black�heckerSpriteIndex = 0;

	for (int i = 0; i < FILD_SIZE; i++)
		for (int j = 0; j < FILD_SIZE; j++)
		{
			if (game->gameBoard.gridView[i][j] == White)
			{
				// ������������� ��� � �������� �������...
				game->gameTextureAndText.whiteSprite[whiteSpriteIndex].setPosition((i + 1) * game->gameBoard.cellSize, (j + 1) * game->gameBoard.cellSize);
				//	�������������
				game->app->draw(game->gameTextureAndText.whiteSprite[whiteSpriteIndex]);
				whiteSpriteIndex++;
			}
			//			else if (game->gameBoard.gridView[i][j] == Green) {
			//				// ������������� ��� � �������� �������
			//				game->gameTextureAndText.greenSprite[greenSpriteIndex].setPosition((i + 1) * game->gameBoard.cellSize, (j + 1) * game->gameBoard.cellSize);
			//				// �������������
			//				game->app->draw(greenSprite[greenSpriteIndex]);
			//				greenSpriteIndex++;
			//			}
			else {
				// ������������� ��� � �������� �������
				game->gameTextureAndText.blueSprite[blueSpriteIndex].setPosition((i + 1) * game->gameBoard.cellSize, (j + 1) * game->gameBoard.cellSize);
				// �������������
				game->app->draw(game->gameTextureAndText.blueSprite[blueSpriteIndex]);
				blueSpriteIndex++;
			}

			//��������� ����� �� ����
			if (game->gameBoard.gridLogic[i][j] == WhiteChecker)
			{
				// ������������� ��� � �������� �������...
				game->gameTextureAndText.white�heckerSprite[white�heckerSpriteIndex].setPosition((i + 1) * game->gameBoard.cellSize + 7, (j + 1) * game->gameBoard.cellSize + 7);
				//	�������������
				game->app->draw(game->gameTextureAndText.white�heckerSprite[white�heckerSpriteIndex]);
				white�heckerSpriteIndex++;
			}
			else if (game->gameBoard.gridLogic[i][j] == BlackChecker) {
				// ������������� ��� � �������� �������
				game->gameTextureAndText.black�heckerSprite[black�heckerSpriteIndex].setPosition((i + 1) * game->gameBoard.cellSize + 7, (j + 1) * game->gameBoard.cellSize + 7);
				// �������������
				game->app->draw(game->gameTextureAndText.black�heckerSprite[black�heckerSpriteIndex]);
				black�heckerSpriteIndex++;
			}
		}
}

void ModelView::Select�heckers()
{
	for (size_t i = 0; i < FILD_SIZE * FILD_SIZE; i++)
	{
		if ((i < 32) && (game->gameTextureAndText.whiteSprite[i % 32].getGlobalBounds().contains(game->e.mouseButton.x, game->e.mouseButton.y)))
		{
			std::cout << "White: " << i + 1 << std::endl;
			std::cout << "mouse x: " << game->e.mouseButton.x << std::endl;
			std::cout << "mouse y: " << game->e.mouseButton.y << "\n" << std::endl;
		}
		if ((i < 32) && (game->gameTextureAndText.blueSprite[i % 32].getGlobalBounds().contains(game->e.mouseButton.x, game->e.mouseButton.y)))
		{
			std::cout << "Blue: " << i + 1 << std::endl;
			std::cout << "mouse x: " << game->e.mouseButton.x << std::endl;
			std::cout << "mouse y: " << game->e.mouseButton.y << "\n" << std::endl;
		}
		if ((i < 12) && (game->gameTextureAndText.white�heckerSprite[i % 12].getGlobalBounds().contains(game->e.mouseButton.x, game->e.mouseButton.y)))
		{

			std::cout << "White Checker Sprite: " << i + 1 << std::endl;
			std::cout << "mouse x: " << game->e.mouseButton.x << std::endl;
			std::cout << "mouse y: " << game->e.mouseButton.y << "\n" << std::endl;
		}
		if ((i < 12) && (game->gameTextureAndText.black�heckerSprite[i % 12].getGlobalBounds().contains(game->e.mouseButton.x, game->e.mouseButton.y)))
		{

			std::cout << "Black Checker Sprite: " << i + 1 << std::endl;
			std::cout << "mouse x: " << game->e.mouseButton.x << std::endl;
			std::cout << "mouse y: " << game->e.mouseButton.y << "\n" << std::endl;

		}
	}
}