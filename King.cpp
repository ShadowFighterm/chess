#include "king.h"
#include"Global.h"
#include"Rook.h"
#include"Bishop.h"
#include<iostream>
using namespace std;
King::King(Position p, int clr,char id)
	:Piece(p, clr,id)
{
	this->IsFirstMove = true;
}
King::King(sf::Vector2f& v, Position p, int clr, char id)
	:Piece(p,clr,id)
{
	if (id == 'k')
		t.loadFromFile("king_black.png");
	else
		t.loadFromFile("king_white.png");
	s.setTexture(t);
	s.setScale(0.08, 0.08);
	s.setPosition(v);
	this->IsFirstMove = true;
}
bool King::IsPathSafe(const ChessBoard&b,Position s,Position d,int turn)const
{
	bool Increment;
	int pclr;
	Position soc = s;
	Position des = d;
	int dim = b.GetDim();
	if (s.ci < d.ci)
	{
		des.ri = soc.ri;
		des.ci = soc.ci + 1;
		Increment = true;
	}
	else
	{
		des.ri = soc.ri;
		des.ci = soc.ci - 1;
		Increment = false;
	}
	if (turn == Global::white)
	{
		turn = Global::black;
		pclr = 0;
	}
	else
	{
		turn = Global::white;
		pclr = 8;
	}
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0;j < dim;j++)
		{
			soc.ri = i;
			soc.ci = j;
			if (b.GetPieceAt(i, j) != nullptr && b.GetPieceAt(i, j)->GetClr() == pclr)
			{
				if (b.GetPieceAt(i, j)->IsLegalMove(b, soc, s, turn))
					return false;
				if (b.GetPieceAt(i, j)->IsLegalMove(b, soc, des, turn))
					return false;
				if (Increment && b.GetPieceAt(i, j)->IsLegalMove(b, soc, { des.ri,des.ci + 1 }, turn))
					return false;
				if (!Increment && b.GetPieceAt(i, j)->IsLegalMove(b, soc, { des.ri,des.ci - 1 }, turn))
					return false;
			}
		}
	}
	return true;
}
bool King::CanCastle(const ChessBoard&b,Position s, Position d,int turn)const
{
	int deltc = abs(s.ci - d.ci);
	int dim = b.GetDim();
	if (!b.GetPieceAt(s.ri, s.ci)->GetIsFirst() || d.ri != s.ri || deltc != 2)
		return false;
	if (turn == Global::white)
	{
		if (s.ci < d.ci)
		{
			if (b.GetPieceAt(7, 7) == nullptr || b.GetPieceAt(7, 7)->GetId() != 'R')
				return false;
		}
		else
		{
			if (b.GetPieceAt(7, 0) == nullptr || b.GetPieceAt(7, 0)->GetId() != 'R')
				return false;
		}
	}
	else
	{
		if (s.ci < d.ci)
		{
			if (b.GetPieceAt(0, 7) == nullptr || b.GetPieceAt(0, 7)->GetId() != 'r')
				return false;
		}
		else
		{
			if (b.GetPieceAt(0, 0) == nullptr || b.GetPieceAt(0, 0)->GetId() != 'r')
				return false;
		}
	}
	if (!IsPathClrHorizon(b, s, d))
		return false;
	if (!IsPathSafe(b, s, d, turn))
		return false;
	return true;
}
bool King::IsLegalMove(const ChessBoard &b,Position s, Position d, int turn)
{
	Rook R(s, turn == Global::white ? 15 : 0,'r');
	Bishop B(s, turn == Global::white ? 15 : 0,'b');
	int Chr = abs(s.ri - d.ri);
	int Chc = abs(s.ci - d.ci);
	if(!CanCastle(b,s,d,turn))
		return R.IsLegalMove(b,s,d,turn) && Chr <= 1 && Chc <= 1 || B.IsLegalMove(b,s, d,turn) && Chr <= 1 && Chc <= 1;
	else
		return R.IsLegalMove(b, s, d, turn) && Chr <= 1 && Chc <= 2 || B.IsLegalMove(b, s, d, turn) && Chr <= 1 && Chc <= 1;
}
void King::DrawPiece(sf::RenderWindow& window)const
{
	window.draw(s);
}
void King::DrawPiece(int cr, int cc, int s, char sym)const 
{
	for (int ln = 2; ln < s / 2; ln++)
	{
		int count = 0;

		for (int s1 = 0; s1 < ln * 2 + 1; s1++)
		{
			if (count % 2 == 0)
			{
				Global::gotoRowCol(cr - ln + 1, cc - ln + s1);
				cout << sym;
			}
			count++;
		}

	}
	for (int ln = 2; ln < s / 2; ln++)
	{

		for (int s1 = 0; s1 < ln * 2 + 1; s1++)
		{

			Global::gotoRowCol(cr - ln + 2, cc - ln + s1);
			cout << sym;

		}

	}
	for (int ln = 2; ln < s / 2; ln++)
	{
		int count = 0;

		for (int s1 = 0; s1 < ln * 2 + 1; s1++)
		{
			if (count % 2 == 0)
			{
				Global::gotoRowCol(cr + ln - 1, cc - ln + s1);
				cout << sym;
			}
			count++;
		}

	}
	for (int ln = 2; ln < s / 2; ln++)
	{

		for (int s1 = 0; s1 < ln * 2 + 1; s1++)
		{

			Global::gotoRowCol(cr + ln, cc - ln + s1);
			cout << sym;

		}

	}
}
void King::SetIsFirst(bool b)
{
	this->IsFirstMove = b;
}
bool King::GetIsFirst()const
{
	return IsFirstMove;
}