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
	TMXTiledMap* TMap;
	Vec2 NextPos;
public:
	hero* Hero;
	monster* Monster[3];
	virtual bool init(hero* Hero, monster** Monster);  //����ʵ��
	//CREATE_FUNC(FightMenu); //������Ŀ
	static Scene* createScene(hero* Hero, monster** Monster,TMXTiledMap* tmap, Vec2 next);//�ܹ�����
	static FightMenu* create(hero* Hero, monster** Monster);
	void goto1(Ref* temp);
	void goto2(Ref* temp);
	void goto3(Ref* temp);
	void comeback(Ref* temp);
};