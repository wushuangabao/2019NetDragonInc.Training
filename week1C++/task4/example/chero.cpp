#include <iostream>
using namespace std;
#include"chero.h"

CHero::CHero(int headPic, int hp, int atk, int def, int exp, int lv)
	:CRole(headPic, hp, atk, def, exp, lv)
{
}

CHero::~CHero()
{
}

int CHero::kick()
{
	cout << "英雄使出了踢腿,对敌人造成了" << m_atk * 2 << "点伤害" << endl;
	return m_atk * 2;
}

int CHero::hugFall()
{
	cout << "英雄使出了抱摔,对敌人造成了" << m_atk * 3 << "点伤害" << endl;
	return m_atk * 3;
}
void CHero::setExp(int exp)
{
	m_exp = exp;
	if (m_exp > m_lv * 100)
	{
		m_exp = 0;
		setLv(getLv() + 1);
		cout << "你升级了,当前等级" << getLv() << endl;
	}
}
