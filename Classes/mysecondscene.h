#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class mysecondscene :public Layer
{
public:
	static Scene* createScene();//�ܹ�����
	virtual bool init();  //����ʵ��
	CREATE_FUNC(mysecondscene); //������Ŀ
	void comeback(Ref* temp);  //�ص�����
};