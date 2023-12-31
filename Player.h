#pragma once
#include<string>
using namespace std;
class Player
{
private:
	string Name;
	int turnNo;
public:
	Player();
	Player(string n, int t);
	void SetName(string n);
	void SetTurnNo(int tn);
	string GetName()const;
	int GetTurnNo()const;
};

