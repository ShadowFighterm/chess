#include<iostream>
#include "ChessBoard.h"
#include"Piece.h"
#include"Pawn.h"
#include"king.h"
#include"Knight.h"
#include"Queen.h"
#include"Bishop.h"
#include"Rook.h"
#include"Position.h"
#include"Player.h"
#include"Global.h"
#include<fstream>
using namespace std;
bool ChessBoard::IsLower(char a)
{
	return a >= 97 && a <= 122;
}
ChessBoard::ChessBoard()
{
	ifstream cin1("load.txt");
	SetDim(8);
	Position p;
	char input;
	int clr;
	this->pc = new Piece * *[this->dim];
	for (int i = 0; i < this->dim; i++)
	{
		this->pc[i] = new Piece * [this->dim];
		for (int j = 0; j < this->dim; j++)
		{
			p.ri = i;
			p.ci = j;
			cin1 >> input;
			if (IsLower(input))
				clr = 0;
			else
				clr = 8;
			switch (input)
			{
			case'r':
			case'R':
				this->pc[i][j] = new Rook(p, clr,input);
				break;
			case'n':
			case'N':
				this->pc[i][j] = new Knight(p, clr, input);
				break;
			case'b':
			case'B':
				this->pc[i][j] = new Bishop(p, clr,input);
				break;
			case'q':
			case'Q':
				this->pc[i][j] = new Queen(p, clr,input);
				break;
			case'k':
			case'K':
				this->pc[i][j] = new King(p, clr,input);
				break;
			case'p':
			case'P':
				this->pc[i][j] = new Pawn(p, clr,input);
				break;
			default:
				this->pc[i][j] = nullptr;
				break;

			}
		}
	}
}
ChessBoard::ChessBoard(sf::RenderWindow& window,const char* fname,int &turn,Player*&ps)
{
	int nop = 2;
	string name;
	this->btext.loadFromFile("chess_board.jpeg");
	board.setTexture(this->btext);
	float x = (float)window.getSize().x / btext.getSize().x, y = (float)window.getSize().y / btext.getSize().y;
	board.setScale(x, y);
	SetSprite(board);
	ifstream cin1(fname);
	SetDim(8);
	Position p;
	char input;
	int clr;
	sf::Vector2f v;
	// boarder 35.5,box 104.5,scale 0.08
	this->pc = new Piece * *[this->dim];
	for (int i = 0; i < this->dim; i++)
	{
		this->pc[i] = new Piece * [this->dim];
		for (int j = 0; j < this->dim; j++)
		{
			v.y = 35.5 + (i * 104.5);
			v.x = 35.5 + (j * 104.5);
			p.ri = i;
			p.ci = j;
			cin1 >> input;
			if (IsLower(input))
				clr = 0;
			else
				clr = 8;
			switch (input)
			{
			case'r':
			case'R':
				this->pc[i][j] = new Rook(v,p, clr, input);
				break;
			case'n':
			case'N':
				this->pc[i][j] = new Knight(v, p, clr, input);
				break;
			case'b':
			case'B':
				this->pc[i][j] = new Bishop(v,p, clr, input);
				break;
			case'q':
			case'Q':
				this->pc[i][j] = new Queen(v,p, clr, input);
				break;
			case'k':
			case'K':
				this->pc[i][j] = new King(v,p, clr, input);
				break;
			case'p':
			case'P':
				this->pc[i][j] = new Pawn(v,p, clr, input);
				break;
			default:
				this->pc[i][j] = nullptr;
				break;

			}
		}
	}
	ps = new Player[nop];
	if (fname == "load.txt")
	{
		turn = Global::white;
		for (int i = 0; i < nop; i++)
		{
			cout << "Enter " << i + 1 << " player's name:" << endl;
			cin >> name;
			ps[i].SetName(name);
		}
		srand(time(0));
		if (rand() % 2 == 0)
		{
			ps[0].SetTurnNo(Global::white);
			ps[1].SetTurnNo(Global::black);
		}
		else
		{
			ps[0].SetTurnNo(Global::black);
			ps[1].SetTurnNo(Global::white);
		}
	}
	else
	{
		cin1 >> turn;
		cin1 >> name;
		ps[0].SetName(name);
		ps[0].SetTurnNo(Global::white);
		cin1 >> name;
		ps[1].SetName(name);
		ps[1].SetTurnNo(Global::black);
	}

	int size = 12;
	Global::ts = new sf::Texture[size];
	for (int i = 0;i < size;i++)
	{
		switch (i)
		{
		case 0:
			Global::ts[i].loadFromFile("pawn_white.png");
			break;
		case 1:
			Global::ts[i].loadFromFile("pawn_black.png");
			break;
		case 2:
			Global::ts[i].loadFromFile("rook_white.png");
			break;
		case 3:
			Global::ts[i].loadFromFile("rook_black.png");
			break;
		case 4:
			Global::ts[i].loadFromFile("bishop_white.png");
			break;
		case 5:
			Global::ts[i].loadFromFile("bishop_black.png");
			break;
		case 6:
			Global::ts[i].loadFromFile("knight_white.png");
			break;
		case 7:
			Global::ts[i].loadFromFile("knight_black.png");
			break;
		case 8:
			Global::ts[i].loadFromFile("king_white.png");
			break;
		case 9:
			Global::ts[i].loadFromFile("king_black.png");
			break;
		case 10:
			Global::ts[i].loadFromFile("queen_white.png");
			break;
		case 11:
			Global::ts[i].loadFromFile("queen_black.png");
			break;
		}
	}
	size = 8;
	Global::promo = new sf::Texture[size];
	for (int i = 0;i < size;i++)
	{
		switch (i)
		{
		case 0:
			Global::promo[i].loadFromFile("rook_black_promo.jpeg");
			break;
		case 1:
			Global::promo[i].loadFromFile("knight_black_promo.jpeg");
			break;
		case 2:
			Global::promo[i].loadFromFile("bishop_black_promo.jpeg");
			break;
		case 3:
			Global::promo[i].loadFromFile("queen_black_promo.jpeg");
			break;
		case 4:
			Global::promo[i].loadFromFile("rook_white_promo.jpeg");
			break;
		case 5:
			Global::promo[i].loadFromFile("knight_white_promo.jpeg");
			break;
		case 6:
			Global::promo[i].loadFromFile("bishop_white_promo.jpeg");
			break;
		case 7:
			Global::promo[i].loadFromFile("queen_white_promo.jpeg");
			break;
		}
	}
	system("cls");
}
void ChessBoard::PromotePiece(Position s,char id)
{
	sf::Vector2f v;
	delete pc[s.ri][s.ci];
	v.x = s.ci;
	v.y = s.ri;
	switch (id)
	{
	case'n':
		this->pc[s.ri][s.ci] = new Knight(v, s, 0, id);
		break;
	case'N':
		this->pc[s.ri][s.ci] = new Knight(v, s, 8, id);
		break;
	case'r':
		this->pc[s.ri][s.ci] = new Rook(v, s, 0, id);
		break;
	case'R':
		this->pc[s.ri][s.ci] = new Rook(v, s, 8, id);
		break;
	case'b':
		this->pc[s.ri][s.ci] = new Bishop(v, s, 0, id);
		break;
	case'B':
		this->pc[s.ri][s.ci] = new Bishop(v, s, 8, id);
		break;
	case'q':
		this->pc[s.ri][s.ci] = new Queen(v, s, 0, id);
		break;
	case'Q':
		this->pc[s.ri][s.ci] = new Queen(v, s, 8, id);
		break;
	}
}
ChessBoard::ChessBoard(const ChessBoard& c)
{
	this->Assign(c);
}
void ChessBoard::Assign(const ChessBoard& c)
{
	bool b;
	char id;
	Position p;
	sf::Vector2f v;
	int clr;
	this->dim = c.GetDim();
	this->pc = new Piece * *[this->dim];
	for (int i = 0;i < this->dim;i++)
	{
		this->pc[i] = new Piece * [this->dim];
		for (int j = 0;j < this->dim;j++)
		{
			if (c.GetPieceAt(i, j) != nullptr)
			{
				id = c.GetPieceAt(i, j)->GetId();
				clr = c.GetPieceAt(i, j)->GetClr();
				v = c.GetPieceAt(i, j)->GetVectorPosition();
				p = c.GetPieceAt(i, j)->GetPosition();
				switch (id)
				{
				case'p':
				case'P':
					this->pc[i][j] = new Pawn(p, clr, id);
					b = c.GetPieceAt(i, j)->GetIsFirst();
					this->pc[i][j]->SetIsFirst(b);
					break;
				case'r':
				case'R':
					this->pc[i][j] = new Rook(p, clr, id);
					break;
				case'b':
				case'B':
					this->pc[i][j] = new Bishop(p, clr, id);
					break;
				case'k':
				case'K':
					this->pc[i][j] = new King(p, clr, id);
					b = c.GetPieceAt(i, j)->GetIsFirst();
					this->pc[i][j]->SetIsFirst(b);
					break;
				case'n':
				case'N':
					this->pc[i][j] = new Knight(p, clr, id);
					break;
				case'q':
				case'Q':
					this->pc[i][j] = new Queen(p, clr, id);
					break;
				}
				this->pc[i][j]->SetSprite({i,j}, id);
			}
			else
				this->pc[i][j] = nullptr;

		}
	}
	/*sf::Vector2f v;
	this->dim = c.GetDim();
	this->pc = new Piece * *[this->dim];
	for (int i = 0;i < this->dim;i++)
	{ 
		this->pc[i] = new Piece * [this->dim];
		for (int j = 0;j < this->dim;j++)
		{
			v.y = 35.5 + (i * 104.5);
			v.x = 35.5 + (j * 104.5);
			this->pc[i][j] = c.GetPieceAt(i, j);
			if (this->GetPieceAt(i, j) != nullptr)
			{
				char id = this->GetPieceAt(i, j)->GetId();
				if (id == 'p' && i == 1 || id == 'P' && i == 6)
					c.GetPieceAt(i, j)->SetIsFirst(true);
				this->GetPieceAt(i, j)->SetVectorPosition(v);
			}
		}
	}*/
}
void ChessBoard::DrawPieces(sf::RenderWindow& window)
{
	for (int i = 0;i < this->dim;i++)
	{
		for (int j = 0;j < this->dim;j++)
		{
			if(this->pc[i][j] != nullptr)
				this->pc[i][j]->DrawPiece(window);
		}
	}
}
void ChessBoard::DrawPieces()const
{
	for (int i = 0; i < this->dim; i++)
	{
		for (int j = 0; j < this->dim; j++)
		{
			if (this->pc[i][j] != nullptr)
			{
				Global::SetClr(pc[i][j]->GetClr());
				pc[i][j]->DrawPiece(Global::brows / 2 + (Global::brows * i), Global::bcols / 2 + (Global::brows * j), 6, -37);
			}
		}
	}
	Global::SetClr(15);
}
void ChessBoard::UpdateBoard(Position s, Position d)
{
	if (pc[s.ri][s.ci]->GetId() == 'k' && d.ci-s.ci==2)
	{
		this->pc[0][7]->Move({ d.ri,d.ci - 1 });
		this->pc[d.ri][d.ci - 1] = this->pc[0][7];
		this->pc[0][7] = nullptr;
	}
	else if (pc[s.ri][s.ci]->GetId() == 'k' && s.ci - d.ci == 2)
	{
		this->pc[0][0]->Move({ d.ri,d.ci + 1 });
		this->pc[d.ri][d.ci + 1] = this->pc[0][0];
		this->pc[0][0] = nullptr;
	}
	else if (pc[s.ri][s.ci]->GetId() == 'K' && d.ci - s.ci == 2)
	{
		this->pc[7][7]->Move({ d.ri,d.ci - 1 });
		this->pc[d.ri][d.ci - 1] = this->pc[7][7];
		this->pc[7][7] = nullptr;
	}
	else if (pc[s.ri][s.ci]->GetId() == 'K' && s.ci - d.ci == 2)
	{
		this->pc[7][0]->Move({ d.ri,d.ci + 1 });
		this->pc[d.ri][d.ci + 1] = this->pc[7][0];
		this->pc[7][0] = nullptr;
	}

	this->pc[s.ri][s.ci]->Move(d);
	this->pc[d.ri][d.ci] = this->pc[s.ri][s.ci];
	this->pc[s.ri][s.ci] = nullptr;
}
void ChessBoard::SetDim(int d)
{
	this->dim = d;
}
Piece* ChessBoard::GetPieceAt(int ri,int ci)const
{
	return this->pc[ri][ci];
}
void ChessBoard::DrawBoard()const
{
	for (int i = 0; i < this->dim; i++)
	{
		for (int j = 0; j < this->dim; j++)
		{
			if ((i + j) % 2 == 0)
				Global::DrawBox(i * Global::brows, j * Global::bcols, 14);
			else
				Global::DrawBox(i * Global::brows, j * Global::bcols, 6);
		}

	}
}
void ChessBoard::DrawBoard(sf::RenderWindow& window)
{
	window.draw(this->board);
}
void ChessBoard::Highlight(int r, int c, int clr)const
{
	r = (r * Global::brows) + (Global::brows / 2);
	c = (c * Global::bcols) + (Global::bcols / 2);
	r = (r / Global::brows) * Global::brows;
	c = (c / Global::bcols) * Global::bcols;
	Global::SetClr(clr);
	for (int j = c; j < c + Global::brows; j++)
	{
		Global::gotoRowCol(r, j);
		cout << char(-37);
	}
	for (int j = (c + Global::bcols) - 1, i = r; i < r + Global::brows; i++)
	{
		Global::gotoRowCol(i, j);
		cout << char(-37);
	}
	for (int i = (r + Global::brows) - 1, j = (c + Global::bcols) - 1; j >= c; j--)
	{
		Global::gotoRowCol(i, j);
		cout << char(-37);
	}
	for (int i = (r + Global::brows) - 1; i >= r; i--)
	{
		Global::gotoRowCol(i, c);
		cout << char(-37);
	}
	Global::SetClr(15);
}
void ChessBoard::Unhighlight(int r, int c)const
{
	if ((r + c) % 2 == 0)
		Highlight(r, c, 14);
	else
		Highlight(r, c, 6);
}
int ChessBoard::GetDim()const
{
	return this->dim;
}
bool ChessBoard::IsEmptyPlace(Position p)const
{
	return this->pc[p.ri][p.ci] == nullptr;
}
void ChessBoard::SetSprite(sf::Sprite& s)
{
	this->board = s;
}
sf::Sprite& ChessBoard::GetSprite()
{
	return this->board;
}
void ChessBoard::DeleteMemory()
{
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0;j < dim;j++)
		{
			delete this->pc[i][j];
		}
		delete[]this->pc[i];
	}
	delete[]this->pc;
	/*for (int i = 0;i < this->dim;i++)
	{
		delete[]this->pc[i];
	}
	delete[]this->pc;
	this->pc = nullptr;*/
}
ChessBoard::~ChessBoard()
{
	this->DeleteMemory();
}