#include "FightMenu.h"
#include <string>
#include <iostream>
using namespace std;
USING_NS_CC;
#define go(i,a,b) for(int i=a;i<=b;++i)


FightMenu* FightMenu::create(hero * Hero, monster * *Monster) {
	FightMenu* pRet = new(std::nothrow) FightMenu();
	//如果当前对象内存分配成功，并且初始化成功
	if (pRet && pRet->init(Hero, Monster))
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

Scene* FightMenu::createScene(hero* Hero, monster** Monster)  //架构场景
{
	auto scene = Scene::create();
	auto layer = FightMenu::create(Hero, Monster);
	scene->addChild(layer);
	return scene;
}
bool FightMenu::init(hero* Her, monster** Monste)  //层的实现
{
	if (!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小
	//if (GameMap::is_playing) {
	//	AudioEngine::pause(GameMap::audioID);
	//}
	auto bgSprite = Sprite::create("rule.png");
	bgSprite->setAnchorPoint(Vec2(0, 0));
	bgSprite->setScale(visibleSize.height / bgSprite->getContentSize().height, visibleSize.width / bgSprite->getContentSize().width);
	bgSprite->setPosition(Vec2(0, 0));
	this->addChild(bgSprite, 0);

	Hero = Her;
	int cnt[3], x;
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < 3; ++i) {
		Monster[i] = Monste[i];
		x = rand() % 3;
		Monster[i]->m_job = x;
		cnt[x]++;
	}


	Label* label1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 46);//白色字体
	label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/15*14));
	addChild(label1, 1);
	label1->setString(StringUtils::format("Enemies:  Saber %d  Lancer %d  Archer%d", cnt[0], cnt[1], cnt[2]));

	Label* label2 = Label::createWithTTF("Please choose your class", "fonts/Marker Felt.ttf", 46);
	label2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 6 * 5));
	addChild(label2, 2);

	auto saber = MenuItemImage::create(
		"saber1.png",
		"saber1.png",
		CC_CALLBACK_1(FightMenu::goto1, this));
	auto saber1 = Menu::create(saber, NULL);
	saber1->setAnchorPoint(Vec2(0, 0));
	saber1->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 2));
	saber1->setScale(0.8f);
	this->addChild(saber1, 3);

	auto lancer = MenuItemImage::create(
		"lancer1.png",
		"lancer1.png",
		CC_CALLBACK_1(FightMenu::goto2, this));
	auto lancer1 = Menu::create(lancer, NULL);
	lancer1->setAnchorPoint(Vec2(0, 0));
	lancer1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	lancer1->setScale(0.8f);
	this->addChild(lancer1, 3);

	auto archer = MenuItemImage::create(
		"archer1.png",
		"archer1.png",
		CC_CALLBACK_1(FightMenu::goto3, this));
	auto archer1 = Menu::create(archer, NULL);
	archer1->setAnchorPoint(Vec2(0, 0));
	archer1->setPosition(Vec2(visibleSize.width / 5 * 4, visibleSize.height / 2));
	archer1->setScale(0.8f);
	this->addChild(archer1, 3);

	/*auto back = MenuItemImage::create(
		"return.png",
		"return.png",
		CC_CALLBACK_1(FightMenu::comeback, this));
	auto back1 = Menu::create(back, NULL);
	back1->setAnchorPoint(Vec2(0, 0));
	back1->setPosition(Vec2(visibleSize.width / 18 * 17, visibleSize.height / 20 * 19));
	back1->setScale(0.6f);
	this->addChild(back1, 3);*/
	return true;
}

void FightMenu::goto1(Ref* temp)
{
	Hero->h_job = 0;
	Director::getInstance()->pushScene(FightScene::createScene(Hero, Monster));

}

void FightMenu::goto2(Ref* temp)
{
	Hero->h_job = 1;
	Director::getInstance()->pushScene(FightScene::createScene(Hero, Monster));
}

void FightMenu::goto3(Ref* temp)
{
	Hero->h_job = 2;
	Director::getInstance()->pushScene(FightScene::createScene(Hero, Monster));
}

void FightMenu::comeback(Ref* temp) {
	auto glview = Director::getInstance()->getOpenGLView();
	glview->setFrameSize(1024, 768);
	Director::getInstance()->popScene();
}