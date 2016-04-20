#include "AnimationAction.h"
#include "cocostudio/CocoStudio.h"
//#include "Final\CRunner.h"

USING_NS_CC;

//#define DOUBLEJUMP 1
#define HEALTHPOINT 5


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

	SimpleAudioEngine::getInstance()->unloadEffect("./music/gainpoint.mp3"); // ���񭵮���
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
    
    auto rootNode = CSLoader::createNode("AnimationAction.csb"); //AnimationAction.csb
    addChild(rootNode);

// �Q�ε{���������ͧǦC�V�ʵe 
// STEP 1 : Ū�J�x�s�h�i�Ϥ��� plist ��
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene101.plist");


//SimpleAudioEngine	���֭��� --------------------------------------------------------------------------
	SimpleAudioEngine::getInstance()->playBackgroundMusic("./music/SR_bg.mp3", true);
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic();	// ����I������
	/*		playBackgroundMusic ��Ū���������ɡA�ä��|�Q�[�J�������x�s�A�ҥH��������A�����������ɡA�O�o������������
			�i�� SimpleAudioEngine::isBackgroundMusicPlaying() �h�d��  �^�ǭ� true �N���b����Afalse �N��S��*/
	SimpleAudioEngine::getInstance()->preloadEffect("./music/running.mp3");	// �w�����J������
	_musiceffect[0] = SimpleAudioEngine::getInstance()->playEffect("./music/gainpoint.mp3");  // ���񭵮���
	SimpleAudioEngine::getInstance()->stopEffect(_musiceffect[0]);  // ����ļ���A�����ϥ� PlayEffect �Ǧ^�� id
	//SimpleAudioEngine::getInstance()->unloadEffect("./music/running.mp3");  // ���񭵮���
//AnimCache ----------------------------------------------------------------------------------------
	auto animCache = AnimationCache::getInstance();
	animCache->addAnimationsWithFile("cuberanim.plist");
// �ǦC�V�ʵe -------------------------------------------------------------------------------------
	auto Viewer = (ActionTimeline *)CSLoader::createTimeline("AnimationAction.csb");
	rootNode->runAction(Viewer);
	Viewer->gotoFrameAndPlay(0, 28, true);//21
// Player&jump -----------------------------------------------------------------------------------------
	//_playercharacter = new CRunner("RunnerNode.csb", *this);
	_playercharacter = new CRunner("RunnerNode2.csb", *this);
	_playercharacter->setPosition(visibleSize.width/ 2.0f + 300, visibleSize.height / 2.0f);
	_playercharacter->setAnimation("cuberanim.plist");
	_playercharacter->go();
	//jump&back
	_NoJumps = 0;
	_myJump = JumpBy::create(0.65f, Point(0, 0), 150, 1);
	_myJump->retain();
	_runnerbodyPt = _playercharacter->_runnerRoot->getPosition();

	_runnerPt = _playercharacter->_allRoot->getPosition();//_allRoot
	_mycallback = CallFunc::create(this, callfunc_selector(AnimationAction::actionFinished));
	_mycallback->retain();
// Score -----------------------------------------------------------------------------------------
	_playerscoretext = (cocos2d::ui::Text *)rootNode->getChildByName("Text_1");
	_iplayerscore = 0;
	_playerscoretext->setString(StringUtils::format("Score %d", _iplayerscore));
// 321GO -----------------------------------------------------------------------------------------
	_Go123 = (cocos2d::ui::Text *)rootNode->getChildByName("GO123");
	_Go123->setVisible(false);
	_bstartGoflag = false;
//HP BAR-------------------------------------------------------------------------------------------
	_hpbar = (cocos2d::ui::LoadingBar *)rootNode->getChildByName("HPbar");
	_hpbar->setDirection(LoadingBar::Direction::LEFT);
	_hpbar->setPercent(100* HEALTHPOINT/ HEALTHPOINT);
	_ihp = HEALTHPOINT;
	_bdieflag = false;
