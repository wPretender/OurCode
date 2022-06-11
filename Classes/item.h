#pragma once
#include<cocos2d.h>
#include<string>
using namespace std;
using namespace cocos2d;

class hero;

class item :
    public Node
{
public:
    //类别
    enum itemtype { Sword, Shield };
    //创建函数
    static item* create();
    static item* create(string image, int type);
    //拾取函数
    virtual void PickedUp(hero& Hero);
    //获取攻击力
    int getATK() const;
    //获取防御力
    int getDEF() const;
    //获取文件
    string getFile() const;
    //设置属性
    void setProperty(int atk, int def);
    //获取精灵
    Sprite* getSprite() const;
    //类型判别
    int getItemtype();
protected:
    Sprite* _image;
    string _file;
    int _health;
    int _atk;
    int _def;
    int _exp;
    int _type;
    item(string image);
};
