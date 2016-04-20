#ifndef __ENEMYROCK_H__
#define __ENEMYROCK_H__

#include "cocos2d.h"
//#include "cocostudio/CocoStudio.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"

class EnemyRock
{
private:
public:
	cocos2d::Node   *_enemyroot;
	cocos2d::Sprite   *_enemypictbody;
	cocos2d::Action *_action;
	cocos2d::Size _enemysize;
	bool _fcollision, _animflag;
	unsigned int _ienemykind;


	EnemyRock(const unsigned int enemykind,const char *csbname, cocos2d::Layer &parent);
	~EnemyRock();
	void setPosition(const cocos2d::Point &pos);
	void setPosition(const float x, const float y);
	//void setColor(const cocos2d::Color3B& color);
	void setAnimation(const char *plistFile);
	void go();
	void setenemysize();
	void collision(int &_ihp, unsigned int &_iplayerscore, unsigned int &playerface , const cocos2d::Point &playerpos);//¥Î_enemyrootªºpos­pºâ
};

#endif
