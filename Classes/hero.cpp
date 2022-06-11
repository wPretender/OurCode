#include "hero.h"
#include"monster.h"
#include"item.h"

hero* hero::create() {
	hero* pRet = new(std::nothrow) hero();
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
}

hero* hero::create(const hero& Hero) 
{
	auto newHero = hero::create();
	newHero->h_image = Hero.h_image;
	newHero->NP = Hero.NP;
	newHero->setProperty(Hero.h_health, Hero.h_atk, Hero.h_def, Hero.h_exp,Hero.h_level, Hero.yellow_key, Hero.orange_key);
	return newHero;
}

hero::hero()
{
	log("Hero creating");
	h_image = Sprite::create("Braver.png");
	this->addChild(h_image);
	sword = NULL;
	shield = NULL;
	if (h_image == NULL)
		log("Fail to create");
	else
		log("Hero created");
}

bool hero::init()
{
	if (!h_image)
		return false;
	return true;
}

//图像函数
void hero::setImage(string image)
{
	delete h_image;
	h_image = Sprite::create(image);
	sword = NULL;
	shield = NULL;
	this->addChild(h_image);
}

Sprite* hero::getSprite()
{
	return h_image;
}

void hero::be_attacked(int atk, monster& mon)
{
	int ac = mon.m_job;
	int bc = h_job;
	NP += 15;
	if ((ac + 1) % 3 == bc) {
		atk = atk * 2;
	}
	else if ((bc + 1) % 3 == ac) {
		atk = atk / 2;
	}
	if (atk > h_def + (shield != NULL ? shield->getDEF() : 0))
		h_health -= (atk - h_def - (shield != NULL ? shield->getDEF() : 0));
	if (h_health <= 0)
		h_health = 0;
}

bool hero::is_death() const
{
	return h_health == 0;
}

void hero::setProperty(int health, int atk, int def, int exp, int level, int ykey, int bkey)
{
	h_health = health;
	h_atk = atk;
	h_def = def;
	h_exp = exp;
	h_level = level;
	yellow_key = ykey;
	orange_key = bkey;
}

void hero::addProperty(int health, int atk, int def, int exp)
{
	h_health += health;
	h_atk += atk;
	h_def += def;
	h_exp += exp;
	if (h_exp == h_level * LEVELUP) {
		h_exp = 0;
		h_health += h_level;
		h_atk += h_level;
		h_def += h_level;
		h_level++;
	}
}

void hero::pick_keys(int ykey, int okey)
{
	yellow_key += ykey;
	orange_key += okey;
}

void hero::move(MoveTo* moveto)
{
	h_image->runAction(moveto);
}

//获取当前位置
Vec2 hero::getPostion()
{
	return h_image->getPosition();
}

//设定位置
void hero::setPosition(Vec2 pos)
{
	h_image->setPosition(pos);
}

//装备拾取函数
void hero::equip(item& Item)
{
	Item.PickedUp(*this);
}

//开锁函数
bool hero::unlock(bool color)
{
	if (color == YELLOWKEY && yellow_key) {
		yellow_key--;
		return true;
	}

	if (color == BLUEKEY && orange_key) {
		orange_key--;
		return true;
	}

	return false;
}