#include "FightBoss.h"
#include "nextPage1.h"
#include "Over.h";
#include "Victory.h"
#include <string>
#include <iostream>
using namespace std;
USING_NS_CC;
#define go(i,a,b) for(int i=a;i<=b;++i)

FightBoss* FightBoss::create(hero* Hero, monster* Monster) {
	FightBoss* pRet = new(std::nothrow) FightBoss();
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

Scene* FightBoss::createScene(hero* Hero, monster* Monster)  //架构场景
{
	auto scene = Scene::create();
	auto layer = FightBoss::create(Hero, Monster);
	scene->addChild(layer);
	return scene;
}

bool FightBoss::init(hero* Her, monster* mon)  //层的实现
{
	if (!Layer::init())
		return false;
	director = Director::getInstance();
	visibleSize = director->getVisibleSize();	//获得屏幕大小
	srand(time(0));
	Sprite* bgSprite;
	if (rand() % 2)
		bgSprite = Sprite::create("grassland.png");
	else
		bgSprite = Sprite::create("snowberg.png");
	bgSprite->setAnchorPoint(Vec2(0, 0));
	bgSprite->setScale(visibleSize.height / bgSprite->getContentSize().height, visibleSize.width / bgSprite->getContentSize().width);
	bgSprite->setPosition(Vec2(0, 0));
	this->addChild(bgSprite, 0);
	Hero = Her;
	Monster = mon;
	if (Monster->m_job == 1) {
		mySprite = Sprite::create("lancer.png");
		monSprite = Sprite::create("arjuna.png");
		mySprite->setScale(0.7);
		monSprite->setScale(0.85);
		monSprite->setPosition(Vec2(visibleSize.width / 24 * 5, visibleSize.height / 3 + 130));
	}
	else if (Monster->m_job == 2) {
		mySprite = Sprite::create("archer.png");
		monSprite = Sprite::create("beast.png");
		mySprite->setScale(0.7);
		monSprite->setPosition(Vec2(visibleSize.width / 24 * 5, visibleSize.height / 3 + 100));
		monSprite->setScale(1.2);
	}
	mySprite->setPosition(Vec2(visibleSize.width / 22 * 18, visibleSize.height / 3 + 60));
	this->addChild(mySprite, 1);
	
	this->addChild(monSprite, 1);

	HP1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	HP1->setColor(Color3B(255, 0, 0));
	HP1->setPosition(Vec2(visibleSize.width / 24 * 5, visibleSize.height / 6 * 5));
	HP1->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster->m_health, Monster->m_atk, Monster->m_def, Monster->m_exp));
	this->addChild(HP1, 1);

	class1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	class1->setColor(Color3B(255, 0, 0));
	class1->setPosition(Vec2(visibleSize.width / 24 * 5, visibleSize.height / 6 * 5 + 95));
	if (Monster->m_job == 1)
		class1->setString(StringUtils::format("Arjuna"));
	else
		class1->setString(StringUtils::format("Beast Kama"));
	this->addChild(class1, 1);

	HP0 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	HP0->setColor(Color3B(255, 0, 0));
	HP0->setPosition(Vec2(visibleSize.width / 22 * 20, visibleSize.height / 6 * 5));
	HP0->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nNP: %d", Hero->h_health, Hero->h_atk + (Hero->sword != NULL ? Hero->sword->getATK() : 0), Hero->h_def + (Hero->shield != NULL ? Hero->shield->getDEF() : 0), Hero->NP));
	this->addChild(HP0, 1);

	class0 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	class0->setColor(Color3B(255, 0, 0));
	class0->setPosition(Vec2(visibleSize.width / 22 * 20, visibleSize.height / 6 * 5 + 95));
	if (Monster->m_job == 1)
		class0->setString(StringUtils::format("Karna"));
	else
		class0->setString(StringUtils::format("Kama"));
	this->addChild(class0, 1);

	button1 = MenuItemImage::create(
		"ch6.png",
		"ch60.png",
		CC_CALLBACK_1(FightBoss::goto1, this));
	auto ch1 = Menu::create(button1, NULL);
	ch1->setAnchorPoint(Vec2(0, 0));
	ch1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 6));
	ch1->setScale(0.6f);
	this->addChild(ch1, 3);

	button4 = MenuItemImage::create(
		"ch4.png",
		"ch40.png",
		CC_CALLBACK_1(FightBoss::goto4, this));
	if (Hero->NP < 100)
		button4->setEnabled(false);
	auto ch4 = Menu::create(button4, NULL);
	ch4->setAnchorPoint(Vec2(0, 0));
	ch4->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 6 * 3));
	ch4->setScale(0.6f);
	this->addChild(ch4, 3);

	button5 = MenuItemImage::create(
		"ch5.png",
		"ch50.png",
		CC_CALLBACK_1(FightBoss::goto5, this));
	auto ch5 = Menu::create(button5, NULL);
	ch5->setAnchorPoint(Vec2(0, 0));
	ch5->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 6 * 2));
	ch5->setScale(0.6f);
	this->addChild(ch5, 3);
	return true;
}

