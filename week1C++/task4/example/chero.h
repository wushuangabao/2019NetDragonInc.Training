#pragma once
#include "crole.h"

class CHero : public CRole
{
public:
	CHero(int headPic = 1, int hp = 100, int atk = 10, int def = 10, int exp = 0, int lv = 1);
	~CHero();
	void setExp(int exp);
	int getExp() const
	{
		return m_exp;
	}
	int kick();
	int hugFall();
};