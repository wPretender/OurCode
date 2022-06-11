#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "FightScene.h"
#include "monster.h"
#include "GameMap.h"
#include <vector>
using namespace cocos2d;
using namespace std;

class nextPage2 :public Layer
{
private:
	MenuItemImage* temp;
	Menu* nxt;
	int Hero;
public:
	virtual bool init(int Hero);  //具体实现
	//CREATE_FUNC(nextPage1); //生成项目
	static Scene* createScene(int Hero);//架构场景
	static nextPage2* create(int Hero);
	void goto1(Ref* temp);
};