void FightBoss::goto1(Ref* temp)
{
	Monster->be_attacked(Hero->h_atk, *Hero);
	Hero->NP += 30;
	if (Hero->NP > 500)
		Hero->NP = 500;
	if (Monster->is_death()) {
		if (Monster->m_job == 1) {
			auto glview = Director::getInstance()->getOpenGLView();
			glview->setFrameSize(1024, 768);
			director->popToRootScene();
		}
		else
			director->replaceScene(Victory::createScene());
	}
	if (Monster->m_job == 1) {
		if (rand() % 3 == 0) {
			director->pushScene(nextPage1::createScene(4));
			Hero->be_attacked(Monster->m_atk * 3, *Monster);
		}
		else
			Hero->be_attacked(Monster->m_atk, *Monster);
	}
	else {
		if (rand() % 3 == 0) {
			director->pushScene(nextPage1::createScene(5));
			Hero->be_attacked(Monster->m_atk * 3 + Hero->h_def, *Monster);
		}
		else
			Hero->be_attacked(Monster->m_atk + Hero->h_def, *Monster);
	}
	HP1->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster->m_health, Monster->m_atk, Monster->m_def, Monster->m_exp));
	HP0->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nNP: %d", Hero->h_health, Hero->h_atk + (Hero->sword != NULL ? Hero->sword->getATK() : 0), Hero->h_def + (Hero->shield != NULL ? Hero->shield->getDEF() : 0), Hero->NP));
	if (Hero->NP < 100)
		button4->setEnabled(false);
	else
		button4->setEnabled(true);
	if (Hero->is_death()) {
		director->replaceScene(Over::createScene());
	}
}

void FightBoss::goto4(Ref* temp)
{
	director->pushScene(nextPage1::createScene(Hero->h_job));
	Monster->be_attacked(Hero->h_atk * 3, *Hero);
	Hero->NP -= 100;
	if (Monster->is_death()) {
		if (Monster->m_job == 1) {
			auto glview = Director::getInstance()->getOpenGLView();
			glview->setFrameSize(1024, 768);
			director->popToRootScene();
		}
		else
			director->replaceScene(Victory::createScene());
	}
	if (Monster->m_job == 1) {
		if (rand() % 3 == 0) {
			director->pushScene(nextPage1::createScene(4));
			Hero->be_attacked(Monster->m_atk * 3, *Monster);
		}
		else
			Hero->be_attacked(Monster->m_atk, *Monster);
	}
	else {
		if (rand() % 3 == 0) {
			director->pushScene(nextPage1::createScene(5));
			Hero->be_attacked(Monster->m_atk * 3 + Hero->h_def, *Monster);
		}
		else
			Hero->be_attacked(Monster->m_atk + Hero->h_def, *Monster);
	}
	HP1->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster->m_health, Monster->m_atk, Monster->m_def, Monster->m_exp));
	HP0->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nNP: %d", Hero->h_health, Hero->h_atk + (Hero->sword != NULL ? Hero->sword->getATK() : 0), Hero->h_def + (Hero->shield != NULL ? Hero->shield->getDEF() : 0), Hero->NP));
	if (Hero->NP < 100)
		button4->setEnabled(false);
	else
		button4->setEnabled(true);
	if (Hero->is_death()) {
		director->replaceScene(Over::createScene());
	}
}

void FightBoss::goto5(Ref* temp)
{
	if (Monster->m_job == 1) {
		if (rand() % 3 == 0) {
			director->pushScene(nextPage1::createScene(4));
			Hero->be_attacked(Monster->m_atk * 3 / 2, *Monster);
		}
		else
			Hero->be_attacked(Monster->m_atk / 2, *Monster);
	}
	else {
		if (rand() % 3 == 0) {
			director->pushScene(nextPage1::createScene(5));
			Hero->be_attacked(Monster->m_atk * 3 / 2 + Hero->h_def, *Monster);
		}
		else
			Hero->be_attacked(Monster->m_atk / 2 + Hero->h_def, *Monster);
	}
	Hero->NP += 60;
	if (Hero->NP > 500)
		Hero->NP = 500;
	HP1->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster->m_health, Monster->m_atk, Monster->m_def, Monster->m_exp));
	HP0->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nNP: %d", Hero->h_health, Hero->h_atk + (Hero->sword != NULL ? Hero->sword->getATK() : 0), Hero->h_def + (Hero->shield != NULL ? Hero->shield->getDEF() : 0), Hero->NP));
	if (Hero->NP < 100)
		button4->setEnabled(false);
	else
		button4->setEnabled(true);
	if (Hero->is_death()) {
			director->replaceScene(Over::createScene());
	}
}
