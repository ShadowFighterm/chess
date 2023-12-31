#include"Chess.h"
#include"Global.h"
#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 900), "Chess", sf::Style::Close | sf::Style::Titlebar);
	Chess c(window);
	c.Play(window);
}