#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class MyMenu :public Layer {//定义Layer类
private:
	Director* director;
	Size visibleSize;
	Vec2 origin;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MyMenu);//增加一个create函数
	void comeback(Ref* Psendeer);//回调函数
	void wudi(Ref* Psendeer);
	void ExitGame(Ref* pSender);
};