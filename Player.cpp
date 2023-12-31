#include "Player.h"
Player::Player()
{
	this->Name = "none";
	this->turnNo = 3;
}
Player::Player(string n, int t)
{
	SetName(n);
	SetTurnNo(t);
}
void Player::SetName(string n)
{
	this->Name = n;
}
void Player::SetTurnNo(int tn)
{
	this->turnNo = tn;
}
string Player::GetName()const
{
	return this->Name;
}
int Player::GetTurnNo()const
{
	return this->turnNo;
}

