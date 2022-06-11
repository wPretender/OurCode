#include "mysecondscene.h"
#include "MyMenu.h"
//同样调用第一个场景的头文件进行场景切换

Scene* mysecondscene::createScene()  //架构场景
{
	auto scene = Scene::create();
	auto layer = mysecondscene::create();
	scene->addChild(layer);
	return scene;
}

bool mysecondscene::init()   //层的实现
{
	if (!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小
	//auto map = TMXTiledMap::create("map2.tmx");
	//this->addChild(map, 0);

	return true;
}

void mysecondscene::comeback(Ref* temp)  //切换场景回调函数1
{
	Director::getInstance()->replaceScene(MyMenu::createScene());
}