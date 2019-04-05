#pragma once
#include "crole.h"
class CEnemy : public CRole
{
public:
	CEnemy(int headPic = 2, int hp = 100, int atk = 10, int def = 10, int exp = 0, int lv = 1);
	~CEnemy();
	int palmAttack();
	int serialKick();
};