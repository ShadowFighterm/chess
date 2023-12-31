#pragma once
#include"Position.h"
#include"Player.h"
#include<SFML/graphics.hpp>
class Piece;
class Global;
class ChessBoard
{
private:
	sf::Sprite board;
	sf::Texture btext;
	int dim;
	Piece*** pc;
	bool IsLower(char a);
public:
	ChessBoard();
	ChessBoard(sf::RenderWindow& window,const char* fname,int &turn,Player*&ps);
	ChessBoard(const ChessBoard& c);
	void Assign(const ChessBoard& c);
	void DeleteMemory();
	bool IsEmptyPlace(Position p)const;
	void DrawBoard()const;
	void PromotePiece(Position s,char id);
	void DrawBoard(sf::RenderWindow& window);
	void DrawPieces()const;
	void DrawPieces(sf::RenderWindow& window);
	void Highlight(int r, int c, int clr)const;
	void Unhighlight(int r, int c)const;
	void UpdateBoard(Position s, Position d);
	void SetDim(int d);
	int GetDim()const;
	void SetSprite(sf::Sprite& s);
	sf::Sprite& GetSprite();
	Piece* GetPieceAt(int ri,int ci)const;
	~ChessBoard();
};
