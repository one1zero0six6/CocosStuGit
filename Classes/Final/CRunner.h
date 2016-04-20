#ifndef __CRUNNER_H__
#define __CRUNNER_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"


#define RUNNERCOLOR1 cocos2d::Color3B(209,73,63)
#define RUNNERCOLOR2 cocos2d::Color3B(200,209,63)
#define RUNNERCOLOR3 cocos2d::Color3B(75,155,77)
#define RUNNERCOLOR4 cocos2d::Color3B(82,131,151);

class CRunner 
{
private:
public:
	cocos2d::Node   *_runnerRoot;
	cocos2d::Node   *_allRoot;
	cocos2d::Node   *_normalFace;
	cocos2d::Node   *_happyFace;
	cocos2d::Node   *_depressedFace;
	cocos2d::Sprite *_body;
	cocos2d::Sprite *_shadow;
	cocos2d::Action *_action;
	unsigned int playerface;
	float playerfacecd;

//public:
	//cocos2d::Sprite *_body;
//	void CRunner::actionFinished2();
	CRunner(const char *csbname, cocos2d::Layer &parent);
	~CRunner();
	void setPosition(const cocos2d::Point &pos);
	void setPosition(const float x, const float y);
	void setColor(const cocos2d::Color3B& color);
	void setAnimation(const char *plistFile);
	void go();
	void getrealPos(cocos2d::Point &pos);
	void changeface(const float dt);
	void changedieface();
//	void playerjump(const cocos2d::JumpBy *_myJump, const cocos2d::CallFunc *_mycallback);
};

#endif