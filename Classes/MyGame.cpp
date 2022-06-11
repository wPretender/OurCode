#include"MyGame.h"

MyGame::MyGame() {}
MyGame::~MyGame() {}

Scene* MyGame::createScene() {
	Scene* MyScene = Scene::create();
	auto MyLayer = MyGame::create();
	MyScene->addChild(MyLayer);
	TransitionCrossFade* crossFade = TransitionCrossFade::create(3.0, MyScene);//���䳡����Ч
	return crossFade;
}

bool MyGame::init() {
	if (!Layer::init())
		return false;
	director = Director::getInstance();
	visibleSize = director->getVisibleSize();
	origin = director->getVisibleOrigin();

	Sprite* bgSprite = Sprite::create("main.png");//����
	bgSprite->setAnchorPoint(Vec2::ZERO);
	bgSprite->setScale(visibleSize.height / bgSprite->getContentSize().height, visibleSize.width / bgSprite->getContentSize().width);
	bgSprite->setPosition(Vec2(0, 0));
	this->addChild(bgSprite);

	//����
	Sprite* fSprite = Sprite::create("sprite.png");
	fSprite->setPosition(visibleSize / 2);
	this->addChild(fSprite);

	/*��ӷ�����һ�����İ�ť
	MenuItemImage* backItem = MenuItemImage::create("Buttons//BackButton.png", "Buttons//BackButtonSelected.png", CC_CALLBACK_0(MyGame::backButton, this));
	Menu* menu = Menu::create(backItem, NULL);
	menu->setAnchorPoint(Vec2::ONE);
	menu->setPosition(visibleSize.width - backItem->getContentSize().width / 2, visibleSize.height - backItem->getContentSize().height / 2);
	this->addChild(menu);
	*/
}

void MyGame::backButton() {//���÷�����һ�����İ�ť
	director->popScene();
}