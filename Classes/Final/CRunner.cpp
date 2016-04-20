#include "CRunner.h"

USING_NS_CC;

//
// 建立角色之前，必須先確定已經讀入儲存角色所有動態圖片的 plist 檔
//

CRunner::CRunner(const char *csbname, cocos2d::Layer &parent)
{
	playerface = 0;
	playerfacecd = 0.0;//表情CD
	// 讀取角色
	_runnerRoot = CSLoader::createNode(csbname);
//	_runnerRoot = (cocos2d::Node*)getNode->getChildByName("RunnerRoot");
	_runnerRoot->setPosition(0,0); // 預設放在 (0,0) 
	_runnerRoot->setScale(0.70f);
	_allRoot = (cocos2d::Node *)_runnerRoot->getChildByName("all");
	_body = (cocos2d::Sprite *)_allRoot->getChildByName("body_cuber01");
	//_body = (cocos2d::Sprite *)_runnerRoot->getChildByName("body_cuber01");
	_body->setColor(Color3B(255, 255, 255));
	_normalFace = (cocos2d::Node *)_allRoot->getChildByName("NormalFace");
	//_normalFace = (cocos2d::Node *)_runnerRoot->getChildByName("NormalFace");
	_happyFace = (cocos2d::Node *)_allRoot->getChildByName("HappyFace");
	//_happyFace = (cocos2d::Node *)_runnerRoot->getChildByName("HappyFace");
	_depressedFace = (cocos2d::Node *)_allRoot->getChildByName("DepressedFace");
	//_depressedFace = (cocos2d::Node *)_runnerRoot->getChildByName("DepressedFace");
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
void CRunner::getrealPos(cocos2d::Point &pos) {
	pos.x = _allRoot->getPosition().x + _runnerRoot->getPosition().x;
	pos.y = _allRoot->getPosition().y + _runnerRoot->getPosition().y;
}
void CRunner::changeface(const float dt) {
	float  cdtime = 1.0f;
	playerfacecd+= dt;
	if (playerfacecd >= 1.0f)playerfacecd = 1.0f;
	if (playerfacecd == cdtime) {
		if (playerface == 0) {//正常臉
			_normalFace->setVisible(true);
			_happyFace->setVisible(false);
			_depressedFace->setVisible(false);
			_body->setColor(Color3B(255, 255, 255));
		}
		else if (playerface == 1) {//笑臉
			_normalFace->setVisible(false);
			_happyFace->setVisible(true);
			_depressedFace->setVisible(false);
			playerface = 0;
			playerfacecd = 0;
			_body->setColor(Color3B(255, 255, 180));
		}
		else if (playerface ==2) {//哭臉
			_normalFace->setVisible(false);
			_happyFace->setVisible(false);
			_depressedFace->setVisible(true);
			playerface = 0;
			playerfacecd = 0;
			_body->setColor(Color3B(255, 180, 180));
		}
	}
}

void CRunner::changedieface() {
	_normalFace->setVisible(false);
	_happyFace->setVisible(false);
	_depressedFace->setVisible(true);
	_body->setColor(Color3B(255, 180, 180));
}