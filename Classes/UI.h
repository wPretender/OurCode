#pragma once
#include<cocos2d.h>
using namespace cocos2d;

class hero;

class UI
	:public Layer
{
public:

	//��ʼ������
	bool init();
	void AcquireHero(hero* Hero);
	static UI* create(hero* Hero);

private:
	hero* Hero;
};
