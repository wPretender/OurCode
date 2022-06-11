#include "FightScene.h"
#include "nextPage1.h"
#include "Over.h";
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
#define go(i,a,b) for(int i=a;i<=b;++i)

FightScene* FightScene::create(hero * Hero, monster * *Monster) {
	FightScene* pRet = new(std::nothrow) FightScene();
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

Scene* FightScene::createScene(hero* Hero,monster** Monster, TMXTiledMap* tmap, Vec2 next)  //架构场景
{
	auto scene = Scene::create();
	auto layer = FightScene::create(Hero, Monster);
	layer->TMap = tmap;
	layer->NextPos = next;
	scene->addChild(layer);
	return scene;
}

bool FightScene::init(hero* Her, monster** mon)  //层的实现
{
	if (!Layer::init())
		return false;
	director = Director::getInstance();
	visibleSize = director->getVisibleSize();	//获得屏幕大小

	//audioID = AudioEngine::play2d("solomon.mp3", true, 1.0f);
	//AudioEngine::setVolume(audioID, volume);
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
	go(i, 0, 2) {
		Monster[i] = mon[i];
	}
	if (Hero->h_job == 0) {
		mySprite = Sprite::create("saber.png");
		mySprite->setScale(0.7);
	}
	if (Hero->h_job == 1) {
		mySprite = Sprite::create("lancer.png");
		mySprite->setScale(0.7);
	}
	if (Hero->h_job == 2) {
		mySprite = Sprite::create("archer.png");
		mySprite->setScale(0.7);
	}
	mySprite->setPosition(Vec2(visibleSize.width / 22 * 18, visibleSize.height / 3+60));
	this->addChild(mySprite, 1);


	HP1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	HP1->setColor(Color3B(255, 0, 0));
	HP1->setPosition(Vec2(visibleSize.width / 12, visibleSize.height / 6 * 5));
	HP1->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster[0]->m_health, Monster[0]->m_atk, Monster[0]->m_def, Monster[0]->m_exp));
	this->addChild(HP1, 1);

	class1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	class1->setColor(Color3B(255, 0, 0));
	class1->setPosition(Vec2(visibleSize.width / 12, visibleSize.height / 6 * 5 + 95));
	if(Monster[0]->m_job==0)
		class1->setString(StringUtils::format("No.1 Saber"));
	if (Monster[0]->m_job == 1)
		class1->setString(StringUtils::format("No.1 Lancer"));
	if (Monster[0]->m_job == 2) 
		class1->setString(StringUtils::format("No.1 Archer"));
	this->addChild(class1, 1);

	if(Monster[0]->m_job==0)
		monSprite[0] = Sprite::create("saber2.png");
	if (Monster[0]->m_job == 1)
		monSprite[0] = Sprite::create("lancer2.png");
	if (Monster[0]->m_job == 2)
		monSprite[0] = Sprite::create("archer2.png");
	monSprite[0]->setPosition(Vec2(visibleSize.width / 12, visibleSize.height / 3));

	
	HP2 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	HP2->setColor(Color3B(255, 0, 0));
	HP2->setPosition(Vec2(visibleSize.width / 24 * 5, visibleSize.height / 6 * 5));
	HP2->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster[1]->m_health, Monster[1]->m_atk, Monster[1]->m_def, Monster[1]->m_exp));
	this->addChild(HP2, 1);

	class2 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	class2->setColor(Color3B(255, 0, 0));
	class2->setPosition(Vec2(visibleSize.width / 24 * 5, visibleSize.height / 6 * 5 + 95));
	if (Monster[1]->m_job == 0)
		class2->setString(StringUtils::format("No.2 Saber"));
	if (Monster[1]->m_job == 1)
		class2->setString(StringUtils::format("No.2 Lancer"));
	if (Monster[1]->m_job == 2)
		class2->setString(StringUtils::format("No.2 Archer"));
	this->addChild(class2, 1);

	if (Monster[1]->m_job == 0)
		monSprite[1] = Sprite::create("saber2.png");
	if (Monster[1]->m_job == 1)
		monSprite[1] = Sprite::create("lancer2.png");
	if (Monster[1]->m_job == 2)
		monSprite[1] = Sprite::create("archer2.png");
	monSprite[1]->setPosition(Vec2(visibleSize.width / 24 * 5, visibleSize.height / 3));
	
	HP3 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	HP3->setColor(Color3B(255, 0, 0));
	HP3->setPosition(Vec2(visibleSize.width / 12 * 4, visibleSize.height / 6 * 5));
	HP3->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster[2]->m_health, Monster[2]->m_atk, Monster[2]->m_def, Monster[2]->m_exp));
	this->addChild(HP3, 1);

	class3 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	class3->setColor(Color3B(255, 0, 0));
	class3->setPosition(Vec2(visibleSize.width / 12 * 4, visibleSize.height / 6 * 5 + 95));
	if (Monster[2]->m_job == 0)
		class3->setString(StringUtils::format("No.3 Saber"));
	if (Monster[2]->m_job == 1)
		class3->setString(StringUtils::format("No.3 Lancer"));
	if (Monster[2]->m_job == 2)
		class3->setString(StringUtils::format("No.3 Archer"));
	this->addChild(class3, 1);

	if (Monster[2]->m_job == 0)
		monSprite[2] = Sprite::create("saber2.png");
	if (Monster[2]->m_job == 1)
		monSprite[2] = Sprite::create("lancer2.png");
	if (Monster[2]->m_job == 2)
		monSprite[2] = Sprite::create("archer2.png");
	monSprite[2]->setPosition(Vec2(visibleSize.width / 12 * 4, visibleSize.height / 3));
	go(i, 0, 2) {
		monSprite[i]->setScale(0.5);
		this->addChild(monSprite[i]);
	}

	HP0 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	HP0->setColor(Color3B(255, 0, 0));
	HP0->setPosition(Vec2(visibleSize.width / 22 * 20, visibleSize.height / 6 * 5));
	HP0->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nNP: %d", Hero->h_health, Hero->h_atk + (Hero->sword != NULL ? Hero->sword->getATK() : 0), Hero->h_def + (Hero->shield != NULL ? Hero->shield->getDEF() : 0), Hero->NP));
	this->addChild(HP0, 1);

	class0 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 34);//白色字体
	class0->setColor(Color3B(255, 0, 0));
	class0->setPosition(Vec2(visibleSize.width / 22 * 20, visibleSize.height / 6 * 5 + 95));
	if (Hero->h_job == 0)
		class0->setString(StringUtils::format("Saber"));
	if (Hero->h_job == 1)
		class0->setString(StringUtils::format("Lancer"));
	if (Hero->h_job == 2)
		class0->setString(StringUtils::format("Archer"));
	this->addChild(class0, 1);
	
	button1 = MenuItemImage::create(
		"ch1.png",
		"ch10.png",
		CC_CALLBACK_1(FightScene::goto1, this));
	auto ch1 = Menu::create(button1, NULL);
	ch1->setAnchorPoint(Vec2(0, 0));
	ch1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 6));
	ch1->setScale(0.6f);
	this->addChild(ch1, 3);

	button2 = MenuItemImage::create(
		"ch2.png",
		"ch20.png",
		CC_CALLBACK_1(FightScene::goto2, this));
	auto ch2 = Menu::create(button2, NULL);
	ch2->setAnchorPoint(Vec2(0, 0));
	ch2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 6*2));
	ch2->setScale(0.6f);
	this->addChild(ch2, 3);

	button3 = MenuItemImage::create(
		"ch3.png",
		"ch30.png",
		CC_CALLBACK_1(FightScene::goto3, this));
	auto ch3 = Menu::create(button3, NULL);
	ch3->setAnchorPoint(Vec2(0, 0));
	ch3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 6*3));
	ch3->setScale(0.6f);
	this->addChild(ch3, 3);

	button4 = MenuItemImage::create(
		"ch4.png",
		"ch40.png",
		CC_CALLBACK_1(FightScene::goto4, this));
	if (Hero->NP < 100)
		button4->setEnabled(false);
	auto ch4 = Menu::create(button4, NULL);
	ch4->setAnchorPoint(Vec2(0, 0));
	ch4->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 6 * 5));
	ch4->setScale(0.6f);
	this->addChild(ch4, 3);

	button5 = MenuItemImage::create(
		"ch5.png",
		"ch50.png",
		CC_CALLBACK_1(FightScene::goto5, this));
	auto ch5 = Menu::create(button5, NULL);
	ch5->setAnchorPoint(Vec2(0, 0));
	ch5->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 6 * 4));
	ch5->setScale(0.6f);
	this->addChild(ch5, 3);
	return true;
}

