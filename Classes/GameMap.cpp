#include "GameMap.h"
#include"UI.h"
#include<map>
#include "AudioEngine.h"
#include "FightMenu.h"
#include "nextPage1.h"
#include "FightBoss.h"
#include "MyMenu.h"
typedef void (Ref::* SEL_CallFunc)();
typedef void (Ref::* SEL_CallFuncN)(Node*);
typedef void (Ref::* SEL_CallFuncND)(Node*, void*);
typedef void (Ref::* SEL_CallFuncO)(Ref*);
typedef void (Ref::* SEL_MenuHandler)(Ref*);
typedef void (Ref::* SEL_SCHEDULE)(float);

#define callfunc_selector(_SELECTOR) static_cast<cocos2d::SEL_CallFunc>(&_SELECTOR)
#define callfuncN_selector(_SELECTOR) static_cast<cocos2d::SEL_CallFuncN>(&_SELECTOR)
#define callfuncND_selector(_SELECTOR) static_cast<cocos2d::SEL_CallFuncND>(&_SELECTOR)
#define callfuncO_selector(_SELECTOR) static_cast<cocos2d::SEL_CallFuncO>(&_SELECTOR)
#define menu_selector(_SELECTOR) static_cast<cocos2d::SEL_MenuHandler>(&_SELECTOR)
#define schedule_selector(_SELECTOR) static_cast<cocos2d::SEL_SCHEDULE>(&_SELECTOR)

