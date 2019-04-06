#include <string>

using namespace std;

#ifndef _CROLES_
#define _CROLES_

//////////////////////////////////////////
// 全局常量
//////////////////////////////////////////
const int O_BAOJI = 25;  //基础暴击率25%
const int EXP_ADD = 300;  //每赢一次所得经验

////////////////////////////////
// Weapon类
////////////////////////////////
class Weapon
{
public:
	string name;
	int ATK;    //给角色增加的额外攻击力
	int BaoJi;  //暴击率,0到100。暴击伤害默认为原伤害的2倍
	inline Weapon(string n, int atk, int bjl) {
		name = n;
		ATK = atk;
		BaoJi = bjl;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////
// 角色类CRole为基类：
// 成员变量：头像、HP（血量）、ATK（攻击力）、DEF（防御力）、Lv（等级），EXP（经验值）
// 成员函数：武器攻击、跳跃。
//////////////////////////////////////////////////////////////////////////////////////////
class CRole
{
public:
	string headIcon;  //头像/名字
	int HP;
	int ATK;
	int DEF;
	int Lv;
	int EXP;
	int BaoJi;   //暴击率
	const int O_LV = 1;     //初始等级
	const int MAX_LV = 15;  //最高等级
	inline int EXP_NEED() { return Lv * Lv * 50; }  //每升一级所需经验
	Weapon* weapon;  //持有的武器
	bool jumping;  //是否处于跳跃中
	int skillATK;  //技能附加的攻击力,可以为负

	CRole();
	CRole(string hi, int a, int d);
	~CRole();

	void atkWeapon(int seed);  //攻击花费时间持续2秒
	void jump();  //跳跃持续时间为1秒，可以躲避1s的技能（如踢腿、劈掌）的伤害。
	void jumpEnd();  //结束跳跃
	void getWeapon(Weapon& wp);  //获得武器，攻击、暴击率提升
	inline void coutAtkDef() { //输出攻、防、暴击率
		cout << headIcon << " ---- ATK " << ATK << " ---- DEF " << DEF << " ---- Bao " << BaoJi << "%" << endl;
	}
};

class CEnemy; // 前置声明

///////////////////////////////////////
// 英雄类CHero
///////////////////////////////////////
class CHero : public CRole
{
public:
	CHero(string headicon, int atk, int def);
	~CHero();
	int skill_kick(CEnemy& enemy);//返回技能的持续时间（秒）
	int skill_hug(CEnemy& enemy);
};

////////////////////////////////////////
//敌人类CEnemy继承于CRole类
////////////////////////////////////////
class CEnemy : public CRole
{
public:
	CEnemy(string headicon, int atk, int def);
	~CEnemy();
	int skill_hand(CHero& hero);
	int skill_kicks(CHero& hero);
};

#endif