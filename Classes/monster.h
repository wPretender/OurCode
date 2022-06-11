#pragma once
#include<cocos2d.h>
#include<string>
#include"item.h"
using namespace cocos2d;
using namespace std;

class hero;

class monster : public Node
{
protected:
	//怪物属性
	Sprite* m_image;
	string m_name;
	Vec2 m_pos;
public:
	//构造函数
	monster(){};
	//析构函数
	virtual ~monster(){};
	//受击函数
	virtual void be_attacked(int atk, hero& Hero);
	//设置属性
	void setProperty(int health, int atk, int def, int exp);
	//判断是否死亡
	virtual bool is_death() const;
	//获取精灵
	Sprite* getSprite() const;
	//CREATE_FUNC(monster);
	static monster* create();
	int m_job;
	int m_health;
	int m_atk;
	int m_def;
	int m_exp;
};

