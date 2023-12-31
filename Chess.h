#pragma once
#include"Position.h";
#include"ChessBoard.h"
#include"Global.h"
#include<SFML/Graphics.hpp>
#include<stack>
#include<fstream>
using namespace std;
class Player;
class ChessBoard;
class Position;
class Chess
{
private:
	sf::Sprite hlight;
	sf::Sprite TMsg;
	sf::Texture ht;
	sf::Clock gclock;
	sf::Time gtime;
	sf::Font f;
	sf::Text GameTime;
	int turn, wi, bi;
	stack<ChessBoard> undo;
	stack<ChessBoard> redo;
	Position s;
	Position d;
	Player* ps;
	ChessBoard* b;
	bool** bmap;
	bool SourceDone;
	bool DestDone;
	bool ShowMap;
	bool ShowPromo;
	char GetPieceToBePromo(Position p,Position s)const;
	void BoolMap();
	void ShowSteps(sf::RenderWindow& window);
	void ShowSteps()const;
	void ShowPromoPieces(sf::RenderWindow&window)const;
	void HideSteps()const;
	bool InBound(Position p)const;
	bool InBoundWindow(sf::RenderWindow& window);
	bool IsRightSource()const;
	bool IsRightDest()const;
	bool IsCapture();
	bool IsPromo()const;
	void ShowCapturedPieces();
	void TurnMsg()const;
	void TurnMsg(sf::RenderWindow& window);
	void TurnCh();
	void SelectPosition();
	void SelectPosition(sf::RenderWindow& window);
	void RemoveTrail(Position s, Position d)const;
	Position FindKing();
	bool IsCheck();
	bool IsDefend();
	bool IsCheckmate();
	bool IsStalemate();
	void Save()const;
public:
	Chess();
	Chess(sf::RenderWindow& window);
	void Play();
	void Play(sf::RenderWindow& window);
	~Chess();
};


