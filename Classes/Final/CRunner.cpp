#include "CRunner.h"

USING_NS_CC;

//
// 建立角色之前，必須先確定已經讀入儲存角色所有動態圖片的 plist 檔
//

CRunner::CRunner(const char *csbname, cocos2d::Layer &parent)
{
	// 讀取角色
	_runnerRoot = CSLoader::createNode(csbname);
//	_runnerRoot = (cocos2d::Node*)getNode->getChildByName("RunnerRoot");
	_runnerRoot->setPosition(0,0); // 預設放在 (0,0) 
	_body = (cocos2d::Sprite *)_runnerRoot->getChildByName("body_cuber01");
	_body->setColor(Color3B(255, 255, 255));
	_normalFace = (cocos2d::Node *)_runnerRoot->getChildByName("NormalFace");
	_happyFace = (cocos2d::Node *)_runnerRoot->getChildByName("HappyFace");
	_depressedFace = (cocos2d::Node *)_runnerRoot->getChildByName("DepressedFace");
	_happyFace->setVisible(false);
	_depressedFace->setVisible(false);
	parent.addChild(_runnerRoot);
}


CRunner::~CRunner()
{
	_action->release();
}


void CRunner::go()
{
	_body->runAction(_action);
}

void CRunner::setAnimation(const char *plistFile)
{
	// 此處假設儲存角色所有動態圖片的 plist 檔已經讀入
	auto cache = AnimationCache::getInstance();
	cache->addAnimationsWithFile(plistFile);
	auto animation = cache->getAnimation("running");
	_action = RepeatForever::create(Animate::create(animation));
	_action->retain();
}

void CRunner::setPosition(const Point &pos)
{
	_runnerRoot->setPosition(pos);
}

void CRunner::setPosition(const float x, const float y)
{
	_runnerRoot->setPosition(x,y);
}

void CRunner::setColor(const Color3B& color)
{
	_body->setColor(color);
}