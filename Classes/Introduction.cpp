#include "Introduction.h"
#include "GameMap.h"

Introduction* Introduction::create(int id) {
	Introduction* pRet = new(std::nothrow) Introduction();
	//如果当前对象内存分配成功，并且初始化成功
	if (pRet && pRet->init(id))
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

bool Introduction::init(int id)
{
	if (!Scene::init())
		return false;
	this->id = id;
	//背景故事部分
	auto bgintro = Label::createWithSystemFont("You      wake up in an unknown rouge.Try your best to escape alive.", "Arial", 30);
	bgintro->setPosition(512, 700);
	addChild(bgintro);
	//操作介绍
	auto ctrlintro = Label::createWithSystemFont("Use WASD to move up,down,left and right", "Arial", 30);
	ctrlintro->setPosition(350, 600);
	addChild(ctrlintro);
	//物品介绍
	auto itemintro = Label::createWithSystemFont("are keys to unlock\n\n\n+50 health or 1/20 health\n\n\n+10 ATK or 1/20 atk\n\n\n+10 DEF or 1/20 DEF", "Arial", 30);
	itemintro->setPosition(350, 350);
	addChild(itemintro);
	//怪物介绍
	auto monsterintro = Label::createWithSystemFont("is monsters' camp,each has 3 monsters inside\n\nmeans a boss fight.", "Arial", 30);
	monsterintro->setPosition(530, 80);
	addChild(monsterintro);

	//图像
	//背景
	auto background = Sprite::create("Background.png");
	background->setPosition(512, 389);
	addChild(background, -1);
	//玩家图像
	auto player = Sprite::create("Braver.png");
	player->setPosition(142, 700);
	addChild(player);
	//道具图像
	auto redbottle = Sprite::create("RedBottle.png");
	redbottle->setPosition(150, 400);
	redbottle->setScale(2, 2);
	addChild(redbottle);

	auto banana = Sprite::create("Banana.png");
	banana->setPosition(150, 300);
	banana->setScale(2, 2);
	addChild(banana);

	auto hamburger = Sprite::create("Hamburger.png");
	hamburger->setPosition(150, 200);
	hamburger->setScale(2, 2);
	addChild(hamburger);
	//敌人图像
	auto monster = Sprite::create("Monster.png");
	monster->setPosition(150, 120);
	monster->setScale(2, 2);
	addChild(monster);

	auto boss = Sprite::create("Boss.png");
	boss->setPosition(150, 40);
	boss->setScale(2, 2);
	addChild(boss);

	auto yellowkey = Sprite::create("yellowkey.png");
	yellowkey->setPosition(190, 500);
	yellowkey->setScale(2, 2);
	addChild(yellowkey);

	auto yellowlock = Sprite::create("yellowlock.png");
	yellowlock->setPosition(600, 500);
	yellowlock->setScale(2, 2);
	addChild(yellowlock);

	auto orangekey = Sprite::create("orangekey.png");
	orangekey->setPosition(120, 500);
	orangekey->setScale(2, 2);
	addChild(orangekey);

	auto orangelock = Sprite::create("orangelock.png");
	orangelock->setPosition(520, 500);
	orangelock->setScale(2, 2);
	addChild(orangelock);

	auto visibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小
	auto temp3 = MenuItemImage::create(
		"next.png",
		"next.png",
		CC_CALLBACK_1(Introduction::Close, this));
	auto ch = Menu::create(temp3, NULL);
	ch->setAnchorPoint(Vec2(0, 0));
	ch->setPosition(Vec2(visibleSize.width / 3 * 2, visibleSize.height / 3));
	ch->setScale(1);
	this->addChild(ch, 3);

	return true;
}

void Introduction::Close(Ref* pSender) {
	Director::getInstance()->replaceScene(GameMap::create(id));
}