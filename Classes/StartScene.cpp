#include "StartScene.h"

//创建场景
Scene* StartScene::createScene()
{
	return StartScene::create();
}
//初始化
bool StartScene::init()
{
    //Scene初始化
    if (!Scene::init())
    {
        return false;
    }
    //背景添加
    auto Background = Sprite::create("StartScene.png");
    Background->setPosition(512, 384);
    addChild(Background,0);

    //创建按钮
    auto StartItem = MenuItemImage::create(
        "Start.png",
        "Start1.png",
        CC_CALLBACK_1(StartScene::StartGame, this));

    auto IntroItem= MenuItemImage::create(
        "Introduction.png",
        "Introduction1.png",
        CC_CALLBACK_1(StartScene::StartGame, this));

    auto SettingItem = MenuItemImage::create(
        "Setting.png",
        "Setting1.png",
        CC_CALLBACK_1(StartScene::StartGame, this));

   //设置按钮属性
    if (StartItem== nullptr){
        log("StartScene Loading Failed");
    }

    auto Start = Menu::create(StartItem, NULL);
    Start->setPosition(512,400);
    this->addChild(Start, 1);
    
    auto Introduction = Menu::create(IntroItem, NULL);
    Introduction->setPosition(512, 300);
    this->addChild(Introduction, 1);

    auto Settings= Menu::create(SettingItem, NULL);
    Settings->setPosition(500, 200);
    this->addChild(Settings, 1);

    return true;
}

void StartScene::StartGame(Ref* pSender)
{
    auto scene = GameMap::create(0);
    Director::getInstance()->replaceScene(scene);
}