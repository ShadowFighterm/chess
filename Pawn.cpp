#include "Pawn.h"
#include"Global.h"
#include<iostream>
using namespace std;
Pawn::Pawn(Position p, int clr,char id)
	:Piece(p, clr,id)
{
	this->IsFirstMove = true;
}
Pawn::Pawn(sf::Vector2f& v, Position p, int clr, char id)
	:Piece(p,clr,id)
{
	if (id == 'p')
		t.loadFromFile("pawn_black.png");
	else
		t.loadFromFile("pawn_white.png");
	s.setTexture(t);
	s.setScale(0.08, 0.08);
	s.setPosition(v);
}
void Pawn::DrawPiece(sf::RenderWindow& window)const
{
	window.draw(s);
}
void Pawn::DrawPiece(int cr, int cc, int s, char sym = -37)const
{
	for (int ln = 0; ln < s / 2; ln++)
	{
		Global::gotoRowCol(cr + ln, cc - ln);
		for (int s = 0; s < ln * 2 + 1; s++)
			cout << sym;
	}
	for (int ln = 1; ln < s / 2; ln++)
	{
		for (int s1 = 0; s1 < ((s / 4) * 2) + 1; s1++)
		{
			Global::gotoRowCol(cr - ln, (cc - (s / 4)) + s1);
			cout << sym;
		}
	}
}
bool Pawn::IsLegalMove(const ChessBoard &b,Position s, Position d, int turn)
{
	int deltR = abs(s.ri - d.ri);
	int deltC = abs(s.ci - d.ci);
	if (IsFirstMove)
	{
		if (turn == Global::white)
			return IsVerticalMove(s, d) && IsPathClrVerti(b, s, d) && b.IsEmptyPlace(d) && s.ri - d.ri == 2 || IsVerticalMove(s, d) && b.IsEmptyPlace(d) && s.ri - d.ri == 1 || IsDiagonalMove(s, d) && !(b.IsEmptyPlace(d)) && s.ri - d.ri == 1 && deltR == 1 && deltC == 1;
		else
			return IsVerticalMove(s, d) && IsPathClrVerti(b, s, d) && b.IsEmptyPlace(d) && d.ri - s.ri == 2 || IsVerticalMove(s, d) && b.IsEmptyPlace(d) && d.ri - s.ri == 1 || IsDiagonalMove(s, d) && !(b.IsEmptyPlace(d)) && d.ri - s.ri == 1 && deltR == 1 && deltC == 1;
	}
	else
	{
		if (turn == Global::white)
			return IsVerticalMove(s, d) && b.IsEmptyPlace(d) && s.ri - d.ri == 1 || IsDiagonalMove(s, d) && !(b.IsEmptyPlace(d)) && s.ri - d.ri == 1 && deltR == 1 && deltC == 1;
		else
			return IsVerticalMove(s, d) && b.IsEmptyPlace(d) && d.ri - s.ri == 1 || IsDiagonalMove(s, d) && !(b.IsEmptyPlace(d)) && d.ri - s.ri == 1 && deltR == 1 && deltC == 1;
	}
}
void Pawn::SetIsFirst(bool b)
{
	this->IsFirstMove = b;
}
bool Pawn::GetIsFirst()const
{
	return IsFirstMove;
}
