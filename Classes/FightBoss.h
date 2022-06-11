#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "monster.h"
#include "GameMap.h"
#include <vector>
using namespace cocos2d;
using namespace std;

class FightBoss :public Layer
{
private:
	Director* director;
	Size visibleSize;
	TMXTiledMap* TMap;
	Vec2 NextPos;
public:
	Label* HP0, * HP1, * class1, * class0;
	MenuItemImage* button1, * button4, * button5;
	Sprite* mySprite, * monSprite;
	hero* Hero;
	monster* Monster;
	static Scene* createScene(hero* Hero, monster* Monster,TMXTiledMap* tmap,Vec2 next);//架构场景
	virtual bool init(hero* Hero, monster* Monster);  //具体实现
	static FightBoss* create(hero* Hero, monster* Monster);
	Vec2 PosToTileCoord(Vec2 pos);
	void goto1(Ref* temp);
	void goto4(Ref* temp);
	void goto5(Ref* temp);
};