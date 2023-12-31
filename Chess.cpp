#include "Chess.h"
#include"Player.h"
#include"Global.h"
#include"ChessBoard.h"
#include"Position.h"
#include"Piece.h"
#include"Pawn.h"
#include<string>
#include<iostream>
#include<stack>
using namespace std;
void Chess::Save()const
{
	int dim = b->GetDim();
	ofstream cout1("save.txt");
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0;j < dim;j++)
		{
			if (b->GetPieceAt(i, j) != nullptr)
				cout1 << b->GetPieceAt(i, j)->GetId() << " ";
			else
				cout1 << '-' << " ";
		}
		cout1 << endl;
	}
	cout1 << turn << endl;
	cout1 << (ps[0].GetTurnNo() == 0 ? ps[0].GetName() : ps[1].GetName()) << endl;
	cout1 << (ps[0].GetTurnNo() == 1 ? ps[0].GetName() : ps[1].GetName()) << endl;
}
Chess::Chess()
{
	this->wi = 0;
	this->bi = 0;
	string name;
	int nop = 2;
	this->ps = new Player[nop];
	this->b = new ChessBoard;
	this->bmap = new bool*[this->b->GetDim()]{};
	for (int i = 0;i < this->b->GetDim();i++)
	{
		this->bmap[i] = new bool[this->b->GetDim()]{};
	}
	for (int i = 0; i < nop; i++)
	{
		cout << "Enter " << i + 1 << " player's name:" << endl;
		cin >> name;
		this->ps[i].SetName(name);
	}
	srand(time(0));
	if (rand() % 2 == 0)
	{
		this->ps[0].SetTurnNo(Global::white);
		this->ps[1].SetTurnNo(Global::black);
	}
	else
	{
		this->ps[0].SetTurnNo(Global::black);
		this->ps[1].SetTurnNo(Global::white);
	}
	this->turn = Global::white;
}
Chess::Chess(sf::RenderWindow& window)
{
	char id;
	char dec;
	cout << "Press c to continue game and n for new game" << endl;
	cin >> dec;
	if (dec == 'n')
		this->b = new ChessBoard(window, "load.txt", this->turn, this->ps);
	else
		this->b = new ChessBoard(window, "save.txt", this->turn, this->ps);
	this->SourceDone = false;
	this->DestDone = false;
	this->ShowMap = false;
	this->ShowPromo = false;
	this->wi = 0;
	this->bi = 0;
	this->bmap = new bool* [this->b->GetDim()] {};
	for (int i = 0;i < this->b->GetDim();i++)
	{
		this->bmap[i] = new bool[this->b->GetDim()] {};
	}
	this->ht.loadFromFile("highlight.png");
	this->hlight.setTexture(ht);
	hlight.setScale(0.1, 0.1);
	f.loadFromFile("arial.ttf");
	GameTime.setFont(f);
	GameTime.setCharacterSize(24);
	id = (turn == Global::white ? 'N' : 'n');
	TMsg.setTexture(Global::GetTexture(id));
	TMsg.setScale(0.03, 0.03);
	TMsg.setPosition(850, 0);
}
bool Chess::InBound(Position p)const
{
	if (p.ri < 0 || p.ri >= this->b->GetDim() || p.ci < 0 || p.ci >= this->b->GetDim())
		return false;
	return true;
}
bool Chess::InBoundWindow(sf::RenderWindow& window)
{
	if (s.ri > window.getSize().x || s.ci > window.getSize().y)
		return true;
	return false;
}
bool Chess::IsRightSource()const
{
	if (b->IsEmptyPlace(this->s))
		return false;
	int pclr = this->b->GetPieceAt(s.ri, s.ci)->GetClr();
	if (pclr == 8 && this->turn == 1 || pclr == 0 && this->turn == 0)
		return false;
	else
		return true;
}
bool Chess::IsRightDest()const
{
	if (this->b->IsEmptyPlace(this->d))
		return true;
	int pclr = this->b->GetPieceAt(d.ri, d.ci)->GetClr();
	if (pclr == 8 && this->turn == 0 || pclr == 0 && this->turn == 1)
		return false;
	else
		return true;
}
bool Chess::IsCapture()
{
	return !(this->b->IsEmptyPlace(this->d));
}
void Chess::ShowCapturedPieces()
{
	if (turn == 0)
	{
		Global::DrawBox((wi < 8 ? 55 : 55 + Global::brows), (wi < 8 ?wi * 10 + 100 : (wi - 8) * 10 + 100), 6);
		Global::SetClr(this->b->GetPieceAt(d.ri, d.ci)->GetClr());
		this->b->GetPieceAt(d.ri, d.ci)->DrawPiece((wi < 8 ? 55 + 5 : 55 + Global::brows + 5), (wi < 8 ? wi * 10 + 100 + Global::brows / 2 : ((wi - 8) * 10 + 100) + Global::brows / 2), 6, -37);
	}
	else
	{ 
		Global::DrawBox((bi < 8 ? 5 : 5 + Global::brows), (bi < 8 ? bi * 10 + 100 : (bi - 8) * 10 + 100), 14);
		Global::SetClr(this->b->GetPieceAt(d.ri, d.ci)->GetClr());
		this->b->GetPieceAt(d.ri, d.ci)->DrawPiece((bi < 8 ? 5 + 5 : 5 + Global::brows + 5), (bi < 8 ? bi * 10 + 100 + Global::brows / 2 : ((bi - 8) * 10 + 100) + Global::brows / 2), 6, -37);
	}
	Global::SetClr(15);
	turn == 0 ? this->wi++ : this->bi++;
}
void Chess::Play(sf::RenderWindow& window)
{
	sf::Text tlimit(" / 30", f, 24);
	sf::Time limittimer = sf::seconds(30.0f);
	tlimit.setPosition(110, 0);
	gclock.restart();
	gtime = gclock.getElapsedTime();
	GameTime.setString(to_string(gtime.asSeconds()));
	GameTime.setFillColor(sf::Color::White);
	GameTime.setPosition(0, 0);
	TurnMsg();
	undo.push(*b);
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case evnt.Closed:
				window.close();
				break;
			case evnt.MouseButtonPressed:
				SelectPosition(window);
				break;
			case evnt.KeyPressed:
				if (evnt.key.code == sf::Keyboard::BackSpace && undo.size() > 1)
				{
					system("cls");
					TurnCh();
					gclock.restart();
					TurnMsg();
					redo.push(undo.top());
					undo.pop();
					this->b->DeleteMemory();
					this->b->Assign(undo.top());
					Save();
				}
				else if (evnt.key.code == sf::Keyboard::Enter && redo.size() > 0)
				{
					system("cls");
					TurnCh();
					gclock.restart();
					TurnMsg();
					undo.push(redo.top());
					this->b->DeleteMemory();
					this->b->Assign(redo.top());
					Save();
					redo.pop();
				}
				break;
			}
		}
		if (gtime >= limittimer)
		{
			system("cls");
			TurnCh();
			ShowMap = false;
			ShowPromo = false;
			TurnMsg();
			gclock.restart();
		}
		window.clear();
		this->b->DrawBoard(window);
		this->b->DrawPieces(window);
		TurnMsg(window);
		gtime = gclock.getElapsedTime();
		GameTime.setString(to_string(gtime.asSeconds()));
		window.draw(GameTime);
		window.draw(tlimit);
		if (ShowMap)
			ShowSteps(window);
		if (ShowPromo)
			ShowPromoPieces(window);
		window.display();
	}
}
bool Chess::IsPromo()const
{
	if (turn == Global::white)
		return d.ri == 0 && b->GetPieceAt(d.ri, d.ci)->GetId() == 'P';
	else
		return d.ri == 7 && b->GetPieceAt(d.ri, d.ci)->GetId() == 'p';
}
void Chess::ShowPromoPieces(sf::RenderWindow&window)const
{
	sf::Sprite p;
	if (turn == Global::white)
	{
		for (int i = 0;i < 4;i++)
		{
			p.setTexture(Global::promo[4 + i]);
			p.setPosition((s.ci * 104) + 36, (i * 104) + 36);
			p.setScale(0.08, 0.08);
			window.draw(p);
		}
	}
	else
	{
		for (int i = 0;i < 4;i++)
		{
			p.setTexture(Global::promo[0 + i]);
			p.setPosition((s.ci * 104) + 36, ((7 - i) * 104) + 36);
			p.setScale(0.08, 0.08);
			window.draw(p);
		}
	}
}
void Chess::Play()
{
	this->b->DrawBoard();
	this->b->DrawPieces();
	while (true)
	{
		TurnMsg();
		SelectPosition();
		if (IsCapture())
			ShowCapturedPieces();
		this->b->UpdateBoard(this->s, this->d);
		RemoveTrail(s, d);
		this->b->DrawPieces();
		if (!IsDefend())
		{
			if (IsCheckmate())
			{
				TurnCh();
				Global::gotoRowCol(Global::brows * (this->b->GetDim()), 0);
				cout << (this->ps[0].GetTurnNo() == this->turn ? this->ps[0].GetName() : this->ps[1].GetName()) << "'s win!" << endl;
				exit(1);
			}
			if (IsStalemate())
			{
				TurnCh();
				Global::gotoRowCol(Global::brows * (this->b->GetDim()), 0);
				cout << "It's a draw!(Stalemate)" << endl;
				exit(1);
			}
		}
		TurnCh();

	}
}
void Chess::TurnCh()
{
	if (this->turn == Global::white)
	{
		turn = Global::black;
		TMsg.setTexture(Global::GetTexture('n'));
	}
	else
	{
		turn = Global::white;
		TMsg.setTexture(Global::GetTexture('N'));
	}
}
void Chess::TurnMsg(sf::RenderWindow& window)
{
	window.draw(TMsg);
}
void Chess::TurnMsg()const
{
	cout << (this->ps[0].GetTurnNo() == this->turn?this->ps[0].GetName():this->ps[1].GetName()) << "'s turn" << (this->turn == 0 ? "(White)" : "(Black)");
}
char Chess::GetPieceToBePromo(Position p,Position s)const
{
	if (p.ci != s.ci)
		return '0';
	if (turn == Global::white)
	{
		if (p.ri < 0 || p.ri>3)
			return '0';
		switch (p.ri)
		{
		case 0:
			return 'R';
		case 1:
			return 'N';
		case 2:
			return 'B';
		case 3:
			return 'Q';
		}
	}
	else
	{
		if (p.ri > 7 || p.ri < 4)
			return '0';
		switch (p.ri)
		{
		case 7:
			return 'r';
		case 6:
			return 'n';
		case 5:
			return 'b';
		case 4:
			return 'q';
		}
	}
}
void Chess::SelectPosition(sf::RenderWindow& window)
{
	ChessBoard c(*b);
	char id;
	Position soc = s;
	Position des = d;
	Position p;
	Global::getRowColbyLeftClick(p.ri, p.ci, window);
	p.ri -= 36;
	p.ci -= 36;
	p.ri /= 104;
	p.ci /= 104;
	s = p;
	d = p;
	if (ShowPromo)
	{
		id = GetPieceToBePromo(p,soc);
		if (id != '0')
		{
			system("cls");
			b->PromotePiece(soc, id);
			b->UpdateBoard(soc, des);
			TurnCh();
			gclock.restart();
			TurnMsg();
			Save();
			undo.push(*b);
			while (!redo.empty())
				redo.pop();
			this->SourceDone = false;
			this->DestDone = false;
			this->ShowPromo = false;
		}
	}
	else if (InBound(p) && IsRightSource() && !SourceDone && !ShowPromo)
	{
		this->SourceDone = true;
		this->s = p;
		soc = p;
		d = des;
		BoolMap();
		this->ShowMap = true;
	}
	else if (InBound(p) && IsRightDest() && SourceDone && !DestDone && bmap[p.ri][p.ci] && !ShowPromo)
	{
		this->DestDone = true;
		this->d = p;
		des = p;
		this->ShowMap = false;
	}
	else
	{
		this->SourceDone = false;
		this->DestDone = false;
		this->ShowMap = false;
	}
	s = soc;
	d = des;
	if (SourceDone && DestDone)
	{
		b->UpdateBoard(s, d);
		if (IsCheck())
		{
			b->DeleteMemory();
			b->Assign(c);
		}
		else if (!IsPromo())
		{
			char c = b->GetPieceAt(d.ri, d.ci)->GetId();
			system("cls");
			if (c == 'p' || c == 'P' || c == 'k' || c == 'K')
				this->b->GetPieceAt(d.ri, d.ci)->SetIsFirst(false);
			if (!IsDefend())
			{
				if (IsCheckmate())
				{
					cout << (this->ps[0].GetTurnNo() == this->turn ? this->ps[0].GetName() : this->ps[1].GetName()) << "'s win!" << endl;
					window.close();
					return;
				}
				if (IsStalemate())
				{
					cout << "It's a draw!(Stalemate)" << endl;
					window.close();
					return;
				}
			}
			TurnCh();
			gclock.restart();
			TurnMsg();
			Save();
			undo.push(*b);
			while (!redo.empty())
				redo.pop();
		}
		else
		{
			b->DeleteMemory();
			b->Assign(c);
			ShowPromo = true;
		}
		this->SourceDone = false;
		this->DestDone = false;
	}
}
void Chess::SelectPosition()
{	
	ChessBoard c(*b);
	int count = 0;
	do
	{
		if (count != 0)
		{
			this->b->DeleteMemory();
			b->Assign(c);
		}
		do
		{
			do
			{
				Global::getRowColbyLeftClick(this->s.ri, this->s.ci);
				this->s.ri /= Global::brows;
				this->s.ci /= Global::bcols;
			} while (!InBound(this->s) || !IsRightSource());
			BoolMap();
			ShowSteps();
			Global::getRowColbyLeftClick(this->d.ri, this->d.ci);
			HideSteps();
			this->d.ri /= Global::brows;
			this->d.ci /= Global::bcols;
		} while (!InBound(this->d) || !bmap[d.ri][d.ci]);
		this->b->UpdateBoard(s, d);
		count++;
	} while (IsCheck());
	this->b->DeleteMemory();
	b->Assign(c);
	char id = this->b->GetPieceAt(s.ri,s.ci)->GetId();
	if (id == 'p' || id == 'P')
		this->b->GetPieceAt(s.ri, s.ci)->SetIsFirst(false);
}
void Chess::RemoveTrail(Position s, Position d)const
{
	int rd = (d.ri * Global::brows) + 5;
	int cd = (d.ci * Global::bcols) + 5;
	int rs = (s.ri * Global::brows) + 5;
	int cs = (s.ci * Global::bcols) + 5;
	rs = (rs / Global::brows) * Global::brows;
	cs = (cs / Global::bcols) * Global::bcols;
	rd = (rd / Global::brows) * Global::brows;
	cd = (cd / Global::bcols) * Global::bcols;
	if ((s.ri + s.ci) % 2 == 0)
		Global::DrawBox(rs, cs, 14);
	else
		Global::DrawBox(rs, cs, 6);
	if ((d.ri + d.ci) % 2 == 0)
		Global::DrawBox(rd, cd, 14);
	else
		Global::DrawBox(rd, cd, 6);

}
void Chess::BoolMap()
{
	Position des = d;
	int dim = this->b->GetDim();
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0;j < dim;j++)
			this->bmap[i][j] = false;
	}
	for (int i = 0;i < dim;i++)
	{
		d.ri = i;
		for (int j = 0;j < dim;j++)
		{
			d.ci = j;
			if (IsRightDest() && this->b->GetPieceAt(s.ri, s.ci)->IsLegalMove(*b, s, d, turn))
				this->bmap[i][j] = true;
		}
	}
	d = des;
}
void Chess::ShowSteps()const
{
	int dim = this->b->GetDim();
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0;j < dim;j++)
		{
			if (bmap[i][j])
				this->b->Highlight(i, j, 11);
		}
	}
}
void Chess::ShowSteps(sf::RenderWindow& window)
{
	int dim = b->GetDim();
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0;j < dim;j++)
		{
			if (bmap[i][j])
			{
				this->hlight.setPosition((j * 104) + 60, (i * 104) + 65);
				window.draw(hlight);
			}
		}
	}
}
void Chess::HideSteps()const
{
	int dim = this->b->GetDim();
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0;j < dim;j++)
		{
			if (bmap[i][j])
				this->b->Unhighlight(i, j);
		}
	}
}
bool Chess::IsCheck()
{
	int dim = this->b->GetDim();
	Position des = d;
	d = FindKing();
	TurnCh();
	Position soc = s;
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0;j < dim;j++)
		{
			s.ri = i;
			s.ci = j;
			if (IsRightSource() && this->b->GetPieceAt(s.ri, s.ci)->IsLegalMove(*b, s, d, turn))
			{
				d = des;
				s = soc;
				TurnCh();
				return true;
			}
		}
	}
	d = des;
	s = soc;
	TurnCh();
	return false;
}
Position Chess::FindKing()
{
	int dim = this->b->GetDim();
	Position soc = s;
	Position des;
	char king;
	if (turn == Global::white)
		king = 'K';
	else
		king = 'k';
	for (int i = 0;i < dim;i++)
	{
		s.ri = i;
		for (int j = 0;j < dim;j++)
		{
			s.ci = j;
			if (IsRightSource())
			{
				if (this->b->GetPieceAt(i, j)->GetId() == king)
				{
					s = soc;
					des.ri = i;
					des.ci = j;
					return des;
				}
			}
		}
	}
}
bool Chess::IsDefend()
{
	ChessBoard c(*b);
	char king;
	int dim = this->b->GetDim();
	TurnCh();
	Position des = d;
	Position soc = s;
	if (turn == Global::white)
		king = 'K';
	else
		king = 'k';
	for (int i = 0;i < dim;i++)
	{
		s.ri = i;
		for (int j = 0;j < dim;j++)
		{
			s.ci = j;
			if (IsRightSource() && this->b->GetPieceAt(s.ri,s.ci)->GetId() != king)
			{
				for (int i1 = 0;i1 < dim;i1++)
				{
					d.ri = i1;
					for (int j1 = 0;j1 < dim;j1++)
					{
						d.ci = j1;
						if (IsRightDest() && this->b->GetPieceAt(s.ri,s.ci)->IsLegalMove(*b,s,d,turn))
						{
							this->b->UpdateBoard(s, d);
							if (!IsCheck())
							{
								this->b->DeleteMemory();
								b->Assign(c);
								s = soc;
								d = des;
								TurnCh();
								return true;
							}
							this->b->DeleteMemory();
							b->Assign(c);
						}

					}
				}
			}
		}
	}
	this->b->DeleteMemory();
	b->Assign(c);
	s = soc;
	d = des;
	TurnCh();
	return false;
}
bool Chess::IsCheckmate()
{
	ChessBoard c(*b);
	int dim = this->b->GetDim();
	int count = 0;
	TurnCh();
	Position soc = s;
	s = FindKing();
	Position des = d;
	if (IsCheck())
		count++;
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0;j < dim;j++)
		{
			d.ri = i;
			d.ci = j;
			if (this->b->GetPieceAt(s.ri,s.ci)->IsLegalMove(*b,s,d,turn) && IsRightDest())
			{
				this->b->UpdateBoard(s, d);
				if (!IsCheck())
				{
					this->b->DeleteMemory();
					b->Assign(c);
					s = soc;
					d = des;
					TurnCh();
					return false;
				}
				this->b->DeleteMemory();
				b->Assign(c);
			}


		}
	}
	count++;
	this->b->DeleteMemory();
	b->Assign(c);
	TurnCh();
	s = soc;
	d = des;
	if (count == 2)
		return true;
	else
		return false;
}
bool Chess::IsStalemate()
{
	ChessBoard c(*b);
	int dim = this->b->GetDim();
	TurnCh();
	Position soc = s;
	s = FindKing();
	Position des = d;
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0;j < dim;j++)
		{
			d.ri = i;
			d.ci = j;
			if (this->b->GetPieceAt(s.ri,s.ci)->IsLegalMove(*b,s,d,turn) && IsRightDest())
			{
				this->b->UpdateBoard(s, d);
				if (!IsCheck())
				{
					this->b->DeleteMemory();
					b->Assign(c);
					s = soc;
					d = des;
					TurnCh();
					return false;
				}
				this->b->DeleteMemory();
				b->Assign(c);
			}


		}
	}
	this->b->DeleteMemory();
	b->Assign(c);
	s = soc;
	d = des;
	TurnCh();
	return true;
}
Chess::~Chess()
{
	delete[]this->ps;
	delete[]this->b;
}
