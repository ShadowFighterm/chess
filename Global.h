#pragma once
#include<SFML/Graphics.hpp>
class Global
{
public:
	static sf::Texture* ts;
	static sf::Texture* promo;
	static sf::Texture& GetTexture(char id);
	static sf::Texture& GetPromoTexture(char id);
	static enum turn { white, black };
	static const int brows = 10, bcols = 10;
	static void getRowColbyLeftClick(int& rpos, int& cpos);
	static void getRowColbyLeftClick(int& rpos, int& cpos, sf::RenderWindow& window);
	static void gotoRowCol(int rpos, int cpos);
	static void SetClr(int clr);
	static void DrawBox(int sr, int sc, int clr, char sym = -37);
	static void SetRGBClr(int r, int g, int b);
};

