#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class mysecondscene :public Layer
{
public:
	static Scene* createScene();//架构场景
	virtual bool init();  //具体实现
	CREATE_FUNC(mysecondscene); //生成项目
	void comeback(Ref* temp);  //回调函数
};