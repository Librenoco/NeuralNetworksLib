#pragma once
#include <vector>

enum class FigureType
{
	Pawn, Knight, Bishop, Rook, Queen, King
};

enum class Team
{
	Black, White
};

struct Coord
{
	Coord(int x, int y) : x(x), y(y) {}
	Coord operator +(const Coord& other) const { return Coord(x + other.x, y + other.y); }
	Coord operator -(const Coord& other) const { return *this + -other; }
	Coord operator -() const { return Coord(-x, -y); }
	Coord operator *(int k) const { return Coord(x * k, y * k); }
	bool operator ==(const Coord& other) const { return x == other.x && y == other.y; }
	int x, y;
};

struct Figure
{
	Figure(const Coord& coord, FigureType type, Team team) : coord(coord), type(type), team(team) {}
	bool operator ==(const Figure& other) const { return coord == other.coord && type == other.type && team == other.team; }
	Coord coord;
	FigureType type;
	Team team;
};

struct Move
{
	Move(const Coord& figureCoord, const Coord& target) : target(target), figureCoord(figureCoord) {};
	bool operator==(const Move& other) { return figureCoord == other.figureCoord && target == other.target; }
	bool operator!=(const Move& other) { return !(*this == other); }
	const Coord figureCoord;
	Coord target;
};

struct GameInfo
{
	GameInfo() : isEnd(false), winner(Team::Black), turn(Team::White), allFigures(0), blackFigures(0), whiteFigures(0), countMoves(0) {}
	bool isEnd;
	Team winner;
	Team turn;
	int allFigures, blackFigures, whiteFigures;
	int countMoves;
};


class ChessGame
{
public:
	ChessGame();

	void NewGame();

	GameInfo GetInfo() const; //�������� ������� ���������� �� ����

	const Figure* GetChosenFigure() const; //�������� ��������� ������

	std::vector<const Figure*> GetFigures() const; //��� ������ �� ����

	std::vector<Move> PossibleMoves(const Figure* figure); //��������� ������ ��� ���� ������

	void Action(const Coord& coord); //������� �� ������

	bool MakeMove(const Figure* figure, const Move& move);

protected:

	Figure* chosenFigure;

	std::vector<Figure*> figures;

	GameInfo info;

	Team turnTeam;

	std::vector<Move> history;

private:

	Figure* FigureByCoords(const Coord& coord); //�������� ������ �� �����������

	void InitializeGame();

	bool CoordsInField(const Coord& coord);

	bool CoordIsEmpty(const Coord& coord);

	bool CheckEndGame();

	void UpdateInfo();

	void ChooseFigure(const Coord& coord);

	void MakeTurn(const Move& move);

	bool IsMovePossible(const Coord& from, const Coord& to) const;
};

