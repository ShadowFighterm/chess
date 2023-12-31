#include "Piece.h"
#include"ChessBoard.h"
#include"Global.h"
#include<iostream>
using namespace std;
Piece::Piece(Position p, int clr,char id)
{
	this->SetPosition(p);
	this->SetClr(clr);
	this->id = id;
}
int Piece::GetClr()const
{
	return this->clr;
}
char Piece::GetId()const
{
	return this->id;
}
bool Piece::IsDiagonalMove(Position s, Position d)
{
	int deltr = abs(s.ri - d.ri), deltc = abs(s.ci - d.ci);
	return deltr == deltc;
}
bool Piece::IsDiagMoveLtoR(Position s, Position d)
{
	return IsDiagonalMove(s, d) && d.ci > s.ci && d.ri > s.ri || IsDiagonalMove(s, d) && d.ci < s.ci&& d.ri < s.ri;
}
bool Piece::IsDiagMoveRtoL(Position s, Position d)
{
	return IsDiagonalMove(s, d) && d.ci < s.ci&& d.ri>s.ri || IsDiagonalMove(s, d) && d.ci > s.ci && d.ri < s.ri;
}
bool Piece::IsHorizonMove(Position s, Position d)
{
	return s.ri == d.ri;
}
bool Piece::IsVerticalMove(Position s, Position d)
{
	return s.ci == d.ci;
}
bool Piece::IsPathClrDiagRtoL(const ChessBoard &b,Position s, Position d)const
{
	int Chr = abs(s.ri - d.ri);
	if (s.ri < d.ri)
	{
		for (int i = 1;i < Chr;i++)
		{
			if (b.GetPieceAt(s.ri+i,s.ci-i) != nullptr)
				return false;
		}
		return true;
	}
	else
	{
		for (int i = 1;i < Chr;i++)
		{
			if (b.GetPieceAt(d.ri+i,d.ci-i) != nullptr)
				return false;
		}
		return true;
	}
}
bool Piece::IsPathClrDiagLtoR(const ChessBoard &b,Position s, Position d)const
{
	int Chr = abs(s.ri - d.ri);
	if (s.ri < d.ri)
	{
		for (int i = 1;i < Chr;i++)
		{
			if (b.GetPieceAt(s.ri+i,s.ci+i) != nullptr)
				return false;
		}
		return true;
	}
	else
	{
		for (int i = 1;i < Chr;i++)
		{
			if (b.GetPieceAt(d.ri+i,d.ci+i) != nullptr)
				return false;
		}
		return true;
	}
}
bool Piece::IsPathClrVerti(const ChessBoard &b,Position s, Position d)const
{
	int st, ed;
	if (s.ri < d.ri)
	{
		st = s.ri + 1;
		ed = d.ri;
	}
	else
	{
		st = d.ri + 1;
		ed = s.ri;
	}
	for (;st < ed;st++)
	{
		if (b.GetPieceAt(st,s.ci) != nullptr)
			return false;
	}
	return true;
}
bool Piece::IsPathClrHorizon(const ChessBoard &b,Position s, Position d)const
{
	int st, ed;
	if (s.ci < d.ci)
	{
		st = s.ci + 1;
		ed = d.ci;
	}
	else
	{
		st = d.ci + 1;
		ed = s.ci;
	}
	for (;st < ed;st++)
	{
		if (b.GetPieceAt(s.ri,st) != nullptr)
			return false;
	}
	return true;
}
void Piece::Move(Position d)
{
	this->SetPosition(d);
	s.setPosition(35.5 + (d.ci * 104.5), 35.5 + (d.ri * 104.5));
}
Position Piece::GetPosition()const
{
	return this->p;
}
sf::Vector2f Piece::GetVectorPosition()const
{
	return s.getPosition();
}
void Piece::SetPosition(Position p)
{
	this->p = p;
}
void Piece::SetVectorPosition(sf::Vector2f& v)
{
	this->s.setPosition(v);
}
void Piece::SetClr(int clr)
{
	this->clr = clr;
}
void Piece::SetSprite(Position p,char id)
{
	this->s.setTexture(Global::GetTexture(id));
	this->s.setScale(0.08, 0.08);
	this->s.setPosition((p.ci * 104) + 36, (p.ri * 104) + 36);
}
sf::Sprite& Piece::GetSprite()
{
	return this->s;
}
void Piece::SetTexture(sf::Texture& t)
{
	this->t = t;
}
sf::Texture& Piece::GetTexture()
{
	return this->t;
}


