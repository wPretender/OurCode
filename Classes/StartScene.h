#pragma once
#include <cocos2d.h>
#include"GameMap.h"

using namespace cocos2d;
class StartScene :
    public Scene
{
public:
    //��������
    static Scene* createScene();
    //��ʼ��
    bool init();

    void StartGame(Ref* pSender);
    //void Introduction(Ref* pSender);
    //void Settings(Ref* pSender);

    //��������ָ��
    CREATE_FUNC(StartScene);
};

