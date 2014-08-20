//#include "cocos-ext.h"
#include "LoginScene.h"



Scene* LoginLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoginLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //登陆界面
	//auto ui = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("startUI_1.ExportJson");
	//this->addChild(ui);
	//Button *startBtn = (Button*)Helper::seekWidgetByTag(ui, 3);
	////为按钮绑定回调函数
	//startBtn->addTouchEventListener(this, toucheventselector(LoginLayer::onClickStartButton));
	//CCLabelTTF * label = CCLabelTTF::create("为选中文字", "MarkerFelt", 25);

	//登陆按钮
	CCMenuItemImage *loginWX = CCMenuItemImage::create("loginWX.png", "loginWX.png", this, menu_selector(LoginLayer::onClickStartButton));
	CCMenuItemImage *loginQQ = CCMenuItemImage::create("loginQQ.png", "loginQQ.png", this, menu_selector(LoginLayer::onClickStartButton));	CCMenuItemImage *menuImage4 = CCMenuItemImage::create("greenButton.png", "greenButton.png", this, menu_selector(LoginLayer::onClickStartButton));
	//loginWX->setPosition(ccp(size.width / 4, size.height / 4));
	//loginQQ->setPosition(ccp(size.width / 4, size.height / 4));
	CCMenu *startMenu = CCMenu::create(loginWX, loginQQ, NULL);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	startMenu->setPosition(ccp(size.width / 2, size.height / 4));
	startMenu->alignItemsHorizontally();
	//startMenu->setOpacity(128);  //设置透明度
	this->addChild(startMenu, 1, 1);

	//【调试】显示屏幕分辨率
	//std::cout << "screen size" << size.width << "," << size.height << " ";
	//char *str1 = (char *)malloc(500);
	//char *str2 = (char *)malloc(500);
	//sprintf(str1, "%f", size.width);
	//sprintf(str2, "%f", size.height);
	//MessageBox(str1, "size.width:");
	//MessageBox(str2, "size.height:");

    return true;
}

void LoginLayer::onClickStartButton(cocos2d::Ref* pSender)
{	
	printf("onClickStartButton Listener ");
	Director::getInstance()->replaceScene(PlayLayer::createScene());
	
}

void LoginLayer::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
