#ifndef __ANIMATIONACTION_SCENE_H__
#define __ANIMATIONACTION_SCENE_H__


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "Final\CRunner.h"
#include "Final\EnemyRock.h"

class AnimationAction : public cocos2d::Layer
{
private:
	cocos2d::Sequence *_mySequence;
	cocos2d::Action   *_myAction;



	//////////////////////////////////////////////////////
	cocos2d::ui::Text *_playerscoretext, *_Go123;
	CRunner *_playercharacter;
	EnemyRock *_rock01, *_rock02, *_rock03;
	cocos2d::Point _runnerbodyPt, _rockstartPt, _rockendPt;
	unsigned int _musiceffect[5];//����arr
	cocos2d::ui::Button *_cuberbtn, *_resetbtn;
	unsigned int _iplayerscore;
	int _ihp;
	cocos2d::ui::LoadingBar * _hpbar;
	float timeloader;
	bool _bstartGoflag, _bdieflag, _benemy1flag, _benemy2flag;
	//////////////////////////////////////////////////////



	// For Double Jump
	cocos2d::JumpBy   *_myJump;
	int _NoJumps;
	cocos2d::CallFunc *_mycallback;
	cocos2d::Point _runnerPt;

public:
	~AnimationAction();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();



	void CuberBtnTouchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void ResetBtnTouchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	//void CuberBtnTouchEvent(Ref *pSender, Widget::TouchEventType type);
	void playerchactermoveset();	//���a��/NODE����
	void rockback();
	void setstart();
	void setreplay();
	void die();
	void TTOGO(float dt);
	void enemyanim();



    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	//void CuberBtnTouchEvent(Ref *pSender, Widget::TouchEventType type);
	void doStep(float dt);

	// Action �� CallBack �禡
	void AnimationAction::actionFinished();

	//Ĳ�I
	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I�}�l�ƥ�
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I���ʨƥ�
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I�����ƥ� 

	// implement the "static create()" method manually
    CREATE_FUNC(AnimationAction);
};

#endif // __HELLOWORLD_SCENE_H__
