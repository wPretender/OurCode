#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class MapScene :public Layer {//定义Layer类
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MapScene);//增加一个create函数
	void comeback(Ref* temp);//回调函数
	void comeback2(Ref* temp);  //回调函数2
};