#include "Global.h"
#include<Windows.h>
#include<iostream>
using namespace std;
sf::Texture* Global::ts;
sf::Texture* Global::promo;
sf::Texture& Global::GetTexture(char id)
{
	switch (id)
	{
	case'p':
		return ts[1];
		break;
	case'P':
		return ts[0];
		break;
	case'r':
		return ts[3];
		break;
	case'R':
		return ts[2];
		break;
	case'b':
		return ts[5];
		break;
	case'B':
		return ts[4];
		break;
	case'n':
		return ts[7];
		break;
	case'N':
		return ts[6];
		break;
	case 'k':
		return ts[9];
		break;
	case'K':
		return ts[8];
		break;
	case'q':
		return ts[11];
		break;
	case'Q':
		return ts[10];
		break;
	}
}
sf::Texture& Global::GetPromoTexture(char id)
{
	switch (id)
	{
	case'r':
		return ts[0];
		break;
	case'R':
		return ts[4];
		break;
	case'b':
		return ts[2];
		break;
	case'B':
		return ts[6];
		break;
	case'n':
		return ts[1];
		break;
	case'N':
		return ts[5];
		break;
	case'q':
		return ts[3];
		break;
	case'Q':
		return ts[7];
		break;
	}
}
void Global::getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void Global::getRowColbyLeftClick(int& rpos, int& cpos, sf::RenderWindow& window)
{
		sf::Vector2i p = sf::Mouse::getPosition(window);
		cpos = p.x;
		rpos = p.y;
	
}
void Global::gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void Global::SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
void Global::SetRGBClr(int r, int g, int b)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int foregroundColor = 0;
	if (r > 128) foregroundColor |= FOREGROUND_RED;
	if (g > 128) foregroundColor |= FOREGROUND_GREEN;
	if (b > 128) foregroundColor |= FOREGROUND_BLUE;
	SetConsoleTextAttribute(hConsole, foregroundColor);
}
void Global::DrawBox(int sr, int sc, int clr, char sym)
{
	SetClr(clr);
	for (int i = 0; i < brows; i++)
	{
		for (int j = 0; j < bcols; j++)
		{
			gotoRowCol(sr + i, sc + j);
			cout << sym;
		}
	}
	SetClr(15);
}