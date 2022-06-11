#pragma once
#include<cocos2d.h>
#include<string>
//#include"UI.h"
using namespace cocos2d;
using namespace std;

#define LEVELUP 100
#define UNIT_DISTANCE 32
#define YELLOWKEY 0
#define BLUEKEY 1

using namespace std;
using namespace cocos2d;

class monster;
class item;

class hero : public Node
{
private:
	Sprite* h_image;
	Vec2 h_pos;
	friend class UI;
public:
	//构造函数
	hero();
	hero(const hero& Hero);
	//析构函数
	~hero() {};
	//初始化函数
	bool init();
	//图像函数
	void setImage(string image);
	//获取精灵
	Sprite* getSprite();
	//受击函数
	void be_attacked(int atk, monster& mon);
	//设置属性
	void setProperty(int health, int atk, int def, int exp = 0, int level = 1, int ykey = 0, int bkey = 0);
	//加成函数
	void addProperty(int health, int atk, int def, int exp);
	//拾取钥匙函数
	void pick_keys(int ykey, int bkey);
	//判断是否死亡
	bool is_death() const;
	//移动函数
	void move(MoveTo* moveto);
	//获取当前位置
	Vec2 getPostion();
	//设定位置
	void setPosition(Vec2 pos);
	//装备拾取函数
	void equip(item& Item);
	//开锁函数
	bool unlock(bool color);
	//获取职阶
	//公有数据成员
	bool canMove;
	int h_job;
	int h_health;
	int h_atk;
	int h_def;
	int h_exp;
	int h_level;
	int yellow_key;
	int orange_key;
	int NP = 0;
	//获得对象指针
	static hero* create();
	static hero* create(const hero& Hero);
	item* sword;
	item* shield;
};
