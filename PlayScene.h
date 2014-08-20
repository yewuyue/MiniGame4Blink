#pragma once
#include "cocos2d.h"
#include "PatientManager.h"
#include <iostream>
//#include <hash_map>
#include "config.h"
#include "EnemyBase.h"


USING_NS_CC;
const int KILL_BUTTON_NUMBER = 3;
const int CIRCLE_RADIUS = 55;

class Circle{
public:
	float radius;
	Vec2 vec;
	Circle(float f, Vec2 v) :radius(f), vec(v.x, v.y){}
};


class PlayLayer : public cocos2d::CCLayer
{
private:
  //CCArmature* armature;
	CCSize winSize;
	TMXTiledMap* _tilemap;
	TMXObjectGroup* _objgroup;
	SpriteBatchNode *_spritesheet;
	Vector<Node *> _pointsvec;
	CCSprite*            m_oButtons[KILL_BUTTON_NUMBER];				//储存按键信息

	E_BLINK_COLOR_TYPE   m_eButtonsColor[KILL_BUTTON_NUMBER];			//对应按键的键值

	std::string			 m_strButtonImagePath[KILL_BUTTON_NUMBER];		//对应按键的图片

	Circle*              m_pButtonPosition[KILL_BUTTON_NUMBER];			//每个按钮的位置

	unsigned int		 m_uLastPressKey;								//上一次按键（只有在上一次按键未能消除且可匹配时存值，否则置零）

	CPatientManager*     m_pPatientManager;

	unsigned int		 m_uClickCount;

	bool				 m_bKeyPressed[KILL_BUTTON_NUMBER];


public:
	//PlayLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void setBackground(const char * imagePath);
	

	void createCartoonPatient();
	//void armatureMove(float delta);

	void initPointsVector(float offx);

	
	void multiButtonListener();

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

	void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);


	//原按钮
	void createButton();

	//文字
	void setLabelTTF(CCPoint showPosition,const char* showStr);
	void setLabelTTF(CCPoint showPosition, int showInt);

	//病人
	void patientFactory(const char * filePath, float whichRoad, unsigned int firstKey, unsigned int secondKey);

	void zygotePatient(float delta);

	void killPatient();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* createScene();
	
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);


	// implement the "static node()" method manually
	CREATE_FUNC(PlayLayer);
};