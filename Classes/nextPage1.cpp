#include "nextPage1.h"
#include "nextPage2.h"
#include <string>
#include <iostream>
using namespace std;
USING_NS_CC;
#define go(i,a,b) for(int i=a;i<=b;++i)


nextPage1* nextPage1::create(int Hero) {
	nextPage1* pRet = new(std::nothrow) nextPage1();
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

Scene* nextPage1::createScene(int Hero)  //架构场景
{
	auto scene = Scene::create();
	auto layer = nextPage1::create(Hero);
	scene->addChild(layer);
	return scene;
}
bool nextPage1::init(int Hero)  //层的实现
{
	if (!Layer::init())
		return false;
	this->Hero = Hero;
	Size visibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小
	if (Hero == 0) {
		temp = MenuItemImage::create(
			"excalibur1.png",
			"excalibur1.png",
			CC_CALLBACK_1(nextPage1::goto1, this));
	}
	else if (Hero == 1) {
		temp = MenuItemImage::create(
			"vasavi1.png",
			"vasavi1.png",
			CC_CALLBACK_1(nextPage1::goto1, this));
	}
	else if (Hero == 2) {
		temp = MenuItemImage::create(
			"samsara1.png",
			"samsara1.png",
			CC_CALLBACK_1(nextPage1::goto1, this));
	}
	else if (Hero == 4) {
		temp = MenuItemImage::create(
			"maha1.png",
			"maha1.png",
			CC_CALLBACK_1(nextPage1::goto1, this));
	}
	else if (Hero == 5) {
		temp = MenuItemImage::create(
			"beast1.png",
			"beast1.png",
			CC_CALLBACK_1(nextPage1::goto1, this));
	}
	nxt = Menu::create(temp, NULL);
	nxt->setAnchorPoint(Vec2(0, 0));
	nxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	nxt->setScale(visibleSize.height / nxt->getContentSize().height, visibleSize.width / nxt->getContentSize().width);
	this->addChild(nxt, 1);
	return true;
}

void nextPage1::goto1(Ref* temp)
{
	Director::getInstance()->pushScene(nextPage2::createScene(Hero));
}
