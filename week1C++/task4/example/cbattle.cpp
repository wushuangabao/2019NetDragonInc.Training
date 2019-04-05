#include <iostream>
using namespace std;
#include<cstdlib>
#include<ctime>
#include "cbattle.h"

CBattle::CBattle()
{
	cout << "战斗准备" << endl;
}

CBattle::~CBattle()
{
}
void CBattle::fight(CHero &hero, CEnemy &enemy)
{
	char control;
	while (1)
	{
		hero.perpare();
		enemy.perpare();
		while (1)
		{
			srand((unsigned)time(NULL) + rand() % 6);//生成随机数
			switch (rand() % 6)
			{

			case 0:
				if (rand() % 4 == 0)
				{
					cout << "英雄对敌人使用了普通攻击，敌人";
					enemy.jump();
					break;
				}
				enemy.beAttack(hero.attack());
				cout << "英雄对敌人使用了普通攻击，造成了" << hero.attack() << "点伤害" << endl;
				break;
			case 1:
				if (rand() % 4 == 0)
				{
					cout << "敌人对英雄使用了普通攻击，英雄";
					hero.jump();
					break;
				}
				cout << "敌人对英雄使用了普通攻击，造成了" << enemy.attack() << "点伤害" << endl;
				hero.beAttack(enemy.attack());
				break;
				
			case 2:
				if (rand() % 4 == 0)
				{
					cout << "英雄使出了抱摔,敌人";
					enemy.jump();
					break;
				}
				enemy.beAttack(hero.hugFall());
				break;
			case 3:
				if (rand() % 4 == 0)
				{
					cout << "敌人使出了劈掌,英雄";
					hero.jump();
					break;
				}
				hero.beAttack(enemy.palmAttack());
				break;
			case 4:
				if (rand() % 4 == 0)
				{
					cout << "英雄使出了踢腿,敌人";
					hero.jump();
					break;
				}
				enemy.beAttack(hero.kick());
				break;
			case 5:
				if (rand() % 4 == 0)
				{
					cout << "敌人使出了连坏腿,英雄";
					hero.jump();
					break;
				}
				hero.beAttack(enemy.serialKick());
				break;
			default:
				break;
			}
			if (enemy.getHp() <= 0)
			{
				cout << "hero win" << endl;
				hero.setExp(hero.getExp() + 50 * hero.getLv());
				enemy.setLv(hero.getLv());
				break;
			}
			if (hero.getHp() <= 0)
			{
				cout << "enemy win" << endl;
				break;
			}
		}
		cout << "输入c开始下一局，输入q退出" << endl;
		while (1)
		{
			control = getchar();
			if (control == 'c')
				break;
			else if (control == 'q')
				return ;
		}
	}
}
