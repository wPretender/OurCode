#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Victory :public Layer {//定义Layer类
private:
	Director* director;
	Size visibleSize;
	Vec2 origin;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Victory);//增加一个create函数
	void goto1(Ref* Psendeer);//回调函数
};