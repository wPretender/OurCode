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
	//���캯��
	hero();
	hero(const hero& Hero);
	//��������
	~hero() {};
	//��ʼ������
	bool init();
	//ͼ����
	void setImage(string image);
	//��ȡ����
	Sprite* getSprite();
	//�ܻ�����
	void be_attacked(int atk, monster& mon);
	//��������
	void setProperty(int health, int atk, int def, int exp = 0, int level = 1, int ykey = 0, int bkey = 0);
	//�ӳɺ���
	void addProperty(int health, int atk, int def, int exp);
	//ʰȡԿ�׺���
	void pick_keys(int ykey, int bkey);
	//�ж��Ƿ�����
	bool is_death() const;
	//�ƶ�����
	void move(MoveTo* moveto);
	//��ȡ��ǰλ��
	Vec2 getPostion();
	//�趨λ��
	void setPosition(Vec2 pos);
	//װ��ʰȡ����
	void equip(item& Item);
	//��������
	bool unlock(bool color);
	//��ȡְ��
	//�������ݳ�Ա
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
	//��ö���ָ��
	static hero* create();
	static hero* create(const hero& Hero);
	item* sword;
	item* shield;
};
