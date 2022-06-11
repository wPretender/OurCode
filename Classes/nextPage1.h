#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "FightScene.h"
#include "monster.h"
#include "GameMap.h"
#include <vector>
using namespace cocos2d;
using namespace std;

class nextPage1 :public Layer
{
private:
	MenuItemImage* temp;
	Menu* nxt;
	int Hero;
public:
	virtual bool init(int job);  //具体实现
	//CREATE_FUNC(nextPage1); //生成项目
	static Scene* createScene(int job);//架构场景
	static nextPage1* create(int job);
	void goto1(Ref* temp);
};