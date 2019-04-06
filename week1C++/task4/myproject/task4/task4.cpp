#include <iostream>
#include "CRoles.h"

using namespace std;

//////////////////////////////////////
// Time类，简单地用来记录时间
//////////////////////////////////////
class Time
{
public:
	int h;	 int m;  int s;
	inline Time() {
		h = 0;
		m = 0;
		s = 0;
	}
	inline Time& operator ++(int) { //加1秒
		if (s >= 60)
			if (m >= 60) {
				h++; m = 0; s = 0;
			}
			else {
				m++; s = 0;
			}
		else s++;
		return *this;
	}
};

/////////////////////////////////////////////////
// 战斗类CBattle
/////////////////////////////////////////////////
class CBattle
{
public:
	void begin(CHero& h, CEnemy& e);
private:
	Time time = Time();
	int tf;    //表示角色某个动作花费的时间
	int turn = 2;   //turn为1表示hero的回合,2表示enemy的回合，当一方阵亡，其值变为0
	void heroAtk(CHero& h, CEnemy& e, int i);  //i=0表示物理攻击，否则i对应技能编号（1-?）
	void enemyAtk(CEnemy& e, CHero& h, int i);
};


//////////////////////////////////////
// Main
//////////////////////////////////////
int main()
{
	string names[3] = { "nameWeapon", "nameHero", "nameEnemy" };
	for (int i = 0; i < 3; i++) {
		cout << "Input " << names[i] << ": ";
		cin >> names[i];
	}

	Weapon sword(names[0], 10, 10);
	CHero hero(names[1], 25, 0);
	CEnemy enemy(names[2], 20, 5);
	CBattle battle;

	hero.coutAtkDef();
	enemy.coutAtkDef();
	hero.getWeapon(sword);

	while (true) {
		system("pause");
		battle.begin(hero, enemy);
		hero.HP = 100;
		enemy.HP = 100;
	}

	system("pause");
	return 0;
}


/////////////////////////////////
// CBattle成员函数实现
/////////////////////////////////

void CBattle::begin(CHero& hero, CEnemy& enemy)
{
	bool jumping[2] = { false,false };
	cout << endl << "-------- Game Begin ---------" << endl;
	cout << "hero HP " << hero.HP << ",   enemy HP " << enemy.HP << "." << endl;
	while (turn)
	{
		for (int i = 0;i < tf;i++)
			time++;
		tf = 1;
		int doer = 0;
		hero.skillATK = 0;
		enemy.skillATK = 0;

		// 选择动作
		string role = turn == 1 ? "Hero" : "Enemy";
		cout << "----- " << role << " Turn --- " << time.h << ":" << time.m << ":" << time.s << " -----" << endl;
		cout << "1: attack physically   2: jump   3: skill_1   4: skill_2" << endl << "Input an integer:";
		do { cin >> doer; } while (!(doer == 1 || doer == 2 || doer == 3 || doer == 4));
		if (turn == 1) { //英雄动作
			switch (doer) {
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
		else { //敌人动作
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

		// 跳跃落地
		if (jumping[0] && hero.jumping) {
			hero.jumpEnd();
			jumping[0] = false;
		}
		else if (hero.jumping)
			jumping[0] = true;
		if (jumping[1] && enemy.jumping) {
			enemy.jumpEnd();
			jumping[1] = false;
		}
		else if (enemy.jumping)
			jumping[1] = true;

		// 血量
		if (hero.HP == 0) {
			cout << "hero's HP = 0. You Lose." << endl;
			break;
		}
		else if (enemy.HP == 0) {
			// 升级判断
			int oldLv = hero.Lv;
			hero.getExp(EXP_ADD);
			if (hero.Lv > oldLv)
				cout << "You win! EXP+" << EXP_ADD << "  And hero'Lv up!  Lv=" << hero.Lv << endl;
			else
				cout << "You win! EXP+" << EXP_ADD << "." << endl;
			cout << "To the next LvUp, still need " << hero.expNeedNext << " Exp." << endl;
			break;
		}
		else cout << "hero HP " << hero.HP << ",   enemy HP " << enemy.HP << "." << endl;

	}
	cout << "-------Game Finish -------" << endl;
}

// 英雄攻击
void CBattle::heroAtk(CHero& hero, CEnemy& emy, int i)
{
	if (i == 0)  //普攻
		hero.atkWeapon(emy, time.s);
	else if (i == 1)  //skill_1
		tf = hero.skill_kick(emy);
	else if (i == 2)  //skill_2
		tf = hero.skill_hug(emy);
	else
		cout << "Error!" << endl;
	int hp = emy.HP;
	hp = hp - hero.ATK - hero.skillATK + emy.DEF;
	if (hp <= 0)
		emy.HP = 0;
	else if (hp < emy.HP)
		emy.HP = hp;
}

// 敌人攻击
void CBattle::enemyAtk(CEnemy& emy, CHero& hero, int i)
{
	if (i == 0)  //普攻
		emy.atkWeapon(hero, time.s);
	else if (i == 1)  //skill_1
		tf = emy.skill_hand(hero);
	else if (i == 2)  //skill_2
		tf = emy.skill_kicks(hero);
	else
		cout << "Error!" << endl;
	int hp = hero.HP;
	hp = hp - emy.ATK - emy.skillATK + hero.DEF;
	if (hp <= 0)
		hero.HP = 0;
	else if (hp < hero.HP)
		hero.HP = hp;
}