bool FightScene::all_death() {
	bool flag = 1;
	go(i, 0, 2)
		if (!Monster[i]->is_death())
			flag = 0;
	return flag;
}

void FightScene::goto1(Ref* temp)
{
	Monster[0]->be_attacked(Hero->h_atk, *Hero);
	Hero->NP += 30;
	if (all_death()) {
		//director->popToRootScene();
		auto glview = Director::getInstance()->getOpenGLView();
		glview->setFrameSize(1024, 768);
		TMap->getLayer("Monster")->removeTileAt(NextPos);
		director->popScene();
		director->popScene();
	}
	go(i, 0, 2) {
		if (!Monster[i]->is_death()) {
			Hero->be_attacked(Monster[i]->m_atk, *Monster[i]);
		}
	}
	if (Hero->NP > 500)
		Hero->NP = 500;
	HP1->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster[0]->m_health, Monster[0]->m_atk, Monster[0]->m_def, Monster[0]->m_exp));
	HP0->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nNP: %d", Hero->h_health, Hero->h_atk + (Hero->sword != NULL ? Hero->sword->getATK() : 0), Hero->h_def + (Hero->shield != NULL ? Hero->shield->getDEF() : 0), Hero->NP));
	if (Monster[0]->is_death()) {
		button1->setEnabled(false);
	}
	if (Hero->NP < 100)
		button4->setEnabled(false);
	else
		button4->setEnabled(true);
	if (Hero->is_death()) {
		director->replaceScene(Over::createScene());
	}
}

