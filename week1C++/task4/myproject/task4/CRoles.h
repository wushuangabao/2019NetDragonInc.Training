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
	int BaoJi;   //暴击率
	int expNeedNext; //距离升级还差的经验数量
	Weapon* weapon;  //持有的武器
	bool jumping;  //是否处于跳跃中
	int skillATK;  //技能附加的攻击力,可以为负

	CRole();
	CRole(string hi, int a, int d);
	~CRole();

	void atkWeapon(CRole& role,int seed);  //普攻，有机会暴击
	void jump();  //跳跃可以躲避普攻和技能1伤害
	void jumpEnd();  //结束跳跃
	void getWeapon(Weapon& wp);  //获得武器，攻击、暴击率提升
	inline void coutAtkDef() { //输出攻、防、暴击率
		cout << headIcon << " ---- ATK " << ATK << " ---- DEF " << DEF << " ---- Bao " << BaoJi << "%" << endl;
	}
	void getExp(int exp);  //获取经验

protected:
	int EXP;            //拥有的总经验
	const int O_LV = 1;     //初始等级
	const int MAX_LV = 15;  //最高等级
	int EXP_NEED(int lv);  //升到lv级所需总经验
	inline int expNeedWhenLv(int lv) { //在lv级时，升一级所需经验
		return lv * lv * 10 + 140;
	}
};

class CEnemy; // 前置声明

///////////////////////////////////////
// 英雄类CHero
// 技能1高额固定伤害
// 技能2低伤害，必中
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
// 敌人类CEnemy
// 技能1高额固定伤害
// 技能2低伤害，必中
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