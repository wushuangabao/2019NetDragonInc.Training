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
	EXP = EXP_NEED(O_LV - 1);
	weapon = NULL;
	jumping = false;
	BaoJi = O_BAOJI;
	skillATK = 0;
	expNeedNext = expNeedWhenLv(O_LV);
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
	expNeedNext = 0;
}

void CRole::jump()
{
	jumping = true;
	cout << headIcon << " starts to jump.\n";
}

void CRole::jumpEnd(){
	jumping = false;
	cout << headIcon << " finishs jumping.\n";
}

void CRole::getWeapon(Weapon& wp){
	// 取消原有的武器效果
	if (weapon != NULL) {
		BaoJi -= weapon->BaoJi;
		ATK -= weapon->ATK;
	}
	// 增添新的武器效果
	BaoJi += wp.BaoJi;
	ATK += wp.ATK;
	cout << headIcon << " gets a weapon named " << wp.name << ", his ATK and BaoJiLv increase!" << endl;
	coutAtkDef();
}

void CRole::atkWeapon(CRole& role, int seed){
	// 被跳跃躲开
	if (role.jumping) {
		cout << headIcon << " attcks physically! But miss." << endl;
		skillATK = -ATK; //通过skillATK减少1倍伤害量，制造躲避效果
		return;
	}

	// 击中，可能暴击
	// TODO: 找出暴击测试时总是不出现的bug
	srand((unsigned int)(seed));  //获取随机数种子
	int n = rand() % 100;  //n是0-99中的随机数
	if (n < BaoJi) {
		skillATK = ATK;  //通过skillATK增加1倍伤害量，制造暴击效果
		cout << headIcon << " attcks physically and it's a BaoJi!" << endl;
	}
	else {
		cout << headIcon << " attcks physically!" << endl;
	}
}

void CRole::getExp(int exp) {
	EXP += exp;
	int i = Lv, expNeed = EXP_NEED(i);
	while (expNeed < EXP && i < MAX_LV)
		expNeed += expNeedWhenLv(++i);
	Lv = i;
	expNeedNext = expNeed - EXP;
}

int CRole::EXP_NEED(int lv) {
	int need = 0;
	for (int i = 1;i <= lv;i++) {
		need += expNeedWhenLv(i);
	}
	return need;
}


/////////////////////////////////
// 英雄
/////////////////////////////////
CHero::CHero(string hi, int a, int d) :CRole(hi, a, d)
{}

CHero::~CHero()
{}

int CHero::skill_kick(CEnemy &emy)
{
	if (emy.jumping) {
		cout << headIcon << " is kicking! But miss." << endl;
		skillATK = -ATK;
	}
	else {
		cout << headIcon << " is kicking " << emy.headIcon << "!" << endl;
		skillATK = 6;
	}
	return 1;
}

int CHero::skill_hug(CEnemy &emy)
{
	if (emy.jumping)
		cout << headIcon << " is hugging " << emy.headIcon << " who is jumping!" << endl;
	else
		cout << headIcon << " is hugging " << emy.headIcon << "!" << endl;
	skillATK = -8;
	return 3;
}

/////////////////////////////////
// 敌人
/////////////////////////////////
CEnemy::CEnemy(string hi, int a, int d) :CRole(hi, a, d)
{}

CEnemy::~CEnemy()
{}

int CEnemy::skill_hand(CHero &emy)
{
	if (emy.jumping) {
		cout << headIcon << " is handinging! But miss." << endl;
		skillATK = -ATK;
	}
	else {
		cout << headIcon << " is handding " << emy.headIcon << "!" << endl;
		skillATK = 8;
	}
	return 1;
}

int CEnemy::skill_kicks(CHero &emy)
{
	if (emy.jumping)
		cout << headIcon << " is kicking for times to " << emy.headIcon << " who is jumping!" << endl;
	else
		cout << headIcon << " is kicking for times to " << emy.headIcon << "!" << endl;
	skillATK = -10;
	return 3;
}
