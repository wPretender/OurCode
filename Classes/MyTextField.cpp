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
	//��ť����
	go = Button::create("CloseNormal.png", "CloseSelected.png", "CloseNormal.png");
	this->addChild(go);
	//Ȩ��Ĭ��Ϊ���ܰ�
	go->setEnabled(false);
	//�˺��ı����ʼ��
	id = MyTextField::create();
	//�����˺��ı�������
	id->setFontName("arial");
	//�����ı����С
	id->setFontSize(36);

	//�����˺��ı���Ĭ����ʾ
	auto _id = String::create(MyTextField::FontToUTF8("�����������˺�"));
	id->setPlaceHolder(_id->getCString());

	//������ʾ��ɫ
	id->setColor(Color3B::RED);
	this->addChild(id);

	//�����˺��ı�������
	id->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	id->setPosition(put_in->getPosition() + Vec2(30, -50));

	//���������ı���
	key = MyTextField::create();
	key->setFontName("arial");
	key->setFontSize(36);
	auto _key = String::create(MyTextField::FontToUTF8("��������������"));
	key->setPlaceHolder(_key->getCString());
	key->setColor(Color3B::RED);
	this->addChild(key);
	key->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	key->setPosition(put_in->getPosition() + Vec2(30, -160));

	//���ð�ť��Ȩ�޸����˺�����Ķ�
	key->addEventListener([&](Ref* ref, ui::MyTextField::EventType type)
		{
			//����ת��
			auto temp = dynamic_cast<MyTextField*>(ref);

			//��ʼ���趨Ϊ�˺ź��������8λ����ʹ��go��ť���е�¼
			if (temp->getStringLength() > 8 && id->getStringLength() > 8)
			{
				go->setEnabled(true);
			}
			else   //������˾�����Ϊ���ɰ�
			{
				go->setEnabled(false);
			}
		});

	//���ð�ť�¼�
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
