#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#include "ui/CocosGUI.h"
using namespace ui;

class MyTextField :public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MyTextField);
	static Scene* createScene();
private:
	TextField* id;  //id文本框
	TextField* key; //keyword文本框
	Button* go;     //登录按钮
};