void FightScene::goto2(Ref* temp)
{
	Monster[1]->be_attacked(Hero->h_atk, *Hero);
	Hero->NP += 30;
	if (all_death()) {
		//director->popToRootScene();
		auto glview = Director::getInstance()->getOpenGLView();
		glview->setFrameSize(1024, 768);
		TMap->getLayer("Monster")->removeTileAt(NextPos);
		director->popScene();
		director->popScene();
	}
	go(i, 0, 2) {
		if (!Monster[i]->is_death()) {
			Hero->be_attacked(Monster[i]->m_atk, *Monster[i]);
		}
	}
	if (Hero->NP > 500)
		Hero->NP = 500;
	HP2->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster[1]->m_health, Monster[1]->m_atk, Monster[1]->m_def, Monster[1]->m_exp));
	HP0->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nNP: %d", Hero->h_health, Hero->h_atk + (Hero->sword != NULL ? Hero->sword->getATK() : 0), Hero->h_def + (Hero->shield != NULL ? Hero->shield->getDEF() : 0), Hero->NP));
	if (Monster[1]->is_death()) {
		button2->setEnabled(false);
	}
	if (Hero->NP < 100)
		button4->setEnabled(false);
	else
		button4->setEnabled(true);
	if (Hero->is_death()) {
		director->replaceScene(Over::createScene());
	}
}

