双击或右键打开Mota(FGO).exe即可在windows系统下运行程序。




《魔塔：FGO》项目介绍

一、项目简介：

项目名称：魔塔：FGO

进度时间线：2022.4.25 小组成员开始学习cocos2d-x

            2022.5.1  开始编写基本类hero，monster，item

            2022.5.5  编写地图场景类GameMap

            2022.5.15 小组成员第一次会议

            2022.5.16 开始制作地图

            2022.5.21 实现英雄移动，移动动画，物品拾取，开门等交互

            2022.5.25 实现地图切换

            2022.5.28 开始编写UI

            2022.5.29 添加背景音乐

            2022.5.30 实现人物连续移动

            2022.6.1  增添武器，实现武器拾取功能，在UI显示武器

            2022.6.3  制作地图        

            2022.6.4  完成了小怪层战斗场景的编写        

            2022.6.5  添加了背景音乐音量控制功能        

            2022.6.6  添加了战斗宝具动画和新的战斗背景        

            2022.6.7  新增了BOSS战：暴击-Arjuna 和真伤-Kama        

            2022.6.8  添加了防御技能       

            2022.6.9  添加了无敌模式，和战斗前存档功能       

二、整体设计框架

1.英雄（hero）
为玩家所扮演的角色，需要实现的功能有：攻击怪物，被攻击，移动，拾取物品，升级，显示自身属性。本身具有显示图像的精灵，生命值，攻击力，防御力，经验值，以及钥匙数量的属性，同时还拥有有剑和盾的装备槽。

2.怪物（monster）
为英雄的敌人，需要实现的功能有：攻击英雄，被攻击，显示自身属性。本身属性有显示图像的精灵，职阶，生命值，攻击力，防御力，击败后可获得的经验值。

3.物品（item）
为英雄所能拾取的有增益效果的道具，所要实现的功能有被拾取，返回自身属性，其自身属性有攻击力和防御力。

4.地图（GameMap）
为游戏的主要场景，其中会生成道具、障碍、怪物等。需要实现的功能有：碰撞检测，物品交互后删除其图像，地图切换，坐标转换，生成物品刷怪点。其自身数据成员有：出入口，用来储存地图的容器。

5.战斗菜单（FightMenu）
为战斗前的介绍场景，会随机生成三种职阶的怪物，并显示每种职阶的数量，玩家需要选择对应的职阶。需要实现的功能有：显示怪物的职阶和数量，设置怪物的各种属性，菜单按钮功能。其自身数据成员有英雄和怪物。

6.战斗场景（FightScene）
为战斗进行时的场景。需要实现的功能有：显示怪物的各种属性，显示英雄的各种属性，英雄的精灵图像和怪物的精灵图像，背景图片的随机切换，攻击键，防御键和宝具释放键的监听与禁用，死亡判断和胜利/失败条件，在敌人死亡后将其从地图上移除。其自身数据成员有英雄，怪物，精灵图片，菜单按钮。

7.Boss战（FightBoss）
与FightScene类似。区别是Boss每次攻击时有1/3的概率暴击并释放宝具，关底Boss会对玩家角色造成真实伤害。功能和数据成员与FightScene类似。

三、实现功能点

1.游戏开始界面，背景音乐切换、音量控制、暂停及恢复功能，退出功能。
实现思路：运用cocos2d-x的Menu类实现各功能按钮的初始化，点击对应按钮实现对应功能。运用AudioEngine类创建对象，并用类内函数实现了音乐方面的功能。

2.地图间的切换
实现思路：借助了Tile Map制作瓦片地图，储存在GameMap类里的数据成员——储存着TMXTileMap类指针的vector中，并用其对应迭代器currentMap指向当前地图；当需要切换地图时，removeChild(*currentMap)移除当前地图，接着改变迭代器所指对象，再addChild(*currentMap)加入新地图。

3.怪物属性
实现思路：用rand函数随机生成怪物的职业，各个职业之间存在克制关系，怪物的各项属性随着层数增加而递增，经过实际测试，递增曲线为层数的三次幂类函数较为合适。

