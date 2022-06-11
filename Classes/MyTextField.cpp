#include "MyTextField.h"

Scene* MyTextField::createScene()
{
	return MyTextField::create();
}

bool MyTextField::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//按钮创建
	go = Button::create("CloseNormal.png", "CloseSelected.png", "CloseNormal.png");
	this->addChild(go);
	//权限默认为不能按
	go->setEnabled(false);
	//账号文本框初始化
	id = MyTextField::create();
	//设置账号文本框字体
	id->setFontName("arial");
	//设置文本框大小
	id->setFontSize(36);

	//设置账号文本框默认显示
	auto _id = String::create(MyTextField::FontToUTF8("请输入您的账号"));
	id->setPlaceHolder(_id->getCString());

	//设置显示颜色
	id->setColor(Color3B::RED);
	this->addChild(id);

	//设置账号文本框坐标
	id->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	id->setPosition(put_in->getPosition() + Vec2(30, -50));

	//设置密码文本框
	key = MyTextField::create();
	key->setFontName("arial");
	key->setFontSize(36);
	auto _key = String::create(MyTextField::FontToUTF8("请输入您的密码"));
	key->setPlaceHolder(_key->getCString());
	key->setColor(Color3B::RED);
	this->addChild(key);
	key->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	key->setPosition(put_in->getPosition() + Vec2(30, -160));

	//设置按钮的权限根据账号密码改动
	key->addEventListener([&](Ref* ref, ui::MyTextField::EventType type)
		{
			//类型转换
			auto temp = dynamic_cast<MyTextField*>(ref);

			//初始化设定为账号和密码大于8位才能使用go按钮进行登录
			if (temp->getStringLength() > 8 && id->getStringLength() > 8)
			{
				go->setEnabled(true);
			}
			else   //如果少了就设置为不可按
			{
				go->setEnabled(false);
			}
		});

	//设置按钮事件
	go->addTouchEventListener([&](Ref* ref, ui::Button::TouchEventType type)
		{
			if (type == Button::TouchEventType::ENDED)
			{
				Director::getInstance()->replaceScene(loding::createScene());
			}
		});
	go->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	go->setPosition(key->getPosition() + Vec2(0, -100));
	return true;
}
