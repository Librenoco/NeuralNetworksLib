#include "ModelView.h"
#include "Log.h"

using namespace std;

ModelView::ModelView()
{
	windowGame = new WindowGame;
	windowGame->app = new (RenderWindow)(VideoMode(1024, 768), "SFML Checkers!", Style::Close | sf::Style::Titlebar);
	LoadTexturesAndText();
}

ModelView::ModelView(std::string name, int windowHight, int windowWidth)
{
	windowGame = new WindowGame;
	windowGame->app = new (RenderWindow)(VideoMode(windowHight, windowWidth), name, Style::Close | sf::Style::Titlebar);
	LoadTexturesAndText();
}

void ModelView::LoadTexturesAndText()
{
	//������� ��� ������� �����
	//windowGame->gameTextureAndText.whiteSprite = new Sprite[FILD_SIZE * (FILD_SIZE / 2)];
	//windowGame->gameTextureAndText.blueSprite = new Sprite[FILD_SIZE * (FILD_SIZE / 2)];
	//windowGame->gameTextureAndText.greenSprite = new Sprite[FILD_SIZE * FILD_SIZE];

	//������� ��� �����
	//windowGame->gameTextureAndText.black�heckerSprite = new Sprite[COUNT_CHECKER];
	//windowGame->gameTextureAndText.white�heckerSprite = new Sprite[COUNT_CHECKER];

	windowGame->gameTextureAndText.font.loadFromFile("..\\Debug\\fonts\\CyrilicOld.TTF");
	windowGame->gameTextureAndText.white.loadFromFile("..\\Debug\\textures\\White.png");
	windowGame->gameTextureAndText.blue.loadFromFile("..\\Debug\\textures\\Blue.png");
	windowGame->gameTextureAndText.green.loadFromFile("..\\Debug\\textures\\Green.JPG");
	windowGame->gameTextureAndText.black�hecker.loadFromFile("..\\Debug\\textures\\blackCh.png");
	windowGame->gameTextureAndText.white�hecker.loadFromFile("..\\Debug\\textures\\whiteCh.png");

	windowGame->gameTextureAndText.whiteSprite.setTexture(windowGame->gameTextureAndText.white);
	windowGame->gameTextureAndText.blueSprite.setTexture(windowGame->gameTextureAndText.blue);
	windowGame->gameTextureAndText.greenSprite.setTexture(windowGame->gameTextureAndText.green);
	
	windowGame->gameTextureAndText.black�heckerSprite.setTexture(windowGame->gameTextureAndText.black�hecker);
	windowGame->gameTextureAndText.white�heckerSprite.setTexture(windowGame->gameTextureAndText.white�hecker);

	//�����
	windowGame->gameTextureAndText.txt = new Text;
	windowGame->gameTextureAndText.txt->setFont(windowGame->gameTextureAndText.font);
	windowGame->gameTextureAndText.txt->setCharacterSize(FONT_SIZE);
	windowGame->gameTextureAndText.txt->setFillColor(TEXT_COLOR);
	windowGame->gameTextureAndText.txt->setStyle(TEXT_TYPE);
}

void ModelView::UpdateFromGame()
{
	//��������� ����������� ���� ����������
	for (int i = 0; i < FILD_SIZE; i++)
		for (int j = 0; j < FILD_SIZE; j++)
			windowGame->gameBoard.gridView[i][j] = (((j + i) % 2 == 0) ? CellType::White : CellType::Blue);

	//��������� ���������� ���� ����������
	for (int i = 0; i < FILD_SIZE; i++)
		for (int j = 0; j < FILD_SIZE; j++)
			windowGame->gameBoard.gridLogic[i][j] = nullptr;
	vector<const Checker*> checkers = game->GetCheckers();
	for (int i = 0; i < checkers.size(); i++)
		if (checkers[i] != nullptr)
			windowGame->gameBoard.gridLogic[checkers[i]->coord.x - 1][checkers[i]->coord.y - 1] = checkers[i];

	vector<Coord> moves = game->GetPossibleMoves(game->GetChosenChecker());
	for (int i = 0; i < moves.size(); i++)
		windowGame->gameBoard.gridView[moves[i].x - 1][moves[i].y - 1] = CellType::Green;

	//windowGame->gameBoard.gridView[game->GetChosenChecker()->coord.x - 1][game->GetChosenChecker()->coord.y - 1] = CellType::Yellow;
}

void ModelView::Start()
{
	GameBoardInit();

	while (windowGame->app->isOpen())
	{
		windowGame->app->clear(Color::Black);
		Events();
		UpdateFromGame();
		GameBoardUpdate();
		windowGame->app->display();
	}
}

void ModelView::Events()
{
	while (windowGame->app->pollEvent(windowGame->e))
	{
		if (windowGame->e.type == Event::Closed)
			windowGame->app->close();

		if (windowGame->e.type == Event::MouseButtonPressed)//���� ������ ������� ����
			if (windowGame->e.key.code == Mouse::Left) {//�����
				Select�heckers();
			}
	}
}


void ModelView::GameBoardInit()
{

	UpdateFromGame();
}