void FightScene::goto3(Ref* temp)
{
	Monster[2]->be_attacked(Hero->h_atk, *Hero);
	Hero->NP += 30;
	if (all_death()) {
		auto glview = Director::getInstance()->getOpenGLView();
		glview->setFrameSize(1024, 768);
		TMap->getLayer("Monster")->removeTileAt(NextPos);
		director->popToRootScene();
	}
	go(i, 0, 2) {
		if (!Monster[i]->is_death()) {
			Hero->be_attacked(Monster[i]->m_atk, *Monster[i]);
		}
	}
	if (Hero->NP > 500)
		Hero->NP = 500;
	HP3->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster[2]->m_health, Monster[2]->m_atk, Monster[2]->m_def, Monster[2]->m_exp));
	HP0->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nNP: %d", Hero->h_health, Hero->h_atk + (Hero->sword != NULL ? Hero->sword->getATK() : 0), Hero->h_def + (Hero->shield != NULL ? Hero->shield->getDEF() : 0), Hero->NP));
	if (Monster[2]->is_death()) {
		button3->setEnabled(false);
	}
	if (Hero->NP < 100)
		button4->setEnabled(false);
	else
		button4->setEnabled(true);
	if (Hero->is_death()) {
		director->replaceScene(Over::createScene());
	}
}

void FightScene::goto4(Ref* temp)
{
	director->pushScene(nextPage1::createScene(Hero->h_job));
	Hero->NP -= 100;
	go(i, 0, 2) {
		Monster[i]->be_attacked(2 * Hero->h_atk, *Hero);
		if (!Monster[i]->is_death()) {
			Hero->be_attacked(Monster[i]->m_atk, *Monster[i]);
		}
	}
	if (Hero->NP > 500)
		Hero->NP = 500;
	if (Monster[0]->is_death()) {
		button1->setEnabled(false);
	}
	if (Monster[1]->is_death()) {
		button2->setEnabled(false);
	}
	if (Monster[2]->is_death()) {
		button3->setEnabled(false);
	}
	HP1->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster[0]->m_health, Monster[0]->m_atk, Monster[0]->m_def, Monster[0]->m_exp));
	HP2->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster[1]->m_health, Monster[1]->m_atk, Monster[1]->m_def, Monster[1]->m_exp));
	HP3->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nEXP: %d", Monster[2]->m_health, Monster[2]->m_atk, Monster[2]->m_def, Monster[2]->m_exp));
	HP0->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nNP: %d", Hero->h_health, Hero->h_atk + (Hero->sword != NULL ? Hero->sword->getATK() : 0), Hero->h_def + (Hero->shield != NULL ? Hero->shield->getDEF() : 0), Hero->NP));
	if (Hero->NP < 100)
		button4->setEnabled(false);
	else
		button4->setEnabled(true);
	if (Hero->is_death()) {
		director->replaceScene(Over::createScene());
	}
	if (all_death()) {
		auto glview = Director::getInstance()->getOpenGLView();
		glview->setFrameSize(1024, 768);
		TMap->getLayer("Monster")->removeTileAt(NextPos);
		director->popToRootScene();
	}
}

void FightScene::goto5(Ref* temp)
{
	go(i, 0, 2) {
		if (!Monster[i]->is_death()) {
			Hero->be_attacked(Monster[i]->m_atk / 2, *Monster[i]);
		}
	}
	Hero->NP += 40;
	if (Hero->NP > 500)
		Hero->NP = 500;
	HP0->setString(StringUtils::format("HP: %d\nATK: %d\nDEF: %d\nNP: %d", Hero->h_health, Hero->h_atk + (Hero->sword != NULL ? Hero->sword->getATK() : 0), Hero->h_def + (Hero->shield != NULL ? Hero->shield->getDEF() : 0), Hero->NP));
	if (Hero->NP < 100)
		button4->setEnabled(false);
	else
		button4->setEnabled(true);
	if (Hero->is_death()) {
		director->replaceScene(Over::createScene());
	}
}

