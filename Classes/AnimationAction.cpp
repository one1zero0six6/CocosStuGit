#include "AnimationAction.h"
#include "cocostudio/CocoStudio.h"
#include "Final\CRunner.h"

USING_NS_CC;

#define DOUBLEJUMP 1

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

Scene* AnimationAction::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AnimationAction::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

AnimationAction::~AnimationAction()
{
	if( _myAction != nullptr ) _myAction->release();
	if (_myJump != nullptr) _myJump->release();
	if (_mycallback != nullptr) _mycallback->release();

	AnimationCache::destroyInstance();  // ���� AnimationCache ���o���귽
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

// on "init" you need to initialize your instance
bool AnimationAction::init()
{
	_myAction = nullptr;
	_myJump = nullptr;
	_mycallback = nullptr;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("AnimationAction.csb");
    addChild(rootNode);

// �Q�ε{���������ͧǦC�V�ʵe 
// STEP 1 : Ū�J�x�s�h�i�Ϥ��� plist ��
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene101.plist");
// ------------------------------------------------------------------------------------------------- 
// ��k�@  �Q�� SpriteFrameCache ���x�s�C�@�i�n�s�򼷩񪺹Ϥ�

	//// STEP 2 : ���ͳs��Ϥ����ɦW�å[�J animation ��
	//auto frameCache = SpriteFrameCache::getInstance();
	//// �Q�� STL �� vector ���x�s�s�� SpriteFrame
	//Vector<SpriteFrame*> animFrames(8);
	//char tmp[50];
	//for (int j = 1; j <= 8; j++)
	//{
	//	sprintf(tmp, "cuber%02d.png", j); // ���� cuber01.png ~  cuber08.png
	//									  //�q plist �����o���ɦW�٨ëإ� spriteFrame
	//	auto frame = frameCache->getSpriteFrameByName(tmp);
	//	animFrames.pushBack(frame);
	//}
	//// STEP 3: �إ� animation
	//auto animation1 = Animation::createWithSpriteFrames(animFrames, 0.04f);

	//// STEP 4�G�إߧǦC�V�ʵe���D��
	//auto runner1 = Sprite::createWithSpriteFrameName("cuber01.png");
	//runner1->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 150);
	//this->addChild(runner1);

	//// STEP 5�G�ѥD��I�s�ʵe������
	//runner1->runAction(RepeatForever::create(Animate::create(animation1)));// �@�����Ƽ���

//--------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------- 
// ��k�G �Q���x�s�ǦC�V�ʵe�� plist �ӫإ�
/*
	// STEP 2: �H AnimationCache ��Ū���� plist ��
	auto animCache = AnimationCache::getInstance();
	animCache->addAnimationsWithFile("cuberanim.plist");
	auto animation2 = animCache->getAnimation("running");

	// STEP 3: �إ� animation
	auto action2 = RepeatForever::create(Animate::create(animation2));

	// STEP 4�G�إߧǦC�V�ʵe���D��
	auto runner2 = Sprite::createWithSpriteFrameName("cuber01.png");
	runner2->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f-150);
	this->addChild(runner2);

	// STEP 5�G�ѥD��I�s�ʵe������
	runner2->runAction(action2);// �@�����Ƽ���
*/
//--------------------------------------------------------------------------------------------------


// Action -----------------------------------------------------------------------------------------
	auto actionBody = Sprite::createWithSpriteFrameName("cuber01.png");
	actionBody->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	actionBody->setTag(101);	// �Ω���o�Ӫ���
	actionBody->setColor(Color3B(200, 209, 63));
	this->addChild(actionBody);
	// �����L���d�ҳ��ϥγo�� actionBody 

// BezierBy/BezierTo
	// BezierTo
	ccBezierConfig bezier;
	/*
	bezier.controlPoint_1 = Point(540, 720);
	bezier.controlPoint_2 = Point(140, 720);
	bezier.endPosition = Point(40, 360);
	BezierTo * bezierto = BezierTo::create(1.5f, bezier);
	actionBody->runAction(bezierto);
	*/
	// BezierBy
	//	bezier.endPosition = Point(0, visibleSize.height / 2.0f);
	/*
	bezier.controlPoint_1 = Point(-100, 360);
	bezier.controlPoint_2 = Point(-500, 360);
	bezier.endPosition = Point(-600, 0);
	BezierBy * bezierby = BezierBy::create(1.5f, bezier);
	actionBody->runAction(bezierby);
	// ���ͤϦV�� Action
	auto bezierbyBack = bezierby->reverse();
	// �N���P�� Action �զ��s�򼷩� Action �զX
	auto sequence = cocos2d::Sequence::create(bezierby, bezierbyBack, NULL);
	// ����o�� Action ����ǦC���զX
	actionBody->runAction(sequence);
	*/
//-------------------------------------------------------------------------------------------------

// MoveTo/MoveBy
	
	//MoveTo * moveto = MoveTo::create(1.25f, Point(40, 360));
	////actionBody->runAction(moveto);
	//// ���ͤϦV�� Action�A�W�@��H�ΥH�U���T��ܤ@����Y�i
	//MoveBy * moveby = MoveBy::create(1.25f, Point(-600, 0));	
	//auto movebyBack = moveby->reverse();
	//actionBody->runAction(Sequence::create(moveby, movebyBack, NULL));
	
//-------------------------------------------------------------------------------------------------

// JumpTo/JumpBy

//	JumpTo * jumpto = JumpTo::create(1.25f, Point(40, 360), 150, 3);
//	//actionBody->runAction(jumpto);
//	// ���ͤϦV�� Action�A�W�@��H�ΥH�U���T��ܤ@����Y�i
//	JumpBy * jumpby = JumpBy::create(1.25f, Point(-600, 0), 150, 3);
//	auto jumpbyBack = jumpby->reverse();
////	auto sequence = Sequence::create(jumpby, jumpbyBack, NULL);////////////////////////////
//	actionBody->runAction(Sequence::create(jumpby, jumpbyBack, NULL));
////	actionBody->runAction(sequence);

//-------------------------------------------------------------------------------------------------

// ScaleTo/ScaleTo
//	
//	ScaleTo * scaleto = ScaleTo::create(1.25f, 0.5f);
////	actionBody->runAction(scaleto);
//	// ���ͤϦV�� Action�A�W�@��H�ΥH�U���Ҧ��{���X�ܤ@����Y�i
//	ScaleBy * scaleby = ScaleBy::create(1.25f, 0.5f);
//	auto scalebyBack = scaleby->reverse();
//	//auto sequence = Sequence::create(scaleby, scalebyBack, NULL);
//	//actionBody->runAction(sequence);
//	auto sequence = Sequence::create(scaleby, scalebyBack, NULL);
//	actionBody->runAction(sequence);
	
//-------------------------------------------------------------------------------------------------

// FadeIn/FadeOut
/*
	FadeIn * fadein = FadeIn::create(1.25f);
	//actionBody->setOpacity(0);  // ��W�ϥ� FadeIn �������]�w�z���׬� 0
//	actionBody->runAction(fadein);
	FadeOut * fadeout = FadeOut::create(1.25f);
//	actionBody->runAction(fadeout);
	FadeTo * fadeto = FadeTo::create(1.25f, 128);
	auto fadeoutBack = fadeout->reverse();
	auto sequence = Sequence::create(fadeout, fadein, fadeto, NULL);
	actionBody->runAction(sequence);
*/
//-------------------------------------------------------------------------------------------------

// TintTo/TintBy

//	TintTo * tintto = TintTo::create(1.0f, Color3B(82, 131, 151));
////	actionBody->runAction(tintto);
//	TintBy * tintby = TintBy::create(1.0f,-118, -78, 88);
////	actionBody->runAction(tintby);
//	auto tintbyBack = tintby->reverse();
//	auto sequence2 = Sequence::create(tintby, tintbyBack, NULL);
//	actionBody->runAction(sequence2);

//-------------------------------------------------------------------------------------------------

// RotateTo/RotateBy
//	RotateTo * rotateto = RotateTo::create(1.0f, 60.0f);
////	actionBody->runAction(rotateto);	
//
//	RotateBy * rotateby = RotateBy::create(1.0f, 30.0f);
//	//actionBody->runAction(rotateby);
//	//	���� RotateBy ���֥[�ĪG   ---------------------------------
//	_myAction = (cocos2d::Action *)RotateBy::create(1.0f, 30.0f);
//	_myAction->retain();
	//---------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// �h�� Action ���ϥ�
	//JumpBy * jumpby = JumpBy::create(1.25f, Point(-600, 0), 150, 3);
	//auto jumpbyBack = jumpby->reverse();
	//auto sequence = Sequence::create(jumpby, jumpbyBack, NULL);
	//actionBody->runAction(Sequence::create(jumpby, jumpbyBack, NULL));

	//ScaleBy * scaleby = ScaleBy::create(1.25f, 0.5f);
	//auto scalebyBack = scaleby->reverse();
	//sequence = Sequence::create(scaleby, scalebyBack, NULL);
	//actionBody->runAction(sequence);

	////// �ϥ� Spawn
	//auto mySpawn = Spawn::createWithTwoActions(jumpby, scaleby);
	//actionBody->runAction(mySpawn);
//-------------------------------------------------------------------------------------------------

//  Spawn �Φb Sequence ��
	////JumpBy * jumpby = JumpBy::create(1.25f, Point(-600, 0), 150, 3);
	////auto jumpbyBack = jumpby->reverse();
	////TintTo * tintto = TintTo::create(1.0f, Color3B(82, 131, 151));
	////auto mySpawn = Spawn::createWithTwoActions(jumpby, tintto);
	////auto sequence = Sequence::create(mySpawn, jumpbyBack, NULL);
	////actionBody->runAction(sequence);
//-------------------------------------------------------------------------------------------------

//  EaseSineOut �P EaseSineIn �f�t Action ���ϥ�
	//MoveBy * moveby = MoveBy::create(1.0f, Point(-600, 0));
	//auto movebyBack = moveby->reverse();
	//auto moveSineOut = EaseSineOut::create(moveby);
	//auto delay = DelayTime::create(0.125f);
	//auto moveSineIn = EaseSineIn::create(movebyBack);
	//actionBody->runAction(Sequence::create(moveSineOut, delay, moveSineIn, NULL));
//-------------------------------------------------------------------------------------------------

//  EaseOut �P EaseIn �f�t Action ���ϥ�
	//MoveBy * moveby = MoveBy::create(1.0f, Point(-600, 0));
	//auto movebyBack = moveby->reverse();
	//auto moveOut = EaseOut::create(moveby,3);
	//auto delay = DelayTime::create(0.125f);
	//auto moveIn = EaseIn::create(movebyBack, 3);
	//actionBody->runAction(Sequence::create(moveOut, delay, moveIn, NULL));
//-------------------------------------------------------------------------------------------------

//  Action �P CallBack Function���ϥ�
	//MoveBy * moveby = MoveBy::create(1.0f, Point(-600, 0));
	//auto moveOut = EaseOut::create(moveby,3);
	//auto callback = CallFunc::create(this, callfunc_selector(AnimationAction::actionFinished));
	//actionBody->runAction(Sequence::create(moveOut, callback, NULL));
//-------------------------------------------------------------------------------------------------

// Double Jump 
#ifdef DOUBLEJUMP
	_NoJumps = 0;
	_myJump = JumpBy::create(0.65f, Point(0, 0), 150, 1);
	_myJump->retain();
	actionBody->setScale(0.65f);
	actionBody->setPosition(visibleSize.width/2.0f, visibleSize.height / 2.0f-50);
	_runnerPt = actionBody->getPosition();
	_mycallback = CallFunc::create(this, callfunc_selector(AnimationAction::actionFinished));
	_mycallback->retain();
#endif
//-------------------------------------------------------------------------------------------------

// CSB �P�{���إߧǦC�V�ʵe���զX
// Example 1 : ASimpleRunner 
//
//	// Ū�J csb �ɨè��o runnerRoot
//	auto runnerRoot = CSLoader::createNode("ASimpleRunner.csb");
//	// �]�w runnerRoot ����m�A�å[�J������
//	runnerRoot->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
//	Point pt = runnerRoot->getPosition();
//	runnerRoot->setScale(0.70f);
//	this->addChild(runnerRoot);
//
//	// �q runnderNode ���o Cuber01_1 �ëإ� Sprite
//	auto runnerBody = (cocos2d::Sprite *)runnerRoot->getChildByName("cuber01_1");
//	// �]�w runner ���C��
//	runnerBody->setColor(Color3B(255, 200, 50));
//
//	// �إ� runnerBody �һݪ��ǦC�V�ʵe
//	auto animCache1 = AnimationCache::getInstance();
//	animCache1->addAnimationsWithFile("cuberanim.plist");
//	auto animation3 = animCache1->getAnimation("running");
//	auto action3 = RepeatForever::create(Animate::create(animation3));
//
//	// �إ� runnerRoot �һݪ� jumpAction
//	auto jumpAction = cocos2d::JumpBy::create(1.25f, Point(-500 , 0), 100, 3);
//	auto jumpBack = jumpAction->reverse();
//	//�H runnerBody ���D��h�����k�@�ҫإߪ� Animation
//	runnerBody->runAction(action3);
//	//�H runnerRoot �P�B���� jumpAction
////	runnerRoot->runAction(cocos2d::Sequence::create(jumpAction, jumpBack, NULL));

//-------------------------------------------------------------------------------------------------

// Example 2 : RunnerNode
	//auto runner = CRunner("RunnerNode.csb", *this);
	//runner.setPosition(visibleSize.width/ 2.0f + 300, visibleSize.height / 2.0f);
	//runner.setAnimation("cuberanim.plist");
	//runner.go();
//-------------------------------------------------------------------------------------------------
	
	_listener1 = EventListenerTouchOneByOne::create();	//�Ыؤ@�Ӥ@��@���ƥ��ť��
	_listener1->onTouchBegan = CC_CALLBACK_2(AnimationAction::onTouchBegan, this);		//�[�JĲ�I�}�l�ƥ�
	_listener1->onTouchMoved = CC_CALLBACK_2(AnimationAction::onTouchMoved, this);		//�[�JĲ�I���ʨƥ�
	_listener1->onTouchEnded = CC_CALLBACK_2(AnimationAction::onTouchEnded, this);		//�[�JĲ�I���}�ƥ�

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//�[�J��Ыت��ƥ��ť��
	this->schedule(CC_SCHEDULE_SELECTOR(AnimationAction::doStep));
    return true;
}

void AnimationAction::actionFinished()
{
	// do something on complete
	CCLOG("B %d\n", _NoJumps);

#ifdef DOUBLEJUMP
	_NoJumps--;
	if (_NoJumps == 1) {
		auto moveto = MoveTo::create(0.15f, _runnerPt);
		auto actionBody = this->getChildByTag(101);
		actionBody->runAction(moveto);
		_NoJumps--;
	}
#endif

}


void AnimationAction::doStep(float dt)
{

}

void AnimationAction::CuberBtnTouchEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
		case Widget::TouchEventType::BEGAN:
			log("Touch Down");
			break;
		case Widget::TouchEventType::MOVED:
			log("Touch Move");
			break;
		case Widget::TouchEventType::ENDED:
			log("Touch Up");
			break;
		case Widget::TouchEventType::CANCELED:
			log("Touch Cancelled");
			break;
		default:
			break;
	}
}

bool AnimationAction::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//Ĳ�I�}�l�ƥ�
{
	Point touchLoc = pTouch->getLocation();

#ifdef DOUBLEJUMP
	auto actionBody = this->getChildByTag(101);
	if (_NoJumps == 0) {  // �Ĥ@���Q���U
		actionBody->runAction(Sequence::create(_myJump, _mycallback, NULL));
		_NoJumps++;
	}
	else if(_NoJumps == 1 ){  // �ĤG���Q���U
		_NoJumps++;
		actionBody->stopAllActions();
		actionBody->runAction(Sequence::create(_myJump, _mycallback, NULL));
	}
#endif
	return true;
}

void  AnimationAction::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //Ĳ�I���ʨƥ�
{
	Point touchLoc = pTouch->getLocation();

}

void  AnimationAction::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //Ĳ�I�����ƥ� 
{
	Point touchLoc = pTouch->getLocation();

//	���� RotateBy ���֥[�ĪG   ---------------------------------
	//auto actionbody = this->getChildByTag(101);
	//actionbody->runAction(_myAction);
	//CCLOG("%d", actionbody->getNumberOfRunningActions());
//--------------------------------------------------------------
}