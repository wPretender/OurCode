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
    //���
    enum itemtype { Sword, Shield };
    //��������
    static item* create();
    static item* create(string image, int type);
    //ʰȡ����
    virtual void PickedUp(hero& Hero);
    //��ȡ������
    int getATK() const;
    //��ȡ������
    int getDEF() const;
    //��ȡ�ļ�
    string getFile() const;
    //��������
    void setProperty(int atk, int def);
    //��ȡ����
    Sprite* getSprite() const;
    //�����б�
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