GameMap* GameMap::create(int id) {
    GameMap* pRet = new(std::nothrow) GameMap();
    //如果当前对象内存分配成功，并且初始化成功
    if (pRet && pRet->init(id))
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

Scene* GameMap::createScene(int id)
{
    return GameMap::create(id);
}


void GameMap::LoadMap()
{
    char mapfile[10] = { 0 };
    for (int i = 1; i <= 10; i++) {
        sprintf(mapfile, "Map%d.tmx", i);
        TMap.pushBack(TMXTiledMap::create(mapfile));
        FirstInit.push_back(true);
        map<Vec2, item*> EmptyItem;
        Item.push_back(EmptyItem);
    }
}

TMXTiledMap* GameMap::getMap()
{
    return (*currentMap);
}


hero* GameMap::getPlayer()
{
    return Hero;
}

bool GameMap::init(int id)
{
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    

    auto closeItem = MenuItemImage::create(
        "MainMenu.png",
        "MainMenu.png",
        CC_CALLBACK_1(GameMap::menuCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        log("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //载入地图
    LoadMap();
    currentMap = TMap.begin();

    //创建角色
    Hero = hero::create();
    if(id==0)
        Hero->setProperty(800, 20, 10);
    else {
        Hero->setProperty(800000, 200000, 10);
        Hero->pick_keys(100, 100);
    }
    //创建怪物
    for (int i = 0; i < 3; ++i)
        Monster[i] = monster::create();


    //初始化地图
    Map_init("HeroEnter");


    //创建一个键盘事件
    auto kblistener = EventListenerKeyboard::create();
    //按下移动
    kblistener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        keypress[keyCode] = true;
        log("key %d pressed", keyCode);

        /*switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_W: {
            NextPos = Vec2(HeroPos.x, HeroPos.y + UNIT_DISTANCE);
            NextMove(NextPos);
            for (int i = 1; i <= 3; i++) {
                char file[15] = { 0 };
                sprintf(file, "Up%d.png", i);
                moveanimation->addSpriteFrameWithFile(file);
            }
            moveanimation->setLoops(1);
            moveanimation->setDelayPerUnit(0.1f);
            auto action = Animate::create(moveanimation);
            Hero->getSprite()->runAction(action);
            break;
        }
        case EventKeyboard::KeyCode::KEY_S: {
            NextPos = Vec2(HeroPos.x, HeroPos.y - UNIT_DISTANCE);
            NextMove(NextPos);
            /*for (int i = 1; i <= 3; i++) {
                char file[15] = { 0 };
                sprintf(file, "Down%d.png", i);
                moveanimation->addSpriteFrameWithFile(file);
            }
            moveanimation->setLoops(1);
            moveanimation->setDelayPerUnit(0.1f);
            auto action = Animate::create(moveanimation);
            Hero->getSprite()->runAction(action);
            break;
        }
        case EventKeyboard::KeyCode::KEY_A: {
            NextPos = Vec2(HeroPos.x - UNIT_DISTANCE, HeroPos.y);
            NextMove(NextPos);

            /*for (int i = 1; i <= 3; i++) {
                char file[15] = { 0 };
                sprintf(file, "Left%d.png", i);
                moveanimation->addSpriteFrameWithFile(file);
            }
            moveanimation->setLoops(1);
            moveanimation->setDelayPerUnit(0.1f);
            auto action = Animate::create(moveanimation);
            Hero->getSprite()->runAction(action);
            break;
        }
        case EventKeyboard::KeyCode::KEY_D: {
            NextPos = Vec2(HeroPos.x + UNIT_DISTANCE, HeroPos.y);
            NextMove(NextPos);

            /*for (int i = 1; i <= 3; i++) {
                char file[15] = { 0 };
                sprintf(file, "Right%d.png", i);
                moveanimation->addSpriteFrameWithFile(file);
            }
            moveanimation->setLoops(1);
            moveanimation->setDelayPerUnit(0.1f);
            auto action = Animate::create(moveanimation);
            Hero->getSprite()->runAction(action);
            break;
        }
        }

        /*if (Hero->canMove) {
            auto moveto = MoveTo::create(0.1f, NextPos);
            Hero->move(moveto);
        }*/
    };

    //按键放开
    kblistener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("keycode %d released", keyCode);
        keypress[keyCode] = false;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(kblistener, this);

    this->schedule(CC_SCHEDULE_SELECTOR(GameMap::update), 0.1);

    //播放音乐
    audioID = AudioEngine::play2d("NEEDY GIRL OVERDOSE; Aiobahn - Angel boring (feat. Aiobahn).mp3", true, 1.0f);
    AudioEngine::setVolume(audioID, volume);
    is_playing = 1;

    auto temp = MenuItemImage::create(
		"play_pause.png",
		"play_pause.png",
		CC_CALLBACK_1(GameMap::playMusic, this));
	auto button = Menu::create(temp, NULL);
    button->setAnchorPoint(Vec2(0, 0));
    button->setPosition(Vec2(visibleSize.width / 7 * 6 + 44, visibleSize.height / 2));
    button->setScale(0.2f);
	this->addChild(button, 3);

    music = Label::createWithSystemFont("", "Arial", 26);
    music->setString(StringUtils::format("Music:\n\n\n\nVolume:%d%%", int(volume*100)));
    music->setPosition(Vec2(visibleSize.width / 9 * 8 + 20, visibleSize.height / 2));
    this->addChild(music, 3);

    auto temp1 = MenuItemImage::create(
        "add.png",
        "add.png",
        CC_CALLBACK_1(GameMap::addVolume, this));
    auto add = Menu::create(temp1, NULL);
    add->setAnchorPoint(Vec2(0, 0));
    add->setPosition(Vec2(visibleSize.width / 7 * 6 + 86, visibleSize.height / 3));
    add->setScale(0.3f);
    this->addChild(add, 3);

    auto temp2 = MenuItemImage::create(
        "reduce.png",
        "reduce.png",
        CC_CALLBACK_1(GameMap::reduceVolume, this));
    auto reduce = Menu::create(temp2, NULL);
    reduce->setAnchorPoint(Vec2(0, 0));
    reduce->setPosition(Vec2(visibleSize.width / 7 * 6 + 2, visibleSize.height / 3));
    reduce->setScale(0.3f);
    this->addChild(reduce, 3);

    auto temp3 = MenuItemImage::create(
        "cha.png",
        "cha.png",
        CC_CALLBACK_1(GameMap::changeMusic, this));
    auto ch = Menu::create(temp3, NULL);
    ch->setAnchorPoint(Vec2(0, 0));
    ch->setPosition(Vec2(visibleSize.width / 7 * 6 + 44, visibleSize.height / 4));
    ch->setScale(0.6f);
    this->addChild(ch, 3);
    //UI
    UI_init();

    return true;
}

void GameMap::changeMusic(Ref* Psendeer) {
    if (!sec) {
        sec = 1;
        is_playing = 1; 
        if(first)
            AudioEngine::resume(audioid);
        else {
            audioid = AudioEngine::play2d("solomon.mp3", true, 1.0f);
            first = 1;
        }
        AudioEngine::setVolume(audioid, volume);
        AudioEngine::pause(audioID);
    }
    else {
        sec = 0;
        is_playing = 1;
        AudioEngine::setVolume(audioID, volume);
        AudioEngine::resume(audioID);
        AudioEngine::pause(audioid);
    }
}


void GameMap::addVolume(Ref* Psendeer) {
    if (volume + 1e-4 < 1.0) {
        volume += 0.1f;
        if(!sec)
            AudioEngine::setVolume(audioID, volume);
        else
            AudioEngine::setVolume(audioid, volume);
        music->setString(StringUtils::format("Music:\n\n\n\nVolume:%d%%", int(volume * 100)));
    }
}

void GameMap::reduceVolume(Ref* Psendeer) {
    if (volume - 1e-4 > 0) {
        volume -= 0.1f;
        if (!sec)
            AudioEngine::setVolume(audioID, volume);
        else
            AudioEngine::setVolume(audioid, volume);
        music->setString(StringUtils::format("Music:\n\n\n\nVolume:%d%%", int(volume * 100)));
    }
}

void GameMap::playMusic(Ref* Psendeer) {//播放、暂停音乐
    if (is_playing) {
        if(!sec)
            AudioEngine::pause(audioID);
        else
            AudioEngine::pause(audioid);
        is_playing = 0;
    }
    else {
        if(!sec)
            AudioEngine::resume(audioID);
        else
            AudioEngine::resume(audioid);
        is_playing = 1;
    }
}

bool GameMap::Map_init(string direction)
{
    //设定出入口位置
    auto group = (*currentMap)->getObjectGroup("Object");
    auto stair = group->getObject("Downstair");
    Entrance = Vec2(stair["x"].asFloat(), stair["y"].asFloat());
    stair = group->getObject("Upstair");
    Exit = Vec2(stair["x"].asFloat(), stair["y"].asFloat());

    //剑生成
    auto findsword = group->getObject("Sword");
    if (findsword.size() && FirstInit[currentMap - TMap.begin()]) {
        auto sword = item::create(findsword["Address"].asString(), item::Sword);
        sword->setProperty(findsword["ATK"].asInt(), findsword["DEF"].asInt());
        sword->getSprite()->setPosition(Vec2(findsword["x"].asFloat(), findsword["y"].asFloat()));
        Item[currentMap - TMap.begin()][Vec2(findsword["x"].asFloat(), findsword["y"].asFloat())] = sword;
        (*currentMap)->addChild(sword, 10);
    }

    //盾生成
    auto findshield = group->getObject("Shield");
    if (findshield.size() && FirstInit[currentMap - TMap.begin()]) {
        auto shield = item::create(findshield["Address"].asString(), item::Shield);
        shield->setProperty(findshield["ATK"].asInt(), findshield["DEF"].asInt());
        shield->getSprite()->setPosition(Vec2(findshield["x"].asFloat(), findshield["y"].asFloat()));
        Item[currentMap - TMap.begin()][Vec2(findshield["x"].asFloat(), findshield["y"].asFloat())] = shield;
        (*currentMap)->addChild(shield, 10);
    }

    auto heropoint = group->getObject(direction);
    Hero->getSprite()->setPosition(Vec2(heropoint["x"].asFloat(), heropoint["y"].asFloat()));
    (*currentMap)->addChild(Hero, 10);
    //加载地图
    (*currentMap)->setPosition(200, 80);
    (*currentMap)->setScale(1.5, 1.5);
    this->addChild(*currentMap);
    FirstInit[currentMap - TMap.begin()] = false;
    return true;
}

Vec2 GameMap::PosToTileCoord(Vec2 pos)
{
    int x = pos.x / ((*currentMap)->getTileSize().width);
    int y = (((*currentMap)->getMapSize().height * (*currentMap)->getTileSize().height) - pos.y) / ((*currentMap)->getTileSize().height);
    return Vec2(x, y);
}

int GameMap::detect(Vec2 tilecoord)
{
    int tileGID;
    if ((*currentMap)->getLayer("Wall")) {
        tileGID = (*currentMap)->getLayer("Wall")->getTileGIDAt(tilecoord);
        if (tileGID) {
            return BARRIER;
        }
    }

    if ((*currentMap)->getLayer("YellowLock")) {
        tileGID = (*currentMap)->getLayer("YellowLock")->getTileGIDAt(tilecoord);
        if (tileGID) {
            return YELLOWLOCK;
        }
    }

    if ((*currentMap)->getLayer("OrangeLock")) {
        tileGID = (*currentMap)->getLayer("OrangeLock")->getTileGIDAt(tilecoord);
        if (tileGID) {
            return ORANGELOCK;
        }
    }

    if ((*currentMap)->getLayer("YellowKey")) {
        tileGID = (*currentMap)->getLayer("YellowKey")->getTileGIDAt(tilecoord);
        if (tileGID) {
            return YELLOW_KEY;
        }
    }

    if ((*currentMap)->getLayer("OrangeKey")) {
        tileGID = (*currentMap)->getLayer("OrangeKey")->getTileGIDAt(tilecoord);
        if (tileGID) {
            return ORANGE_KEY;
        }
    }

    if ((*currentMap)->getLayer("RedBottles")) {
        tileGID = (*currentMap)->getLayer("RedBottles")->getTileGIDAt(tilecoord);
        if (tileGID) {
            return REDBOTTLES;
        }
    }

    if ((*currentMap)->getLayer("Banana")) {
        tileGID = (*currentMap)->getLayer("Banana")->getTileGIDAt(tilecoord);
        if (tileGID) {
            return BANANA;
        }
    }

    if ((*currentMap)->getLayer("Hamburger")) {
        tileGID = (*currentMap)->getLayer("Hamburger")->getTileGIDAt(tilecoord);
        if (tileGID) {
            return HAMBURGER;
        }
    }

    if ((*currentMap)->getLayer("Monster")) {
        tileGID = (*currentMap)->getLayer("Monster")->getTileGIDAt(tilecoord);
        if (tileGID) {
            return MONSTER;
        }
    }
    if ((*currentMap)->getLayer("Boss")) {
        tileGID = (*currentMap)->getLayer("Boss")->getTileGIDAt(tilecoord);
        if (tileGID) {
            return BOSS;
        }
    }
    //可以增加更多的图层选项(怪物图层目前有"Skull"和"Boss")
}

void GameMap::NextMove(Vec2 NextMove, EventKeyboard::KeyCode keyC)
{
    Vec2 tilecoord = PosToTileCoord(NextMove);
    int det = detect(tilecoord);
    Hero->canMove = false;

    if (NextMove == Entrance) {
        (*currentMap)->removeChild(Hero);
        removeChild(*currentMap--);
        Map_init("HeroExit");
        return;
    }

    if (NextMove == Exit) {
        (*currentMap)->removeChild(Hero);
        removeChild(*currentMap++);
        Map_init("HeroEnter");
        return;
    }


    if (Item[currentMap - TMap.begin()].count(NextMove)) {
        Equip(NextMove, Item[currentMap - TMap.begin()].find(NextMove)->second->getItemtype());
        return;
    }

    if (det == BARRIER)
        ;

    else if (det == YELLOWLOCK) {
        if (Hero->unlock(YELLOWKEY)) {
            (*currentMap)->getLayer("YellowLock")->removeTileAt(tilecoord);
        }
    }

    else if (det == ORANGELOCK) {
        if (Hero->unlock(BLUEKEY)) {
            (*currentMap)->getLayer("OrangeLock")->removeTileAt(tilecoord);
        }
    }

    else if (det == YELLOW_KEY) {
        Hero->pick_keys(1, 0);
        (*currentMap)->getLayer("YellowKey")->removeTileAt(tilecoord);
    }

    else if (det == ORANGE_KEY) {
        Hero->pick_keys(0, 1);
        (*currentMap)->getLayer("OrangeKey")->removeTileAt(tilecoord);
    }
    else if (det == MONSTER) {
        //存档
        Save(*Hero);
        //战斗系统写入
        keypress[keyC] = false;
        int mapID = currentMap - TMap.begin();//当前处于第几层
        for (int i = 0; i < 3; ++i) {
            Monster[i] = monster::create();
            if (mapID <= 2)
                Monster[i]->setProperty(35 + 15 * mapID, 18 + 7 * mapID, 6 + 3 * mapID, 15 + 10 * mapID);
            else if(mapID <= 4)
                Monster[i]->setProperty(35 + 15 * mapID * mapID * mapID, 18 +10 * mapID * mapID * mapID, 6 + 5 * mapID * mapID, 15 + 30 * mapID);
            else
                Monster[i]->setProperty(35 + 25 * mapID * mapID * mapID, 18 + 50 * mapID * mapID * mapID, 6 + 5 * mapID * mapID, 15 + 40 * mapID);
        }
        auto glview = Director::getInstance()->getOpenGLView();
        glview->setFrameSize(1280, 720);
        Director::getInstance()->pushScene(FightMenu::createScene(Hero, Monster,*currentMap,tilecoord));
        //Director::getInstance()->pushScene(nextPage1::createScene(Hero));
        //glview->setFrameSize(1024, 768);
       

        //Hero->canMove = 0;
    }
    else if (det == BOSS) {
        //存档
        Save(*Hero);
        //战斗系统写入
        keypress[keyC] = false;
        int mapID = currentMap - TMap.begin();//当前处于第几层
        Monster[0] = monster::create();
        if (mapID == 4) {
            Monster[0]->setProperty(35000, 1500, 100, 10000);
            Monster[0]->m_job = 1;
            Hero->h_job = 1;
        }
        else {
            Monster[0]->setProperty(250000, 15000, 5000, 100000);
            Monster[0]->m_job = 2;
            Hero->h_job = 2;
        }
        while (Hero->h_exp >= Hero->h_level * 100) {
            Hero->h_exp -= Hero->h_level * 100;
            Hero->addProperty(1000 * Hero->h_level, 40 * Hero->h_level, 15 * Hero->h_level, 0);
            Hero->h_level++;
        }
        auto glview = Director::getInstance()->getOpenGLView();
        glview->setFrameSize(1280, 720);
        Director::getInstance()->pushScene(FightBoss::createScene(Hero, Monster[0],*currentMap,tilecoord));
    }

    else if (det == REDBOTTLES) {
        Hero->addProperty(100 > Hero->h_health / 20 ? 100 : Hero->h_health / 10, 0, 0, 0);
        (*currentMap)->getLayer("RedBottles")->removeTileAt(tilecoord);
    }
    else if (det == BANANA) {
        Hero->addProperty(0, 10 > Hero->h_atk / 20 ? 20 : Hero->h_atk / 20, 0, 0);
        (*currentMap)->getLayer("Banana")->removeTileAt(tilecoord);
    }
    else if (det == HAMBURGER) {
        Hero->addProperty(0, 0, 10 > Hero->h_def / 20 ? 20 : Hero->h_def / 20, 0);
        (*currentMap)->getLayer("Hamburger")->removeTileAt(tilecoord);
    }
    else {
        Hero->canMove = true;
    }
}

void GameMap::Equip(Vec2 pos, int type)
{
    item* weapon = NULL;
    map<Vec2, item*>::iterator It = Item[currentMap - TMap.begin()].find(pos);


    log("removed successfully");
    if (type == item::Sword) {
        weapon = Hero->sword;
        Hero->sword = It->second;
    }

    if (type == item::Shield) {
        weapon = Hero->shield;
        Hero->shield = It->second;
    }
    //移除地上武器
    (*currentMap)->removeChild(It->second);
    Item[currentMap - TMap.begin()].erase(pos);
    //不是空指针便生成新变量
    if (weapon) {
        Item[currentMap - TMap.begin()][pos] = weapon;
        weapon->getSprite()->setPosition(pos);
        (*currentMap)->addChild(weapon);
    }
}
/*bool GameMap::Battle(hero* Hero, monster* Mon)
{
    while (1) {
        //Hero->attack(*Mon);
        if (Mon->is_death())
            return true;
        //Mon->attack(*Hero);
        if (Hero->is_death())
            return false;
    }
}*/

void GameMap::UI_init()
{
    ui = UI::create(Hero);
    ui->setPosition(0, 0);
    addChild(ui, 5);
}

void GameMap::update(float delta)
{
    auto up = EventKeyboard::KeyCode::KEY_W;
    auto down = EventKeyboard::KeyCode::KEY_S;
    auto left = EventKeyboard::KeyCode::KEY_A;
    auto right = EventKeyboard::KeyCode::KEY_D;

    //偏移量
    int offsetX = 0, offsetY = 0;
    //动画
    auto moveanimation = Animation::create();
    moveanimation->setLoops(1);
    moveanimation->setDelayPerUnit(0.1f);

    while (Hero->h_exp >= Hero->h_level * 100) {
        Hero->h_exp -= Hero->h_level * 100;
        Hero->addProperty(1000 * Hero->h_level, 40 * Hero->h_level, 15 * Hero->h_level, 0);
        Hero->h_level++;
    }

    auto nextKey = EventKeyboard::KeyCode::KEY_W;
    //读键
    if (keypress[up]) {
        offsetY = UNIT_DISTANCE;
        for (int i = 1; i <= 3; i++) {
            char file[15] = { 0 };
            sprintf(file, "Up%d.png", i);
            moveanimation->addSpriteFrameWithFile(file);
        }
        nextKey = up;
    }

    else if (keypress[down]) {//改成了else if
        offsetY = -UNIT_DISTANCE;
        for (int i = 1; i <= 3; i++) {
            char file[15] = { 0 };
            sprintf(file, "Down%d.png", i);
            moveanimation->addSpriteFrameWithFile(file);
        }
        nextKey = down;
    }

    else if (keypress[left]) {
        offsetX = -UNIT_DISTANCE;
        for (int i = 1; i <= 3; i++) {
            char file[15] = { 0 };
            sprintf(file, "Left%d.png", i);
            moveanimation->addSpriteFrameWithFile(file);
        }
        nextKey = left;
    }

    else if (keypress[right]) {
        offsetX = UNIT_DISTANCE;
        for (int i = 1; i <= 3; i++) {
            char file[15] = { 0 };
            sprintf(file, "Right%d.png", i);
            moveanimation->addSpriteFrameWithFile(file);
        }
        nextKey = right;
    }

    auto HeroPos = Hero->getSprite()->getPosition();
    auto NextPos = Vec2(HeroPos.x + offsetX, HeroPos.y + offsetY);
    NextMove(NextPos, nextKey);

    //加载存档
    if (Hero->is_death()) {
        Hero->setProperty(SaveHero->h_health, SaveHero->h_atk, SaveHero->h_def, SaveHero->h_exp, SaveHero->h_level, SaveHero->yellow_key, SaveHero->orange_key);
        Hero->NP = SaveHero->NP;
    }

    //动作
    auto action = Animate::create(moveanimation);
    Hero->getSprite()->runAction(action);
    if (Hero->canMove) {
        auto moveto = MoveTo::create(delta, NextPos);
        Hero->move(moveto);
    }
    //重新加载UI
    removeChild(ui);
    UI_init();
}

void GameMap::Save(const hero& savehero)
{
    if (SaveHero)
        delete SaveHero;
    SaveHero = hero::create(savehero);
}

void GameMap::menuCallback(Ref* pSender)
{

    auto scene = MyMenu::createScene();
    AudioEngine::stopAll();
    auto glview = Director::getInstance()->getOpenGLView();
    glview->setFrameSize(1280, 720);
    Director::getInstance()->replaceScene(scene);
    
}