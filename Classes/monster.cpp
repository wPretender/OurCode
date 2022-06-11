#include "monster.h"
#include"hero.h"

monster* monster::create() {
	monster* pRet = new(std::nothrow) monster();
	//�����ǰ�����ڴ����ɹ������ҳ�ʼ���ɹ�
	if (pRet && pRet->init())
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

void monster::be_attacked(int atk, hero& Hero)
{
	atk += (Hero.sword != NULL ? Hero.sword->getATK() : 0);
	int ac = Hero.h_job;
	int bc = m_job;
	if ((ac + 1) % 3 == bc) {
		atk = atk * 2;
	}
	else if ((bc + 1) % 3 == ac) {
		atk = atk / 2;
	}
	if (atk - m_def > 0)
		m_health -= atk - m_def;
	if (m_health <= 0) {
		m_health = 0;
		Hero.addProperty(0, 0, 0, m_exp);
	}
}

//��������
void monster::setProperty(int health, int atk, int def, int exp)
{
	m_health = health;
	m_atk = atk;
	m_def = def;
	m_exp = exp;
}

bool monster::is_death() const
{
	return m_health == 0;
}

Sprite* monster::getSprite() const
{
	return m_image;
}