4.道具系统
实现思路：一些道具因为功能简单数量丰富（如钥匙，回血药），因此采用制作地图时单独做成图层，触碰时增加英雄对应属性，然后从图层上删除这个瓦片来实现。而武器则是使用对象层创建对象来确定在地图上的位置、属性，在GameMap中获取储存在一个map<Vec2,item*>中，当英雄走到对应位置便拾取武器，若手上原有武器，则将原武器图像生成在位置上，并将map中的item*改为指向原武器。

5.回合制战
实现思路：利用MenuItemImage 的鼠标监听器功能实现回合制战斗功能。即点击按钮->己方攻击->敌方攻击。
当x号敌人死亡后，通过setEnabled 函数禁用攻击x号敌人的按钮。
当全部敌人死亡后，通过TMap->getLayer("Monster")->removeTileAt(NextPos) 来移除其在地图上的图像。

6.战斗中可选敌人和技能
实现思路：
可选敌人：分为小怪层和BOSS层。

小怪层有三种敌人，saber, lancer, archer。每次进入战斗会出现三名敌人，它们的种类是随机的。用rand实现，m_job记录。
怪物的属性曲线是与层数有关的类三次幂函数。
每次进入战斗前，玩家可以选择saber, lancer, archer三职阶的其中一种，saber克lancer，lancer克archer，archer克saber，用h_job记录。

BOSS层有两种敌人，名为Arjuna和Beast-Kama。
Arjuna的攻击有1/3的概率暴击，造成三倍伤害。当他暴击时，会加载宝具图层，用nextPage1生成新图层并覆盖在原图层上面，利用鼠标监听器更换图片。
Beast-Kama的攻击有1/3的概率暴击，造成三倍伤害，且她的攻击无视防御力。当她暴击时同样会加载她的宝具图层。

可选功能：攻击1号，2号，3号敌人，防御，释放宝具

攻击会在职阶克制的基础上造成伤害，克制则翻倍，逆克制则减半。
防御会降低主角受到的伤害，并额外获得NP。
当NP大于100时，可以释放宝具，对全体敌人造成双倍攻击力的伤害，在BOSS战中，这个倍率被提高到三倍。攻击，受击和防御都能获得NP。宝具按钮的开启与关闭用setEnabled控制。所有按钮都用MenuItemImage实现。

7.键盘控制角色移动
实现思路：用监听器来侦测键盘响应，用一个map<coocs2d::EventKeyboard::KeyCode,bool>来记录对应按键的状态（按下或松开），侦测到对应按键便调用英雄的移动函数。

8.无敌模式
实现思路：初始化英雄对象时战斗数值拉满，并用pick_keys函数获得大量的钥匙。

四、游戏亮点

1.独特的战斗模式

独特的职业克制系统，三种职业任意选择，通过克制关系选择策略，增添了游戏的策略兴趣；np系统可释放宝具造成范围大量伤害，而攻击与防御的抉择，更是增添了游戏的策略性。

2.可更换武器

通过map来储存武器对象及其位置，通过获取和更改map里的内容来实现武器更换。玩家可以根据自己的喜好选择自己喜欢的武器。

3.动感或宏伟的背景音乐

游戏内提供了两种风格明快和恢弘的背景音乐供玩家选择，可优化玩家的游玩体验。

4.魂系风格

难度与乐趣并存。

5.战斗系统的随机性

该游戏《魔塔：FGO》区别于传统的魔塔游戏最大的特点就是随机性对游戏的影响很大。

在选择职阶时，你并非每次都能做出正确的选择——当敌人为1saber 1lancer 1archer时，无论选择哪种职阶，都会被其中一个敌人克制。这会给你带来更大的血量消耗。

在BOSS战中，由于BOSS的暴击特性，你可能轻松通关，也可能运气不好被BOSS的连续暴击秒杀。

因此玩家可能需要多次尝试才能顺利通关。随机性即所谓“运气”元素的加入提高了游戏的趣味性、紧张度和难度。