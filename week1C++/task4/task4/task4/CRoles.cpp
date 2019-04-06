#include <iostream>
#include "CRoles.h"

using namespace std;

/////////////////////////////////
// 基类CRole
/////////////////////////////////
CRole::CRole()
{
	headIcon = "";
	HP = 100;
	ATK = 10;
	DEF = 0;
	Lv = O_LV;
	EXP = 0;
	weapon = NULL;
	jumping = false;
	BaoJi = O_BAOJI;
	skillATK = 0;
}

CRole::CRole(string hi, int a, int d)
{
	headIcon = hi;
	HP = 100;
	ATK = a;
	DEF = d;
	Lv = O_LV;
	EXP = 0;
	weapon = NULL;
	jumping = false;
	BaoJi = O_BAOJI;
	skillATK = 0;
}

CRole::~CRole()
{
	headIcon.~basic_string();
	HP = 0;
	ATK = 0;
	DEF = 0;
	Lv = 0;
	EXP = 0;
	weapon = NULL;
	jumping = 0;
	BaoJi = 0;
	skillATK = 0;
}

void CRole::jump()
{
	jumping = true;
	cout << headIcon << " starts to jump.\n";
}

void CRole::jumpEnd()
{
	jumping = false;
	cout << headIcon << " finishs jumping.\n";
}

void CRole::getWeapon(Weapon& wp)
{
	BaoJi += wp.BaoJi;
	ATK += wp.ATK;
	if (BaoJi > 100) BaoJi = 100;
	cout << headIcon << " gets a weapon named " << wp.name << ", his ATK and BaoJiLv increase!" << endl;
	coutAtkDef();
}

void CRole::atkWeapon(int seed)
{
	if (weapon != NULL) {
		ATK = ATK + weapon->ATK;
	}
	srand((unsigned int)(seed));  //获取随机数种子
	int n = rand() % 100;  //n是0-99中的随机数
	if (n < BaoJi)
	{
		skillATK = ATK;  //通过skillATK模拟暴击
		cout << headIcon << " attcks physically and it's a BaoJi!" << endl;
	}
	else {
		cout << headIcon << " attcks physically!" << endl;
	}
}

/////////////////////////////////
// 英雄
/////////////////////////////////
CHero::CHero(string hi, int a, int d) :CRole(hi, a, d)
{
}

CHero::~CHero()
{
}

int CHero::skill_kick(CEnemy &emy)
{
	if (emy.jumping)
	{
		cout << headIcon << " is kicking! But " << emy.headIcon << " jumps for 1 second." << endl;
		skillATK = 0 - ATK;
	}
	else
	{
		cout << headIcon << " is kicking " << emy.headIcon << " !" << endl;
		skillATK = 5;
	}
	return 1;
}

int CHero::skill_hug(CEnemy &emy)
{
	if (emy.jumping)
	{
		cout << headIcon << " is hugging " << emy.headIcon << " who is jumping!" << endl;
		skillATK = 25;
	}
	else
	{
		cout << headIcon << " is hugging " << emy.headIcon << " !" << endl;
		skillATK = 15;
	}
	return 5;
}

/////////////////////////////////
// 敌人
/////////////////////////////////
CEnemy::CEnemy(string hi, int a, int d) :CRole(hi, a, d)
{
}

CEnemy::~CEnemy()
{
}

int CEnemy::skill_hand(CHero &emy)
{
	if (emy.jumping)
	{
		cout << headIcon << " is handinging! But " << emy.headIcon << " jumps for 1 second." << endl;
		skillATK = 0 - ATK;
	}
	else
	{
		cout << headIcon << " is handding " << emy.headIcon << " !" << endl;
		skillATK = 5;
	}
	return 1;
}

int CEnemy::skill_kicks(CHero &emy)
{
	if (emy.jumping)
	{
		cout << headIcon << " is kicking for times to " << emy.headIcon << " who is jumping!" << endl;
		skillATK = 25;
	}
	else
	{
		cout << headIcon << " is kicking for times to " << emy.headIcon << " !" << endl;
		skillATK = 15;
	}
	return 5;
}
