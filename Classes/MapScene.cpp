#include"MapScene.h"
#include"MyMenu.h"
//USING_NS_CC;

Scene* MapScene::createScene() {
	auto scene = Scene::create();
	auto layer = MapScene::create();
	scene->addChild(layer);
	return scene;
}

bool MapScene::init() {
	if (!Layer::init())
	{
		return false;
	}

	Size VisibleSize = Director::getInstance()->getVisibleSize();	//�����Ļ��С

	auto label = Label::createWithSystemFont("this is my mysecondscene!,great!!!", "fonts/arial.ttf", 30);

	//�������ְ�ť
	auto menuitem = MenuItemLabel::create(label, CC_CALLBACK_1(MapScene::comeback, this));
	//�������õİ�ťװ��˵���Ŀ ,�������ص�����
	auto menu = Menu::create(menuitem, NULL);
	//����Ŀװ��ϵͳ�Ĳ˵���
	this->addChild(menu);

	/*//����ͼƬ�ص�
	auto label2 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseNormal.png",
		this,
		menu_selector(mysecondscene::comeback2)
	);*/
	//auto menuitem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(mysecondscene::comeback2, this));
	//label2->setPositionX(1800);
	//auto menu2 = Menu::create(label2, NULL);

	//this->addChild(menu2);   //װ���

	return true;
}

void MapScene::comeback(Ref* temp) {
}