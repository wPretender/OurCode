#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Over :public Layer {//����Layer��
private:
	Director* director;
	Size visibleSize;
	Vec2 origin;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Over);//����һ��create����
	void goto1(Ref* Psendeer);//�ص�����
};