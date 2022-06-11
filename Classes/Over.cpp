#include"Over.h"

Scene* Over::createScene() {
	Scene* MyScene = Scene::create();
	auto MyLayer = Over::create();
	MyScene->addChild(MyLayer);
	return MyScene;
}

bool Over::init() {
	if (!Layer::init())
		return false;
	director = Director::getInstance();
	visibleSize = director->getVisibleSize();//��ȡ��Ļ��С
	origin = director->getVisibleOrigin();

	auto bgSprite = Sprite::create("defeat.png");
	bgSprite->setAnchorPoint(Vec2(0, 0));
	bgSprite->setScale(visibleSize.height / bgSprite->getContentSize().height, visibleSize.width / bgSprite->getContentSize().width);
	bgSprite->setPosition(Vec2(0, 0));
	this->addChild(bgSprite, 0);


	auto nextItem = MenuItemImage::create(
		"end.png",
		"end.png",
		CC_CALLBACK_1(Over::goto1, this));
	auto menu = Menu::create(nextItem, NULL);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(visibleSize.width / 2, 75));
	menu->setScale(0.3f);
	this->addChild(menu, 2);

	return true;
}

void Over::goto1(Ref* Psendeer) {
	exit(0);
}