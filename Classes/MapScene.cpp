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

	Size VisibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小

	auto label = Label::createWithSystemFont("this is my mysecondscene!,great!!!", "fonts/arial.ttf", 30);

	//创建文字按钮
	auto menuitem = MenuItemLabel::create(label, CC_CALLBACK_1(MapScene::comeback, this));
	//将创建好的按钮装入菜单条目 ,并创建回调函数
	auto menu = Menu::create(menuitem, NULL);
	//将条目装入系统的菜单里
	this->addChild(menu);

	/*//创建图片回调
	auto label2 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseNormal.png",
		this,
		menu_selector(mysecondscene::comeback2)
	);*/
	//auto menuitem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(mysecondscene::comeback2, this));
	//label2->setPositionX(1800);
	//auto menu2 = Menu::create(label2, NULL);

	//this->addChild(menu2);   //装入层

	return true;
}

void MapScene::comeback(Ref* temp) {
}