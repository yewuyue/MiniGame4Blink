#pragma once
#include "cocos2d.h"
#include <map>
#include "base\CCVector.h"

USING_NS_CC;

const int ACTION_NUNM = 16;

typedef std::pair<unsigned int, cocos2d::Vector<CCSprite*>*> PatientMapPair;
typedef std::map<unsigned int, cocos2d::Vector<CCSprite*>*> PatientMap;
class CPatientManager
{
private:
	PatientMap				m_patientMap;

	CCLayer *				m_pLayer;

	static CPatientManager* m_pInstace;

	CPatientManager();

public:
	~CPatientManager();

	// 获取本类实例
	static CPatientManager* GetInstance(CCLayer * pLayer);
	
	// 添加精灵
	int Insert(unsigned int eFirstPressKey, unsigned int eSecondPressKey, CCSprite * pPatient);

	/**********************************************************************************************************
	***返回值：-1,0,1
	*** -1 ： 表示没有找到该脑残病人 or 输入无法匹配，需要清空输入
	*** 0  ： 表示可以匹配到，但是还没输入完呢
	*** 1  ： 表示成果的消除了一个
	**********************************************************************************************************/
	int DeletePatient(unsigned int eFirstPressKey, unsigned int eSecondPressKey);
};