//Rock -----------------------------------------------------------------------------------------
	//_rockstartPt = Point(-100, visibleSize.height / 2.0f);
	//_rockendPt = Point(visibleSize.width + 100, visibleSize.height / 2.0f - 30);
	_rockstartPt = Point(-100, visibleSize.height / 2.0f-10 );
	_rockendPt = Point(visibleSize.width+100, visibleSize.height / 2.0f-10);
	_rock01 = new EnemyRock(1,"triangleNodeN.csb", *this);
	_rock01->setPosition(_rockstartPt);


	_rock02 = new EnemyRock(2,"triangleNode.csb", *this);
	_rock02->setPosition(_rockstartPt);
	_rock02->_enemyroot->setVisible(false);

	

	_rock03 = new EnemyRock(3, "triangleNodeT.csb", *this);
	_rock03->setPosition(_rockstartPt);
	_rock03->_enemyroot->setVisible(false);

//StartBtn -------------------------------------------------------------------------
	//cuberbtn = dynamic_cast<Button*>(rootNode->getChildByName("Cuberbtn"));
	_cuberbtn = (cocos2d::ui::Button *)(rootNode->getChildByName("Cuberbtn"));
	_cuberbtn->addTouchEventListener(CC_CALLBACK_2(AnimationAction::CuberBtnTouchEvent, this));
//Resetbtn ----------------------------
	_resetbtn = (cocos2d::ui::Button *)(rootNode->getChildByName("Reset"));
	_resetbtn->addTouchEventListener(CC_CALLBACK_2(AnimationAction::ResetBtnTouchEvent, this));
	_resetbtn->setVisible(false);


	//MoveTo * moveto = MoveTo::create(1.25f, Point(40, 360));
	//enemyrock->runAction(moveto);
	//// ���ͤϦV�� Action�A�W�@��H�ΥH�U���T��ܤ@����Y�i
	//MoveBy * moveby = MoveBy::create(1.25f, Point(-600, 0));
	//auto movebyBack = moveby->reverse();
	//enemyrock->runAction(Sequence::create(moveby, movebyBack, NULL));
/////////// -----------------------------------------------------------------------//////////////////


	////auto actionBody = Sprite::createWithSpriteFrameName(runnerNode);
	auto actionBody = Sprite::createWithSpriteFrameName("cuber01.png");
	////auto actionBody = (cocos2d::Sprite *)animRoot->getChildByName("cuber01_1");
	//actionBody->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	//actionBody->setScale(0.70f);
	//actionBody->setTag(101);	// �Ω���o�Ӫ���
	//actionBody->setColor(Color3B(200, 209, 63));
	//this->addChild(actionBody);

		// �إ� runnerBody �һݪ��ǦC�V�ʵe
	//auto animCache1 = AnimationCache::getInstance();
	//animCache1->addAnimationsWithFile("cuberanim.plist");
	//auto animation3 = animCache1->getAnimation("running");
	//auto action3 = RepeatForever::create(Animate::create(animation3));//���Ƽ���
	//actionBody->runAction(action3);





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
	/*
	MoveTo * moveto = MoveTo::create(1.25f, Point(40, 360));
	actionBody->runAction(moveto);
	// ���ͤϦV�� Action�A�W�@��H�ΥH�U���T��ܤ@����Y�i
	MoveBy * moveby = MoveBy::create(1.25f, Point(-600, 0));	
	auto movebyBack = moveby->reverse();
	actionBody->runAction(Sequence::create(moveby, movebyBack, NULL));
	*/
//-------------------------------------------------------------------------------------------------

