#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class MyMenu :public Layer {//����Layer��
private:
	Director* director;
	Size visibleSize;
	Vec2 origin;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MyMenu);//����һ��create����
	void comeback(Ref* Psendeer);//�ص�����
	void wudi(Ref* Psendeer);
	void ExitGame(Ref* pSender);
};