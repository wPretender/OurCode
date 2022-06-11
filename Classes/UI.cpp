#include "UI.h"
#include"hero.h"
#include"item.h"
#include<string>
using namespace std;

bool UI::init()
{
	if (!Layer::init())
		return false;


	//角色UI
	auto player = Sprite::create("Braver.png");
	player->setPosition(80, 650);
	player->setScale(3, 3);
	this->addChild(player);

	char property[100] = { 0 };
	sprintf(property, "HEALTH: %d\nATK:     %d\nDEF:     %d\nLEVEL:   %d\nEXP:    %d/%d\nNP:      %d/500",
		Hero->h_health, Hero->h_atk + (Hero->sword != NULL ? Hero->sword->getATK() : 0), Hero->h_def + (Hero->shield != NULL ? Hero->shield->getDEF() : 0), Hero->h_level, Hero->h_exp, Hero->h_level * 100, Hero->NP);
	auto UIproperty = Label::createWithSystemFont(property, "Arial", 20);
	UIproperty->setPosition(80, 520);
	addChild(UIproperty);

	/*char health[20] = {0};
	sprintf(health, "HEALTH: %d", Hero->h_health);
	auto UIhealth = Label::createWithSystemFont(health, "Arial", 20);
	char atk[20] = { 0 };
	sprintf(atk, "ATK:     %d", Hero->h_atk);
	auto UIatk = Label::createWithSystemFont(atk, "Arial", 20);
	char def[20] = { 0 };
	sprintf(def, "DEF:     %d", Hero->h_def);
	auto UIdef = Label::createWithSystemFont(def, "Arial", 20);
	char level[20] = { 0 };
	sprintf(level, "LEVEL:   %d", Hero->h_level);
	auto UIlevel = Label::createWithSystemFont(level, "Arial", 20);
	char exp[30] = { 0 };
	sprintf(exp, "EXP:    %d/%d", Hero->h_exp, Hero->h_level * 100);
	auto UIexp = Label::createWithSystemFont(exp, "Arial", 20);

	UIhealth->setPosition(180, 100);
	addChild(UIhealth);
	UIatk->setPosition(180, 80);
	addChild(UIatk);
	UIdef->setPosition(180, 60);
	addChild(UIdef);
	UIlevel->setPosition(180, 40);
	addChild(UIlevel);
	UIexp->setPosition(180, 20);
	addChild(UIexp);*/

	//钥匙部分UI
	auto okey = Sprite::create("bluekey.png");
	auto ykey = Sprite::create("yellowkey.png");
	okey->setPosition(900, 650);
	okey->setScale(2, 2);
	ykey->setPosition(900, 550);
	ykey->setScale(2, 2);
	addChild(okey);
	addChild(ykey);
	char ykeynum[5] = { 0 };
	char okeynum[5] = { 0 };
	sprintf(okeynum, "X%d", Hero->orange_key);
	sprintf(ykeynum, "X%d", Hero->yellow_key);
	auto UIokey = Label::createWithSystemFont(okeynum, "Arial", 30);
	auto UIykey = Label::createWithSystemFont(ykeynum, "Arial", 30);
	UIokey->setPosition(950, 650);
	UIykey->setPosition(950, 550);
	addChild(UIokey);
	addChild(UIykey);

	//装备部分UI
	auto swordtext = Label::createWithSystemFont("Sword:", "Arial", 20);
	auto shieldtext = Label::createWithSystemFont("Shield:", "Arial", 20);
	swordtext->setPosition(80, 400);
	shieldtext->setPosition(80, 200);
	addChild(swordtext);
	addChild(shieldtext);

	if (Hero->sword) {
		auto sword = Sprite::create(Hero->sword->getFile());
		char swordATK[10];
		sprintf(swordATK, "ATK: %d", Hero->sword->getATK());
		sword->setPosition(80, 330);
		sword->setScale(2, 2);
		addChild(sword);
		auto UIswordATK = Label::createWithSystemFont(swordATK, "Arial", 20);
		UIswordATK->setPosition(80, 250);
		addChild(UIswordATK);
	}

	if (Hero->shield) {
		auto shield = Sprite::create(Hero->shield->getFile());
		char shieldDEF[10];
		sprintf(shieldDEF, "DEF: %d", Hero->shield->getDEF());
		shield->setPosition(80, 120);
		shield->setScale(2, 2);
		addChild(shield);
		auto UIshieldDEF = Label::createWithSystemFont(shieldDEF, "Arial", 20);
		UIshieldDEF->setPosition(80, 50);
		addChild(UIshieldDEF);
	}

	return true;
}

void UI::AcquireHero(hero* Hero)
{
	if (!Hero)
		Hero = hero::create();
	this->Hero = Hero;
}

UI* UI::create(hero* Hero)
{
	auto ui = new UI();
	ui->AcquireHero(Hero);
	ui->init();
	return ui;
}