// JumpTo/JumpBy
/*
	JumpTo * jumpto = JumpTo::create(1.25f, Point(40, 360), 150, 3);
	actionBody->runAction(jumpto);
	// ���ͤϦV�� Action�A�W�@��H�ΥH�U���T��ܤ@����Y�i
	JumpBy * jumpby = JumpBy::create(1.25f, Point(-600, 0), 150, 3);
	auto jumpbyBack = jumpby->reverse();
	auto sequence = Sequence::create(jumpby, jumpbyBack, NULL);
	actionBody->runAction(Sequence::create(jumpby, jumpbyBack, NULL));
*/
//-------------------------------------------------------------------------------------------------

// ScaleTo/ScaleTo
	/*
	ScaleTo * scaleto = ScaleTo::create(1.25f, 0.5f);
//	actionBody->runAction(scaleto);
	// ���ͤϦV�� Action�A�W�@��H�ΥH�U���Ҧ��{���X�ܤ@����Y�i
	ScaleBy * scaleby = ScaleBy::create(1.25f, 0.5f);
	auto scalebyBack = scaleby->reverse();
	auto sequence = Sequence::create(scaleby, scalebyBack, NULL);
	actionBody->runAction(sequence);
	*/
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
/*
	TintTo * tintto = TintTo::create(1.0f, Color3B(82, 131, 151));
	actionBody->runAction(tintto);
	TintBy * tintby = TintBy::create(1.0f,-118, -78, 88);
//	actionBody->runAction(tintby);
	//auto tintbyBack = tintby->reverse();
	//auto sequence = Sequence::create(tintby, tintbyBack, NULL);
	//actionBody->runAction(sequence);
*/
//-------------------------------------------------------------------------------------------------

// RotateTo/RotateBy
	RotateTo * rotateto = RotateTo::create(1.0f, 60.0f);
//	actionBody->runAction(rotateto);	

	RotateBy * rotateby = RotateBy::create(1.0f, 30.0f);
	//actionBody->runAction(rotateby);
	//	���� RotateBy ���֥[�ĪG   ---------------------------------
	//_myAction = (cocos2d::Action *)RotateBy::create(1.0f, 30.0f);
	//_myAction->retain();
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

	// �ϥ� Spawn
	//auto mySpawn = Spawn::createWithTwoActions(jumpby, scaleby);
	//actionBody->runAction(mySpawn);
//-------------------------------------------------------------------------------------------------

//  Spawn �Φb Sequence ��
	//JumpBy * jumpby = JumpBy::create(1.25f, Point(-600, 0), 150, 3);
	//auto jumpbyBack = jumpby->reverse();
	//TintTo * tintto = TintTo::create(1.0f, Color3B(82, 131, 151));
	//auto mySpawn = Spawn::createWithTwoActions(jumpby, tintto);
	//auto sequence = Sequence::create(mySpawn, jumpbyBack, NULL);
	//actionBody->runAction(sequence);
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
	//auto moveSineOut = EaseOut::create(moveby,3);
	//auto delay = DelayTime::create(0.125f);
	//auto moveSineIn = EaseIn::create(movebyBack, 3);
	//actionBody->runAction(Sequence::create(moveSineOut, delay, moveSineIn, NULL));
//-------------------------------------------------------------------------------------------------

//  Action �P CallBack Function���ϥ�
	//MoveBy * moveby = MoveBy::create(1.0f, Point(-600, 0));
	//auto moveSineOut = EaseOut::create(moveby,3);
	//auto callback = CallFunc::create(this, callfunc_selector(AnimationAction::actionFinished));
	//actionBody->runAction(Sequence::create(moveSineOut, callback, NULL));
//-------------------------------------------------------------------------------------------------

// Double Jump 
//-------------------------------------------------------------------------------------------------

// CSB �P�{���إߧǦC�V�ʵe���զX
//// Example 1 : ASimpleRunner 
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
//	//auto jumpAction = cocos2d::JumpBy::create(1.25f, Point(-500 , 0), 100, 3);////
//	//auto jumpBack = jumpAction->reverse();////
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
//SETStart ---------------------------
//	setstart();
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
	SimpleAudioEngine::getInstance()->stopEffect(_musiceffect[0]);
	_NoJumps--;
	if (_NoJumps == 1) {
		SimpleAudioEngine::getInstance()->stopEffect(_musiceffect[0]);
		auto moveto = MoveTo::create(0.15f, _runnerPt);
		_playercharacter->_allRoot->runAction(moveto);
		_NoJumps--;
	}
}


