#include "PlayScene.h"
//#define CCLOG //
Scene* PlayLayer::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PlayLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);


	// return the scene
	return scene;
}

bool PlayLayer::init()
{	
	//初始化参数

	m_uLastPressKey = 0;

	m_uClickCount = 0;

	m_pPatientManager = CPatientManager::GetInstance(this);
	winSize = Director::getInstance()->getWinSize();

	//设置背景
	PlayLayer::setBackground("background.png");
	//消除按钮
	PlayLayer::createButton();
	//出怪
	this->setTouchEnabled(true);

	PlayLayer::multiButtonListener();

	this->schedule(schedule_selector(PlayLayer::zygotePatient), 4);
	
	return true;
}

void PlayLayer::setBackground(const char * imagePath)
{
	CCSprite *background = CCSprite::create(imagePath);
	background->setAnchorPoint(ccp(0, 0));
	background->setPosition(ccp(0, 0));
	this->addChild(background);
}

//创建人物动画
void PlayLayer::createCartoonPatient()
{	
	//添加地图
	_tilemap = TMXTiledMap::create("blink_tilemap.tmx");

	

	auto bglayer = _tilemap->getLayer("bg");
	bglayer->setAnchorPoint(Point(0, 0));
	bglayer->setPosition(ccp(0,0));

	_objgroup = _tilemap->getObjectGroup("path");

	this->addChild(_tilemap, -1);

	//添加sprite
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite1.plist");
	_spritesheet = SpriteBatchNode::create("sprite1.png");
	this->addChild(_spritesheet);

	/*
	Sprite *_sprite = Sprite::createWithSpriteFrameName("sprite1.png");
	_sprite->setPosition( Point(winSize.width/2, winSize.height/2) );
	_spritesheet->addChild( _sprite );
	*/

	//
	float offx = (_tilemap->getContentSize().width - winSize.width) / 2;
	initPointsVector(offx);
	Zoombie *zoombie = Zoombie::createZoombie(_pointsvec);
	zoombie->setScale(0.3f);
	this->addChild(zoombie);

	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Cowboy0.png", "Cowboy0.plist", "Cowboy.ExportJson");
	//CCArmatureDataManager::getInstance()->addArmatureFileInfo("DemoPlayer.ExportJson");
	//armature = Armature::create("DemoPlayer");
	//armature->setTag(1);
	//armature->setPosition(ccp(initX, 200));
	//armature->setScale(0.1);
	////CCActionInterval * moveBy = CCMoveBy::create(5, ccp(-700, 0));
	//armature->getAnimation()->playByIndex(0);
	//this->armature->setMovementEventCallFunc(this, movementEvent_selector(Player::onAnimationEvent));
	//this->addChild(armature);

	//this->schedule(schedule_selector(PlayLayer::armatureMove, 4));

	////
	//CCComRender *pRender = static_cast<CCComRender*>(playerNode->getChildByTag(10004)->getComponent("CCArmature"));
	//this->playerNode = playerNode->getChildByTag(10004);
	//CCArmature* animationNode = static_cast<CCArmature*>(pRender->getNode());
	//this->animation = animationNode->getAnimation();
	//this->animation->setMovementEventCallFunc(this, movementEvent_selector(Player::onAnimationEvent));
	//currentState = IDLE;
	//newState = IDLE;
	//lockState = false;
}

void PlayLayer::initPointsVector(float offx)
{
	Node *runOfPoint = NULL;

	int count = 1;
	ValueMap point;
	point = _objgroup->getObject(std::to_string(count));

	while (point.begin() != point.end())
	{
		float x = point.at("x").asFloat();
		float y = point.at("y").asFloat();

		runOfPoint = Node::create();
		runOfPoint->setPosition(Point(x - offx, y));
		this->_pointsvec.pushBack(runOfPoint);

		count++;
		point = _objgroup->getObject(std::to_string(count));
	}

	runOfPoint = NULL;
}

