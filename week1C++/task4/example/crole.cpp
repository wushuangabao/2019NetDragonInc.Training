#include <iostream>
using namespace std;
#include"crole.h"

CRole::CRole(int headPic, int hp, int atk, int def, int exp, int lv)
	:m_headPic(headPic), m_hp(hp), m_atk(atk), m_def(def), m_exp(exp), m_lv(lv)
{
}

CRole::~CRole()
{
}

int CRole::attack()
{
	return m_atk;
}

void CRole::jump()
{
	cout << "跳起来躲过了攻击" << endl;
}

int CRole::getHp() const
{
	return m_hp;
}

void CRole::beAttack(int damage)
{
	m_hp -= damage;
}
//战斗开始前的准备
void CRole::perpare()
{
	m_hp = 100 * m_lv;
	m_atk = 10 * m_lv;
	m_def = 10 * m_lv;
	if (m_headPic == HEROHEAD)
		cout << "角色：英雄" << endl;
	else if (m_headPic == ENEMYHEAD)
	{
		cout << "vs" << endl;
		cout << "角色：敌人" << endl;
	}
	cout << "等级:" << m_lv << endl;
	cout << "生命值:" << m_hp << endl;
	cout << "攻击力:" << m_atk << endl;
	cout << "防御力:" << m_def << endl;
}