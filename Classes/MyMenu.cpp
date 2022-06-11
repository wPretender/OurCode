#include"MyMenu.h"
#include"FightMenu.h"
#include"GameMap.h"
#include "Introduction.h"

Scene* MyMenu::createScene() {
	Scene* MyScene = Scene::create();
	auto MyLayer = MyMenu::create();
	MyScene->addChild(MyLayer);
	return MyScene;
}

bool MyMenu::init() {
	if (!Layer::init())
		return false;
	director = Director::getInstance();
	visibleSize = director->getVisibleSize();//获取屏幕大小
	origin = director->getVisibleOrigin();
	
	srand(time(0));
	auto bgSprite = Sprite::create("main.png");
	bgSprite->setAnchorPoint(Vec2(0, 0));
	bgSprite->setScale(visibleSize.height / bgSprite->getContentSize().height, visibleSize.width / bgSprite->getContentSize().width);
	bgSprite->setPosition(Vec2(0,0));
	this->addChild(bgSprite, 0);

	auto* saber= Sprite::create("sprite.png");
	saber->setPosition(Vec2(visibleSize.width/9*8, visibleSize.height / 9 * 7));
	saber->setScale(0.2f);
	this->addChild(saber, 1);

	auto nextItem = MenuItemImage::create(
		"button1.png",
		"button2.png",
		CC_CALLBACK_1(MyMenu::comeback, this));
	auto menu = Menu::create(nextItem, NULL);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(visibleSize.width / 2, 100));
	menu->setScale(0.5f);
	this->addChild(menu, 2);

	auto nextItem1 = MenuItemImage::create(
		"button3.png",
		"button3.png",
		CC_CALLBACK_1(MyMenu::wudi, this));
	auto menu1 = Menu::create(nextItem1, NULL);
	menu1->setAnchorPoint(Vec2(0, 0));
	menu1->setPosition(Vec2(238, 148));
	menu1->setScale(0.9f);
	this->addChild(menu1, 2);

	return true;
}

void MyMenu::comeback(Ref* Psendeer) {
	auto glview = director->getOpenGLView();
	glview->setFrameSize(1024, 768);
	director->replaceScene(TransitionJumpZoom::create(3.0f, Introduction::create(0)));
}

void MyMenu::wudi(Ref* Psendeer) {
	auto glview = director->getOpenGLView();
	glview->setFrameSize(1024, 768);
	director->replaceScene(TransitionJumpZoom::create(3.0f, Introduction::create(1)));
}