#include "Knight.h"
#include<iostream>
#include"Global.h"
using namespace std;

Knight::Knight(Position p, int clr,char id)
	:Piece(p, clr,id)
{

}
Knight::Knight(sf::Vector2f& v, Position p, int clr, char id)
	:Piece(p,clr,id)
{
	if (id == 'N')
		t.loadFromFile("knight_white.png");
	else
		t.loadFromFile("knight_black.png");
	s.setTexture(t);
	s.setScale(0.08,0.08); //104.5 for each square ,35.5 for up and ,35.5 for left ,scale is 0.08
	s.setPosition(v);
}
bool Knight::IsLegalMove(const ChessBoard &b,Position s, Position d,int turn)
{
	int Chr, Chc;  
	Chr = abs(s.ri - d.ri);
	Chc = abs(s.ci - d.ci);
	return Chr == 2 && Chc == 1 || Chr == 1 && Chc == 2;
}
void Knight::DrawPiece(sf::RenderWindow& window)const
{
	window.draw(s);
}
void Knight::DrawPiece(int cr, int cc, int s, char sym)const
{
	for (int ln = 1; ln < s / 2; ln++)
	{
		for (int s1 = 0; s1 <= ln + 1; s1++)
		{
			Global::gotoRowCol(cr + ln, cc - 2 + s1);
			cout << sym;
		}
	}
	for (int ln = 0; ln < s / 2; ln++)
	{
		for (int s1 = 0; s1 < ln * 2 + 1; s1++)
		{
			if (ln != s / 2 - 1)
			{
				Global::gotoRowCol(cr - 2 + ln, cc - ln + s1);
				cout << sym;
			}
			else
			{
				if (cc - ln + s1 != cc)
				{
					Global::gotoRowCol(cr - 2 + ln, cc - ln + s1);
					cout << sym;
				}
			}
		}
	}
}
void Knight::SetIsFirst(bool b)
{
	return;
}
bool Knight::GetIsFirst()const
{
	return false;
}
