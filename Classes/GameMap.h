#pragma once
#include<cocos2d.h>
#include<string>
#include<map>
#include<vector>
#include<ui/CocosGUI.h>
#include"hero.h"
#include"monster.h"
#include"item.h"
using namespace cocos2d::ui;
using namespace cocos2d;
USING_NS_CC;

#define PATH              0
#define BARRIER           1
#define MONSTER           2
#define YELLOW_KEY        3
#define ORANGE_KEY        4
#define SWORD             5
#define ARMOR             6
#define YELLOWLOCK        7
#define ORANGELOCK        8
#define REDBOTTLES        9
#define BANANA            10
#define HAMBURGER         11
#define BOSS              12
#define UNIT_DISTANCE     32

class UI;

class GameMap :
    public Scene
{
public:
    static Scene* createScene(int id);
    //接口
    TMXTiledMap* getMap();
    hero* getPlayer();
    bool init(int id);
    //加载地图
    void LoadMap();
    bool Map_init(string direction);
    Vec2 PosToTileCoord(Vec2 pos);
    int detect(Vec2 HeroPos);
    void NextMove(Vec2 NextMove, EventKeyboard::KeyCode keyCode);
    void UI_init();
    //更新函数
    void update(float delta) override;
    void playMusic(Ref* Psendeer);
    void addVolume(Ref* Psendeer);
    void reduceVolume(Ref* Psendeer);
    void changeMusic(Ref* Psendeer);
    void Equip(Vec2 pos, int type);
    static GameMap* create(int id);
    
    //CREATE_FUNC(GameMap);
protected:
    GameMap() {};
    bool first = 0;
    bool is_playing;
    bool sec = 0;
    int audioID, audioid;
    Vector<TMXTiledMap*> TMap;
    vector<map<Vec2, item*>> Item;
    float volume = 0.5f;
    Vec2 Entrance;
    Vec2 Exit;
    vector<bool> FirstInit;
    Label* music;
    hero* Hero;
    monster* Monster[3];
    UI* ui;
    map<EventKeyboard::KeyCode, bool> keypress;
    Vector<TMXTiledMap*>::iterator currentMap;
};


