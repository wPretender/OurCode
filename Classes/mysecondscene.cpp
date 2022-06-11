#include "mysecondscene.h"
#include "MyMenu.h"
//ͬ�����õ�һ��������ͷ�ļ����г����л�

Scene* mysecondscene::createScene()  //�ܹ�����
{
	auto scene = Scene::create();
	auto layer = mysecondscene::create();
	scene->addChild(layer);
	return scene;
}

bool mysecondscene::init()   //���ʵ��
{
	if (!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();	//�����Ļ��С
	//auto map = TMXTiledMap::create("map2.tmx");
	//this->addChild(map, 0);

	return true;
}

void mysecondscene::comeback(Ref* temp)  //�л������ص�����1
{
	Director::getInstance()->replaceScene(MyMenu::createScene());
}