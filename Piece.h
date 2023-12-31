#pragma once
#include"Position.h"
#include"ChessBoard.h"
#include<SFML/Graphics.hpp>
class Piece
{
protected:
	sf::Sprite s;
	sf::Texture t;
	Position p;
	int clr;
	char id;
	static bool IsDiagonalMove(Position s, Position d);
	static bool IsHorizonMove(Position s, Position d);
	static bool IsVerticalMove(Position s, Position d);
	static bool IsDiagMoveLtoR(Position s, Position d);
	static bool IsDiagMoveRtoL(Position s, Position d);
	bool IsPathClrDiagRtoL(const ChessBoard &b,Position s, Position d)const;
	bool IsPathClrDiagLtoR(const ChessBoard &b,Position s, Position d)const;
	bool IsPathClrVerti(const ChessBoard &b,Position s, Position d)const;
	bool IsPathClrHorizon(const ChessBoard &b,Position s, Position d)const;
public:
	virtual void SetIsFirst(bool b) = 0;
	virtual bool GetIsFirst()const = 0;
	Piece(Position p, int clr,char id);
	void Move(Position d);
	virtual bool IsLegalMove(const ChessBoard &b,Position s, Position d,int turn) = 0;
	virtual void DrawPiece(int cr, int cc, int s, char sym)const = 0;
	virtual void DrawPiece(sf::RenderWindow& window)const = 0;
	int GetClr()const;
	Position GetPosition()const;
	sf::Vector2f GetVectorPosition()const;
	char GetId()const;
	sf::Texture& GetTexture();
	void SetVectorPosition(sf::Vector2f& v);
	void SetTexture(sf::Texture& t);
	void SetSprite(Position p,char id);
	sf::Sprite& GetSprite();
	void SetPosition(Position p);
	void SetClr(int clr);
};


