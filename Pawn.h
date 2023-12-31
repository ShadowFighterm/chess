#pragma once
#include"Piece.h"
#include"Position.h"
class Pawn :public Piece
{
private:
	bool IsFirstMove;
public:
	Pawn(Position p, int clr,char id);
	Pawn(sf::Vector2f& v,Position p, int clr, char id);
	bool IsLegalMove(const ChessBoard &b,Position s, Position d, int turn)override;
	void DrawPiece(int cr, int cc, int s, char sym)const override;
	void DrawPiece(sf::RenderWindow& window)const override;
	void SetIsFirst(bool b)override;
	bool GetIsFirst()const override;
};

