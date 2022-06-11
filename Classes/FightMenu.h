#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "FightScene.h"
#include "monster.h"
#include "GameMap.h"
#include <vector>
using namespace cocos2d;
using namespace std;

class FightMenu :public Layer
{
private:
public:
	hero* Hero;
	monster* Monster[3];
	virtual bool init(hero* Hero, monster** Monster);  //具体实现
	//CREATE_FUNC(FightMenu); //生成项目
	static Scene* createScene(hero* Hero, monster** Monster);//架构场景
	static FightMenu* create(hero* Hero, monster** Monster);
	void goto1(Ref* temp);
	void goto2(Ref* temp);
	void goto3(Ref* temp);
	void comeback(Ref* temp);
};