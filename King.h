#pragma once
#include"Piece.h"
class King :public Piece
{
private:
	bool IsFirstMove;
public:
	King(Position p, int clr,char id);
	King(sf::Vector2f& v, Position p, int clr, char id);
	bool IsLegalMove(const ChessBoard &b,Position s, Position d, int turn)override;
	bool CanCastle(const ChessBoard& b, Position s, Position d, int turn)const;
	bool IsPathSafe(const ChessBoard&b,Position s,Position d,int turn)const;
	void DrawPiece(int cr, int cc, int s, char sym)const override;
	void DrawPiece(sf::RenderWindow& window)const override;
	void SetIsFirst(bool b)override;
	bool GetIsFirst()const override;
};
