#include"Queen.h"
#include"Global.h"
#include"Rook.h"
#include"Bishop.h"
#include<iostream>
using namespace std;

Queen::Queen(Position p, int clr,char id)
	:Piece(p, clr,id)
{
}
Queen::Queen(sf::Vector2f& v, Position p, int clr, char id)
	:Piece(p, clr, id)
{
	if (id == 'q')
		t.loadFromFile("queen_black.png");
	else
		t.loadFromFile("queen_white.png");
	s.setTexture(t);
	s.setScale(0.08, 0.08);
	s.setPosition(v);
}
bool Queen::IsLegalMove(const ChessBoard &b,Position s, Position d, int turn)
{
	Rook R(s, turn == Global::white ? 15 : 0,'r');
	Bishop B(s, turn == Global::white ? 15 : 0, 'b');
	return R.IsLegalMove(b, s, d, turn) || B.IsLegalMove(b, s, d, turn);
}
void Queen::DrawPiece(sf::RenderWindow& window)const
{
	window.draw(s);
}
void Queen::DrawPiece(int cr, int cc, int s, char sym)const
{
	int count = 0;
	for (int ln = 0; ln < s / 2; ln++)
	{
		for (int s1 = 0; s1 < ln * 2 + 1; s1++)
		{
			if (count != 2)
			{
				if (s1 == 0 || s1 == ln * 2 + 1 - 1)
				{
					Global::gotoRowCol(cr - 2 + ln, cc - ln + s1);
					cout << sym;
				}
			}
			else
			{
				Global::gotoRowCol(cr - 2 + ln, cc - ln + s1);
				cout << sym;
			}
		}
		count++;
	}
	count = 0;
	for (int ln = 1; ln < s / 2; ln++)
	{
		for (int s1 = 0; s1 < ln * 2 + 1; s1++)
		{
			if (count != 1)
			{
				if (s1 == 0 || s1 == ln * 2 + 1 - 1)
				{
					Global::gotoRowCol(cr + ln, cc - ln + s1);
					cout << sym;
				}
			}
			else
			{
				Global::gotoRowCol(cr + ln, cc - ln + s1);
				cout << sym;
			}
		}
		count++;
	}
}
void Queen::SetIsFirst(bool b)
{
	return;
}
bool Queen::GetIsFirst()const
{
	return false;
}