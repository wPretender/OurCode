#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "FightScene.h"
#include "monster.h"
#include "GameMap.h"
#include <vector>
using namespace cocos2d;
using namespace std;

class nextPage3 :public Layer
{
private:
	MenuItemImage* temp;
	Menu* nxt;
	int Hero;
public:
	virtual bool init(int Hero);  //����ʵ��
	//CREATE_FUNC(nextPage1); //������Ŀ
	static Scene* createScene(int Hero);//�ܹ�����
	static nextPage3* create(int Hero);
	void goto1(Ref* temp);
};