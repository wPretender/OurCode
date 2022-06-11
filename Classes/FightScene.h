#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "monster.h"
#include <vector>
#include "AudioEngine.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;

class FightScene :public Layer
{
private:
	Director* director;
	Size visibleSize;
	TMXTiledMap* TMap;
	Vec2 NextPos;
public:
	Label* HP0, * HP1, * HP2, * HP3, * class1, * class2, * class3, * class0;
	MenuItemImage* button1, * button2, * button3, * button4, * button5;
	Sprite* mySprite, * monSprite[3];
	hero* Hero;
	monster* Monster[3];
	static Scene* createScene(hero* Hero,monster** Monster,TMXTiledMap* tmap,Vec2 next);//架构场景
	virtual bool init(hero* Hero, monster** Monster);  //具体实现
	//CREATE_FUNC(FightScene); //生成项目
	static FightScene* create(hero* Hero, monster** Monster);
	void goto1(Ref* temp);
	void goto2(Ref* temp);
	void goto3(Ref* temp);
	void goto4(Ref* temp);
	void goto5(Ref* temp);
	bool all_death();
};