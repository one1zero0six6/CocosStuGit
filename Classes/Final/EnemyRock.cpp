#include "EnemyRock.h"

USING_NS_CC;
#define SCORECOUNT1 100;
#define SCORECOUNT2 200;
#define SCORECOUNT3 300;
#define HPCOUNT1 1;
#define HPCOUNT2 2;
#define HPCOUNT3 3;
EnemyRock::EnemyRock(const unsigned int enemykind ,const char *csbname, cocos2d::Layer &parent)
{
	_ienemykind = enemykind;
	_animflag = true;
	_fcollision = true;
	// 讀取角色
	_enemyroot = CSLoader::createNode(csbname);
	_enemyroot->setPosition(0, 0); // 預設放在 (0,0) 
	_enemyroot->setScale(0.70f);
	_enemypictbody = (cocos2d::Sprite *)_enemyroot->getChildByName("triblock");
	if (_ienemykind == 3)_enemypictbody->setVisible(false);
	setenemysize();
	parent.addChild(_enemyroot);
}

EnemyRock::~EnemyRock()
{
	//if(_fanimaction)_action->release();
}

void EnemyRock::go(){
	//_body->runAction(_action);
}

void EnemyRock::setAnimation(const char *plistFile){


	//// 此處假設儲存角色所有動態圖片的 plist 檔已經讀入
	//auto cache = AnimationCache::getInstance();
	////AnimationFrame
	//cache->addAnimationsWithFile(plistFile);
	//auto animation = cache->getAnimation("running");
	//_action = RepeatForever::create(Animate::create(animation));
	//_action->retain();
}


void EnemyRock::setPosition(const cocos2d::Point &pos) {
	_enemyroot->setPosition(pos);
}
void EnemyRock::setPosition(const float x, const float y) {
	_enemyroot->setPosition(x, y);
}

void EnemyRock::setenemysize() {
	_enemysize = _enemypictbody->getContentSize();
}
void EnemyRock::collision(int &_ihp, unsigned int &_iplayerscore , unsigned int &playerface, const cocos2d::Point &playerpos) {//用_enemyroot的pos計算
	bool ontouch = false;
	Point nowlocation;

	nowlocation = _enemyroot->getPosition();
	if (playerpos.x >= (nowlocation.x - _enemysize.width / 2) && playerpos.x <= (nowlocation.x + _enemysize.width / 2)) {
		if (playerpos.y >= (nowlocation.y - _enemysize.height / 2) && playerpos.y <= (nowlocation.y + _enemysize.height / 2)) {
			ontouch = true;
		}
	}

	if (ontouch &&_fcollision) {
		playerface = 2;
		_fcollision = false;
		switch (_ienemykind)
		{
		case 1:
			_ihp -= HPCOUNT1;
			break;
		case 2:
			_ihp -= HPCOUNT2;
			break;
		case 3:
			_ihp -= HPCOUNT3;
			break;
		default:
			break;
		}
	}
	if (_enemyroot->getPosition().x > playerpos.x + 20 && _fcollision)
	{
		playerface = 1;
		_fcollision = false;

		switch (_ienemykind)
		{
		case 1:
			_iplayerscore += SCORECOUNT1;
			break;
		case 2:
			_iplayerscore += SCORECOUNT2;
			break;
		case 3:
			_iplayerscore += SCORECOUNT3;
			break;
		default:
			break;
		}

	}
}