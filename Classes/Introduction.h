#pragma once
#include<cocos2d.h>
using namespace cocos2d;

class Introduction 
	:public Scene
{
public:
	int id;
	//��ʼ��
	bool init(int id);
	//�ر�
	void Close(Ref* pSender);
	static Introduction* create(int id);
	Introduction() {};
};

