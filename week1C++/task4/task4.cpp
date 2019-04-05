// task4.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include "string"

using namespace std;


//////////////////////////////////////
//Time类，简单地用来记录时间
//
class Time
{
public:
	int h;	 int m;  int s;
	Time() {
		h = 0;
		m = 0;
		s = 0;
	}
	Time& operator ++(int) //加1秒
	{
		if (s >= 60) {
			if (m >= 60)
			{
				h++;m = 0;s = 0;
			}
			else
			{
				m++;s = 0;
			}
		}
		else {
			s++;
		}
		return *this;
	}
	//Time& operator --();
	//Time& operator =();
};

////////////////////////////////////////////////////////////////
//全局变量&常量
Time time;
const int O_BAOJI = 5;  //初始暴击率5%
const int O_LV = 1;     //初始等级
const int MAX_LV = 15;  //最高等级
const int EXP_NEED = 100;  //每升一级所需经验
const int EXP_ADD = 300;  //每赢一次所得经验

////////////////////////////////
//Weapon类
//
class Weapon
{
public:
	string name;
	int ATK;    //给角色增加的额外攻击力
	int BaoJi;  //暴击率,0到100。暴击伤害默认为原伤害的2倍
	Weapon(char* n, int atk, int bjl) {
		name = n;
		ATK = atk;
		BaoJi = bjl;
	}
	//void skill();  //武器主动技
};

/////////////////////////////////////////////////////////////////////////////////////////////
//角色类CRole为基类：
//成员变量：头像、HP（血量）、ATK（攻击力）、DEF（防御力）、Lv（等级），EXP（经验值）；
//成员函数：武器攻击、跳跃。
//
class CRole
{
public:
	string headIcon;
	int HP;
	int ATK;
	int DEF;
	int Lv;
	int EXP;
	Weapon* weapon;  //持有的武器
	bool jumping;  //是否处于跳跃中
	int skillATK;  //技能附加的攻击力,可以为负
	CRole();
	CRole(char* hi, int a, int d);
	~CRole();
	void atkWeapon();  //默认持续2秒
	void jump();  //默认跳跃持续时间为1秒，可以躲避1s的技能（如踢腿、劈掌）的伤害，但是会更容易被持续时间较长的技能打击（受到伤害增加）。
	void getWeapon(Weapon& wp);  //获得武器
	int BaoJi;   //暴击率0-100
	//int ShanBi;  //初始闪避率
	void jumpEnd();  //结束跳跃
};

class CEnemy; // 前置声明
/////////////////////////////////////////////////////////////////////////////////////////////
//英雄类CHero继承于CRole类
//英雄类新增技能踢腿（成员函数）、抱摔（成员函数），给对方造成伤害具体值由学员自己进行设定；
//
class CHero: public CRole
{
public:
	CHero(char* headicon, int atk, int def);
	~CHero();
	int skill_kick(CEnemy& enemy);//返回技能的持续时间（秒）
	int skill_hug(CEnemy& enemy);
};

/////////////////////////////////////////////////////////////////////////////////////////////
//敌人类CEnemy继承于CRole类
//新增技能劈掌（成员函数）、连环腿（成员函数），给对方造成伤害值由学员自己进行设定；
//
class CEnemy: public CRole
{
public:
	CEnemy(char* headicon, int atk, int def);
	~CEnemy();
	int skill_hand(CHero& hero);
	int skill_kicks(CHero& hero);
};

//////////////////////////////////////////////////////////////////////////////////////////////
//战斗类CBattle
//双方HP(血量)初始值为100，开始战斗以后，英雄和敌人轮流攻击对方，
//掉血量 = 攻击方技能伤害值 + ATK（攻击方的攻击力） - DEF（防御方的防御力），
//当一方血量为0时，战斗结束，玩家经验值增加相应点数，当经验等级达一定时候，玩家等级提升。
//
class CBattle
{
public:
	friend CHero;
	friend CEnemy;
	int tf;    //表示一回合持续的时间（秒）
	int turn;   //turn为1表示hero的回合,2表示enemy的回合，当一方阵亡，其值变为0
	CBattle();
	~CBattle();
	void begin(CHero& h, CEnemy& e);
	void heroAtk(CHero& h, CEnemy& e,int i);  //i=0表示物理攻击，否则i对应技能编号（1-?）
	void enemyAtk(CEnemy& e, CHero& h, int i);
};



/////////////////////////////////////////////////////////////////
//主函数
//
int main()
{
	Weapon sword("sword", 10, 10);
	CHero hero("WHA",25,0);
	hero.getWeapon(sword);
	CEnemy enemy("Evil",20,5);
	CBattle battle;
	battle.begin(hero,enemy);
	cout << "Game finished." << endl;
	int i;
	cin >> i;
    return 0;
}

//////////////////////////////////////////////////////////////////
//各种成员函数的实现
//
//CRole-------------------------------------------
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

CRole::CRole(char* hi, int a, int d)
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
	cout << headIcon << " is going to jump.\n";
}

void CRole::jumpEnd()
{
	jumping = false;
	cout << headIcon << " finishs jumping.\n";
}

