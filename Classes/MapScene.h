#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class MapScene :public Layer {//����Layer��
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MapScene);//����һ��create����
	void comeback(Ref* temp);//�ص�����
	void comeback2(Ref* temp);  //�ص�����2
};