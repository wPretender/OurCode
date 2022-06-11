#pragma once
#include <cocos2d.h>
#include"GameMap.h"

using namespace cocos2d;
class StartScene :
    public Scene
{
public:
    //创建场景
    static Scene* createScene();
    //初始化
    bool init();

    void StartGame(Ref* pSender);
    //void Introduction(Ref* pSender);
    //void Settings(Ref* pSender);

    //创建对象指针
    CREATE_FUNC(StartScene);
};

