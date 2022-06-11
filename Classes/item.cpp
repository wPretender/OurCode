#include "item.h"
#include<cocos2d.h>
#include<string>
#include"hero.h"
using namespace std;
using namespace cocos2d;

item::item(string image)
{
	_image = Sprite::create(image);
	this->addChild(_image);
}

/*item* item::create()
{
	item* pRet = new(std::nothrow) item();
	//如果当前对象内存分配成功，并且初始化成功
	if (pRet && pRet->init())
	{
		//pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}*/

item* item::create(string image, int type)
{
	item* Item = new(std::nothrow) item(image);
	if (Item) {
		Item->_file = image;
		Item->_type = type;
		log("succeeded");
		return Item;

	}
	log("failed");
	return NULL;
}

void item::PickedUp(hero& Hero)
{
	Hero.addProperty(_health, _atk, _def, _exp);
}

int item::getATK() const
{
	return _atk;
}

int item::getDEF() const
{
	return _def;
}

Sprite* item::getSprite() const
{
	return _image;
}

string item::getFile() const
{
	return _file;
}

void item::setProperty(int atk, int def)
{
	_atk = atk;
	_def = def;
}

int item::getItemtype()
{
	return _type;
}