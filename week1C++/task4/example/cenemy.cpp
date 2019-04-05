#include <iostream>
using namespace std;
#include"cenemy.h"

CEnemy::CEnemy(int headPic, int hp, int atk, int def, int exp, int lv)
	:CRole(headPic, hp, atk, def, exp, lv)
{
}

CEnemy::~CEnemy()
{
}

int CEnemy::palmAttack()
{
	cout << "敌人使出了劈掌,对英雄造成了" << m_atk * 2 << "点伤害" << endl;
	return m_atk * 2;
}

int CEnemy::serialKick()
{
	cout << "敌人使出了连坏腿,对英雄造成了" << m_atk * 3 << "点伤害" << endl;
	return m_atk * 3;
}