//多点触摸
void PlayLayer::multiButtonListener()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
	auto listener = EventListenerTouchAllAtOnce::create();
	this->setSwallowsTouches(true);//新增，是否向下传递触摸
	listener->onTouchesBegan = CC_CALLBACK_2(PlayLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(PlayLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(PlayLayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(PlayLayer::onTouchesCancelled, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void PlayLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	CCLOG("onTouchesBegan");

	if (m_uClickCount++ % 2 != 0)
		return;
	
	//short int iClickCount = 0;   //记录正确点击按钮次数，多余两次则取消此次按键(暂时不实现)
	auto iter = touches.begin();

	for (; iter != touches.end(); iter++) {
		CCTouch * pTouch = (CCTouch *)(*iter);
		Vec2 vec = pTouch->getLocation();	

		for (int i = 0; i < KILL_BUTTON_NUMBER; ++i)
		{
			Circle* pCir = m_pButtonPosition[i];
			bool bCollision = (((vec.x - pCir->vec.x) *(vec.x - pCir->vec.x) + (vec.y - pCir->vec.y) *(vec.y - pCir->vec.y)) <= (pCir->radius * pCir->radius));
			if (bCollision)
			{
				m_oButtons[i]->setOpacity(100);//按下按钮更改透明度				
				m_bKeyPressed[i] = true;
				break;
			}			
		}
	}
	
}


void PlayLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	CCLOG("onTouchesMoved");
}
void PlayLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	CCLOG("onTouchesEnded");
	unsigned int uPressType = 0;
	int iRet = -2;
		
	for (int i = 0; i < KILL_BUTTON_NUMBER; ++i)
	{
		if (m_bKeyPressed[i])
		{
			uPressType = (uPressType | m_eButtonsColor[i]);			
		}
		m_oButtons[i]->setOpacity(255);//按下按钮更改透明度
	}	

	if (uPressType != 0)
	{
		CCLOG("press key = %u", uPressType);

		if (m_uLastPressKey == 0)
		{
			iRet = m_pPatientManager->DeletePatient(uPressType, 0);
			if (iRet == 0)
				m_uLastPressKey = uPressType;
		}
		else
		{
			iRet = m_pPatientManager->DeletePatient(m_uLastPressKey, uPressType);
			m_uLastPressKey = 0;
		}

		/*根据返回值，适当清空当前输入*/
	}


	for (int i = 0; i < KILL_BUTTON_NUMBER; ++i)
	{
		m_bKeyPressed[i] = false;
	}
}
void PlayLayer::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	CCLOG("onTouchesCancelled");
}


void PlayLayer::createButton()
{
	m_strButtonImagePath[0] = "redButton.png";
	m_strButtonImagePath[1] = "greenButton.png";
	m_strButtonImagePath[2] = "blueButton.png";

	m_eButtonsColor[0] = E_BLINK_COLOR_TYPE::RED;
	m_eButtonsColor[1] = E_BLINK_COLOR_TYPE::GREEN;
	m_eButtonsColor[2] = E_BLINK_COLOR_TYPE::Blue;

	for (int i = 0; i < KILL_BUTTON_NUMBER; ++i)
	{
		m_bKeyPressed[i] = false;
	}
	//消除按钮
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint converPoint = CCDirector::sharedDirector()->convertToGL(size);

	for (int i = 0; i < KILL_BUTTON_NUMBER; ++i)
	{
		m_oButtons[i] = CCSprite::create(m_strButtonImagePath[i]);
	}
	m_oButtons[0]->setPosition(ccp(200, size.height / 6));
	m_oButtons[1]->setPosition(ccp(size.width / 2, size.height / 6));
	m_oButtons[2]->setPosition(ccp(size.width - 200, size.height / 6));
	for (int i = 0; i < KILL_BUTTON_NUMBER; ++i)
		CCLOG("button%d x = %f,y = %f", i+1,m_oButtons[i]->getPositionX(), m_oButtons[i]->getPositionY());
		
	this->addChild(m_oButtons[0]);
	this->addChild(m_oButtons[1]);
	this->addChild(m_oButtons[2]);

	m_pButtonPosition[0] = new Circle(CIRCLE_RADIUS, ccp(200, size.height / 6));
	m_pButtonPosition[1] = new Circle(CIRCLE_RADIUS, ccp(size.width / 2, size.height / 6));
	m_pButtonPosition[2] = new Circle(CIRCLE_RADIUS, ccp(size.width - 200, size.height / 6));

}

void PlayLayer::setLabelTTF(CCPoint showPosition, const char* showStr)
{
	CCLabelAtlas *showInfomation = CCLabelAtlas::create(showStr, "nums_font.png", 14, 21, '0');
	this->addChild(showInfomation); 
	showInfomation->setPosition(showPosition);
}
void PlayLayer::setLabelTTF(CCPoint showPosition, int showInt)
{
	char show[128];
	sprintf(show, "show: %d", showInt);
	setLabelTTF(showPosition, show);
}

void PlayLayer::patientFactory(const char * filePath, float whichRoad, unsigned int firstKey, unsigned int secondKey)
{
	CCSprite * patient = CCSprite::create(filePath);	
	patient->setPosition(ccp(930, whichRoad));
	this->addChild(patient, 1);

	//动作
	CCActionInterval * moveBy = CCMoveBy::create(5, ccp(-700, 0));
	CCActionInterval * blink = CCBlink::create(2, 5);
	CCFiniteTimeAction * sequence = CCSequence::create(moveBy, blink, NULL);
	m_pPatientManager->Insert(firstKey, secondKey, patient);
	patient->runAction(sequence);

}

void PlayLayer::zygotePatient(float delta)
{
	patientFactory("redMan.png", winSize.height/2, 1, 1);
	patientFactory("greenMan.png", winSize.height*0.375, 1, 3);
	patientFactory("blueMan.png", winSize.height/4, 3, 4);
}

void PlayLayer::killPatient()
{

}

void PlayLayer::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}