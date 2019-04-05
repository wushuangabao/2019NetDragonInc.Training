#pragma once

#define HEROHEAD 1
#define ENEMYHEAD 2
class CRole
{
public:
	CRole(int headPic = 1, int hp = 100, int atk = 10, int def = 10, int exp = 0, int lv = 1);
	~CRole();
	int attack();
	void jump();
	void setLv(int lv)
	{
		m_lv = lv;
	}
	int getLv() const
	{
		return m_lv;
	}
	void perpare();
	int getHp() const;
	void beAttack(int damage);
protected:
	int m_headPic;
	int m_hp;
	int m_atk;
	int m_def;
	int m_lv;
	int m_exp;
};
