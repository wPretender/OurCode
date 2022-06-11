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
	//��������
	Sprite* m_image;
	string m_name;
	Vec2 m_pos;
public:
	//���캯��
	monster(){};
	//��������
	virtual ~monster(){};
	//�ܻ�����
	virtual void be_attacked(int atk, hero& Hero);
	//��������
	void setProperty(int health, int atk, int def, int exp);
	//�ж��Ƿ�����
	virtual bool is_death() const;
	//��ȡ����
	Sprite* getSprite() const;
	//CREATE_FUNC(monster);
	static monster* create();
	int m_job;
	int m_health;
	int m_atk;
	int m_def;
	int m_exp;
};

