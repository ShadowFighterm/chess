#include "Rook.h"
#include"Global.h"
#include"ChessBoard.h"
#include"Position.h"
#include<iostream>
using namespace std;
Rook::Rook(Position p, int clr,char id)
	:Piece(p, clr,id)
{
}
Rook::Rook(sf::Vector2f& v, Position p, int clr,char id)
	:Piece(p,clr,id)
{
	if (id == 'r')
		t.loadFromFile("rook_black.png");
	else
		t.loadFromFile("rook_white.png");
	s.setTexture(t);
	s.setScale(0.08, 0.08);
	s.setPosition(v);
}
bool Rook::IsLegalMove(const ChessBoard &b,Position s, Position d,int turn)
{
	return IsHorizonMove(s, d) && IsPathClrHorizon(b,s, d) || IsVerticalMove(s, d) && IsPathClrVerti(b,s, d);
}
void Rook::DrawPiece(sf::RenderWindow& window)const
{
	window.draw(s);
}
void Rook::DrawPiece(int cr, int cc, int s, char sym)const
{
	int count = 0;
	for (int ln = 1; ln < s / 2; ln++)
	{
		for (int s1 = 0; s1 < ln * 2 + 1; s1++)
		{
			Global::gotoRowCol(cr + ln, cc - ln + s1);
			cout << sym;
		}
	}
	for (int ln = 0; ln < 1; ln++)
	{
		for (int s1 = 0; s1 < (ln + 1) * 2 + 1; s1++)
		{
			if (count % 2 == 0)
			{
				Global::gotoRowCol(cr + ln, cc - 1 + s1);
				cout << sym;
			}
			count++;
		}
	}
	for (int ln = 2; ln < s / 2; ln++)
	{
		for (int s1 = 0; s1 < ln * 2 + 1; s1++)
		{
			Global::gotoRowCol(cr - ln + 1, cc - ln + s1);
			cout << sym;
		}
	}
	for (int ln = 2; ln < s / 2; ln++)
	{
		count = 0;
		for (int s1 = 0; s1 < ln * 2 + 1; s1++)
		{
			if (count % 2 == 0)
			{
				Global::gotoRowCol(cr - ln, cc - ln + s1);
				cout << sym;
			}
			count++;
		}
	}
}
void Rook::SetIsFirst(bool b)
{
	return;
}
bool Rook::GetIsFirst()const
{
	return false;
}
