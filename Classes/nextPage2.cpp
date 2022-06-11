#include "nextPage2.h"
#include "nextPage3.h"
#include <string>
#include <iostream>
using namespace std;
USING_NS_CC;
#define go(i,a,b) for(int i=a;i<=b;++i)


nextPage2* nextPage2::create(int Hero) {
	nextPage2* pRet = new(std::nothrow) nextPage2();
	//如果当前对象内存分配成功，并且初始化成功
	if (pRet && pRet->init(Hero))
	{
		//pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

Scene* nextPage2::createScene(int Hero)  //架构场景
{
	auto scene = Scene::create();
	auto layer = nextPage2::create(Hero);
	scene->addChild(layer);
	return scene;
}
bool nextPage2::init(int Her)  //层的实现
{
	if (!Layer::init())
		return false;
	Hero = Her;
	Size visibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小
	if (Hero == 0) {
		temp = MenuItemImage::create(
			"excalibur2.png",
			"excalibur2.png",
			CC_CALLBACK_1(nextPage2::goto1, this));
	}
	else if (Hero == 1) {
		temp = MenuItemImage::create(
			"vasavi2.png",
			"vasavi2.png",
			CC_CALLBACK_1(nextPage2::goto1, this));
	}
	else if (Hero == 2) {
		temp = MenuItemImage::create(
			"samsara2.png",
			"samsara2.png",
			CC_CALLBACK_1(nextPage2::goto1, this));
	}
	else if (Hero == 4) {
		temp = MenuItemImage::create(
			"maha2.png",
			"maha2.png",
			CC_CALLBACK_1(nextPage2::goto1, this));
	}
	else if (Hero == 5) {
		temp = MenuItemImage::create(
			"beast2.png",
			"beast2.png",
			CC_CALLBACK_1(nextPage2::goto1, this));
	}
	nxt = Menu::create(temp, NULL);
	nxt->setAnchorPoint(Vec2(0, 0));
	nxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	nxt->setScale(visibleSize.height / nxt->getContentSize().height, visibleSize.width / nxt->getContentSize().width);
	this->addChild(nxt, 1);
	return true;
}

void nextPage2::goto1(Ref* temp)
{
	Director::getInstance()->pushScene(nextPage3::createScene(Hero));
}