void ModelView::GameBoardUpdate()
{
	//������� ����� ������������� (������� �������� �����) 
	RectangleShape rectangleBoardWhite(Vector2f((windowGame->gameBoard.cellSize * (windowGame->gameBoard.size + 1)), (windowGame->gameBoard.cellSize * (windowGame->gameBoard.size + 1))));
	//���������� ��� � ������ ��� ������ �� ��������������
	rectangleBoardWhite.move((windowGame->gameBoard.cellSize / 2), (windowGame->gameBoard.cellSize / 2));
	//������������� ��� ����
	rectangleBoardWhite.setFillColor(WHITE);
	//��������� ��������������
	windowGame->app->draw(rectangleBoardWhite);

	//������� ������ ������������� (���������� ����������� ����� ��������) (5 � 10 �������� � �������� �� ������ �����)
	RectangleShape rectangleBoardBlack(Vector2f(windowGame->gameBoard.cellSize * windowGame->gameBoard.size + 10, windowGame->gameBoard.cellSize * windowGame->gameBoard.size + 10));
	//���������� ��� � ������ ��� ������ �� ��������������
	rectangleBoardBlack.move(windowGame->gameBoard.cellSize - 5, windowGame->gameBoard.cellSize - 5);
	//������������� ��� ����
	rectangleBoardBlack.setFillColor(BLACK);
	//��������� ��������������
	windowGame->app->draw(rectangleBoardBlack);

	//��������� ���� � ���� �� ����
	//���������� ��� ����
	int digitStartPosLeftX = windowGame->gameBoard.cellSize - windowGame->gameBoard.cellSize / 3;
	int digitStartPosRightX = (windowGame->gameBoard.cellSize * 9) + windowGame->gameBoard.cellSize / 6;
	//���������� ��� ����
	int charPosX = windowGame->gameBoard.cellSize + windowGame->gameBoard.cellSize / 3;
	int	charStartPosTopY = windowGame->gameBoard.cellSize / 2;
	int	charStartPosBottomY = (windowGame->gameBoard.cellSize * 9);

	for (int i = 1, digitPosY = (windowGame->gameBoard.cellSize + (windowGame->gameBoard.cellSize / 5)); i < 9; i += 1, digitPosY += windowGame->gameBoard.cellSize)
	{
		windowGame->gameTextureAndText.txt->setPosition(digitStartPosLeftX, digitPosY);
		windowGame->gameTextureAndText.txt->setString(std::to_string(i));
		windowGame->app->draw(*windowGame->gameTextureAndText.txt);

		windowGame->gameTextureAndText.txt->setPosition(digitStartPosRightX, digitPosY);
		windowGame->gameTextureAndText.txt->setString(std::to_string(i));
		windowGame->app->draw(*windowGame->gameTextureAndText.txt);
	}

	for (char ch = 'a'; ch < 'i'; ch += 1, charPosX += windowGame->gameBoard.cellSize)
	{
		windowGame->gameTextureAndText.txt->setPosition(charPosX, charStartPosTopY);
		windowGame->gameTextureAndText.txt->setString(ch);
		windowGame->app->draw(*windowGame->gameTextureAndText.txt);

		windowGame->gameTextureAndText.txt->setPosition(charPosX, charStartPosBottomY);
		windowGame->gameTextureAndText.txt->setString(ch);
		windowGame->app->draw(*windowGame->gameTextureAndText.txt);
	}

	//��������� ����������� ��������� �� ���� � �����

	auto drawSprite = [&](Sprite& sprite, int x, int y)
	{
		// ������������� ��� � �������� �������...
		sprite.setPosition(x, y);
		//	�������������
		windowGame->app->draw(sprite);
	};
	int x, y;

	for (int i = 0; i < FILD_SIZE; i++)
		for (int j = 0; j < FILD_SIZE; j++)
		{
			x = (i + 1) * windowGame->gameBoard.cellSize;
			y = (j + 1) * windowGame->gameBoard.cellSize;
			switch (windowGame->gameBoard.gridView[i][j])
			{
			case CellType::Blue:
				drawSprite(windowGame->gameTextureAndText.blueSprite, x, y);
				break;
			case CellType::White:
				drawSprite(windowGame->gameTextureAndText.whiteSprite, x, y);
				break;
			case CellType::Green:
				drawSprite(windowGame->gameTextureAndText.greenSprite, x, y);
				break;
			}

			if (windowGame->gameBoard.gridLogic[i][j] == nullptr)
				continue;

			//��������� ����� �� ����

			x = (i + 1) * windowGame->gameBoard.cellSize + 7;
			y = (j + 1) * windowGame->gameBoard.cellSize + 7;
			switch (windowGame->gameBoard.gridLogic[i][j]->team)
			{
			case Team::White:
				drawSprite(windowGame->gameTextureAndText.white�heckerSprite, x, y);
				break;
			case Team::Black:
				drawSprite(windowGame->gameTextureAndText.black�heckerSprite, x, y);
				break;
			}
		}
}

void ModelView::Select�heckers()
{
	int fx = windowGame->e.mouseButton.x / 70, fy = windowGame->e.mouseButton.y / 70;
	Log::Write("(" + to_string(fx) + ";" + to_string(fy) + ")");
	game->Action(Coord(fx, fy));
}