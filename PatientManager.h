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

	// ��ȡ����ʵ��
	static CPatientManager* GetInstance(CCLayer * pLayer);
	
	// ��Ӿ���
	int Insert(unsigned int eFirstPressKey, unsigned int eSecondPressKey, CCSprite * pPatient);

	/**********************************************************************************************************
	***����ֵ��-1,0,1
	*** -1 �� ��ʾû���ҵ����Բв��� or �����޷�ƥ�䣬��Ҫ�������
	*** 0  �� ��ʾ����ƥ�䵽�����ǻ�û��������
	*** 1  �� ��ʾ�ɹ���������һ��
	**********************************************************************************************************/
	int DeletePatient(unsigned int eFirstPressKey, unsigned int eSecondPressKey);
};

