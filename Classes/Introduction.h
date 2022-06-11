#pragma once
#include<cocos2d.h>
using namespace cocos2d;

class Introduction 
	:public Scene
{
public:
	int id;
	//≥ı ºªØ
	bool init(int id);
	//πÿ±’
	void Close(Ref* pSender);
	static Introduction* create(int id);
	Introduction() {};
};