void CRole::getWeapon(Weapon& wp)
{
	weapon = &wp;
	BaoJi += wp.BaoJi;
	cout << headIcon << " gets a weapon named " << wp.name <<", his ATK and BaoJiLv increase!"<< endl;
}

void CRole::atkWeapon()
{
	if (weapon != NULL) {
		ATK = ATK + weapon->ATK;
	}
	srand((unsigned int)(time.s));  //随机数种子
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

//CHero--------------------------------------------------
CHero::CHero(char* hi, int a, int d):CRole(hi,a,d)
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

//CEnemy-------------------------------------------------
CEnemy::CEnemy(char* hi, int a, int d) :CRole(hi, a, d)
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

//CBattle-------------------------------------------------
CBattle::CBattle()
{
	tf = 0;
	turn = 2;
}

CBattle::~CBattle()
{
	tf = 0;
	turn = 0;
}

void CBattle::begin(CHero& hero,CEnemy& enemy)
{
	int doer, t;
	t = 0;tf = 1;
	while (turn)
	{
		time++;
		//判断角色是否落地---------------------------------
		if (hero.jumping) { hero.jumpEnd(); }
		if (enemy.jumping) { enemy.jumpEnd(); }
		t++;
		//如果上一回合结束了，那么-------------------------------
		if(t==tf)
		{
			tf = 1;t = 0;
			hero.skillATK = 0;
			enemy.skillATK = 0;
			cout << endl << "The time is " << time.h << ":" << time.m << ":" << time.s << endl;
			//判断血量-----------------------------------
			if (hero.HP == 0)  //英雄阵亡，游戏结束
			{
				cout << "hero's HP = 0. You Lose." << endl;
				break;
            }
			else if (enemy.HP == 0)  //胜利，游戏结束
			{
				int exp = hero.EXP;
				exp+= EXP_ADD;
				int lv = exp / EXP_NEED;
				if (lv > hero.Lv) {
					if (lv > MAX_LV) { lv = MAX_LV; }
					hero.Lv = lv;
					cout << "You win! EXP+" << EXP_ADD << "  And your hero'Lv up! Lv=" << lv << endl;
				}
				else
				{
					cout << "You win! EXP+" << EXP_ADD << "."<<endl;
				}
				hero.EXP = exp;
				break;
			}
			else  //还没结束
			{
				cout << "hero's HP = " << hero.HP << ",   enemy's HP = " << enemy.HP << "." << endl;
			}
			cout << endl << "Input 0 to exit, other integer to continue:" << endl;
		    cin >> doer;
		    if (doer == 0) { break; }
			//选择本回合的动作------------------------------------
		    if (turn == 1)
		    {
		    	cout << "Hero choose what to do:" << endl << "Input 1 to attack physically, 2 to jump, 3 to use skill_1, 4 to use skill_2:";
				cin >> doer;
				switch (doer)
				{
				case 1:
					heroAtk(hero, enemy, 0);
					break;
				case 2:
					hero.jump();
					break;
				case 3:
					heroAtk(hero, enemy, 1);
					break;
				case 4:
					heroAtk(hero, enemy, 2);
					break;
				}
				turn = 2;
		    }
		    else
		    {
		    	cout << "Enemy choose what to do:" << endl<< "Input 1 to attack physically, 2 to jump, 3 to use skill_1, 4 to use skill_2:";
				cin >> doer;
				switch (doer)
				{
				case 1:
					enemyAtk(enemy, hero, 0);
					break;
				case 2:
					enemy.jump();
					break;
				case 3:
					enemyAtk(enemy, hero, 1);
					break;
				case 4:
					enemyAtk(enemy, hero, 2);
					break;
				}
				turn = 1;
		    }
		}
	}
}

void CBattle::heroAtk(CHero& hero, CEnemy& emy, int i)
{
	if (i == 0)  // 普攻
	{
		hero.atkWeapon();
		tf = 2;
	}
	else if (i == 1)  //skill_1
	{
		tf = hero.skill_kick(emy);
	}
	else if (i == 2)  //skill_2
	{
		tf = hero.skill_hug(emy);
	}
	else
	{
		cout << "Error!" << endl;
	}
	int hp = emy.HP;
	hp = hp - hero.ATK - hero.skillATK + emy.DEF;
	if (hp <= 0)
	{
		emy.HP = 0;
	}
	else if(hp<emy.HP)
	{
		emy.HP = hp;
	}
}

void CBattle::enemyAtk(CEnemy& emy, CHero& hero, int i)
{
	if (i == 0)  // 普攻
	{
		emy.atkWeapon();
		tf = 2;
	}
	else if (i == 1)  //skill_1
	{
		tf = emy.skill_hand(hero);
	}
	else if (i == 2)  //skill_2
	{
		tf = emy.skill_kicks(hero);
	}
	else
	{
		cout << "Error!" << endl;
	}
	int hp = hero.HP;
	hp = hp - emy.ATK - emy.skillATK + hero.DEF;
	if (hp <= 0)
	{
		hero.HP = 0;
	}
	else if(hp<hero.HP)
	{
		hero.HP = hp;
	}
}