void AnimationAction::doStep(float dt)
{
	//�o���]�m
	if (_ihp<=0)_bdieflag = true;
	if(_bstartGoflag)TTOGO(dt);
	_playerscoretext->setString(StringUtils::format("Score %d", _iplayerscore));
	_playercharacter->changeface(dt);
	_hpbar->setPercent(100 * _ihp / HEALTHPOINT);
	if(!_bdieflag)rockback();
	else if(_bdieflag && _ihp <= 0)die();

}

void AnimationAction::CuberBtnTouchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
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
			setstart();
			_cuberbtn->setVisible(false);
			_resetbtn->setVisible(true);
			break;
		case Widget::TouchEventType::CANCELED:
			log("Touch Cancelled");
			break;
		default:
			break;
	}
}
void AnimationAction::ResetBtnTouchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type) {
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		log("Touch Up");
		setreplay();
		_resetbtn->setVisible(false);
		_cuberbtn->setVisible(true);
		break;
	default:
		break;
	}
}
bool AnimationAction::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//Ĳ�I�}�l�ƥ�
{
	Point touchLoc = pTouch->getLocation();

	
	if (_NoJumps == 0) {  // �Ĥ@���Q���U
		SimpleAudioEngine::getInstance()->playEffect("./music/gainpoint.mp3");  // ���񭵮���
		playerchactermoveset();
		_NoJumps++;
	}
	else if (_NoJumps == 1) {  // �ĤG���Q���U
		SimpleAudioEngine::getInstance()->playEffect("./music/gainpoint.mp3");  // ���񭵮���
		_NoJumps++;
		_playercharacter->_allRoot->stopAllActions();
		playerchactermoveset();
	}

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




void  AnimationAction::playerchactermoveset() {
	auto sequencejump = Sequence::create(_myJump, _mycallback, NULL);
	_playercharacter->_allRoot->runAction(sequencejump);
}

void AnimationAction::rockback() {
	
	_playercharacter->getrealPos(_runnerbodyPt);//���o���a��m
	enemyanim();
	 _rock01->collision(_ihp, _iplayerscore, _playercharacter->playerface, _runnerbodyPt);//�I��
	 _rock02->collision(_ihp, _iplayerscore, _playercharacter->playerface, _runnerbodyPt);//�I��
	 _rock03->collision(_ihp, _iplayerscore, _playercharacter->playerface, _runnerbodyPt);//�I��

	if (_rock01->_enemyroot->getPosition().x >= _rockendPt.x-10) {
		_rock01->_enemyroot->setPosition(_rockstartPt);
		_rock01->_fcollision = true;
		auto  enemyrockmoveto = MoveTo::create(3.5f, _rockendPt);
		_rock01->_enemyroot->runAction(enemyrockmoveto);
	}
	if (_rock02->_enemyroot->getPosition().x >= _rockendPt.x - 10) {
		_rock02->_enemyroot->setPosition(_rockstartPt);
		_rock02->_enemyroot->setVisible(false);
		_rock02->_animflag = true;
		_rock02->_fcollision = true;
		auto  enemyrockmoveto = MoveTo::create(3.5f, _rockendPt);
		_rock02->_enemyroot->runAction(enemyrockmoveto);
	}
	if (_rock03->_enemyroot->getPosition().x >= _rockendPt.x - 10) {
		_rock03->_enemyroot->setPosition(_rockstartPt);
		_rock03->_enemyroot->setVisible(false);
		_rock03->_animflag = true;
		_rock03->_fcollision = true;
		auto  enemyrockmoveto = MoveTo::create(3.5f, _rockendPt);
		_rock03->_enemyroot->runAction(enemyrockmoveto);
	}

}

void AnimationAction::setstart() {
	_Go123->setVisible(true);
	_bdieflag = false;
	_bstartGoflag = true;
	_benemy1flag = true;
	_benemy2flag = true;
	timeloader = 0.0;
	_ihp = HEALTHPOINT;
	_iplayerscore = 0;


	_rock01->_fcollision = true;
	_rock01->_enemyroot->setPosition(_rockstartPt);//���]�ĤH��m
	_rock02->_fcollision = true;
	_rock02->_enemyroot->setPosition(_rockstartPt);//���]�ĤH��m
	_rock03->_fcollision = true;
	_rock03->_enemyroot->setPosition(_rockstartPt);//���]�ĤH��m
}

void AnimationAction::setreplay() {
	_Go123->setVisible(false);
	_Go123->setString(StringUtils::format(""));
	
	_ihp = HEALTHPOINT;
	_iplayerscore = 0;

	_rock01->_enemyroot->stopAllActions();//�Ȱ��ĤH����
	_rock02->_enemyroot->stopAllActions();//�Ȱ��ĤH����
	_rock03->_enemyroot->stopAllActions();//�Ȱ��ĤH����
}
void AnimationAction::die() {
	_playercharacter->changedieface();
	_Go123->setVisible(true);
	_Go123->setString(StringUtils::format("fail"));
		
}
void AnimationAction::TTOGO(float dt) {
	timeloader+= dt;
	if (timeloader >= 6.0f ) {
		_bstartGoflag = false;
		timeloader = 6.0f;

		auto  enemyrockmoveto = MoveTo::create(3.5f, _rockendPt);
		_rock03->_enemyroot->runAction(enemyrockmoveto);

	}
	if (timeloader >= 5.0f && _benemy2flag) {
		auto  enemyrockmoveto = MoveTo::create(3.5f, _rockendPt);
		_rock02->_enemyroot->runAction(enemyrockmoveto);
		_benemy2flag = false;
	}
	else if (timeloader >= 4.0f && _benemy1flag){
		_Go123->setVisible(false);
		auto  enemyrockmoveto = MoveTo::create(3.5f, _rockendPt);
		_rock01->_enemyroot->runAction(enemyrockmoveto);
		_benemy1flag = false;
	}
	//GO//1//2//3
	else if (timeloader >= 3.0f)	_Go123->setString(StringUtils::format("GO"));
	else if (timeloader >= 2.0f)	_Go123->setString(StringUtils::format("1"));
	else if (timeloader >= 1.0f) 	_Go123->setString(StringUtils::format("2"));
	else if (timeloader >= 0.0f) 	_Go123->setString(StringUtils::format("3"));
}
void AnimationAction::enemyanim() {
	if (_rock02->_enemyroot->getPosition().x >= 300 && _rock02->_animflag) {
		_rock02->_enemyroot->setVisible(true);
		_rock02->_animflag = false;
		//�ĤH�ʵeTAT -------------------------------------------------------------------------
		auto enemyanimaction = (ActionTimeline *)CSLoader::createTimeline("triangleNode.csb");
		enemyanimaction->gotoFrameAndPlay(0, 35, false);
		_rock02->_enemyroot->runAction(enemyanimaction);
	}

	if (_rock03->_enemyroot->getPosition().x >= 600 && _rock03->_animflag) {
		_rock03->_enemyroot->setVisible(true);
		_rock03->_animflag = false;
		//�ĤH�ʵeTAT -------------------------------------------------------------------------
		auto enemyanimaction = (ActionTimeline *)CSLoader::createTimeline("triangleNodeT.csb");
		enemyanimaction->gotoFrameAndPlay(0, 32, true);
		_rock03->_enemyroot->runAction(enemyanimaction);
	}
}
