#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class MyGame :public Layer {//定义Layer类
public:
	MyGame();
	~MyGame();
private:
	Director* director;
	Size visibleSize;
	Vec2 origin;
	void backButton();
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MyGame);//增加一个create函数
};