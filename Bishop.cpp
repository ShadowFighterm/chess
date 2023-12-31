#include "Bishop.h"
#include"Global.h"
#include<iostream>
using namespace std;

Bishop::Bishop(Position p, int clr,char id)
	:Piece(p, clr,id)
{

}
Bishop::Bishop(sf::Vector2f& v, Position p, int clr, char id)
	:Piece(p,clr,id)
{
	if (id == 'b')
		t.loadFromFile("bishop_black.png");
	else
		t.loadFromFile("bishop_white.png");
	s.setTexture(t);
	s.setScale(0.08, 0.08);
	s.setPosition(v);
}
bool Bishop::IsLegalMove(const ChessBoard &b,Position s, Position d, int turn)
{
	return IsDiagMoveLtoR(s, d) && IsPathClrDiagLtoR(b,s, d) || IsDiagMoveRtoL(s, d) && IsPathClrDiagRtoL(b,s, d);
}
void Bishop::DrawPiece(int cr, int cc, int s, char sym)const
{
	for (int ln = 0; ln < s / 2; ln++)
	{
		Global::gotoRowCol(cr + ln, cc - ln);
		for (int s = 0; s < ln * 2 + 1; s++)
			cout << sym;
	}
	for (int ln = 0; ln < s / 2 - 1; ln++)
	{
		for (int s1 = 0; s1 < ln * 2 + 1; s1++)
		{
			Global::gotoRowCol(cr - ((s / 2 - 1) - ln), (cc - ln) + s1);
			cout << sym;
		}
	}
}
void Bishop::DrawPiece(sf::RenderWindow& window)const
{
	window.draw(s);
}
void Bishop::SetIsFirst(bool b)
{
	return;
}
bool Bishop::GetIsFirst()const
{
	return false;
}