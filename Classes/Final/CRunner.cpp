#include "CRunner.h"

USING_NS_CC;

//
// �إߨ��⤧�e�A�������T�w�w�gŪ�J�x�s����Ҧ��ʺA�Ϥ��� plist ��
//

CRunner::CRunner(const char *csbname, cocos2d::Layer &parent)
{
	playerface = 0;
	playerfacecd = 0.0;//��CD
	// Ū������
	_runnerRoot = CSLoader::createNode(csbname);
//	_runnerRoot = (cocos2d::Node*)getNode->getChildByName("RunnerRoot");
	_runnerRoot->setPosition(0,0); // �w�]��b (0,0) 
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
	// ���B���]�x�s����Ҧ��ʺA�Ϥ��� plist �ɤw�gŪ�J
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
		if (playerface == 0) {//���`�y
			_normalFace->setVisible(true);
			_happyFace->setVisible(false);
			_depressedFace->setVisible(false);
			_body->setColor(Color3B(255, 255, 255));
		}
		else if (playerface == 1) {//���y
			_normalFace->setVisible(false);
			_happyFace->setVisible(true);
			_depressedFace->setVisible(false);
			playerface = 0;
			playerfacecd = 0;
			_body->setColor(Color3B(255, 255, 180));
		}
		else if (playerface ==2) {//���y
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