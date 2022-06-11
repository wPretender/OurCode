#include"Victory.h"

Scene* Victory::createScene() {
	Scene* MyScene = Scene::create();
	auto MyLayer = Victory::create();
	MyScene->addChild(MyLayer);
	return MyScene;
}

bool Victory::init() {
	if (!Layer::init())
		return false;
	director = Director::getInstance();
	visibleSize = director->getVisibleSize();//获取屏幕大小
	origin = director->getVisibleOrigin();

	auto bgSprite = Sprite::create("victory.png");
	bgSprite->setAnchorPoint(Vec2(0, 0));
	bgSprite->setScale(visibleSize.height / bgSprite->getContentSize().height, visibleSize.width / bgSprite->getContentSize().width);
	bgSprite->setPosition(Vec2(0, 0));
	this->addChild(bgSprite, 0);


	auto nextItem = MenuItemImage::create(
		"end.png",
		"end.png",
		CC_CALLBACK_1(Victory::goto1, this));
	auto menu = Menu::create(nextItem, NULL);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(visibleSize.width / 2, 75));
	menu->setScale(0.3f);
	this->addChild(menu, 2);

	return true;
}

void Victory::goto1(Ref* Psendeer) {
	exit(0);
}